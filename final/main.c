/*
cd final
gcc main.c -o main.exe -lgdi32 -lmsimg32
start conhost main.exe

*/

// 0 22 45 90 135 157 179

#include "main.h"

void ScreenBar();
void BottomBar();
void ScreenBarButton(int button1, int button2);
void EnforceButton(int button1);

void StartView();
void MainView();
void DestroyedView();
void ShopView();
void ForgeView();
void EtcView();

int LoadHardCsv(char *path);
int LoadEasyPercent(char *path);
void LoadEnhanceData(int mode);

int level = 0;
int consoleWidth = 180 + 1;
int consoleHeight = 50 + 1;
char view[30];

int enhanceItemCount = 0;
int currentEnhanceIndex = 0;

int main(void)
{
    // 콘솔 제목 설정
    SetTitle();

    SetConsoleOutputCP(65001); // 인코딩 UTF-8 고정

    // QuickEdit 모드 비활성화
    // 마우스 이벤트 후 키보드 입력을 받아야 넘어가지는 버그가 있었는데
    // 이를 제거해주는 설정이라고 함
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
void BottomBar()
{
    UserInfo *playerInfom = &playerInfo;
    char temp[100];

    snprintf(temp, sizeof(temp), "방지권: %d", playerInfom->guard);
    PrintTextLeft(temp, 2, 44);
    snprintf(temp, sizeof(temp), "%d 원", playerInfom->money);
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
            // level에 따라 csv에서 읽어오는 난이도가 달라짐
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
    // 만약 정보 갱신이 생기는 이벤트가 있다면 isUpdate를 1로 지정하여 화면을 재출력하게 함
    int isUpdate = 1;
    UserInfo *playerInfom = &playerInfo;
    EnhanceItem *item = &enhanceItems[currentEnhanceIndex];

    while (1)
    {
        if (isUpdate)
        {
            EnhanceItem *item = &enhanceItems[currentEnhanceIndex];
            // UI 부분
            Clear();
            ScreenBar();

            if (currentEnhanceIndex == 0)
            {

                PrintText("[ 조합소 ]", 22, 9);
                PrintText("[ 상점 ]", 157, 9);
            }
            else if (currentEnhanceIndex == 28)
            {
                PrintText("[ 판매불가 ]", 157, 9);
            }
            else
            {
                PrintText("[ 판매 ]", 157, 9);
            }
            snprintf(temp, sizeof(temp), "강화비용: %d원", item->cost);
            PrintTextLeft(temp, 2, 15);
            snprintf(temp, sizeof(temp), "판매가격: %d원", item->price);
            PrintTextLeft(temp, 2, 17);

            snprintf(temp, sizeof(temp), "+%d %s", item->step, item->name);
            PrintCenter(temp, 40, consoleWidth);
            snprintf(temp, sizeof(temp), "성공률 %d %%", item->successRate);
            PrintCenter(temp, 42, consoleWidth);

            BottomBar();

            isUpdate = 0;
        }
        if (currentEnhanceIndex == 0) // 강화 0강일 경우 양쪽 버튼 보이기
        {
            ScreenBarButton(1, 1);
        }
        else // 아니면 오른쪽만
        {
            ScreenBarButton(0, 1);
        }
        // asset에 강화 단계에 따른 이미지 별 출력
        char imagePath[100];
        snprintf(imagePath, sizeof(imagePath), "asset/sword_%d.bmp", currentEnhanceIndex);
        DrawImage(imagePath, 90, 23, 600, 350);
        EnforceButton(1); // 강화 버튼 이미지 보이기

        BOOL clicked = MouseLeftButtonClicked();
        // 클릭 + 현재 강화 단계가 0 이라면 왼쪽 Forge 오른쪽 Shop으로 이동
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

        // 강화 단계 1단계 이상일 경우 shop 이동 자리에 판매버튼으로 대체됨
        if (clicked && IsMouseClickOnImage(157, 6, 75, 75) && currentEnhanceIndex > 0)
        {
            if (currentEnhanceIndex == 28) // 28단계는 판매 불가
            {
                continue;
            }
            EnhanceItem *item = &enhanceItems[currentEnhanceIndex];
            playerInfom->money += item->price; // 판매금액만큼 추가
            currentEnhanceIndex = 0;           // 팔았으므로 0단계로
            isUpdate = 1;
            continue;
        }

        // 강화 버튼
        if (clicked && IsMouseClickOnImage(152, 24, 150, 150))
        {
            EnhanceItem *item = &enhanceItems[currentEnhanceIndex];
            if (playerInfom->money < item->cost) // 소지 금액 < 강화 비용
            {
                continue;
            }

            playerInfom->money -= item->cost;  // 강화 금액만큼 차감
            int random = rand() % 100 + 1;     // 1 ~ 100
            if (random <= (item->successRate)) // random < 성공확률
            {
                if (currentEnhanceIndex < enhanceItemCount - 1) // 최대강화 수가 아니면
                {
                    currentEnhanceIndex++; // 단계 +1
                    isUpdate = 1;
                }
            }
            else // 실패
            {
                PushView(DestroyedView); // destroyed로 이동
                return;
            }
            continue;
        }
        // 과연산 방지(while문에 다 넣었으므로 아래 설명 생략)
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
    UserInfo *playerInfom = &playerInfo;

    if (item->dropItem[0] != '\0')
        dropCount = rand() % 10; // 0~9개 랜덤 드롭

    while (1)
    {
        if (isUpdate)
        {
            Clear();
            ScreenBar();
            PrintText("[ 살리기 ]", 157, 9);
            BottomBar();

            if (item->dropItem[0] != '\0') // 드랍 아이템이 있다면 출력
            {
                snprintf(dropText, sizeof(dropText), "%s %3d 개 줍기", item->dropItem, dropCount);
                PrintTextLeft(dropText, 10, 17);
            }

            if (item->guardCost > 0) // 방지권으로 살릴 수 있는 아이템이면 출력
            {
                PrintTextLeft("방지권으로 살리기 버튼을 눌러 살릴 수 있습니다.", 10, 9);
                snprintf(temp, sizeof(temp), "%s: 방지권 %d개 소모", item->name, item->guardCost);
                PrintTextLeft(temp, 10, 11);
            }
            // ASCII 아트
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
        // 드랍 텍스트 클릭 시(드랍 아이템이 있는 경우)
        if (clicked && IsMouseClickOnText(10, 17, dropText) && item->dropItem[0] != '\0')
        {
            AddDropItem(item->dropItem, dropCount); // 아이템 칸에 추가
            dropCount = 0;                          // 습득했으므로 drop count는 0
            isUpdate = 1;
            continue;
        }
        // 방지권 눌렀을 때
        if (clicked && IsMouseClickOnImage(157, 6, 75, 75))
        {
            // 방지권이 필요 방지권보다 같거나 크면서 해당 아이템이 방지권 사용 가능할 때
            if (playerInfom->guard >= item->guardCost && item->guardCost > 0)
            {
                playerInfom->guard -= item->guardCost;
                PopView();
                return;
            }
        }

        // 오른쪽 큰 버튼을 누르면 0강으로 돌아감
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

    int isUpdate = 1;
    char temp[100];

    int x = 15;

    ShopProductInfo *shop = shopProductInfo;
    UserInfo *playerInfom = &playerInfo;

    while (1)
    {
        if (isUpdate)
        {
            // UI
            Clear();
            ScreenBar();
            PrintTextLeft("Tip: 돈을 다 쓰시면 강화 비용을 지불할 수 없게 됩니다.", 7, 7);
            PrintText("[ 나가기 ]", 157, 9);

            for (int i = 0; i < SHOP_ITEM_TYPES; i++)
            {
                snprintf(temp, sizeof(temp), "%s", shop[i].ItemNames);
                PrintTextLeft(temp, x, 15 + 5 * i);
                snprintf(temp, sizeof(temp), "%d원", shop[i].price);
                PrintCenter(temp, 15 + 5 * i, consoleWidth);
            }

            BottomBar();
            isUpdate = 0;
        }
        ScreenBarButton(0, 1);

        for (int i = 0; i < SHOP_ITEM_TYPES; i++)
        {
            DrawImage("asset/item.bmp", 10, 15 + 5 * i, 40, 40);
            DrawImage("asset/button.bmp", 157, 15 + 5 * i, 40, 40);
        }
        BOOL clicked = MouseLeftButtonClicked();

        for (int i = 0; i < SHOP_ITEM_TYPES; i++)
        {
            if (clicked && IsMouseClickOnImage(157, 15 + 5 * i, 40, 40) && playerInfom->money >= shop[i].price)
            {
                playerInfom->money -= shop[i].price;
                if (i < 4)
                {
                    switch (i)
                    {
                    case 0: // 9 워프
                        currentEnhanceIndex = 9;
                        break;
                    case 1: // 13 워프
                        currentEnhanceIndex = 13;
                        break;
                    case 2: // 14 워프
                        currentEnhanceIndex = 14;
                        break;
                    case 3: // 15 워프
                        currentEnhanceIndex = 15;
                        break;

                    default:
                        break;
                    }
                    PopView();
                    return;
                }
                isUpdate = 1; // 화면 다시 그려주기
                switch (i)
                {
                case 4: // 방지권 1개
                    playerInfom->guard += 1;

                    break;
                case 5: // 방지권 3개
                    playerInfom->guard += 3;
                    break;

                default:
                    break;
                }
            }
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

void ForgeView()
{
    snprintf(view, sizeof(view), "Forge");

    int isUpdate = 1;
    char temp[100];

    int x = 10;
    ForgeInfo *fgInfo = forgeInfo;

    while (1)
    {
        if (isUpdate)
        {
            // UI
            Clear();
            BottomBar();
            ScreenBar();
            PrintText("[ 잡템 창 ]", 22, 9);
            PrintText("[ 나가기 ]", 157, 9);
            for (int i = 0; i < MAX_DROP_ITEM_TYPES; i++)
            {
                snprintf(temp, sizeof(temp), "%s %d개 -> 깨짐 방지권 %d개", fgInfo[i].DropItemNames,
                         fgInfo[i].DropItemCounts, fgInfo[i].GuardCounts);
                PrintTextLeft(temp, x, 15 + 3 * i);
            }

            isUpdate = 0;
        }
        ScreenBarButton(1, 1);
        for (int i = 0; i < MAX_DROP_ITEM_TYPES; i++)
        {
            DrawImage("asset/button.bmp", 157, 15 + 3 * i, 40, 40);
        }

        UserInfo *playerInfom = &playerInfo;
        ForgeInfo *fgInfo = forgeInfo;
        BOOL clicked = MouseLeftButtonClicked();

        for (int i = 0; i < SHOP_ITEM_TYPES; i++)
        {

            if (clicked && IsMouseClickOnImage(157, 15 + 5 * i, 40, 40) &&
                playerInfom->dropItemCounts[i] >= fgInfo[i].DropItemCounts)
            {
                isUpdate = 1;
                switch (i)
                {
                case 0:
                    playerInfom->dropItemCounts[i] -= fgInfo[i].DropItemCounts;
                    playerInfom->guard += fgInfo[i].GuardCounts;
                    break;
                case 1:
                    playerInfom->dropItemCounts[i] -= fgInfo[i].DropItemCounts;
                    playerInfom->guard += fgInfo[i].GuardCounts;
                    break;
                case 2:
                    playerInfom->dropItemCounts[i] -= fgInfo[i].DropItemCounts;
                    playerInfom->guard += fgInfo[i].GuardCounts;
                    break;
                case 3:
                    playerInfom->dropItemCounts[i] -= fgInfo[i].DropItemCounts;
                    playerInfom->guard += fgInfo[i].GuardCounts;
                    break;
                case 4:
                    playerInfom->dropItemCounts[i] -= fgInfo[i].DropItemCounts;
                    playerInfom->guard += fgInfo[i].GuardCounts;
                    break;
                case 5:
                    playerInfom->dropItemCounts[i] -= fgInfo[i].DropItemCounts;
                    playerInfom->guard += fgInfo[i].GuardCounts;
                    break;
                case 6:
                    playerInfom->dropItemCounts[i] -= fgInfo[i].DropItemCounts;
                    playerInfom->guard += fgInfo[i].GuardCounts;
                    break;
                case 7:
                    playerInfom->dropItemCounts[i] -= fgInfo[i].DropItemCounts;
                    playerInfom->guard += fgInfo[i].GuardCounts;
                    break;

                default:
                    break;
                }
            }
        }

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

    int isUpdate = 1;
    char temp[100];
    char dropNames[MAX_DROP_ITEM_TYPES][50] = {{0}};
    int dropCount = 0;

    while (1)
    {
        if (isUpdate)
        {
            Clear();
            PrintText("[ 나가기 ]", 157, 9);
            BottomBar();
            isUpdate = 0;
            UserInfo *playerInfom = &playerInfo;

            ScreenBar();

            // hard.csv의 모든 드랍 아이템 이름을 고유하게 수집
            for (int i = 0; i < enhanceItemCount && dropCount < MAX_DROP_ITEM_TYPES; i++)
            {
                const char *name = enhanceItems[i].dropItem; // 드랍 아이템이 비어있는 경우 skip
                if (name == NULL || name[0] == '\0')
                    continue;

                int found = 0;
                for (int j = 0; j < dropCount; j++) // drop names에 추가된 적 있는지 확인
                {
                    if (strcmp(dropNames[j], name) == 0) // 있다면 break
                    {
                        found = 1;
                        break;
                    }
                }
                if (found == 0) // 추가된 적 없으면 추가
                {
                    strncpy(dropNames[dropCount], name, sizeof(dropNames[dropCount]) - 1); // NULL 자리
                    dropNames[dropCount][sizeof(dropNames[dropCount]) - 1] = '\0';         // 마지막 NULL 추가
                    dropCount++; // 추가되었으므로 drop count +1
                }
            }

            // 보유 수량 출력
            for (int i = 0; i < dropCount; i++)
            {
                int idx = GetDropItemIndex(dropNames[i]);
                int count = idx >= 0 ? playerInfom->dropItemCounts[idx] : 0;
                snprintf(temp, sizeof(temp), "%s: %d개", dropNames[i], count);
                PrintTextLeft(temp, 10, 15 + 3 * i);
            }
        }
        ScreenBarButton(0, 1); // 우측 상탄 버튼 이미지 표시

        // 우측 상단(나가기) 버튼 클릭 시 팝
        BOOL clicked = MouseLeftButtonClicked();
        if (clicked && IsMouseClickOnImage(157, 6, 75, 75))
        {
            PopView();
            return;
        }
        Sleep(30);
    }
}

int LoadHardCsv(char *path)
{
    FILE *fp = fopen(path, "r");
    if (!fp) // 예외(NULL)
        return 0;

    char line[200];
    if (!fgets(line, sizeof(line), fp)) // 1줄 스킵, 스킵 후 비었을 경우 아래 조건문
    {
        fclose(fp);
        return 0;
    }

    int count = 0;
    // 파일 끝 or MAX_ENHANCE_ITEMS까지 while
    while (fgets(line, sizeof(line), fp) && count < MAX_ENHANCE_ITEMS) // MAX_ENHANCE_ITEMS = 30
    {
        char *fields[7];
        ParseCsvFields(line, fields, 7); // 7 fields로 쪼개기

        if (fields[0] == NULL || fields[0][0] == '\0') // 빈 값이면 skip
            continue;

        EnhanceItem *item = &enhanceItems[count]; // 구조체 포인터 선언(여기다 저장)
        item->step = ParseNumber(fields[0]);      // 단계 저장

        if (fields[1]) // 이름 저장
        {
            TrimQuotes(fields[1]);
            strncpy(item->name, fields[1], sizeof(item->name) - 1);
            item->name[sizeof(item->name) - 1] = '\0'; // NULL 자리
        }
        else
        {
            item->name[0] = '\0'; // NULL 추가
        }

        item->cost = fields[2] ? ParseNumber(fields[2]) : 0;        // 강화 비용
        item->successRate = fields[3] ? ParseNumber(fields[3]) : 0; // 강화 확률
        item->price = fields[4] ? ParseNumber(fields[4]) : 0;       // 판매 가격
        if (fields[5])
        {
            TrimQuotes(fields[5]);                       // 방지권 소모 개수
            if (strstr(fields[5], "방지권불가") != NULL) // "방지권불가"인 경우 -1
                item->guardCost = -1;
            else
                item->guardCost = ParseNumber(fields[5]);
        }
        else
        {
            item->guardCost = 0; // - 인 경우
        }

        if (fields[6]) // 드랍 아이템
        {
            TrimQuotes(fields[6]);
            strncpy(item->dropItem, fields[6], sizeof(item->dropItem) - 1); // NULL 자리
            item->dropItem[sizeof(item->dropItem) - 1] = '\0';
            if (strcmp(item->dropItem, "-") == 0) // - 인 경우 \0
                item->dropItem[0] = '\0';
        }
        else
        {
            item->dropItem[0] = '\0'; // 비었을 경우
        }

        count++;
    }

    fclose(fp); // 닫기
    enhanceItemCount = count;
    return 1;
}

int LoadEasyPercent(char *path)
{
    FILE *fp = fopen(path, "r");
    if (!fp) // 예외(NULL)
        return 0;

    char line[200];
    if (!fgets(line, sizeof(line), fp)) // 첫 줄 스킵, 스킵 후 파일 끝이라면 아래 조건문
    {
        fclose(fp);
        return 0;
    }

    int idx = 0;
    // 파일 끝까지 enhanceItemCount만큼 반복(둘 중 하나가 끝에 도달할 때까지)
    while (fgets(line, sizeof(line), fp) && idx < enhanceItemCount)
    {
        char *fields[1];
        ParseCsvFields(line, fields, 1);       // 데이터 내 따옴표나 콤마 등 제거하여 저장
        if (fields[0] && fields[0][0] != '\0') // fields[0] 널이 아니면서 [0][0]이 빈 문자열이 아닐 때
        {
            int percent = ParseNumber(fields[0]);
            if (percent > 0) // percent가 양수일 경우 successRate에 저장
                enhanceItems[idx].successRate = percent;
        }
        idx++;
    }

    fclose(fp); // 닫기
    return 1;
}

void LoadEnhanceData(int mode) // 1, 2
{
    if (!LoadHardCsv("csv/hard.csv")) // hard 모드 기본
        return;

    if (mode == 1) // easy인 경우 확률 덮어쓰기
        LoadEasyPercent("csv/easy_percent.csv");
}