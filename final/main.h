#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define MAX_ENHANCE_ITEMS 30
#define MAX_DROP_ITEM_TYPES 8
#define SHOP_ITEM_TYPES 6

// 강화 아이템 구조체(csv 파일 받는)
typedef struct
{
    int step;
    char name[50];
    int cost;
    int successRate;
    int price;
    int guardCost;
    char dropItem[50];
} EnhanceItem;
EnhanceItem enhanceItems[MAX_ENHANCE_ITEMS];

// User 정보
typedef struct
{
    int money;
    int guard;
    char dropItemNames[MAX_DROP_ITEM_TYPES][100];
    int dropItemCounts[MAX_DROP_ITEM_TYPES];
} UserInfo;
UserInfo playerInfo = {1000000, 0, {{0}}, {0}}; // init

// ShopItem 정보
typedef struct
{
    char ItemNames[100];
    int price;
} ShopProductInfo;
ShopProductInfo shopProductInfo[SHOP_ITEM_TYPES] = {
    {"+9강 워프권", 800000},    {"+13강 워프권", 5000000},    {"+14강 워프권", 7500000},
    {"+15강 워프권", 10000000}, {"깨짐 방지권 x 1", 2100000}, {"깨짐 방지권 x 3", 6000000},
};

// Forge 정보
typedef struct
{
    char DropItemNames[100];
    int DropItemCounts;
    int GuardCounts;
} ForgeInfo;
ForgeInfo forgeInfo[MAX_DROP_ITEM_TYPES] = {
    {"국적불분명 철조각", 8, 1}, {"타우의 뼈 부스러기", 5, 1}, {"빛 바랜 형광물질", 3, 1}, {"스위스산 철조각", 5, 2},
    {"불꽃마검 손잡이", 2, 1},   {"사악한 영혼", 1, 1},        {"도끼 가루", 3, 5},        {"투명 물질", 4, 11},
};

// 해당 좌표로 이동
void GotoXY(int _x, int _y)
{

    COORD pos = {_x, _y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 화면 비우기
void Clear(void)
{
    system("cls");
}

// 기본 세팅값
// 콘솔 제목
void SetTitle(void)
{
    // UTF-16 지정 (제목만)
    SetConsoleTitleW(L"검 강화하기");
}

// 배경, 글자색 지정
void SetColor(unsigned char _BgColor, unsigned char _TextColor)
{
    if (_BgColor > 15 || _TextColor > 15)
        return;

    unsigned short ColorNum = (_BgColor << 4) | _TextColor;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ColorNum);
}

// 콘솔 커서 on off
void MySetCursor(BOOL _bShow)
{
    CONSOLE_CURSOR_INFO curInfor;
    curInfor.dwSize = 1;
    curInfor.bVisible = _bShow;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfor);
}

// 콘솔 사이즈 지정
void SetConsoleSize(int _col, int _lines)
{
    char setText[100];
    snprintf(setText, sizeof(setText), "mode con cols=%d lines=%d", _col, _lines);
    system(setText);
}
// 기본 세팅값

// 출력
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
    if (bm.bmWidth * maxHeight > bm.bmHeight * maxWidth) // 가로(width)가 더 긴 경우
    {
        targetWidth = maxWidth;                               // 가로폭을 박스 최대 크기에 맞춘 뒤
        targetHeight = (bm.bmHeight * maxWidth) / bm.bmWidth; // 가로폭 비율에 맞게 세로폭 조정
    }
    else // 세로(height)가 더 긴 경우
    {
        targetHeight = maxHeight;                             // 세로폭을 최대로 맞추고
        targetWidth = (bm.bmWidth * maxHeight) / bm.bmHeight; // 가로폭은 비율에 맞게
    }

    // 좌표로 받아서 픽셀값으로 바꾸기
    int pixelX = x * 8;  // 칸 당 8픽셀
    int pixelY = y * 16; // 칸 당 16픽셀

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
// 출력

// 마우스 event
// 좌측 마우스가 클릭 되었는지
BOOL MouseLeftButtonClicked(void)
{
    static BOOL wasDown = FALSE;
    BOOL isDown = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
    BOOL clicked = isDown && !wasDown;
    wasDown = isDown;
    return clicked;
}

// 마우스의 좌표가 텍스트 위치에 있는지(PrintTextLeft 기준)
BOOL IsMouseClickOnText(int textX, int textY, const char *text)
{
    POINT pt;
    if (!GetCursorPos(&pt))
        return FALSE;

    HWND hwnd = GetConsoleWindow();
    if (hwnd == NULL)
        return FALSE;

    if (!ScreenToClient(hwnd, &pt))
        return FALSE;

    int textWidth = GetDisplayWidth(text);
    int left = textX * 8;
    int top = textY * 16;
    int right = left + textWidth * 8;
    int bottom = top + 16;

    return pt.x >= left && pt.x <= right && pt.y >= top && pt.y <= bottom;
}

// 마우스의 좌표가 이미지 영역 내에 있는지
BOOL IsMouseClickOnImage(int imageX, int imageY, int imageWidth, int imageHeight)
{
    POINT pt;
    if (!GetCursorPos(&pt))
        return FALSE;

    HWND hwnd = GetConsoleWindow();
    if (hwnd == NULL)
        return FALSE;

    if (!ScreenToClient(hwnd, &pt))
        return FALSE;

    // 좌표(픽셀값)는 DrawImage에서 참고
    int left = imageX * 8 - imageWidth / 2;
    int top = imageY * 16 - imageHeight / 2;
    int right = left + imageWidth;
    int bottom = top + imageHeight;

    return pt.x >= left && pt.x <= right && pt.y >= top && pt.y <= bottom;
}
// 마우스 event

// view stack
typedef struct ViewNode
{
    void (*view)(void); // 함수 포인터
    struct ViewNode *next;
} ViewNode;
static ViewNode *viewStackTop = NULL; // init

void PushView(void (*view)(void))
{
    ViewNode *node = (ViewNode *)malloc(sizeof(ViewNode)); // 새 view node
    if (node == NULL)                                      // 메모리 할당 실패 시 예외
        return;
    node->view = view;         // node의 view에 받아온 view 저장
    node->next = viewStackTop; // node의 text를 top에 연결(처음인 경우 NULL)
    viewStackTop = node;       // top을 현재 노드로
}

void PopView(void)
{
    if (viewStackTop == NULL) // 스택이 비어있으면 return
        return;
    ViewNode *top = viewStackTop;
    viewStackTop = top->next; // 다음 노드를 top으로 지정
    free(top);                // 메모리 해제
}

void (*TopView(void))(void)
{
    if (viewStackTop == NULL) // 스택이 비어있으면 NULL
        return NULL;
    return viewStackTop->view; // Top의 view 반환
}

int IsViewStackEmpty(void)
{
    return viewStackTop == NULL; // 스택이 비어있으면 1, 아니면 0
}
// view stack

// csv
void TrimQuotes(char *str)
{
    char *start = str;    // 문자열의 시작
    while (*start == ' ') // 시작 공백인 경우 공백 전부 스킵
        start++;

    char *end = start + strlen(start) - 1; // 끝

    // 뒷부분이 공백, 탭, \r, \n 인 경우 '\0'로 덮어쓰기
    while (end >= start && (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n'))
    {
        *end = '\0';
        end--;
    }

    // 큰 따옴표 없애기
    if (*start == '"' && end > start && *end == '"')
    {
        start++;
        *end = '\0';
    }
    // strcpy를 쓰면 메모리 오염이 있을 수 있기 때문에 memmove를 사용
    // 메모리 영역이 겹쳐있을 경우 strcpy 사용 시 데이터가 덮어씌워질 수 있음
    if (start != str)
        memmove(str, start, strlen(start) + 1);
}

// 숫자 추출
int ParseNumber(const char *text)
{
    int value = 0;
    int found = 0;
    while (*text)
    {
        if (*text >= '0' && *text <= '9')
        {
            found = 1;
            value = value * 10 + (*text - '0');
            // 자릿수 밀어내고 숫자 추가, ASCII '0': 48 ~
            // ex 48 => 480(48*10) + 5
        }
        text++;
    }
    return found ? value : 0; // 숫자가 없었다면 0, 있었다면 value
}

void ParseCsvFields(char *line, char *fields[], int maxFields)
{
    int idx = 0;
    char *p = line;

    while (idx < maxFields && *p)
    {
        if (*p == '"') // 큰따옴표로 시작하는 경우
        {
            p++; // 큰따옴표 스킵
            fields[idx++] = p;
            while (*p && // 문자열 끝이 아니면서 닫는 큰따옴표를 만난 게 아니라면
                   !(*p == '"' && (*(p + 1) == ',' || *(p + 1) == '\0')))
                p++;
            if (*p == '"') // 큰따옴표 닫힘이므로 NULL 대체
                *p++ = '\0';
            if (*p == ',') // 큰따옴표가 닫히기 전이라면 콤마 스킵
                p++;
        }
        else // 큰따옴표로 시작하는 게 아니면
        {
            fields[idx++] = p;
            while (*p && *p != ',')
                p++;
            if (*p == ',') // 다음 필드로 넘어가는 콤마이므로 NULL 대체
                *p++ = '\0';
        }
    }

    while (idx < maxFields) // 예외 처리(csv 필드 수가 maxFields보다 적은 경우)
        fields[idx++] = NULL;
}
// csv

int GetDropItemIndex(const char *itemName)
{
    // itemName이 비어있다면 -1
    if (itemName == NULL || itemName[0] == '\0')
        return -1;

    for (int i = 0; i < MAX_DROP_ITEM_TYPES; i++)
    {
        // 아이템 슬롯이 비어있지 않고 얻은 아이템과 아이템 슬롯의 이름이 같은 경우 해당 슬롯 인덱스 반환
        if (playerInfo.dropItemNames[i][0] != '\0' && strcmp(playerInfo.dropItemNames[i], itemName) == 0)
            return i;
    }
    return -1;
}

void AddDropItem(const char *itemName, int count)
{
    if (itemName == NULL || itemName[0] == '\0' || count <= 0)
        return;

    // 해당 아이템 슬롯의 개수를 증가시킴(아이템 슬롯에 있는 경우)
    int idx = GetDropItemIndex(itemName);
    if (idx >= 0)
    {
        playerInfo.dropItemCounts[idx] += count;
        return;
    }

    // 인벤토리에 없는 새로운 아이템이면 빈 슬롯을 찾아 새로 등록
    for (int i = 0; i < MAX_DROP_ITEM_TYPES; i++)
    {
        if (playerInfo.dropItemNames[i][0] == '\0') // 빈 슬롯 발견
        {
            // 이름 복사
            strncpy(playerInfo.dropItemNames[i], itemName, sizeof(playerInfo.dropItemNames[i]) - 1);
            playerInfo.dropItemNames[i][sizeof(playerInfo.dropItemNames[i]) - 1] = '\0'; // NULL 추가

            // 개수 저장
            playerInfo.dropItemCounts[i] = count;
            return;
        }
    }
}
