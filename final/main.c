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
    // 콘솔 제목 설정
    SetTitle();

    SetConsoleOutputCP(65001); // 인코딩 UTF-8 고정

    // QuickEdit 모드 비활성화
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    if (hIn != INVALID_HANDLE_VALUE)
    {
        DWORD mode;
        if (GetConsoleMode(hIn, &mode))
        {
            mode |= ENABLE_EXTENDED_FLAGS;
            mode &= ~ENABLE_QUICK_EDIT_MODE;
            SetConsoleMode(hIn, mode);
        }
        FlushConsoleInputBuffer(hIn);
    }

    SetConsoleSize(consoleWidth, consoleHeight); // x, y

    SetColor(15, 0); // 배경 흰색, 글자 검정색
    Clear();         // 배경과 글자를 지정한 뒤 Clear 해줘야 함

    // StartView는 한 번만 표시하므로 스택에 넣지 않음
    StartView();

    // 나머지 뷰는 스택으로 관리
    while (IsViewStackEmpty() != 1) // 스택이 비어있지 않으면
    {
        void (*cur)(void) = TopView(); // 스택의 top view를 cur에 저장

        cur(); // cur 보여줌
    }
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
    Clear();
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
                PushView(MainView);
                return;
            case 2:
                PushView(MainView);
                return;

            default:
                break;
            }
        }
        Sleep(20);
    }
}

void MainView()
{
    snprintf(view, sizeof(view), " ");
    Clear();
    ScreenBar();
    PrintText("[ 조합소 ]", 22, 9);
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
        ScreenBarButton(1, 1);
        EnforceButton(1);
        DrawImage("asset/sword_0.bmp", 90, 23, 600, 350);

        BOOL clicked = MouseLeftButtonClicked();
        if (clicked && IsMouseClickOnImage(157, 6, 75, 75))
        {
            PushView(ShopView);
            return;
        }
        if (clicked && IsMouseClickOnImage(22, 6, 75, 75))
        {
            PushView(ForgeView);
            return;
        }

        Sleep(30);
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

        // 우측 상단(나가기) 버튼 클릭 시 현재 뷰 팝
        BOOL clicked = MouseLeftButtonClicked();
        if (clicked && IsMouseClickOnImage(157, 6, 75, 75))
        {
            PopView();
            return;
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

        BOOL clicked = MouseLeftButtonClicked();

        // 좌측 상단 버튼 클릭 시 EtcView로 이동
        if (clicked && IsMouseClickOnImage(22, 6, 75, 75))
        {
            PushView(EtcView);
            return;
        }

        // 우측 상단(나가기) 버튼 클릭 시 현재 뷰 팝
        if (clicked && IsMouseClickOnImage(157, 6, 75, 75))
        {
            PopView();
            return;
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

        // 우측 상단(나가기) 버튼 클릭 시 현재 뷰 팝
        BOOL clicked = MouseLeftButtonClicked();
        if (clicked && IsMouseClickOnImage(157, 6, 75, 75))
        {
            PopView();
            return;
        }
        Sleep(30);
    }
}
