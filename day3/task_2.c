#include <stdio.h>
#include <stdlib.h>

void main()
{
    int arr[4][3] = {0};

    int k = 1;

    for (int i = 0; i < 4; i++)
    {

        for (int j = 0; j < 3; j++)
        {
            arr[i][j] = k;
            k++;
        }
    }

    // 출력
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%2d ", arr[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    // 출력 2
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%2d ", arr[j][i]);
        }
        printf("\n");
    }
}