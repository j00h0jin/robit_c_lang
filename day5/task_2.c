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
    // day 3 task 3 로직 활용
    int r = *sizeRow;
    int c = *sizeCol;
    int size = r * c;
    int i = 0, j = 0, temp = 0, k = 1;

    while (k <= size)
    {
        // 우
        while (j < c - temp && k <= size) // 우측 끝까지 && k가 size보다 같거나 작을 때
        {
            *(*(pArr + i) + j) = k++; // 해당 칸에 k를 채우고 k++;
            j++;                      // 우로 이동
        }
        j--, i++;
        // 하
        while (i < r - temp && k <= size) // 하단 끝까지 && k가~(위 동일)
        {
            *(*(pArr + i) + j) = k++;
            i++; // 하로 이동
        }
        // 좌
        j--, i--;
        while (j >= 0 + temp && k <= size) // 좌측 끝까지 && k가~
        {
            *(*(pArr + i) + j) = k++;
            j--; // 좌로 이동
        }
        // 상
        j++, i--;
        while (i >= 1 + temp && k <= size) // 상단 끝까지 && k가~
        {
            *(*(pArr + i) + j) = k++;
            i--; // 상으로 이동
        }
        j++, i++;
        // 한 바퀴를 돌았다면 temp++ (이전 사이클보다 상하좌우가 한칸씩 줄었으므로)
        temp++;
    }
    /*
    ex)
    5 by 5
    (k가 움직이면 원래 있던 자리에 숫자가 채워짐)
    k0000
    00000
    00000
    00000
    우측 끝까지 이동
    =>
    12345k
    00000
    00000
    00000
    j--,i++ // 숫자 채우지 않고 이동 좌 1칸, 하 1칸

    =>
    12345
    0000k
    00000
    00000
    하단 끝까지 이동

    ...
    */

    printf("\n");
    // arr_ij에서 받아온 값이 포인터이므로 그대로 넣어줌
    print(sizeRow, sizeCol, pArr);
}