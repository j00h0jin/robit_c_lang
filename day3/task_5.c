// MxN 입력 받아 대각선 숫자 채우고 출력
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

    // 55
    // i j
    // 00
    // 01 10
    // 02 11 20
    // 03 12 21 30
    // 04 13 22 31 40
    // 14 23 32 41
    // 24 33 42
    // 34 43
    // 44

    // 4 5(5x4)
    // i j
    // 00
    // 01 10
    // 02 11 20
    // 03 12 21 30
    // 04 13 22 31
    // 14 23 32
    // 24 33
    // 34

    // 5 4 (4x5)
    // i j
    // 00
    // 01 10
    // 02 11 20
    // 03 12 21 30
    // 13 22 31 40
    // 23 32 41
    // 33 42
    // 43

    // 패턴 분석: 같은 줄에서 i는 늘어나고 j는 줄어듦
    // i가 y 크기만큼이 오거나, j가 0까지 오는 경우 다음 줄로 이동
    for (; j < x && k <= x * y; j++)
    {
        temp = 0;
        while (i + temp < y && j - temp >= 0 && k <= x * y)
        {
            *(*(arr + i + temp) + j - temp) = k;
            k++, temp++;
        }
    }
    i++, j--;
    for (; i < y && k <= x * y; i++)
    {
        temp = 0;
        while (i + temp < y && j - temp >= 0 && k <= x * y)
        {
            *(*(arr + i + temp) + j - temp) = k;
            k++, temp++;
        }
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