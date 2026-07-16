// N, B, 수열(A)
// 1부터 N까지 자연수가 들어있는 수열 A
// 각 자연수는 한번씩만 들어가고, A는 앞, 뒤 숫자를 자를 수 있음
// 중앙값이 B인 부분 수열의 개수를 구하는 프로그램
// ex) N = 7, B = 4, A = {1, 2, 3, 5, 6, 4, 7}
// 일 때 4가 중앙값인 A의 부분 수열 가능 경우의 수
// *중앙값이 있으려면 홀수개만 남겨야 함
// A' = {2, 3, 5, 6, 4} 1개

// 입력 개수 제한 숫자 10개(임의)

#include <stdio.h>

void main()
{
    int n, b;
    char arr[100];

    printf("N : ");
    scanf(" %d", &n);

    printf("B : ");
    scanf(" %d", &b);

    printf("\n");

    scanf(" %s", &arr);

    for (int i = 0; i < 7; i++)
    {
        printf("%2d ", arr[i]);
    }
    printf("\n");
}