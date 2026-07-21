/*
동적할당 메모리 "최소화"
물품 개수
(물품 가격) x 개수 -> 구조체 저장
마지막에 string 입력
위에 입력 했던 물품인 경우 금액 합계
아닌 경우 0
*/

typedef struct _Info
{
    char name[10];
    int price;
} Info;

#include <stdio.h>
#include <stdlib.h>

void main()
{
    int cnt;
    scanf("%d ", &cnt);

    // input값만큼 좌표 list 동적할당
    Info *list;
    list = (Info *)malloc(sizeof(Info) * cnt);

    // input 개수만큼 x y 좌표 받기
    for (int i = 0; i < cnt; i++)
    {
        scanf(" %s %d", list[i].name, &list[i].price);
    }

    char last_name[10];
    scanf(" %s", last_name);
}