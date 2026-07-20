// 모래 시계

#include <stdio.h>
#include <stdlib.h>

void main()
{
    int arr[5][5] = {0};

    int k = 1;

    for (int i = 0; i < 5; i++)
    {
        // 중앙(3번째 줄)으로부터 얼마나 떨어졌는지
        int d = abs(2 - i);

        for (int j = 2 - d; j <= 2 + d; j++)
        {
            arr[i][j] = k;
            k++;
        }
    }

    // 출력
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%2d ", arr[i][j]);
        }
        printf("\n");
    }
}