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
    e d c b a(front)
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
    scanf(" %[^\n]", str);

    char without_space[30];
    int length = 0;

    for (int i = 0; str[i] != '\0'; i++) // 받은 str 끝까지
    {
        if (str[i] != ' ') // 공백이 아닐 경우 저장(abb         a와 같은 경우 판별해야되므로)
        {
            without_space[length++] = str[i];
        }
    }
    without_space[length] = '\0';

    // stack에 푸시
    for (int i = 0; i < length; i++)
    {
        push(stack_list, without_space[i]);
    }

    // 스택에서 큐로 엔큐(pop함수에서 pop된 값을 반환함 -> 그대로 엔큐)
    for (int i = 0; i < length; i++)
    {
        enqueue(queue_list, pop(stack_list));
    }

    // 현재 맨 위에 있는 주석 ii까지 되었음
    // 이제 queue의 front부터 읽으면 문자열을 뒤집은 것과 동일
    Node *temp = queue_list->front;
    // Palindraome인지 판별
    int is_palindraome = 1;

    for (int i = 0; i < length; i++)
    {
        if (without_space[i] != temp->data) // 하나라도 같지 않다면 Palindraome이 아님(is_palindraome = 0)
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

    curr = queue_list->front;
    while (curr != NULL)
    {
        Node *temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(queue_list);

    return;
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

void init_queue_list(Queue *list)
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
        // 기존 rear의 next를 new node에 연결하고 rear를 new node에 지정
        // new node의 next는 NULL
        list->rear->next = new_node;
        list->rear = new_node;
        new_node->next = NULL;
    }
    list->size++;
    // printf("enqueue %d\n", data);
}
