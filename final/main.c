/*
gcc main.c -o app.exe -lgdi32 -luser32
app.exe
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_SWORDS 30

// 1. 각 검의 이미지 정보를 담을 구조체 정의
typedef struct
{
    BITMAPINFOHEADER bih;
    unsigned char *pixelData;
    int isLoaded;
} BMPImage;

// 30개의 검 이미지를 저장할 배열
BMPImage g_swords[MAX_SWORDS];
int g_currentSwordIndex = 0; // 현재 화면에 띄울 검 번호 (0 ~ 29)

// BMP 파일 로드 함수 (구조체로 저장하도록 변경)
int load_bmp(const char *filename, BMPImage *outImg)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp)
    {
        printf("[오류] 파일 열기 실패: %s\n", filename);
        outImg->isLoaded = 0;
        return 0;
    }

    BITMAPFILEHEADER bfh;
    fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fp);
    fread(&outImg->bih, sizeof(BITMAPINFOHEADER), 1, fp);

    if (bfh.bfType != 0x4D42)
    { // 'BM' 마크 확인
        printf("[오류] 올바른 BMP 포맷이 아닙니다: %s\n", filename);
        fclose(fp);
        outImg->isLoaded = 0;
        return 0;
    }

    int imgWidth = outImg->bih.biWidth;
    int imgHeight = abs(outImg->bih.biHeight);
    int bpp = outImg->bih.biBitCount;

    int rowSize = ((imgWidth * bpp + 31) / 32) * 4;
    int imageSize = rowSize * imgHeight;

    outImg->pixelData = (unsigned char *)malloc(imageSize);
    if (!outImg->pixelData)
    {
        fclose(fp);
        outImg->isLoaded = 0;
        return 0;
    }

    fseek(fp, bfh.bfOffBits, SEEK_SET);
    fread(outImg->pixelData, 1, imageSize, fp);
    fclose(fp);

    // ★ [수정] 32bit BMP 투명 배경 보정
    if (bpp == 32)
    {
        for (int i = 0; i < imageSize; i += 4)
        {
            unsigned char alpha = outImg->pixelData[i + 3];

            // 알파(투명도)가 0인 투명 영역은 완전한 불투명 흰색(255)으로 변경
            if (alpha == 0)
            {
                outImg->pixelData[i] = 255;     // Blue
                outImg->pixelData[i + 1] = 255; // Green
                outImg->pixelData[i + 2] = 255; // Red
                outImg->pixelData[i + 3] = 255; // ★ Alpha도 255(불투명)로 설정해야 보임!
            }
        }
    }

    outImg->isLoaded = 1;
    printf("[성공] 로드 완료: %s\n", filename);
    return 1;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // 현재 선택된 검 이미지 가져오기
        BMPImage *curImg = &g_swords[g_currentSwordIndex];

        if (curImg->isLoaded && curImg->pixelData != NULL)
        {
            BITMAPINFO bmi;
            ZeroMemory(&bmi, sizeof(BITMAPINFO));

            bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            bmi.bmiHeader.biWidth = curImg->bih.biWidth;
            bmi.bmiHeader.biHeight = curImg->bih.biHeight;
            bmi.bmiHeader.biPlanes = 1;
            bmi.bmiHeader.biBitCount = curImg->bih.biBitCount;
            bmi.bmiHeader.biCompression = BI_RGB;

            SetDIBitsToDevice(hdc, 10, 10, curImg->bih.biWidth, abs(curImg->bih.biHeight), 0, 0, 0,
                              abs(curImg->bih.biHeight), curImg->pixelData, &bmi, DIB_RGB_COLORS);
        }

        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
        // 프로그램 종료 시 모든 메모리 해제
        for (int i = 0; i < MAX_SWORDS; i++)
        {
            if (g_swords[i].pixelData)
            {
                free(g_swords[i].pixelData);
            }
        }
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int main()
{
    // 30개 검 이미지 반복문으로 로드
    char filePath[256];
    for (int i = 0; i < MAX_SWORDS; i++)
    {
        sprintf(filePath, "asset/sword_%d.bmp", i);
        load_bmp(filePath, &g_swords[i]);
    }

    HINSTANCE hInstance = GetModuleHandle(NULL);
    const char g_szClassName[] = "MyBMPWindowClass";

    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = g_szClassName;

    RegisterClassEx(&wc);

    HWND hwnd = CreateWindowExA(WS_EX_CLIENTEDGE, g_szClassName, "검 강화하기 - 테스트", WS_OVERLAPPEDWINDOW,
                                CW_USEDEFAULT, CW_USEDEFAULT, 900, 1000, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG Msg;
    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}