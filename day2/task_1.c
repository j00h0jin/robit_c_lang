// 길이와 종류 받아서 별 출력
// 함수 이용
// 종류1 -> 오른쪽 바라보는 삼각형
// 종류2 -> 왼쪽 바라보는 삼각형
// 종류3 -> 모래 시계
// 종류4 -> \ 로 기울어진(?) 모래시계
// 삼각형 구현이라 length가 홀수인 경우
// ex length = 4일 때
// *
// **
// **
// *
// 위처럼 구현하기 vs 홀수만 받기
// 홀수만 받기로 결정(모양이 안 예쁨)
// 짝수도 받는 경우에 center를 2번 구현하면 됨
// 함수는 하나의 함수에 1가지 기능만 작동하도록 설계

#include <stdio.h>

// 순서대로 종류 1, 2, 3, 4
void rightTriangle(int length);

void leftTriangle(int length);

void hourGlass(int length);

void tilltedHourGlass(int length);

void main()
{
    int length, kind;

    printf("자연수만 입력 가능, 길이는 홀수만, 종류 1 ~ 4 중 택 1\n");
    printf("사이즈와 종류를 입력하세요: ");
    scanf(" %d %d", &length, &kind);

    if ((length < 1) || (kind < 1)) //
    {
        printf("자연수(양의 정수)만 입력\n");
        return;
    }
    else if (length % 2 == 0)
    {
        printf("길이는 홀수만 입력\n");
        return;
    }

    switch (kind)
    {
    case 1:
        rightTriangle(length);
        break;

    case 2:
        leftTriangle(length);
        break;

    case 3:
        hourGlass(length);
        break;

    case 4:
        tilltedHourGlass(length);
        break;

    default: // kind 1 ~ 4 외 입력 시 예외처리
        printf("종류 값 잘못 입력");
        return;
    }
}

void rightTriangle(int length)
{
    // day 1 task 5 로직을 살려서 쓰려고 center값을 지정하였음
    int center = (int)(length / 2) + 1;

    for (int n = 1; n <= length; n++)
    {
        if (n <= center)
        {
            for (int i = 0; i < n; i++)
                printf("*");
            // 왼쪽 정렬이라 공백 없어도 되나 종류 2 구현에 재사용하기 쉽게 짬
            for (int j = 0; j < center - n; j++)
                printf(" ");
        }
        else // n > center
        {
            for (int i = 0; i < 2 * center - n; i++)
                printf("*");
            for (int j = 0; j < -center + n; j++)
                // center - (2 * center - n) = -center + n
                printf(" ");
        }

        printf("\n");
    }
}

void leftTriangle(int length)
{
    // day 1 task 5 로직을 살려서 쓰려고 center값을 지정하였음
    int center = (int)(length / 2) + 1;

    for (int n = 1; n <= length; n++)
    {
        if (n <= center)
        {
            for (int j = 0; j < center - n; j++)
                printf(" ");
            for (int i = 0; i < n; i++)
                printf("*");
        }
        else // n > center
        {
            for (int j = 0; j < -center + n; j++)
                // center - (2 * center - n) = -center + n
                printf(" ");
            for (int i = 0; i < 2 * center - n; i++)
                printf("*");
        }

        printf("\n");
    }
}

// 메모장 규칙 찾은 거
// ex)
// length = 5
// center 3
// *****
//  ***
//   *
//  ***
// *****

// n=1 *12345  3-2 ~ 3+2, c - (c - n) ~ c + (c - n)까지 별
// n=2 *234     3-1 ~ 3+1, c - (c - n) ~ c + (c - n)
// n=3 *3        3+0 ~ 3+0, c - (c - n) ~ c + (c - n))
// n=4 *234      4 - 2 = 2, n - 2(n-c)
// n=5 *12345  5 - 4 = 1, n - 2(n-c) => 5 -10 +6 = 1, 규칙 n-2(n-c) ~ n까지 별

void hourGlass(int length)
{

    int center = (int)(length / 2) + 1;

    for (int n = 1; n <= length; n++)
    {
        if (n <= center)
        {
            for (int i = 1; i <= length; i++)
            {
                if (i >= n && i <= 2 * center - n)
                // center - (center - n) = n, center + (center - n) = 2center - n
                {
                    printf("*");
                    continue;
                }
                printf(" ");
            }
        }
        else
        {
            for (int i = 1; i <= length; i++)
            {
                if (i >= -n + 2 * center && i <= n)
                //  n - 2 * (n - center) = -n + 2center
                {
                    printf("*");
                    continue;
                }
                printf(" ");
            }
        }

        printf("\n");
    }
}

void tilltedHourGlass(int length) // HourGlass 코드 재활용
{
    int center = (int)(length / 2) + 1;

    for (int n = 1; n <= length; n++)
    {
        if (n < center)
        {
            for (int i = 1; i <= length; i++)
            {
                if (i >= n && i <= center)
                // center - (center - n) = n, center + (center - n) = 2center - n
                {
                    printf("*");
                    continue;
                }
                printf(" ");
            }
        }
        else
        {
            for (int i = 1; i <= length; i++)
            {
                if (i >= center && i <= n)
                //  n - 2 * (n - center) = -n + center
                {
                    printf("*");
                    continue;
                }
                printf(" ");
            }
        }

        printf("\n");
    }
}