#include <stdio.h>
#include <windows.h>

void GotoXY(int _x, int _y)
{

    COORD pos = {_x, _y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

COORD GetXY(void)
{

    COORD pos;
    CONSOLE_SCREEN_BUFFER_INFO curInfor;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfor);
    pos.X = curInfor.dwCursorPosition.X;
    pos.Y = curInfor.dwCursorPosition.Y;

    return pos;
}

void Clear(void)
{
    system("cls");
}

void SetTitle(char *_szConsoleName)
{
    SetConsoleTitle(_szConsoleName);
}

void SetColor(unsigned char _BgColor, unsigned char _TextColor)
{
    if (_BgColor > 15 || _TextColor > 15)
        return;

    unsigned short ColorNum = (_BgColor << 4) | _TextColor;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ColorNum);
}

void MySetCursor(BOOL _bShow)
{

    CONSOLE_CURSOR_INFO curInfor;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfor);

    curInfor.bVisible = _bShow;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfor);
}

void SetConsoleSize(int _col, int _lines)
{
    char setText[100];
    snprintf(setText, sizeof(setText), "mode con cols=%d lines=%d", _col, _lines);
    system(setText);
}

// 문자열 칸 수 구하기
int GetDisplayWidth(const char *str)
{
    int width = 0;
    unsigned char *p = (unsigned char *)str;

    while (*p)
    {
        if (*p < 0x80)
        {
            width += 1; // 영문, 숫자, 특수문자 = 1칸
            p += 1;
        }
        else if ((*p & 0xE0) == 0xC0)
        {
            width += 2; // 2바이트 UTF-8 = 2칸
            p += 2;
        }
        else if ((*p & 0xF0) == 0xE0)
        {
            width += 2; // 3바이트 UTF-8 (한글) = 2칸
            p += 3;
        }
        else
        {
            width += 2;
            p += 4;
        }
    }
    return width;
}

// 출력(x좌표가 중앙)
void PrintText(const char *text, int x, int y)
{
    int textWidth = GetDisplayWidth(text);
    int _x = x - (textWidth / 2);

    if (x < 0)
        _x = 0; // 예외 처리

    GotoXY(_x, y);
    printf("%s", text);
}

// 출력(x좌표부터)
void PrintTextLeft(const char *text, int x, int y)
{
    int _x = x;

    if (x < 0)
        _x = 0; // 예외 처리

    GotoXY(_x, y);
    printf("%s", text);
}

// 출력(x좌표까지)
void PrintTextRight(const char *text, int x, int y)
{
    int textWidth = GetDisplayWidth(text);
    int startX = x - textWidth; // x좌표에서 텍스트 너비만큼 빼줌

    if (startX < 0)
        startX = 0; // 예외 처리

    GotoXY(startX, y);
    printf("%s", text);
}

// 가운데 정렬 출력
void PrintCenter(const char *text, int y, int consoleWidth)
{
    int textWidth = GetDisplayWidth(text);
    int x = (consoleWidth - textWidth) / 2;

    if (x < 0)
        x = 0; // 예외 처리

    GotoXY(x, y);
    printf("%s", text);
}

// 이미지 출력(좌표 중앙값)
void DrawImage(const char *imagePath, int x, int y, int maxWidth, int maxHeight)
{
    HWND hwnd = GetConsoleWindow();
    if (hwnd == NULL)
        return;

    HDC hdc = GetDC(hwnd);

    HBITMAP hBitmap = (HBITMAP)LoadImageA(NULL, imagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    if (hBitmap == NULL)
    {
        ReleaseDC(hwnd, hdc);
        return;
    }

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);

    BITMAP bm;
    GetObject(hBitmap, sizeof(BITMAP), &bm);

    int targetWidth = maxWidth;
    int targetHeight = maxHeight;

    // 원본의 비율을 지키면서 박스 안에서 최대 크기로 설정함
    if (bm.bmWidth * maxHeight > bm.bmHeight * maxWidth)
    {
        targetWidth = maxWidth;
        targetHeight = (bm.bmHeight * maxWidth) / bm.bmWidth;
    }
    else
    {
        targetHeight = maxHeight;
        targetWidth = (bm.bmWidth * maxHeight) / bm.bmHeight;
    }

    // 이미지 픽셀 -> 좌표화
    int pixelX = x * 8;
    int pixelY = y * 16;

    int drawX = pixelX - (targetWidth / 2);
    int drawY = pixelY - (targetHeight / 2);

    TransparentBlt(hdc, drawX, drawY,                                       // 위치
                   targetWidth, targetHeight,                               // 비율 유지된 최종 크기
                   memDC, 0, 0, bm.bmWidth, bm.bmHeight, RGB(255, 255, 255) // transparent color (흰색 지정)
    );

    SelectObject(memDC, hOldBitmap);
    DeleteDC(memDC);
    DeleteObject(hBitmap);
    ReleaseDC(hwnd, hdc);
}
