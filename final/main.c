/*
cd final
gcc main.c -o main.exe -lgdi32 -lmsimg32
start conhost main.exe

*/

// 0 22 45 90 135 157 179

#include "main.h"

void ScreenBar(int consoleWidth);
void ScreenBarButton(int button1, int button2);
void EnforceButton(int button1);

void StartView(int consoleWidth);
void MainView(int consoleWidth);

int main(void)
{
    SetConsoleOutputCP(65001); // 인코딩 UTF-8 고정

    int consoleWidth = 180 + 1;
    int consoleHeight = 50 + 1;
    SetConsoleSize(consoleWidth, consoleHeight); // x, y

    SetColor(15, 0);
    Clear();

    StartView(consoleWidth);
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

void ScreenBarButton(int button1, int button2)
{
    if (button1)
        DrawImage("asset/button.bmp", 22, 6, 75, 75);

    if (button2)
        DrawImage("asset/button.bmp", 157, 6, 75, 75);
}

void EnforceButton(int button)
{
    if (button)
        DrawImage("asset/button.bmp", 152, 24, 150, 150);
    // PrintText("[ BUTTON ]", 157, 24);
}

void StartView(int consoleWidth)
{
    ScreenBar(consoleWidth);
    PrintText("  easy  ", 60, 24);
    PrintText("  hard  ", 120, 24);

    PrintCenter("<- -> 방향키로 난이도 지정 후 엔터", 35, consoleWidth);
    PrintCenter("난이도 지정 후 인게임에서 마우스로 조작", 38, consoleWidth);

    int state = 0;

    while (1)
    {

        if (GetAsyncKeyState(VK_LEFT) & 0x8000) // 비트 연산
        {
            PrintText("[  easy  ]", 60, 24);
            PrintText("   hard   ", 120, 24);
            state = 1;
        }

        if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            PrintText("   easy   ", 60, 24);
            PrintText("[  hard  ]", 120, 24);
            state = 2;
        }
        if (GetAsyncKeyState(VK_RETURN) & 0x8000)
        {
            switch (state)
            {
            case 0:
                break;

            case 1:
                MainView(consoleWidth);
                break;

            case 2:
                MainView(consoleWidth);
                break;

            default:
                break;
            }
        }
        Sleep(20);
    }
}

void MainView(int consoleWidth)
{
    Clear();
    ScreenBar(consoleWidth);

    char temp[100];

    int isUpdate = 1;

    while (1)
    {
        if (isUpdate)
        {
            PrintText("[ 아이템 창 ]", 22, 9);
            PrintText("[ 상  점 ]", 157, 9);

            snprintf(temp, sizeof(temp), "강화비용: %d원", 300);
            PrintTextLeft(temp, 2, 15);
            snprintf(temp, sizeof(temp), "판매가격: %d원", 1000000000);
            PrintTextLeft(temp, 2, 17);

            snprintf(temp, sizeof(temp), "+%d %s", 0, "낡은 단검");
            PrintCenter(temp, 40, consoleWidth);
            snprintf(temp, sizeof(temp), "성공률 %d %%", 100);
            PrintCenter(temp, 42, consoleWidth);

            snprintf(temp, sizeof(temp), "방지권: %d", 0);
            PrintTextLeft(temp, 2, 44);
            snprintf(temp, sizeof(temp), "%d 원", 1000000);
            PrintTextRight(temp, 175, 46);
            isUpdate = 0;
        }

        ScreenBarButton(1, 1);
        EnforceButton(1);
        DrawImage("asset/sword_0.bmp", 90, 23, 600, 350);

        Sleep(30);
    }
}