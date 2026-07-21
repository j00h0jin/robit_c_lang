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

    // 보기가 3x4 배열이여서 최대 12개가 들어가는 pattern 선언
    int pattern[12] = {0};
    // 패턴에 몇개의 숫자가 들어갔는지 확인
    int idx = 0;

    // 숫자는 양의 정수(자연수)라 가정
    while (pattern[11] == 0)
    {
        int input_num;
        printf("input: ");
        scanf(" %d", &input_num);

        // 패턴에 해당 숫자 추가해줌
        pattern[idx++] = input_num;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                int k = i * 4 + j;                    // k는 현재 위치
                *(*(arr + i) + j) = pattern[k % idx]; // k % idx로 패턴이 무한으로 돌게 해줌
            }
        }

        printf("\n");

        // 출력
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