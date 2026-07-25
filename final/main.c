/*
cd final
gcc main.c -o main.exe -lgdi32 -lmsimg32
start conhost main.exe

*/

// 0 22 45 90 135 157 179

#include "main.h"

void ScreenBar();
void BottomBar(int guardCard, int money);
void ScreenBarButton(int button1, int button2);
void EnforceButton(int button1);

void StartView();
void MainView();
void DestroyedView();
void EquipmentView();
void ShopView();
void ForgeView();
void EtcView();

int level = 0;
int consoleWidth = 180 + 1;
int consoleHeight = 50 + 1;
char view[30];

int main(void)
{
    SetConsoleOutputCP(65001); // 인코딩 UTF-8 고정

    SetConsoleSize(consoleWidth, consoleHeight); // x, y

    SetColor(15, 0);
    Clear();

    // StartView();
    DestroyedView();
}

void ScreenBar()
{
    PrintCenter("------------------------------------------------------------------------------------------------------"
                "------------------------------------------------------------------------",
                1, consoleWidth);
    PrintCenter("-----------------", 5, consoleWidth);
    PrintCenter("    검 강화하기    ", 6, consoleWidth);
    PrintCenter("-----------------", 7, consoleWidth);
    PrintCenter(view, 9, consoleWidth);
    PrintCenter("------------------------------------------------------------------------------------------------------"
                "------------------------------------------------------------------------",
                48, consoleWidth);
    if (level == 1)
        PrintText("easy", 110, 6);
    else if (level == 2)
        PrintText("hard", 110, 6);
}

void BottomBar(int guardCard, int money)
{
    char temp[100];

    snprintf(temp, sizeof(temp), "방지권: %d", 0);
    PrintTextLeft(temp, 2, 44);
    snprintf(temp, sizeof(temp), "%d 원", 1000000);
    PrintTextRight(temp, 175, 46);
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
}

void StartView()
{
    snprintf(view, sizeof(view), " ");
    ScreenBar();
    PrintText("  easy  ", 60, 24);
    PrintText("  hard  ", 120, 24);

    PrintCenter("<- -> 방향키로 난이도 지정 후 엔터", 35, consoleWidth);
    PrintCenter("난이도 지정 후 인게임에서 마우스로 조작", 38, consoleWidth);

    while (1)
    {

        if (GetAsyncKeyState(VK_LEFT) & 0x8000) // 비트 연산
        {
            PrintText("[  easy  ]", 60, 24);
            PrintText("   hard   ", 120, 24);
            level = 1;
        }

        if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            PrintText("   easy   ", 60, 24);
            PrintText("[  hard  ]", 120, 24);
            level = 2;
        }
        if (GetAsyncKeyState(VK_RETURN) & 0x8000)
        {
            switch (level)
            {
            case 1:
                MainView();
                break;

            case 2:
                MainView();
                break;

            default:
                break;
            }
        }
        Sleep(20);
    }
}

void DestroyedView()
{
    snprintf(view, sizeof(view), " ");
    Clear();
    ScreenBar();
    PrintText("[ 살리기 ]", 157, 9);

    char temp[50];
    int isUpdate = 1, y = 30;

    PrintTextLeft("방지권으로 살리기 버튼을 눌러 살릴 수 있습니다.", 10, 9);
    snprintf(temp, sizeof(temp), "%s: 방지권 %d개 소모", "마력의 검", 1);
    PrintTextLeft(temp, 10, 11);

    PrintTextLeft(
        " ████ █   █  ███  ████  ████     █   █  ███   ████    ████  █████  ████ █████ ████   ███  █   █ █████ ████  ",
        10, y);
    PrintTextLeft(
        "█     █   █ █   █ █   █ █   █    █   █ █   █ █        █   █ █     █       █   █   █ █   █  █ █  █     █   █ ",
        10, y + 1);
    PrintTextLeft(
        " ███  █ █ █ █   █ ████  █   █    █ █ █ █████  ███     █   █ ████   ███    █   ████  █   █   █   ████  █   █ ",
        10, y + 2);
    PrintTextLeft(
        "    █ ██ ██ █   █ █  █  █   █    ██ ██ █   █     █    █   █ █         █   █   █  █  █   █   █   █     █   █ ",
        10, y + 3);
    PrintTextLeft(
        "████  █   █  ███  █   █ ████     █   █ █   █ ████     ████  █████ ████    █   █   █  ███    █   █████ ████  ",
        10, y + 4);

    while (1)
    {
        if (isUpdate)
        {
            BottomBar(0, 0);
            snprintf(temp, sizeof(temp), "%s %3d 개 줍기", "국적불분명 철조각", 1);
            PrintTextLeft(temp, 10, 17);
            isUpdate = 0;
        }
        ScreenBarButton(0, 1);
        EnforceButton(1);

        Sleep(30);
    }
}

void MainView()
{
    snprintf(view, sizeof(view), " ");
    Clear();
    ScreenBar();
    PrintText("[ 아이템 창 ]", 22, 9);
    PrintText("[ 상  점 ]", 157, 9);

    char temp[100];

    int isUpdate = 1;

    while (1)
    {
        if (isUpdate)
        {
            snprintf(temp, sizeof(temp), "강화비용: %d원", 300);
            PrintTextLeft(temp, 2, 15);
            snprintf(temp, sizeof(temp), "판매가격: %d원", 1000000000);
            PrintTextLeft(temp, 2, 17);

            snprintf(temp, sizeof(temp), "+%d %s", 0, "낡은 단검");
            PrintCenter(temp, 40, consoleWidth);
            snprintf(temp, sizeof(temp), "성공률 %d %%", 100);
            PrintCenter(temp, 42, consoleWidth);

            BottomBar(0, 0);

            isUpdate = 0;
        }

        ScreenBarButton(1, 1);
        EnforceButton(1);
        DrawImage("asset/sword_0.bmp", 90, 23, 600, 350);

        Sleep(30);
    }
}

void EquipmentView()
{
    snprintf(view, sizeof(view), "Equipment");
    Clear();
    PrintText("[ 나가기 ]", 157, 9);

    int isUpdate = 1, x = 10;
    char temp[30];

    ScreenBar();

    for (int i = 0; i < 11; i++)
    {
        snprintf(temp, sizeof(temp), "%s: %d", "국적불분명 철조각", 0);
        PrintTextLeft(temp, x, 11 + 3 * i);
    }

    while (1)
    {
        if (isUpdate)
        {
            BottomBar(0, 0);
            isUpdate = 0;
        }
        ScreenBarButton(0, 1);
        Sleep(30);
    }
}

void ShopView()
{
    snprintf(view, sizeof(view), "Welcome to shop");
    Clear();
    int isUpdate = 1;
    char temp[100];

    ScreenBar();
    PrintTextLeft("Tip: 돈을 다 쓰시면 강화 비용을 지불할 수 없게 됩니다.", 7, 7);
    PrintText("[ 나가기 ]", 157, 9);

    int x = 15;
    for (int i = 0; i < 6; i++)
    {
        snprintf(temp, sizeof(temp), "%s", "+9강 워프권");
        PrintTextLeft(temp, x, 15 + 5 * i);
        snprintf(temp, sizeof(temp), "%d원", 1000000);
        PrintCenter(temp, 15 + 5 * i, consoleWidth);
    }

    while (1)
    {
        if (isUpdate)
        {
            BottomBar(0, 0);
            isUpdate = 0;
        }
        ScreenBarButton(0, 1);

        for (int i = 0; i < 6; i++)
        {
            DrawImage("asset/item.bmp", 10, 15 + 5 * i, 40, 40);
            DrawImage("asset/button.bmp", 157, 15 + 5 * i, 40, 40);
        }

        Sleep(30);
    }
}

void ForgeView()
{
    snprintf(view, sizeof(view), "Forge");
    Clear();
    int isUpdate = 1;
    char temp[100];

    ScreenBar();
    PrintText("[ 잡템 창 ]", 22, 9);
    PrintText("[ 나가기 ]", 157, 9);

    int x = 10;
    for (int i = 0; i < 9; i++)
    {
        snprintf(temp, sizeof(temp), "%s %d개 -> %s %d개", "국적불분명 철조각", 5, "깨짐 방지권", 1);
        PrintTextLeft(temp, x, 15 + 3 * i);
    }

    while (1)
    {
        if (isUpdate)
        {
            BottomBar(0, 0);
            isUpdate = 0;
        }
        ScreenBarButton(1, 1);
        for (int i = 0; i < 9; i++)
        {
            DrawImage("asset/button.bmp", 157, 15 + 3 * i, 40, 40);
        }

        Sleep(30);
    }
}

void EtcView()
{
    snprintf(view, sizeof(view), "etc.");
    Clear();
    PrintText("[ 나가기 ]", 157, 9);

    int isUpdate = 1, x = 10;
    char temp[30];

    ScreenBar();

    for (int i = 0; i < 8; i++)
    {
        snprintf(temp, sizeof(temp), "%s: %d", "국적불분명 철조각", 0);
        PrintTextLeft(temp, x, 15 + 3 * i);
    }

    while (1)
    {
        if (isUpdate)
        {
            BottomBar(0, 0);
            isUpdate = 0;
        }
        ScreenBarButton(0, 1);
        Sleep(30);
    }
}
