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
void ShopView();
void ForgeView();
void EtcView();

int level = 0;
int consoleWidth = 180 + 1;
int consoleHeight = 50 + 1;
char view[30];

int enhanceItemCount = 0;
int currentEnhanceIndex = 0;

int LoadHardCsv(char *path)
{
    FILE *fp = fopen(path, "r");
    if (!fp)
        return 0;

    char line[200];
    if (!fgets(line, sizeof(line), fp))
    {
        fclose(fp);
        return 0;
    }

    int count = 0;
    while (fgets(line, sizeof(line), fp) && count < MAX_ENHANCE_ITEMS)
    {
        char *fields[7];
        ParseCsvFields(line, fields, 7);

        if (fields[0] == NULL || fields[0][0] == '\0')
            continue;

        EnhanceItem *item = &enhanceItems[count];
        item->step = ParseNumber(fields[0]);

        if (fields[1])
        {
            TrimQuotes(fields[1]);
            strncpy(item->name, fields[1], sizeof(item->name) - 1);
            item->name[sizeof(item->name) - 1] = '\0';
        }
        else
        {
            item->name[0] = '\0';
        }

        item->cost = fields[2] ? ParseNumber(fields[2]) : 0;
        item->successRate = fields[3] ? ParsePercent(fields[3]) : 0;
        item->price = fields[4] ? ParseNumber(fields[4]) : 0;
        if (fields[5])
        {
            TrimQuotes(fields[5]);
            if (strstr(fields[5], "방지권불가") != NULL)
                item->guardCost = -1;
            else
                item->guardCost = ParseNumber(fields[5]);
        }
        else
        {
            item->guardCost = 0;
        }

        if (fields[6])
        {
            TrimQuotes(fields[6]);
            strncpy(item->dropItem, fields[6], sizeof(item->dropItem) - 1);
            item->dropItem[sizeof(item->dropItem) - 1] = '\0';
            if (strcmp(item->dropItem, "-") == 0)
                item->dropItem[0] = '\0';
        }
        else
        {
            item->dropItem[0] = '\0';
        }

        count++;
    }

    fclose(fp);
    enhanceItemCount = count;
    return 1;
}

int LoadEasyPercent(char *path)
{
    FILE *fp = fopen(path, "r");
    if (!fp)
        return 0;

    char line[200];
    if (!fgets(line, sizeof(line), fp))
    {
        fclose(fp);
        return 0;
    }

    int idx = 0;
    while (fgets(line, sizeof(line), fp) && idx < enhanceItemCount)
    {
        char *fields[1];
        ParseCsvFields(line, fields, 1);
        if (fields[0] && fields[0][0] != '\0')
        {
            int percent = ParsePercent(fields[0]);
            if (percent > 0)
                enhanceItems[idx].successRate = percent;
        }
        idx++;
    }

    fclose(fp);
    return 1;
}

void LoadEnhanceData(int mode)
{
    if (!LoadHardCsv("csv/hard.csv"))
        return;

    if (mode == 1)
        LoadEasyPercent("csv/easy_percent.csv");
}

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

    srand((unsigned)time(NULL)); // 난수 생성(현재 시간 시드를 기준으로)
    SetColor(15, 0);             // 배경 흰색, 글자 검정색
    MySetCursor(FALSE);          // 콘솔 커서 끄기
    Clear();                     // 배경과 글자를 지정한 뒤 Clear 해줘야 함

    // StartView는 한 번만 표시하므로 스택에 넣지 않음
    StartView();

    // StartView에서 난이도 선택 후 csv 로드함
    LoadEnhanceData(level);

    // 나머지 뷰는 스택으로 관리
    while (IsViewStackEmpty() != 1) // 스택이 비어있지 않으면
    {
        void (*cur)(void) = TopView(); // 스택의 top view를 cur에 저장

        cur(); // cur 보여줌
    }
}

// 제목 + 현재 페이지 이름 + 최상하단 '-' + 난이도 출력
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

// 방지권 개수와 돈 출력
void BottomBar(int guardCard, int money)
{
    char temp[100];

    snprintf(temp, sizeof(temp), "방지권: %d", guardCard);
    PrintTextLeft(temp, 2, 44);
    snprintf(temp, sizeof(temp), "%d 원", money);
    PrintTextRight(temp, 175, 46);
}

// 상단 양쪽 버튼 2개 출력
void ScreenBarButton(int button1, int button2)
{
    if (button1)
        DrawImage("asset/button.bmp", 22, 6, 75, 75);

    if (button2)
        DrawImage("asset/button.bmp", 157, 6, 75, 75);
}

// 우측 중앙 버튼 출력(강화 버튼 자리)
void EnforceButton(int button)
{
    if (button)
        DrawImage("asset/button.bmp", 152, 24, 150, 150);
}

// 시작 화면
void StartView()
{
    snprintf(view, sizeof(view), "start menu");
    Clear();
    ScreenBar();
    PrintText("  easy  ", 60, 24);
    PrintText("  hard  ", 120, 24);

    PrintCenter("<- -> 방향키로 난이도 지정 후 엔터", 35, consoleWidth);
    PrintCenter("난이도 지정 후 인게임에서 마우스로 조작", 38, consoleWidth);

    while (1)
    {
        // 0x8000 이전에 누른 적이 없고 호출 시점에서 눌린 상태
        // 0x8001 이전에 누른 적이 있고 호출 시점에서 눌린 상태
        // 위 두 리턴값을 둘 다 만족시키는 조건을 간단하게 비트 연산으로 표현
        // https://www.youtube.com/watch?v=lKQbupTlXTU (10:00)
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
            case 1: // easy
                PushView(MainView);
                return;
            case 2: // hard
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
    // 현재 페이지
    snprintf(view, sizeof(view), "main");

    // 가변 텍스트를 출력하기 위한 임시 문자열
    char temp[100];
    // 페이지가 바뀌면 isUpdate는 항상 1 (모든 페이지)
    int isUpdate = 1;

    while (1)
    {
        if (isUpdate)
        {
            Clear();
            ScreenBar();

            if (currentEnhanceIndex == 0)
            {

                PrintText("[ 조합소 ]", 22, 9);
                PrintText("[ 상  점 ]", 157, 9);
            }
            else
            {

                PrintText("[ 판매 ]", 157, 9);
            }

            EnhanceItem *item = &enhanceItems[currentEnhanceIndex];
            snprintf(temp, sizeof(temp), "강화비용: %d원", item->cost);
            PrintTextLeft(temp, 2, 15);
            snprintf(temp, sizeof(temp), "판매가격: %d원", item->price);
            PrintTextLeft(temp, 2, 17);

            snprintf(temp, sizeof(temp), "+%d %s", item->step, item->name);
            PrintCenter(temp, 40, consoleWidth);
            snprintf(temp, sizeof(temp), "성공률 %d %%", item->successRate);
            PrintCenter(temp, 42, consoleWidth);

            BottomBar(playerInfo.guard, playerInfo.money);

            isUpdate = 0;
        }
        if (currentEnhanceIndex == 0)
        {
            ScreenBarButton(1, 1);
        }
        else
        {
            ScreenBarButton(0, 1);
        }
        char imagePath[100];
        snprintf(imagePath, sizeof(imagePath), "asset/sword_%d.bmp", currentEnhanceIndex);
        DrawImage(imagePath, 90, 23, 600, 350);
        EnforceButton(1);

        BOOL clicked = MouseLeftButtonClicked();
        if (clicked && IsMouseClickOnImage(22, 6, 75, 75) && currentEnhanceIndex == 0)
        {
            PushView(ForgeView);
            return;
        }
        if (clicked && IsMouseClickOnImage(157, 6, 75, 75) && currentEnhanceIndex == 0)
        {
            PushView(ShopView);
            return;
        }

        if (clicked && IsMouseClickOnImage(157, 6, 75, 75) && currentEnhanceIndex > 0)
        {
            EnhanceItem *item = &enhanceItems[currentEnhanceIndex];
            playerInfo.money += item->price;
            currentEnhanceIndex = 0;
            isUpdate = 1;
            continue;
        }

        if (clicked && IsMouseClickOnImage(152, 24, 150, 150))
        {
            EnhanceItem *item = &enhanceItems[currentEnhanceIndex];
            if (playerInfo.money < item->cost)
            {
                continue;
            }

            playerInfo.money -= item->cost;
            int random = rand() % 100 + 1;
            if (random <= (item->successRate))
            {
                if (currentEnhanceIndex < enhanceItemCount - 1)
                {
                    currentEnhanceIndex++;
                    isUpdate = 1;
                }
            }
            else
            {
                PushView(DestroyedView);
                return;
            }
            continue;
        }

        Sleep(30);
    }
}

void DestroyedView()
{
    snprintf(view, sizeof(view), "destroyed");

    char temp[100];
    char dropText[100] = "";
    int isUpdate = 1, y = 30;
    int dropCount = 0;

    EnhanceItem *item = &enhanceItems[currentEnhanceIndex];
    if (item->dropItem[0] != '\0')
        dropCount = rand() % 10;

    while (1)
    {
        if (isUpdate)
        {
            Clear();
            ScreenBar();
            PrintText("[ 살리기 ]", 157, 9);
            BottomBar(playerInfo.guard, playerInfo.money);

            if (item->dropItem[0] != '\0') // 드랍 아이템이 있다면
            {
                snprintf(dropText, sizeof(dropText), "%s %3d 개 줍기", item->dropItem, dropCount);
                PrintTextLeft(dropText, 10, 17);
            }

            if (item->guardCost > 0)
            {
                PrintTextLeft("방지권으로 살리기 버튼을 눌러 살릴 수 있습니다.", 10, 9);
                snprintf(temp, sizeof(temp), "%s: 방지권 %d개 소모", item->name, item->guardCost);
                PrintTextLeft(temp, 10, 11);
            }

            PrintTextLeft(" ████ █   █  ███  ████  ████     █   █  ███   ████    ████  █████  ████ █████ ████   ███  █ "
                          "  █ █████ ████  ",
                          10, y);
            PrintTextLeft("█     █   █ █   █ █   █ █   █    █   █ █   █ █        █   █ █     █       █   █   █ █   █  "
                          "█ █  █     █   █ ",
                          10, y + 1);
            PrintTextLeft(" ███  █ █ █ █   █ ████  █   █    █ █ █ █████  ███     █   █ ████   ███    █   ████  █   █   "
                          "█   ████  █   █ ",
                          10, y + 2);
            PrintTextLeft("    █ ██ ██ █   █ █  █  █   █    ██ ██ █   █     █    █   █ █         █   █   █  █  █   █   "
                          "█   █     █   █ ",
                          10, y + 3);
            PrintTextLeft("████  █   █  ███  █   █ ████     █   █ █   █ ████     ████  █████ ████    █   █   █  ███    "
                          "█   █████ ████  ",
                          10, y + 4);

            isUpdate = 0;
        }
        ScreenBarButton(0, 1);
        EnforceButton(1);

        BOOL clicked = MouseLeftButtonClicked();
        if (clicked && IsMouseClickOnText(10, 17, dropText) && item->dropItem[0] != '\0')
        {
            AddDropItem(item->dropItem, dropCount);
            dropCount = 0;
            // dropText[0] = '\0';
            isUpdate = 1;
            continue;
        }

        if (clicked && IsMouseClickOnImage(157, 6, 75, 75))
        {
            if (playerInfo.guard >= item->guardCost && item->guardCost > 0)
            {
                playerInfo.guard -= item->guardCost;
                PopView();
                return;
            }
        }

        if (clicked && IsMouseClickOnImage(152, 24, 150, 150))
        {
            currentEnhanceIndex = 0;
            PopView();
            return;
        }

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

    while (1)
    {
        if (isUpdate)
        {
            for (int i = 0; i < 6; i++)
            {
                snprintf(temp, sizeof(temp), "%s", "+9강 워프권");
                PrintTextLeft(temp, x, 15 + 5 * i);
                snprintf(temp, sizeof(temp), "%d원", 1000000);
                PrintCenter(temp, 15 + 5 * i, consoleWidth);
            }

            BottomBar(playerInfo.guard, playerInfo.money);
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
            BottomBar(playerInfo.guard, playerInfo.money);
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
    char temp[100];
    char dropNames[MAX_DROP_ITEM_TYPES][50] = {{0}};
    int dropCount = 0;

    ScreenBar();

    // hard.csv의 모든 드랍 아이템 이름을 고유하게 수집
    for (int i = 0; i < enhanceItemCount && dropCount < MAX_DROP_ITEM_TYPES; i++)
    {
        const char *name = enhanceItems[i].dropItem;
        if (name == NULL || name[0] == '\0')
            continue;

        int found = 0;
        for (int j = 0; j < dropCount; j++)
        {
            if (strcmp(dropNames[j], name) == 0)
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            strncpy(dropNames[dropCount], name, sizeof(dropNames[dropCount]) - 1);
            dropNames[dropCount][sizeof(dropNames[dropCount]) - 1] = '\0';
            dropCount++;
        }
    }

    for (int i = 0; i < dropCount; i++)
    {
        int idx = GetDropItemIndex(dropNames[i]);
        int count = idx >= 0 ? playerInfo.dropItemCounts[idx] : 0;
        snprintf(temp, sizeof(temp), "%s: %d개", dropNames[i], count);
        PrintTextLeft(temp, x, 15 + 3 * i);
    }

    while (1)
    {
        if (isUpdate)
        {
            BottomBar(playerInfo.guard, playerInfo.money);
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
