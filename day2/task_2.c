// 선택 정렬
// 정렬 된 부분 / 안 된 부분 구분한 뒤
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

    for (int i = 0; i < 8; i++)
    {
        printf("%2d ", arr[i]);
    }
    printf("\n");

    int last = 7;
    int k = 0;

    while (last > 0)
    {
        temp = arr[0];

        for (int i = 1; i <= last; i++)
        {
            if (temp < arr[i])
            {
                temp = arr[i];
                k = i;
            }
        }

        printf("%d\n", k);

        max = temp;
        printf("%d ", max);
        temp = arr[last];
        printf("%d ", temp);
        arr[last] = max;
        printf("%d ", arr[last]);
        arr[k] = temp;
        printf("%d\n", arr[k]);

        // if k = last => skip

        for (int i = 0; i < 8; i++)
        {
            printf("%2d ", arr[i]);
        }
        printf("\n");

        last -= 1;
    }
}