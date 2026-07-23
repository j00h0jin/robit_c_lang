/*
회문 판별하기
• 회문 또는 팰린드롬(Palindraome)은 앞 뒤 방향으로 볼 때 같은 순서의 문자로 구성된 문자열을말한다.
• Ex) abba, madam, was it a cat i saw
• 문자열을 입력받아 회문인지 아닌지 판별하여 출력
• hint : 스택과 큐를 이용(LIFO, FIFO)

day 6 task 2, 3 참조

i) 문자열을 받아 스택에 넣음
    ex) abcde
    ---------|
    a b c d e|
    ---------|

ii) 스택에서 큐로 엔큐함

    ---------
    e d c b a
    ---------

iii) 문자열과 queue의 front부터 비교

++ 공백 제거

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    char data;
    struct Node *next; // 다음 노드의 주소
} Node;

typedef struct _Stack
{
    Node *top; // 최상단
    int size;
} Stack;

typedef struct Queue
{
    Node *rear;
    Node *front; // 나가는 쪽이 front
    int size;
} Queue;

void init_stack_list(Stack *list);
void push(Stack *list, int data);
char pop(Stack *list);

void init_queue_list(Queue *list);
void enqueue(Queue *list, int data);

void main()
{
    Stack *stack_list = (Stack *)malloc(sizeof(Stack));
    init_stack_list(stack_list);

    Queue *queue_list = (Queue *)malloc(sizeof(Queue));
    init_queue_list(queue_list);

    char str[30];
    printf("문자열 입력(최대 30자): ");
    scanf(" %s", str);

    int length = get_length(str);

    for (int i = 0; i < length; i++)
    {
        push(stack_list, str[i]);
    }

    for (int i = 0; i < length; i++)
    {
        enqueue(queue_list, pop(stack_list));
    }

    Node *temp = queue_list->rear;
    int is_palindraome = 1;

    for (int i = 0; i < length; i++)
    {
        if (str[i] != temp->data)
        {
            is_palindraome = 0;
            break;
        }
        temp = temp->next;
    }

    if (is_palindraome)
        printf("Palindraome\n");
    else
        printf("Not Palindraome\n");

    // 메모리 해제
    Node *curr = stack_list->top;
    while (curr != NULL)
    {
        Node *temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(stack_list);

    curr = queue_list->rear;
    while (curr != NULL)
    {
        Node *temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(queue_list);
}

void init_stack_list(Stack *list)
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
}

char pop(Stack *list)
{
    if (list->top == NULL)
    {
        printf("스택이 비어있음\n");
        return 0;
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
    return deleted_val;
}

void init_list(Queue *list)
{
    list->rear = NULL;
    list->front = NULL;
    list->size = 0;
}

void enqueue(Queue *list, int data)
{
    // 새 노드 생성
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;

    // 첫번째 노드의 next는 없음
    if (list->rear == NULL)
    {
        // queue에서 노드가 하나인 경우 front이자 rear가 될 것
        list->rear = new_node;
        list->front = new_node;
        new_node->next = NULL;
    }
    else // 첫번째 노드가 아니라면
    {
        // 새 노드의 next를 기존의 rear와 연결해주고 새 노드를 rear으로 지정
        new_node->next = list->rear;
        list->rear = new_node;
    }
    list->size++;
    printf("enqueue %c\n", data);
}