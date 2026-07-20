// 5x5 [0][0] == 1 시계방향 소용돌이 채우기
// 동적할당 사용

#include <stdio.h>
#include <stdlib.h>

void main()
{
    int **arr;
    int x, y;

    printf("input x : ");
    scanf(" %d", &x);
    printf("input y : ");
    scanf(" %d", &y);

    // sizeof(int*) = 8byte, sizeof(int) = 4byte
    arr = (int **)malloc(sizeof(int *) * y);
    for (int i = 0; i < y; i++)
    {
        arr[i] = (int *)malloc(sizeof(int) * x);
    }

    int k = 1;
    int i = 0, j = 0;
    int temp = 0;

    // 좌 -> 하 -> 우 -> 상 반복
    while (k <= x * y)
    {
        for (; j < x - temp && k <= x * y; j++)
        {
            *(*(arr + i) + j) = k;
            k++;
        }
        j--, i++; // 양의 y축에서 반시계
        for (; i < y - temp && k <= x * y; i++)
        {
            *(*(arr + i) + j) = k;
            k++;
        }
        j--, i--;
        for (; j >= 0 + temp && k <= x * y; j--)
        {
            *(*(arr + i) + j) = k;
            k++;
        }
        j++, i--;
        for (; i >= 1 + temp && k <= x * y; i--)
        {
            *(*(arr + i) + j) = k;
            k++;
        }
        j++, i++;
        temp++;
    }

    printf("\n");
    // 출력
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            printf("%3d ", arr[i][j]);
        }
        printf("\n");
    }

    // 메모리 해제
    for (int i = 0; i < y; i++)
    {
        free(arr[i]);
    }
    free(arr);
}