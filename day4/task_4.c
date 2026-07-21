/*
중첩 구조체 사용
현재 날짜, 시각
2개의 날짜 시간 입력 받은 뒤
그 차이를 시 분 초로 출력
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int year, month, day;
} DATE;

typedef struct
{
    int hour, min, sec;
} TIME;

typedef struct
{
    DATE date;
    TIME Time;
} TIMESTAMP;

void main()
{
    TIMESTAMP list[2];

    for (int i = 0; i < 2; i++)
    {
        scanf(" %d %d %d %d %d %d", &list[i].date.year, &list[i].date.month, &list[i].date.day, &list[i].Time.hour,
              &list[i].Time.min, &list[i].Time.sec);
    }

    unsigned long long time1 = 0, time2 = 0, gap;

    // 1년 = 360, 1개월 = 30일로 잡고 계산
    int year = 12, month = 30, day = 24, hour = 60, min = 60;
    int year_to_sec = year * month * day * hour * min;
    int month_to_sec = month * day * hour * min;
    int day_to_sec = day * hour * min;
    int hour_to_sec = hour * min;
    int min_to_sec = min;

    // 날짜를 초로 환산하여 계산
    time1 = (list + 0)->date.year * year_to_sec + (list + 0)->date.month * month_to_sec +
            (list + 0)->date.day * day_to_sec + (list + 0)->Time.hour * hour_to_sec +
            (list + 0)->Time.min * min_to_sec + (list + 0)->Time.hour;

    time2 = (list + 1)->date.year * year_to_sec + (list + 1)->date.month * month_to_sec +
            (list + 1)->date.day * day_to_sec + (list + 1)->Time.hour * hour_to_sec +
            (list + 1)->Time.min * min_to_sec + (list + 1)->Time.hour;

    // 더 뒤의 날짜(time이 더 큰 쪽)에서 앞의 날짜를 빼줌
    if (time1 >= time2)
        gap = time1 - time2;
    else
        gap = time2 - time1;

    int gap_h = 0, gap_m = 0, gap_s = 0;
    gap_s = gap;

    // printf("\n%d\n", gap_s);

    // gap_s가 60초 미만이 될 때까지
    while (gap_s > 60)
    {
        // 1시간씩 count를 올리면 연산이 많아지므로 100시간 단위부터 검사
        if (gap_s > 3600 * 100)
        {
            gap_h += 100 * (gap_s / (3600 * 100));
            gap_s = gap_s % (3600 * 100);
        }
        else if (gap_s > 3600 * 10) // 10시간
        {
            gap_h += 10 * (gap_s / (3600 * 10));
            gap_s = gap_s % (3600 * 10);
        }
        else if (gap_s > 3600) // 1시간
        {
            gap_h += (gap_s / 3600);
            gap_s = gap_s % 3600;
        }
        else if (gap_s > 60 * 10) // 10분
        {
            gap_m += 10 * (gap_s / (60 * 10));
            gap_s = gap_s % (60 * 10);
        }
        else if (gap_s > 60) // 1분
        {
            gap_m += (gap_s / 60);
            gap_s = gap_s % (60);
        }
    }

    printf("\n%d시 %d분 %d초", gap_h, gap_m, gap_s);
}