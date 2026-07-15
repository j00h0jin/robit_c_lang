// 윤년 판단
// 4의 배수 and (100의 배수 아닐 때 or 400의 배수일 때)
// ex) 2500 윤년 아님, 2400 윤년

#include <stdio.h>

void main()
{

    int year;

    printf("연도 입력 : ");
    scanf("%d", &year);

    if ((year % 4) == 0 && (!((year % 100) == 0) || ((year % 400) == 0)))
        printf("윤년입니다.");
    else if (year > 0)
        printf("윤년이 아닙니다.");
}