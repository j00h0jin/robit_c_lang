// 음계
// 조건: 함수 사용하여 반환 값에 따른 switch문 사용
// 다장조는 c d e f g a b C, 8개 음으로 구성, 그 외 mixed랑 구별(mixed랑 다장조가 아닌 것)

#include <stdio.h>

int identify(char arr[]);

void main()
{
    char arr[8];

    printf("음 입력\n");
    scanf(" %s", &arr);

    printf("결과 : ");

    switch (identify(arr))
    {
    case 1:
        printf("ascending");
        break;

    case 2:
        printf("descending");
        break;

    case 3:
        printf("mixed");
        break;

    default:
        printf("ERROR: c d e f g a b C 중 입력");
        break;
    };
}

// ascending -> 1, discending -> 2, mixed -> 3, 그 외 -> 4 반환
int identify(char arr[])
{
    char ascending[8] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};
    char discending[8] = {'C', 'b', 'a', 'g', 'f', 'e', 'd', 'c'};

    int cnt;

    char key;

    cnt = 0;
    // 문자열을 비교해서 같으면 count +1
    for (int i = 0; i < 8; i++)
    {
        key = arr[i];
        if (key == ascending[i])
            cnt += 1;
    }

    if (cnt == 8)
        return 1;

    cnt = 0;
    for (int i = 0; i < 8; i++)
    {
        key = arr[i];
        if (key == discending[i])
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