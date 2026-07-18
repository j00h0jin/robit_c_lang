// 선택 정렬
// 정렬 안 된 부분에서 최댓값 지정

#include <stdio.h>

void main()
{
    int arr[8] = {
        0,
    };
    int temp, max;

    printf("입력\n");
    for (int i = 0; i < 8; i++)
    {
        printf("%d : ", i + 1);
        scanf(" %d", &arr[i]);
    }

    printf("\n");

    // 처음에 입력 값 출력
    for (int i = 0; i < 8; i++)
    {
        printf("%2d ", arr[i]);
    }
    printf("\n\n");

    int last = 7;

    while (last > 0)
    {
        // 항상 배열의 첫번째 수를 기준으로
        temp = arr[0];
        int k = 0;

        // 최댓값 찾기 (k는 최댓값의 인덱스 번호임)
        for (int i = 1; i <= last; i++)
        {
            if (temp < arr[i])
            {
                temp = arr[i];
                k = i;
            }
        }

        max = temp;
        // if (max = last) => skip
        // last는 정렬이 안된 수 중에 가장 마지막 index
        if (max == arr[last])
        {
            last -= 1;
            continue;
        }
        temp = arr[last];
        arr[last] = max;
        arr[k] = temp;

        for (int i = 0; i < 8; i++)
        {
            printf("%2d ", arr[i]);
        }
        printf("\n\n");

        last -= 1;
    }

    printf("출력\n");
    for (int i = 0; i < 8; i++)
        printf("%d : %2d\n", i + 1, arr[i]);
}