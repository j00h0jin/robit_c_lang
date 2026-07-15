// 사칙 연산과 거듭 제곱 계산기 ( + - * / ^n )
// input값: a 기호 b
// 식 = 결과 형식으로 출력
// 계속 진행
// 예외 처리 0으로 나누기, 거듭 제곱 정수형

#include <conio.h>
#include <stdio.h>

void main()
{

    float a, b, answer;
    char sign;

    printf("Input Arithmetic Operation\n");
    printf("ex)\t3.4 * 8.5\n");
    printf("   \t2.9 - 5.4\n");
    printf("   \t3.9 / 8.0\n");
    printf("   \t3.9 ^ 8\n");
    while (1)
    {
        printf("input : ");
        scanf(" %f %c %f", &a, &sign, &b);

        switch (sign)
        {
        case '+':
            answer = a + b;
            break;

        case '-':
            answer = a - b;
            break;

        case '*':
            answer = a * b;
            break;

        case '/':
            if (b == 0)
            {
                printf("0으로 나눌 수 없음");
                return;
            }
            answer = a / b;
            break;

        case '^': {
            int int_b = (int)b;
            if (b - int_b == 0)
            {
                answer = 1;
                for (int i = 0; i < b; i++)
                    answer *= a;
                break;
            }
            else
                printf("거듭 제곱의 지수는 정수만 입력 가능");
            return;
        }
        default:
            printf("잘못된 기호 입력");
            return;
        }

        printf("%.2f %c %.2f = %.2f", a, sign, b, answer);

        int any = -1;
        printf("\n계속하려면 아무 키나 누르십시오 . . .");
        // _getch(): 단일 문자 하나를 즉시 입력받는 함수
        // 값 범위 0 ~ 255
        any = _getch();

        while (any == -1)
        {
            // _getch() 값이 들어오기 전까지
            // 빈 코드를 돌려서 버퍼를 줌
        }
        printf("\n");
    }
}