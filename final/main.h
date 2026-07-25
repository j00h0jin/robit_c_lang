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
    int textWidth = GetDisplayWidth(text); // 한글/영문 실제 출력 너비 계산
    int startX = x - textWidth;            // 끝점(anchorX)에서 너비만큼 왼쪽으로 시작점 이동

    if (startX < 0)
        startX = 0; // 예외 처리 (화면 좌측 이탈 방지)

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
