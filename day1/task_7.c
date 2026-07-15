// n, r을 입력받아 순열, 중복 순열, 조합, 중복 조합
// n, r값 정수
// 0 < r =< n
// 팩토리얼 값 -> unsigned long long으로 오버플로우 최대한 방지

#include <stdio.h>

int factorial(int num)
{
    unsigned long long result = 1;

    for (int i = 1; i <= num; i++)
    {
        result *= i;
    }
    return result;
}

void main()
{
    float n, r;
    unsigned long long answer;

    printf("순열, 중복 순열, 조합, 중복 조합 값 구하기");
    printf("\n입력값 예시) 4 2\n");

    printf("\nn과 r값을 입력해주세요 : ");
    scanf(" %f %f", &n, &r);

    int int_n = (int)n;
    int int_r = (int)r;

    if (r > n)
    {
        printf("r > n");
        return;
    }

    if (r < 1)
    {
        printf("\n0 < r =< n");
        return;
    }

    if (r - int_r == 0 && n - int_n == 0)
    {

        // 순열
        if (factorial(n - r) == 0)
        {
            printf("\n(n - r)! = 0");
            return;
        }
        answer = factorial(n) / factorial(n - r);
        printf("\n순열 값: %d", answer);

        // 중복 순열
        answer = 1;
        for (int i = 0; i < r; i++)
            answer *= n;
        printf("\n중복순열 값: %d", answer);

        // 조합
        if (factorial(n - r) * factorial(r) == 0)
        {
            printf("\n(n - r)!r! = 0");
            return;
        }
        answer = factorial(n) / (factorial(n - r) * factorial(r));
        printf("\n조합 값: %d", answer);

        // 중복 조합
        if (factorial(n - r) * factorial(r) == 0)
        {
            printf("\n(n-1)!r! = 0");
            return;
        }
        int combination_n = n + r - 1;
        answer = factorial(combination_n) / (factorial(combination_n - r) * factorial(r));
        printf("\n중복조합 값: %d", answer);
    }
    else
        printf("\n정수 값이 아님");
}