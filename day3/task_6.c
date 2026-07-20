// MxN 입력 받아 중앙부터 아래 한칸 후 반시계로 돌기(ppt 참조)
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

    // 로직

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