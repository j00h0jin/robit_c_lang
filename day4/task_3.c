/*
동적할당 메모리 "최소화"
물품 개수
(물품 가격) x 개수 -> 구조체 저장
마지막에 string 입력
위에 입력 했던 물품인 경우 금액 합계
아닌 경우 0
*/

// 작업중
#include <stdio.h>
#include <stdlib.h>

typedef struct _Info
{
    char *name;
    int price;
} Info;

// 길이 반환
int get_length(const char *str)
{
    const char *p = str;
    int len = 0;
    // 널 문자('\0')를 만날 때까지 길이를 1씩 증가
    while (*(p + len) != '\0')
    {
        len++;
    }
    return len;
}
// string copy
void my_strcpy(char *s1, char *s2)
{
    //'\0' 전까지 복사
    while ((*s1 = *s2) != '\0')
    {
        s1++;
        s2++;
    }
}
// string compare
int my_strcmp(char *s1, char *s2)
{
    // 같으면서 '\0'이 아닐 때까지
    while (*s1 != '\0' && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    // 문자열이 같으면 0 반환
    return *s1 - *s2;
}

void main()
{
    int cnt;
    scanf("%d ", &cnt);

    // input값만큼 좌표 list 동적할당
    Info *list;
    list = (Info *)malloc(sizeof(Info) * cnt);

    char temp[20];

    // input 개수만큼 x y 좌표 받기
    for (int i = 0; i < cnt; i++)
    {
        scanf(" %s %d", temp, &list[i].price);

        // temp의 length를 구함
        int name_length = get_length(temp);
        (list + i)->name = (char *)malloc(name_length + 1); // length + '\0'만큼 메모리 할당
        my_strcpy((list + i)->name, temp);
    }

    // 마지막 받는 물품도 동적할당
    scanf(" %s", temp);
    int name_length = get_length(temp);
    char *p;
    p = (char *)malloc(name_length + 1);
    my_strcpy(p, temp);

    int total_price = 0;

    // name에 있으면 is_exist 카운트
    int is_exist = 0;
    for (int i = 0; i < cnt; i++)
    {
        if (my_strcmp((list + i)->name, temp) == 0)
            is_exist += 1;
    }
    for (int i = 0; i < cnt; i++) // is_exist > 0이면 total price 계산
    {
        if (is_exist > 0)
            total_price += (list + i)->price;
    }

    // 메모리 해제
    for (int i = 0; i < cnt; i++)
    {
        free((list + i)->name);
    }
    free(list);
    free(p);

    printf("\n%d\n", total_price);
}