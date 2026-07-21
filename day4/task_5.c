/*
문장 입력
거꾸로 출력
최빈 문자 출력
포인터 이용
*/

#include <stdio.h>
#include <stdlib.h>

char lower(char c);
int get_length(const char *str);

void main()
{
    char str[100]; // 크기 임의 지정
    char *p = str;

    printf("입력: ");
    scanf(" %[^\n]", str);

    int length = get_length(str);

    char *start = str;
    char *end = str + length - 1;
    char temp;

    // 뒤집기(시작과 끝을 바꿈 (length / 2까지))
    for (int i = 0; i < length / 2; i++)
    {
        temp = *(start + i);
        *(start + i) = *(end - i);
        *(end - i) = temp;
    }

    // 거꾸로 출력
    printf("\n출력: ");
    for (int i = 0; i < length; i++)
    {
        printf("%c", *(p + i));
    }

    // 최빈문자 찾기
    int ascii[256] = {0};
    char *ascii_p = str;

    // 대문자 -> 소문자로 변경(ascii 비교를 위해)
    while (*ascii_p != '\0')
    {
        char c = lower(*ascii_p);
        ascii[(char)c]++;
        ascii_p++;
    }

    char max_char;
    int max_count = 0;

    for (int i = 0; i < 256; i++)
    {
        // 공백 제외 최빈 문자 탐색
        if (i != ' ' && *(ascii + i) > max_count)
        {
            max_count = *(ascii + i);
        }
    }

    // 최다 등장 문자 출력
    printf("\n최다 등장 문자: ");
    for (int i = 0; i < 256; i++)
    {
        if (max_count > 0 && max_count == *(ascii + i))
        {
            max_char = (char)i;
            printf("%c ", max_char);
        }
    }
}

char lower(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 32;

    return c;
}

// 길이 반환
int get_length(const char *str)
{
    const char *p = str;
    int len = 0;
    // 널 문자('\0')를 만날 때까지 길이를 1씩 증가
    while (*(p + len) != '\0')
    {
        len++;
    }
    return len;
}