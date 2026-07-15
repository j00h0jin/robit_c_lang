// 값을 입력하세요.
// 나비 모양 출력
// ex 1 **
// 2n-1줄 (n번째 줄 기점으로 리버스)
// 줄당 2n개 (공백 + 별 개수)
// 줄당 별 1++, 공백 1--

#include <stdio.h>

void main()
{
    int n;
    printf("값을 입력하세요. ");
    scanf(" %d", &n);

    // 줄 개수
    for (int i = 1; i <= 2 * n - 1; i++)
    {
        if (i > n)
        {
            // 리버스 이후 별 개수 2n - i개
            // ex)n = 4, 6번째 줄 별 개수 => 8 - 6 = 2개
            for (int j = 0; j < 2 * n - i; j++)
                printf("*");

            // 리버스 이후 공백은 개수는 대칭을 이루기 때문에 k식에 (-) 곱해줌
            for (int k = i - n; k > 0; k--)
                printf("  "); // 공백 2번

            for (int j = 0; j < 2 * n - i; j++)
                printf("*");
            printf("\n");
            continue;
        }

        // 별은 리버스 이전 n번째 줄 => 별 n개만큼 찍기
        for (int j = 0; j < i; j++)
            printf("*");

        // 공백 최대 개수는 n-1개부터 1씩 줄어서 최소 0까지
        for (int k = n - i; k > 0; k--)
            printf("  "); // 공백 2번(대칭이기 때문에)

        for (int j = 0; j < i; j++)
            printf("*");

        printf("\n");
    }
}