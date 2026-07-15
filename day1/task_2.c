// 피보나치 출력 (n0 = 0, n1 = 1, n2 = 1, 2, 3, 5 ...)
// n을 받으면 F(n) = F(n-1) + F(n-2) (n 2 이상)

#include <stdio.h>

void main()
{

    int n;
    int Fn, Fn1 = 1, Fn2 = 0;

    printf("n : ");
    scanf("%d", &n);

    if (n == 0)
        printf("0");
    else if (n == 1)
        printf("1");
    else
    {
        n -= 1;

        while (1)
        {
            if (n == 0)
            {
                printf("%d", Fn);
                return;
            }

            Fn = Fn1 + Fn2;

            Fn2 = Fn1;
            Fn1 = Fn;

            n -= 1;
        }
    }
}