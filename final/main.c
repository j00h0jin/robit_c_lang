/*
cd final
gcc main.c -o main.exe
start conhost main.exe

*/

#include "main.h"

void ScreenBar(int consoleWidth);

void StartView(int consoleWidth);

int main(void)
{
    SetConsoleOutputCP(65001); // 인코딩 UTF-8 고정

    int consoleWidth = 180;
    int consoleHeight = 50;
    SetConsoleSize(consoleWidth, consoleHeight); // x, y

    SetColor(15, 0);
    Clear();

    StartView(consoleWidth);

    return 0;
}

void ScreenBar(int consoleWidth)
{
    PrintCenter("------------------------------------------------------------------------------------------------------"
                "------------------------------------------------------------------------",
                1, consoleWidth);
    PrintCenter("-----------------", 5, consoleWidth);
    PrintCenter("    검 강화하기    ", 6, consoleWidth);
    PrintCenter("-----------------", 7, consoleWidth);
    PrintCenter("------------------------------------------------------------------------------------------------------"
                "------------------------------------------------------------------------",
                48, consoleWidth);
}

void StartView(int consoleWidth)
{
    ScreenBar(consoleWidth);
    PrintText("  easy  ", 60 - 1, 24);
    PrintText("  hard  ", 120 - 1, 24);

    PrintCenter("<- -> 방향키로 난이도 지정 후 엔터", 35, consoleWidth);
    PrintCenter("난이도 지정 후 인게임에서 마우스로 조작", 37, consoleWidth);

    int state = 0;

    while (1)
    {

        if (GetAsyncKeyState(VK_LEFT) & 0x8000) // 비트 연산
        {
            PrintText("[  easy  ]", 60 - 1, 24);
            PrintText("   hard   ", 120 - 1, 24);
            state = 1;
        }

        if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            PrintText("   easy   ", 60 - 1, 24);
            PrintText("[  hard  ]", 120 - 1, 24);
            state = 2;
        }
        if (GetAsyncKeyState(VK_RETURN) & 0x8000)
        {
            switch (state)
            {
            case 0:
                break;

            case 1:
                PrintText("   easy 모드 입장  ", 60 - 1, 27);
                break;

            case 2:
                PrintText("   hard 모드 입장   ", 120 - 1, 27);
                break;

            default:
                break;
            }
        }
        Sleep(20);
    }
}