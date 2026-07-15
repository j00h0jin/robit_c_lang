// 별 출력
// 속이 빈 트리(삼각형)
// n줄 출력, 별 + 공백 = 2n - 1
// 첫번째 줄 별은 항상 n번째, 별이 나오기 전 공백 n-i개, 사이 공백 0개
// 2번째 줄 별은 항상 n-1, n+1, 공백 n-i개, 별 사이 공백 2i-3개
// 3번째 줄 별은 항상 n-2, n+2, 공백 n-i개 별 사이 공백 2i-3개
// 공백 n-i개, 시작 별 + 별 사이 공백 + 별 추가, 공백 n-i개s
// i...번째 줄에서 n+(i-1)이 2n-1과 동일해졌을 때 전부 별, 공백 0(n-i)개
// 첫번째, 마지막 줄만 로직 따로 그 사이 공통 로직

#include <stdio.h>

void main()
{
    int n;
    printf("값을 입력하세요. ");
    scanf(" %d", &n);

    // 줄 n개 출력
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < n - i; j++)
            printf(" ");

        // 첫번째, 마지막 제외 로직
        if (n > i && i > 1)
        {
            printf("*");
            // 별 사이 공백 2i-3개만큼 출력
            for (int k = 0; k < 2 * i - 3; k++)
                printf(" ");

            printf("*");
        }
        else if (i == 1)
        { // 첫번째는 별 하나만
            printf("*");
        }
        else if (i == n)
        { // 마지막은 전부 별
            for (int j = 0; j < 2 * i - 1; j++)
                printf("*");
        }
        for (int j = 0; j < n - i; j++)
            printf(" ");

        printf("\n");
    }
}