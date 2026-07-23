/*
단순 연결 리스트를 이용한 stack구현
• push : 정수 push // ex) push 30
• pop : pop하고 pop된 값 출력. stack이 비어있을 시 비어있다고 출력
• size : stack 크기 출력
• top : top에 위치한 값 반환.
• isEmpty : stack에 데이터가 없으면 true, 있으면 false 반환
• printStack : stack 내 모든 값 출력. stack이 비어있을 시 비어있다고 출력
• Data 자료형 자유

day 4 task 7 참조

stack
*/

#include <stdio.h>
#include <stdlib.h>

// 노드
typedef struct Node
{
    int data;
    struct Node *next; // 다음 노드의 주소
} Node;

typedef struct _Stack
{
    Node *top; // 최상단
    int size;
} Stack;

int my_strcmp(char *s1, char *s2);
void init_list(Stack *list);
void push(Stack *list, int data);
void pop(Stack *list);
int isEmpty(Stack *list);
void printStack(Stack *list);

void main()
{
    // 선언 후 빈 값 초기화
    Stack *list = (Stack *)malloc(sizeof(Stack));
    init_list(list);

    char str[30];

    while (1)
    {
        printf("입력: ");
        scanf(" %s", str);

        if (my_strcmp(str, "push") == 0)
        {
            int val; // value
            scanf("%d", &val);
            push(list, val);
        }
        else if (my_strcmp(str, "pop") == 0)
        {
            pop(list);
        }
        else if (my_strcmp(str, "size") == 0)
        {
            printf("크기: %d\n", list->size);
        }
        else if (my_strcmp(str, "top") == 0)
        {
            if (list->top == NULL) // top이 없으면 비어 있다고 출력하고 continue
            {
                printf("EMPTY\n");
                continue;
            }
            printf("top: %d\n", list->top->data);
        }
        else if (my_strcmp(str, "isEmpty") == 0 || my_strcmp(str, "isempty") == 0)
        {
            if (isEmpty(list)) // isEmpty == 1 -> 비어 있음
                printf("True\n");
            else
                printf("False\n");
        }
        else if (my_strcmp(str, "printStack") == 0 || my_strcmp(str, "printstack") == 0)
        {
            printStack(list);
        }
        else
        {
            printf("존재하지 않는 명령어\n");
        }
    }
}

int my_strcmp(char *s1, char *s2)
{
    // 같으면서 '\0'이 아닐 때까지
    while (*s1 != '\0' && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    // 문자열이 같으면 0 반환
    return *s1 - *s2;
}

// list 빈 값 초기화
void init_list(Stack *list)
{
    list->top = NULL;
    list->size = 0;
}

void push(Stack *list, int data)
{
    // 새 노드 생성
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;

    // 첫번째 노드의 next는 없음
    if (list->top == NULL)
    {
        list->top = new_node;
        new_node->next = NULL;
    }
    else // 첫번째 노드가 아니라면
    {
        // 새 노드의 next를 기존의 top과 연결해주고 새 노드를 top으로 지정
        new_node->next = list->top;
        list->top = new_node;
    }
    list->size++;
    printf("push %d\n", data);
}

void pop(Stack *list)
{
    if (list->top == NULL)
    {
        printf("스택이 비어있음\n");
        return;
    }
    int deleted_val = list->top->data;

    // 노드가 1개만 있는 경우
    if (list->top->next == NULL)
    {
        // 메모리 해제
        free(list->top);
        // top 지정 없음
        list->top = NULL;
    }
    else
    {
        // 현재 top을 temp에 지정
        Node *temp = list->top;
        // top의 next를 top으로 넘김
        list->top = list->top->next;

        // top을 넘겼으므로 temp는 메모리 해제
        free(temp);
    }
    list->size--;
    printf("pop %d\n", deleted_val);
}

int isEmpty(Stack *list)
{
    if (list->size == 0) // size가 0이면 1
        return 1;
    else
        return 0;
}

void printStack(Stack *list)
{
    // 현재 리스트 출력
    Node *curr = list->top;
    if (curr == NULL)
    {
        printf("\nEMPTY\n");
        return;
    }
    // top쪽이 열려있으므로 괄호 X
    printf("\n <- \n"); // 방향 표시(왼쪽이 열려있는 스택같이 보이게)
    while (curr != NULL)
    {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("]\n");
}