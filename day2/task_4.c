// N, B, 수열(A)
// 1부터 N까지 자연수가 들어있는 수열 A
// 각 자연수는 한번씩만 들어가고, A는 앞, 뒤 숫자를 자를 수 있음
// 중앙값이 B인 부분 수열의 개수를 구하는 프로그램
// ex) N = 7, B = 4, A = {1, 2, 3, 5, 6, 4, 7}
// 일 때 4가 중앙값인 A의 부분 수열 가능 경우의 수
// *중앙값이 있으려면 홀수개(자기 자신, + 전체 포함)
// A' = {1, 2, 3, 5, 6, 4, 7}, {2, 3, 5, 6, 4}, {4} 3개

// 입력 개수 제한 숫자 100개(임의)

#include <conio.h>
#include <stdio.h>

void main()
{
    while (1)
    {

        int n, b, bIdx, answer = 0;
        int arr[100] = {
            0,
        };
        int isExist[101] = {
            0,
        };

        printf("N : ");
        scanf(" %d", &n);

        // N 범위 검사
        if (n < 1 || n > 100)
        {
            printf("100>=N>=1");
            return;
        }

        printf("B : ");
        scanf(" %d", &b);

        // B 범위 검사
        if (b > n || b < 1)
        {
            printf("N>=B>=1");
            return;
        }

        // 배열 받기
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &arr[i]);
        }

        // 1 ~ N까지의 자연수가 입력되었는지 확인함
        // isExist[i] == 0인 경우 배열에 해당 자연수가 없음
        for (int i = 0; i < n; i++)
        {
            if (n >= arr[i] && arr[i] >= 0)
                isExist[arr[i]] = 1;
        };

        // 1 ~ N까지 자연수가 하나라도 입력되지 않은 경우
        for (int i = 1; i <= n; i++)
        {
            if (isExist[i] == 0)
            {
                printf("1~N까지의 정수가 한번씩 입력되어야 합니다");
                return;
            }
        }

        printf("\n");

        // B의 index 찾기
        for (int i = 0; i < n; i++)
        {
            if (arr[i] == b)
            {
                bIdx = i;
                break;
            }
        }
        // 여기부터 부분 수열을 찾는 로직까지 로직이 너무 안떠올라서 LLM 활용함(87 ~ 134줄)
        // cnt 200 => 배열이 최대 100이므로
        // B값을 기준으로 왼쪽 최대 99개(cnt[1~99]) + 오른쪽 최대 99개[101~199] + 자기 자신(cnt[100])
        // cnt[0]은 사용 안함(편의상)
        int cnt[200] = {
            0,
        };
        int offset = 100; // 기준(B)

        // 정렬했을 때 중앙값이 B인 수열의 개수 조건
        // {B}, B보다 큰 수의 개수 = B보다 작은 수의 개수(ex {B+K, B, B=K})
        // current_sum => B를 기준으로 B~해당 인덱스까지 사이에 B보다 큰 수가 있다면 +1, 작은 수가 있다면 -1
        // ex) B는 3이고 S = {4, 1, 2, 3, 5}라면
        // S[0] => current_sum = -1(4, 1, 2), S[1] => current_sum = -2(1, 2),
        // S[2] => current_sum = -1(1), S[3] => current_sum = 0, S[4] => current_sum = 1(5)
        int current_sum = 0;
        cnt[current_sum + offset]++; // 자기 자신{B}만 있는 경우 count

        // B기준 왼쪽 검사 실행
        for (int i = bIdx - 1; i >= 0; i--)
        {
            if (arr[i] > b)
                current_sum++;
            else if (arr[i] < b)
                current_sum--;

            cnt[current_sum + offset]++;
        }
        // cnt[98] == 1, cnt[99] == 2, cnt[100] == 1({B})
        // 왼쪽 검사 결과 B보다 작은 수가 2개(100-2) 있는 경우가 1번
        // 작은 수가 1(100-1)개 있는 경우가 2번

        // B기준 오른쪽 검사 후 조건 성립 시 answer에 기록
        current_sum = 0;
        for (int i = bIdx; i < n; i++)
        {
            if (i > bIdx)
            {
                if (arr[i] > b)
                    current_sum++;
                else if (arr[i] < b)
                    current_sum--;
            }

            // 오른쪽 검사 중 현재 index에서 crnt_sum값이 n이라면 왼쪽으로 -n만큼 있어야 성립
            // ex) {4, 1, 2, 3, 5} 기준으로 S[4] => currrent_num == 1
            // 따라서 -1인 경우(cnt[99])의 값이 경우의 수가 됨
            int target_left_sum = -current_sum;

            // B보다 큰 수의 개수 = B보다 작은 수의 개수가 성립하면 answer에 기록
            answer += cnt[target_left_sum + offset];
        }

        printf("중앙값이 %d인 부분 수열의 개수 : %d", b, answer);

        // day1 task 4 코드 활용
        int any = -1;
        printf("\n\n계속하려면 아무 키나 누르십시오 . . .");
        // _getch(): 단일 문자 하나를 즉시 입력받는 함수
        // 값 범위 0 ~ 255
        any = _getch();

        while (any == -1)
        {
            // _getch() 값이 들어오기 전까지
            // 빈 코드를 돌려서 버퍼를 줌
        }
        printf("\n\n");
    }
}