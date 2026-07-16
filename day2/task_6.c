// 비어있는 공집합 S가 주어졌을 때
// add, remove, check, toggle, all 0, empty 0 기능
// 숫자 추가는 1~20 자연수, 겹치면 무시
// toggle -> if check

#include <stdio.h>

int identify(char arr[]);

void main()
{

    int sArr[20] = {
        0,
    };
    printf("연산을 선택하세요. ( 1<= x <= 20)");
    printf("\nadd x");
    printf("\nremove x");
    printf("\ncheck x");
    printf("\ntoggle x");
    printf("\nall 0");
    printf("\nempty 0");

    while (1)
    {
        // 최대 길이 remove 20
        //          012345678
        char input[9];

        printf("\ninput : ");
        scanf(" %s", &input);
    }
}

int identify(char arr[])
{
    char add[3] = {'a', 'd', 'd'};
    char remove[6] = {'r', 'e', 'm', 'o', 'v', 'e'};
    char check[5] = {'c', 'h', 'e', 'c', 'k'};
    char toggle[6] = {'t', 'o', 'g', 'g', 'l', 'e'};
    char all[5] = {'a', 'l', 'l', ' ', '0'};
    char empty[7] = {'e', 'm', 'p', 't', 'y', ' ', '0'};

    int cnt;

    char key;

    cnt = 0;
    // 문자열을 비교해서 같으면 count +1
    for (int i = 0; i < 8; i++)
    {
        key = arr[i];
        if (key == 1)
            cnt += 1;
    }

    if (cnt == 8)
        return 1;

    cnt = 0;
    for (int i = 0; i < 8; i++)
    {
        key = arr[i];
        if (key == 1)
            cnt += 1;
    }

    if (cnt == 8)
        return 2;

    cnt = 0;
    // ASCII a ~ g => 97 ~ 103, C => 67
    for (int i = 0; i < 8; i++)
    {
        key = (int)arr[i];
        if ((103 >= key && key >= 97) || key == 67)
            cnt += 1;
    }

    if (cnt == 8)
        return 3;

    return 4;
}