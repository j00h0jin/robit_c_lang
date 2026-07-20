// MxN 입력 받아 중앙부터 아래 한칸 후 반시계로 돌기(M, N 홀수)
// 동적할당 사용
// 아래 > ++ > +- > -- > -+
// 끝에 닿으면 조건에 따라 이동
// 시작 위치(중앙)
// 중앙 행, 열에서 꺾

#include <stdio.h>
#include <stdlib.h>

void main()
{
    int **arr;
    int n, m;

    printf("input n : ");
    scanf(" %d", &n);
    printf("input m : ");
    scanf(" %d", &m);

    arr = (int **)malloc(sizeof(int *) * m);
    for (int i = 0; i < m; i++)
    {
        // 배열을 0으로 초기화(calloc)
        arr[i] = (int *)calloc(n, sizeof(int));
    }

    int k = 1;
    int center_m = m / 2, center_n = n / 2; // 중앙
    int i = center_m, j = center_n;
    int temp = 0;

    // 로직
    *(*(arr + i) + j) = k++;

    while (k <= m * n)
    {
        // 아래가 비어있다면 한칸 내리기
        if (i + 1 < m && *(*(arr + i + 1) + j) == 0)
        {
            i++;
            *(*(arr + i) + j) = k++;
        }

        // ++
        while (j < center_n && k <= m * n)
        {
            // ++ 이동
            if (i + 1 < m)
                i++;
            if (j + 1 < n)
                j++;

            // 해당 칸이 이미 차있다면 이동하기
            while (*(*(arr + i) + j) != 0)
            {
                // 배열 크기를 초과하는 경우 벽을 긁도록 함
                if (j + 1 < n)
                    j++;
                else if (i + 1 < m)
                    i++;
                else
                    break;
            }
            // 이동한 칸이 차있다면 break
            if (*(*(arr + i) + j) != 0)
                break;
            // 이동한 칸이 빈칸인 경우 채우기
            *(*(arr + i) + j) = k++;
        } // 이하 로직 동일(방향만 다름)

        // +-
        while (i > center_m && k <= m * n)
        {
            if (i - 1 >= 0)
                i--;
            if (j + 1 < n)
                j++;

            while (*(*(arr + i) + j) != 0)
            {
                if (j + 1 < n)
                    j++;
                else if (i - 1 >= 0)
                    i--;
                else
                    break;
            }
            if (*(*(arr + i) + j) != 0)
                break;

            *(*(arr + i) + j) = k++;
        }

        // --
        while (j > center_n && k <= m * n)
        {
            if (i - 1 >= 0)
                i--;
            if (j - 1 >= 0)
                j--;

            while (*(*(arr + i) + j) != 0)
            {
                if (j - 1 >= 0)
                    j--;
                else if (i - 1 >= 0)
                    i--;
                else
                    break;
            }
            if (*(*(arr + i) + j) != 0)
                break;

            *(*(arr + i) + j) = k++;
        }

        // -+
        while (i < center_m && k <= m * n)
        {
            if (i + 1 < m)
                i++;
            if (j - 1 >= 0)
                j--;

            while (*(*(arr + i) + j) != 0)
            {
                if (j - 1 >= 0)
                    j--;
                else if (i + 1 < m)
                    i++;
                else
                    break;
            }
            if (*(*(arr + i) + j) != 0)
                break;

            *(*(arr + i) + j) = k++;
        }
    }

    printf("\n");
    // 출력
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%3d ", arr[i][j]);
        }
        printf("\n");
    }

    // 메모리 해제
    for (int i = 0; i < m; i++)
    {
        free(arr[i]);
    }
    free(arr);
}