/*
void print(int *row, int *col, int **pArr) 함수 사용
void arr_ij(int *sizeRow, int *sizeCol, int **pArr) 함수 사용
(달팽이 만드는 함수)
*/

void print(int *row, int *col, int **pArr);
void arr_ij(int *sizeRow, int *sizeCol, int **pArr);

#include <stdio.h>
#include <stdlib.h>

void main()
{
    int **arr = NULL;
    int row, col, sizeRow, sizeCol;

    printf("행의 수를 입력하세요: ");
    scanf(" %d", &sizeRow);
    printf("열의 수를 입력하세요: ");
    scanf(" %d", &sizeCol);

    row = sizeRow;
    col = sizeCol;

    // 동적 메모리 할당
    // sizeof(int*) = 8byte, sizeof(int) 4byte
    arr = (int **)malloc(sizeof(int *) * row);
    for (int i = 0; i < row; i++)
    {
        arr[i] = (int *)malloc(sizeof(int) * col);
    }

    arr_ij(&sizeRow, &sizeCol, arr);

    // 메모리 해제
    for (int i = 0; i < row; i++)
    {
        free(arr[i]);
    }
    free(arr);

    return;
}

void print(int *row, int *col, int **pArr)
{
    int r = *row;
    int c = *col;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("%3d ", *(*(pArr + i) + j));
        }
        printf("\n");
    }
}

void arr_ij(int *sizeRow, int *sizeCol, int **pArr)
{
    int r = *sizeRow;
    int c = *sizeCol;
    int size = r * c;
    int i = 0, j = 0, temp = 0, k = 1;

    while (k <= size)
    {
        while (j < c - temp && k <= size)
        {
            *(*(pArr + i) + j) = k++;
            j++;
        }
        j--, i++;
        while (i < r - temp && k <= size)
        {
            *(*(pArr + i) + j) = k++;
            i++;
        }
        j--, i--;
        while (j >= 0 + temp && k <= size)
        {
            *(*(pArr + i) + j) = k++;
            j--;
        }
        j++, i--;
        while (i >= 1 + temp && k <= size)
        {
            *(*(pArr + i) + j) = k++;
            i--;
        }
        j++, i++;
        temp++;
    }

    printf("\n");
    // arr_ij에서 받아온 값이 포인터이므로 그대로 넣어줌
    print(sizeRow, sizeCol, pArr);
}