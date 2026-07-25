/*
gcc main.c -o app.exe -lgdi32
app.exe
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

BITMAPFILEHEADER bfh;
BITMAPINFOHEADER bih;
unsigned char *pixelData = NULL;

int load_bmp(const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp)
        return 0;

    fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fp);
    fread(&bih, sizeof(BITMAPINFOHEADER), 1, fp);

    if (bfh.bfType != 0x4D42)
    { // 'BM' 마크 확인
        fclose(fp);
        return 0;
    }

    int imgWidth = bih.biWidth;
    int imgHeight = abs(bih.biHeight);
    int bpp = bih.biBitCount;

    int rowSize = ((imgWidth * bpp + 31) / 32) * 4;
    int imageSize = rowSize * imgHeight;

    pixelData = (unsigned char *)malloc(imageSize);
    if (!pixelData)
    {
        fclose(fp);
        return 0;
    }

    fseek(fp, bfh.bfOffBits, SEEK_SET);
    fread(pixelData, 1, imageSize, fp);
    fclose(fp);

    // ★ [핵심] 32bit BMP의 투명 배경(Alpha = 0)을 흰색(255)으로 보정 ★
    if (bpp == 32)
    {
        for (int i = 0; i < imageSize; i += 4)
        {
            unsigned char alpha = pixelData[i + 3];

            // 알파(투명도)가 0인 투명 배경은 흰색으로 칠함
            if (alpha == 0)
            {
                pixelData[i] = 255;     // Blue
                pixelData[i + 1] = 255; // Green
                pixelData[i + 2] = 255; // Red
            }
        }
    }

    return 1;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        if (pixelData != NULL)
        {
            BITMAPINFO bmi;
            ZeroMemory(&bmi, sizeof(BITMAPINFO));

            bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            bmi.bmiHeader.biWidth = bih.biWidth;
            bmi.bmiHeader.biHeight = bih.biHeight;
            bmi.bmiHeader.biPlanes = 1;
            bmi.bmiHeader.biBitCount = bih.biBitCount;
            bmi.bmiHeader.biCompression = BI_RGB;

            SetDIBitsToDevice(hdc, 10, 10, bih.biWidth, abs(bih.biHeight), 0, 0, 0, abs(bih.biHeight), pixelData, &bmi,
                              DIB_RGB_COLORS);
        }

        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
        if (pixelData)
            free(pixelData);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int main()
{
    HINSTANCE hInstance = GetModuleHandle(NULL);

    if (!load_bmp("asset/test.bmp"))
    {
        printf("[오류] test.bmp 읽기 실패!\n");
        system("pause");
        return 0;
    }

    const char g_szClassName[] = "MyBMPWindowClass";
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = g_szClassName;

    RegisterClassEx(&wc);

    // 이미지 해상도(846x896)에 맞춰 창 크기도 넉넉하게 설정 (900x1000)
    HWND hwnd = CreateWindowExA(WS_EX_CLIENTEDGE, g_szClassName, "검 강화하기", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                                CW_USEDEFAULT, 900, 1000, NULL, NULL, hInstance, NULL);

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