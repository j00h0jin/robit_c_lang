// 5개의 실수를 입력받아 평균과 최댓값, 최솟값을 출력하는 프로그램
// n번째 실수를 입력하시오. (input)
// --- 결과 ---
// 평균은 a 입니다.
// 최댓값은 b 입니다.
// 최솟값은 c 입니다.

#include <stdio.h>

void main()
{
    float arr[5];
    float avg, max, min, temp;

    for (int i = 1; i < 6; i++)
    {
        printf("%d번째 실수를 입력하시오. ", i);
        scanf(" %f", &arr[i - 1]);
    }

    for (int i = 0; i < 5; i++)
    {
        temp += arr[i];
    }

    avg = temp / 5;

    temp = arr[0];
    for (int i = 1; i < 5; i++)
    {
        if (temp < arr[i])
            temp = arr[i];
    }
    max = temp;

    temp = arr[0];
    for (int i = 1; i < 5; i++)
    {
        if (temp > arr[i])
            temp = arr[i];
    }
    min = temp;

    printf("--- 결과 ---\n");
    printf("평균은 %f 입니다.\n최댓값은 %f 입니다.\n최솟값은 %f 입니다.", avg, max, min);
}