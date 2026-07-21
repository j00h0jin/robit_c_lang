/*
문장 입력
거꾸로 출력
최빈 문자 출력
포인터 이용
*/

#include <stdio.h>
#include <stdlib.h>

void main()
{
    char str[100]; // 크기 임의 지정
    char *p = str;

    printf("입력: ");
    scanf(" %[^\n]", str);

    // 문자열 길이 구하기
    int length = 0;
    for (int i = 0; i < 100; i++)
    {
        if (*(p + i) == '\0')
        {
            length = i;
            break;
        }
    }

    // 짝수 length/2, 홀수 (length-1)/2
    int center = length / 2;
    char temp;

    for (int i = 0; i < length / 2; i++)
    {
        temp = *(p + i);
        *(p + i) = *(p - (length - 1 - i));
        *(p - (length - 1 - i)) = temp;
    }

    printf("\n출력: ");
    for (int i = 0; i < length; i++)
    {
        printf("%c", *(p + i));
    }
}