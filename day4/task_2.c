/*
동적할당 좌표 수 + 좌표 입력 받기
좌표는 구조체에 저장

좌표 사이의 거리 중 거리가 가장 긴 좌표?

자기 자신 제외한 다른 점들의 두 점 사이의 거리의 합이 가장 큰 좌표인 것 같다
*/

typedef struct _Coordinate
{
    int x;
    int y;
} Coordinate;

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void main()
{
    int cnt;
    scanf("%d ", &cnt);

    Coordinate *list;
    list = (Coordinate *)malloc(sizeof(Coordinate) * cnt);

    for (int i = 0; i < cnt; i++)
    {
        scanf(" %d %d", &list[i].x, &list[i].y);
    }

    float d_total = 0;
    float d_max = 0;
    int m;

    for (int i = 0; i < cnt; i++)
    {
        d_total = 0;
        for (int j = 0; j < cnt; j++)
        {
            float squareXY = pow((list + j)->x - (list + i)->x, 2) + pow((list + j)->y - (list + i)->y, 2);
            d_total += sqrt(squareXY);
        }
        if (d_total > d_max)
        {
            d_max = d_total;
            m = i;
        }
    }

    printf("가장 거리가 먼 좌표는 (%d, %d)이며, ", (list + m)->x, (list + m)->y);
    printf("다른 좌표의 거리 총합은 약 %.1f입니다.", d_max);

    free(list);
}