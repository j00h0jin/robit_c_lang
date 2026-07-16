// 소인수 분해 제곱 수 없는 경우 (제곱 ㄴㄴ 수)
// 입력 1 ~ 10000 정수

#include <conio.h>
#include <stdio.h>

void main()
{
    while (1)
    {
        int min, max;

        int arr[10000], isSquare = 0;

        printf("min : ");
        scanf(" %d", &min);

        printf("max : ");
        scanf(" %d", &max);

        if (min < 1 || max < 1 || min > 10000 || max > 10000 || min > max)
        {
            printf("ERROR: 입력 범위(1~10000 정수) 벗어남 or min > max");
            return;
        }

        // min ~ max의 숫자 판별
        for (int i = min; i <= max; i++)
        {
            int num = i;
            int cnt[100] = {
                0,
            };
            // 소인수분해 로직(1, 자기 자신 제외 cnt 기록)
            for (int j = 2; j * j <= num; j++)
            {
                while (num % j == 0)
                {
                    // 소인수 분해된 값을 cnt에 넣어줌
                    // ex) num이 2로 나누어졌다면 cnt[1]에 +1
                    cnt[j - 1] += 1;
                    num /= j;
                }
            }

            // 해당 숫자의 cnt를 읽음
            // cnt의 인덱스 중 하나가 2 이상이라는 건 같은 수가 2번 이상 곱해졌다는 뜻
            for (int k = 1; k < 100; k++)
            {
                if (cnt[k] > 1)
                {
                    arr[i - 1] = 1;
                    // arr에서 0이 아닌 값 or 1인 값을 읽어도 되지만 코드 길어져서 isSquare 사용
                    isSquare += 1;
                    break;
                }
            }
        }
        // answer = min ~ max 사이의 숫자 개수 - 제곱 수가 인수로 들어간 수
        int answer = (max - min + 1) - isSquare;

        printf("제곱 ㄴㄴ 수 : %d개\n", answer);
        for (int i = min; i <= max; i++)
        {
            if (arr[i - 1] == 0)
                printf("%d ", i);
        }
        printf("\n");

        // day1 task 4 코드 활용
        int any = -1;
        printf("계속하려면 아무 키나 누르십시오 . . .");
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