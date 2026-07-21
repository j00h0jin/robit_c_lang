/*
3x4배열
숫자 하나 입력
ex) 3
3333
3333
3333

그 다음 숫자 5
3535
3535
3535

그 다음 1
3513
5135
1351

그 다음 4
3514
3514
3514
3514

...

포인터 사용
*/

#include <stdio.h>
#include <stdlib.h>

void main()
{
    int **arr;

    arr = (int **)malloc(sizeof(int *) * 3);
    for (int i = 0; i < 3; i++)
    {
        arr[i] = (int *)malloc(sizeof(int) * 4);
    }

    int pattern[12] = {0};

    while (pattern[12] == 0)
    {
        int idx = 0;
        int input_num;
        printf("input: ");
        scanf(" %d", &input_num);

        pattern[idx++] = input_num;

        int k = 0;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                *(*(arr + i) + j) = pattern[k <= idx ? k++ : k - idx];
            }
        }

        printf("\n");

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                printf("%d", *(*(arr + i) + j));
            }
            printf("\n");
        }

        printf("\n");
    }

    // 메모리 해제
    for (int i = 0; i < 3; i++)
    {
        free(arr[i]);
    }
    free(arr);
}