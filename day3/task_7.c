/*
동적할당으로 스택 구현(Last In First Out)
HTML 태그의 중첩 구조를 시각적으로 표현
잘못된 태그 구조를 입력 받을 시 오류

HTML을 잘 몰라서 일단 예시에 나와있는 div p b 외 잘못된 태그로 설정
div -> container
p -> 문장
b -> Bold(굵게)

p 안에 div는 불가능

<> 열기
</> 닫기

task 7번은 코드를 어떻게 짤지 감이 안와서 LLM 사용
-> 코드 리뷰와 동시에 학습 및 수정 (탑다운)
*/

#include <stdio.h>
#include <stdlib.h>

char **stack = NULL;    // 문자열(배열)을 담을 배열이므로 이중포인터 지정
int stack_size = 0;     // 현재 스택에 저장된 태그 개수
int stack_capacity = 5; // 스택의 최대 용량(임의 지정)

void my_strcpy(char dest[], const char src[]);
int my_streq(const char s1[], const char s2[]);
int is_valid_tag(const char tag[]);
void push(const char tag[]);
int pop_and_check(const char tag[]);
int is_in_stack(const char tag[]);
void print_indent(int depth);

void main()
{
    // [1단계] 입력 문자열 동적 할당
    int input_capacity = 5; // 입력값 최대 용량(임의 지정)
    int input_len = 0;
    char *input = (char *)malloc(sizeof(char) * input_capacity);

    printf("입력 : ");
    char ch;
    while ((ch = getchar()) != '\n') // enter 입력 전까지 반복
    {
        input[input_len++] = ch;
        // 입력값이 임의 지정 capacity보다 큰 경우 realloc 메모리 재할당
        if (input_len >= input_capacity - 1) // - 1 => '\0' 자리
        {
            input_capacity *= 2; // 할당량을 2배로 늘림(realloc), 연산 최소화(+1보다 2배가 연산량이 적어짐)
            input = (char *)realloc(input, sizeof(char) * input_capacity);
        }
    }
    input[input_len] = '\0'; // 문자열 끝 지정 '\0'

    printf("\n출력 :\n");

    // 문자열(배열)을 담을 배열이므로 이중포인터 지정
    stack = (char **)malloc(sizeof(char *) * stack_capacity);

    int i = 0;
    int has_error = 0;

    // 입력값을 다 읽을 때까지 반복
    while (input[i] != '\0')
    {

        // 태그 처리 ( < 인식 시 태그 )
        if (input[i] == '<')
        {
            i++;

            // 닫는 태그인지 구분
            int is_close = 0;
            if (input[i] == '/')
            {
                is_close = 1;
                i++;
            }

            // 태그 이름 추출
            char tag[10];
            int t = 0;
            // 닫힘(>)이나 문자열이 끝날 때까지 읽기
            while (input[i] != '>' && input[i] != '\0')
            {
                tag[t++] = input[i++];
            }
            tag[t] = '\0';
            if (input[i] == '>')
                i++;

            // 태그 검사
            if (!is_valid_tag(tag))
            {
                printf("\n허용되지 않은 태그");
                has_error = 1;
                break;
            }

            // 닫는 태그라면
            if (is_close)
            {
                // 태그의 맞는 경우 stack에서 pop, 짝이 안맞는 경우 에러
                if (!pop_and_check(tag))
                {
                    printf("\n태그 짝이 안 맞음");
                    has_error = 1;
                    break;
                }
                print_indent(stack_size);
                printf("</%s>\n", tag);
            }
            // 여는 태그라면(닫는 태그 X)
            else
            {
                // <p> 안에 <div>가 포함된 경우 에러 처리
                // 지금 검사하는 tag가 div이면서 stack에 p가 있는 상태인 경우(닫히지 않은 경우)
                // p 스택 안에 div가 들어갈 수 없으므로 error
                if (my_streq(tag, "div") && is_in_stack("p"))
                {
                    printf("\n<p> 태그 내부에는 <div> 태그가 포함될 수 없음\n");
                    has_error = 1;
                    break;
                }
                // 현재 저장된 stack만큼 들여쓰기 후 출력한 뒤 stack에 push
                print_indent(stack_size);
                printf("<%s>\n", tag);
                push(tag);
            }
        }
        // 일반 텍스트 처리(태그 X)
        else
        {
            char text[100];
            int t = 0;
            // 다음 태그를 읽기 전까지 혹은 텍스트 끝까지
            while (input[i] != '<' && input[i] != '\0')
            {
                text[t++] = input[i++];
            }
            text[t] = '\0';

            if (t > 0) // 일반 텍스트가 스택 사이에 있다면 (t > 0) 출력
            {
                print_indent(stack_size);
                printf("%s\n", text);
            }
        }
    }

    // 앞에서 에러가 없는 경우 + 안 닫힌 태그가 있는 경우
    if (!has_error && stack_size > 0)
    {
        printf("\n닫히지 않은 태그가 존재");
    }

    // 메모리 해제
    for (int i = 0; i < stack_size; i++)
    {
        free(stack[i]);
    }
    free(stack);
    free(input);
}

// 문자열 복사
void my_strcpy(char dest[], const char src[])
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// 문자열 비교
int my_streq(const char s1[], const char s2[])
{
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] != s2[i])
            return 0;
        i++;
    }
    return (s1[i] == '\0' && s2[i] == '\0') ? 1 : 0;
}

// 유효한 태그인지 확인
int is_valid_tag(const char tag[])
{
    return my_streq(tag, "div") || my_streq(tag, "p") || my_streq(tag, "b");
}

// 스택에 태그 추가
void push(const char tag[])
{
    // stack 사이즈가 capacity를 넘어선 경우 realloc 메모리 재할당
    if (stack_size >= stack_capacity)
    {
        stack_capacity *= 2; // realloc으로 사이즈 2배 할당(연산 최소화)
        stack = (char **)realloc(stack, sizeof(char *) * stack_capacity);
    }
    // 스택에 push
    stack[stack_size] = (char *)malloc(sizeof(char) * 10);
    my_strcpy(stack[stack_size], tag); // tag의 문자열을 stack에 저장(push)
    stack_size++;
}

// 태그 제거 및 짝 검증
int pop_and_check(const char tag[])
{
    // 스택 짝이 안 맞으면 0을 리턴
    if (stack_size == 0)
        return 0;
    if (!my_streq(stack[stack_size - 1], tag))
        return 0;

    // 짝이 맞으면 1을 리턴하고 스택에서 pop
    free(stack[stack_size - 1]);
    stack_size--;
    return 1;
}

// 햔재 스택에 tag가 있는지 확인(열려있는지)
int is_in_stack(const char tag[])
{
    for (int i = 0; i < stack_size; i++)
    {
        if (my_streq(stack[i], tag))
            return 1;
    }
    return 0;
}

// 들여쓰기 출력
void print_indent(int depth)
{
    for (int i = 0; i < depth; i++)
    {
        printf("    ");
    }
}