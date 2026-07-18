// 비어있는 공집합 S가 주어졌을 때
// add, remove, check, toggle, all 0, empty 0 기능
// 숫자 추가는 1~20 자연수, 겹치면 무시
// toggle -> if check; add; remove

// 기본 로직
// 1 ~ 20이 범위여서 배열을 0값으로 지정
// 0이 들어있으면 비어있다고 판단, printArr에서 0인 경우 출력 X
// 순서 기억 및 입력 숫자가 배열 안에 있는지의 여부를 판단해야 하므로 sArrIdx, isExist로 판별
// x는 입력 때 받은 숫자

#include <stdio.h>

int identify(char arr[]);

void printArr(int arr[]);

int add(int arr[], int x, int sArrIdx);

int remv(int arr[], int x, int sArrIdx);

int isCheck(int arr[], int x);

void main()
{

    int sArr[20] = {
        0,
    };
    int sArrIdx = 0;

    printf("연산을 선택하세요. ( 1<= x <= 20)");
    printf("\nadd x");
    printf("\nremove x");
    printf("\ncheck x");
    printf("\ntoggle x");
    printf("\nall 0");
    printf("\nempty 0\n");

    while (1)
    {
        char input[10] = {
            '\0',
        };
        int x = 0;

        printf("\ninput : ");
        scanf(" %s %d", &input, &x);

        printf("집합 : ");

        // 입력 값 벗어난 경우 종료(0은 add, empty 사용)
        if ((20 < x || x < 0))
            break;

        switch (identify(input))
        {
        // add
        case 1:
            sArrIdx = add(sArr, x, sArrIdx);
            printArr(sArr);
            break;
        // remove
        case 2:
            sArrIdx = remv(sArr, x, sArrIdx);
            printArr(sArr);
            break;
        // check
        case 3:
            printArr(sArr);
            printf("\n%d", isCheck(sArr, x));
            break;
        // toggle
        case 4:
            if (isCheck(sArr, x))
                sArrIdx = remv(sArr, x, sArrIdx);
            else
                sArrIdx = add(sArr, x, sArrIdx);

            printArr(sArr);
            break;
        // all 0
        case 5:
            if (x == 0)
            {
                for (int i = 0; i < 20; i++)
                    sArr[i] = i + 1;
                sArrIdx = 20;
                printArr(sArr);
                break;
            }
            return;
        // empty 0
        case 6:
            if (x == 0)
            {
                for (int i = 0; i < 20; i++)
                    sArr[i] = 0;
                sArrIdx = 0;
                printArr(sArr);
                break;
            }
            return;
        // 잘못 입력
        default:
            return;
        }
        printf("\n");
    }
}

// 입력값 체크
// strcmp(string compare) 안 쓰고 구현하느라 하드코딩
int identify(char arr[])
{
    char add[3] = {'a', 'd', 'd'};
    char remove[6] = {'r', 'e', 'm', 'o', 'v', 'e'};
    char check[5] = {'c', 'h', 'e', 'c', 'k'};
    char toggle[6] = {'t', 'o', 'g', 'g', 'l', 'e'};
    char all[3] = {'a', 'l', 'l'};
    char empty[5] = {'e', 'm', 'p', 't', 'y'};

    int cnt;

    char key;

    // 문자열을 비교해서 같으면 count +1
    // add
    cnt = 0;
    for (int i = 0; i < 3; i++)
    {
        key = arr[i];
        if (key == add[i])
            cnt += 1;
    }
    if (cnt == 3)
        return 1;

    // remove
    cnt = 0;
    for (int i = 0; i < 6; i++)
    {
        key = arr[i];
        if (key == remove[i])
            cnt += 1;
    }
    if (cnt == 6)
        return 2;

    // check
    cnt = 0;
    for (int i = 0; i < 5; i++)
    {
        key = arr[i];
        if (key == check[i])
            cnt += 1;
    }
    if (cnt == 5)
        return 3;

    // toggle
    cnt = 0;
    for (int i = 0; i < 6; i++)
    {
        key = arr[i];
        if (key == toggle[i])
            cnt += 1;
    }
    if (cnt == 6)
        return 4;

    // all
    cnt = 0;
    for (int i = 0; i < 3; i++)
    {
        key = arr[i];
        if (key == all[i])
            cnt += 1;
    }
    if (cnt == 3)
        return 5;

    // empty
    cnt = 0;
    for (int i = 0; i < 5; i++)
    {
        key = arr[i];
        if (key == empty[i])
            cnt += 1;
    }
    if (cnt == 5)
        return 6;

    return 0;
}

// 배열(집합) 출력해주는 함수
// 반복 사용해서 함수화 했음
void printArr(int arr[])
{
    printf("{ ");
    for (int i = 0; i < 20; i++)
    {
        if (arr[i] != 0)
        {
            if (i == 19)
                printf("%d", arr[i]);
            else
                printf("%d, ", arr[i]);
        }
    }
    printf(" }");
}

// add 함수
// toggle에서도 쓰여서 함수화
// sArrIdx 값을 리턴함(remv도)
int add(int arr[], int x, int sArrIdx)
{
    int isExist = 0;

    for (int i = 0; i < 20; i++)
        if (arr[i] == x)
            isExist = 1;

    if (isExist == 0)
    {
        arr[sArrIdx] = x;
        sArrIdx += 1;
    }

    return sArrIdx;
}

// remove 함수 (기존 remove와 중복 떠서 remv로 지음)
// toggle에서도 쓰여서 함수화
int remv(int arr[], int x, int sArrIdx)
{
    for (int i = 0; i < 20; i++)
        if (arr[i] == x)
        {
            // 한 칸씩 당기기
            for (int j = i; j < 19; j++)
            {
                arr[j] = arr[j + 1];
            }

            arr[sArrIdx - 1] = 0;
            sArrIdx -= 1;
            break;
        }

    return sArrIdx;
}

// check 함수
// toggle에서도 쓰여서 함수화
// 존재하면 1, 아니면 0
int isCheck(int arr[], int x)
{
    int isExist = 0;

    for (int i = 0; i < 20; i++)
        if (arr[i] == x)
            isExist = 1;

    if (isExist)
        return 1;
    else
        return 0;
}