// 동적할당, 배열 값의 max, min, sum, avg 출력

#include <stdio.h>
#include <stdlib.h>

void main()
{
    int *arr;
    int x;

    printf("몇 개의 원소를 할당하겠습니까? : ");
    scanf(" %d", &x);

    // x개만큼 할당
    arr = (int *)malloc(sizeof(int) * x);

    for (int j = 0; j < x; j++)
    {
        printf("정수형 데이터 입력 : ");
        scanf(" %d", arr + j);
    }

    int max, min, sum = 0;
    float avg;

    // max 구하기
    max = *(arr + 0);
    for (int i = 1; i < x; i++)
    {
        if (*(arr + i) > max)
        {
            max = *(arr + i);
        }
    }

    // min 구하기
    min = *(arr + 0);
    for (int i = 1; i < x; i++)
    {
        if (*(arr + i) < min)
        {
            min = *(arr + i);
        }
    }

    // sum 구하기
    for (int i = 0; i < x; i++)
    {
        sum += *(arr + i);
    }

    // sum -> float 변환 후 avg 구하기
    avg = (float)sum / x;

    // 출력
    printf("최댓값 : %d\n", max);
    printf("최솟값 : %d\n", min);
    printf("전체합 : %d\n", sum);
    printf("평  균 : %f\n", avg);

    free(arr);
}