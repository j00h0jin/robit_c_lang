/*
단순 연결 리스트를 이용한 Queue 구현
• Enqueue : Queue에 data 입력
• Dequeue : Dequeue하고 Dequeue된 값 출력. Queue가 비어있을 시 비어있다고 출력
• size : Queue 크기 출력
• front : front에 위치한 값 반환.
• rear : rear에 위치한 값 반환.
• isEmpty : Queue에 데이터가 없으면 true, 있으면 false 반환
• printQueue : Queue 내 모든 값 출력. Queue가 비어있을 시 비어있다고 출력

day 4 task 7, day 6 task 2 참조

queue

+ 처음에 front와 rear를 반대로 놓고 주석과 코드를 짠 뒤 수정해서 혹시 놓친 주석이 있으면 주석 설명이 반대일 수 있음

++ rear가 새 노드를 가리켜야 한다고 함 지금 next의 완전 반대 방향(수정 완)

*/

#include <stdio.h>
#include <stdlib.h>

// 노드
typedef struct Node
{
    int data;
    struct Node *next; // 다음 노드의 주소
} Node;

typedef struct Queue
{
    Node *rear;
    Node *front; // 나가는 쪽이 front
    int size;
} Queue;

int my_strcmp(char *s1, char *s2);
void init_list(Queue *list);
void enqueue(Queue *list, int data);
void dequeue(Queue *list);
int isEmpty(Queue *list);
void printQueue(Queue *list);

void main()
{
    Queue *list = (Queue *)malloc(sizeof(Queue));
    init_list(list);

    char str[30];
    while (1)
    {
        printf("입력: ");
        scanf(" %s", str);

        if (my_strcmp(str, "Enqueue") == 0 || my_strcmp(str, "enqueue") == 0)
        {
            int val; // value
            scanf("%d", &val);
            enqueue(list, val);
        }
        else if (my_strcmp(str, "Dequeue") == 0 || my_strcmp(str, "dequeue") == 0)
        {
            dequeue(list);
        }
        else if (my_strcmp(str, "size") == 0)
        {
            printf("크기: %d\n", list->size);
        }
        else if (my_strcmp(str, "rear") == 0)
        {
            if (list->rear == NULL) // rear가 없으면 비어 있다고 출력하고 continue
            {
                printf("EMPTY\n");
                continue;
            }
            printf("rear: %d\n", list->rear->data);
        }
        else if (my_strcmp(str, "front") == 0)
        {
            if (list->front == NULL) // front가 없으면 비어 있다고 출력하고 continue
            {
                printf("EMPTY\n");
                continue;
            }
            printf("front: %d\n", list->front->data);
        }
        else if (my_strcmp(str, "isEmpty") == 0 || my_strcmp(str, "isempty") == 0)
        {
            if (isEmpty(list)) // isEmpty == 1 -> 비어 있음
                printf("True\n");
            else
                printf("False\n");
        }
        else if (my_strcmp(str, "printQueue") == 0 || my_strcmp(str, "printqueue") == 0)
        {
            printQueue(list);
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
        // 기존 rear의 next를 new node에 연결하고 rear를 new node에 지정
        // new node의 next는 NULL
        list->rear->next = new_node;
        list->rear = new_node;
        new_node->next = NULL;
    }
    list->size++;
    printf("enqueue %d\n", data);
}

void dequeue(Queue *list)
{
    if (list->rear == NULL)
    {
        printf("큐가 비어있음\n");
        return;
    }
    int deleted_val = list->front->data;

    // 노드가 1개만 있는 경우
    if (list->rear == list->front)
    {
        // 메모리 해제
        free(list->rear); // == free(list->front)
        // front와 rear은 둘 다 지정되어 있으므로 둘 다 해제
        list->rear = NULL;
        list->front = NULL;
    }
    else
    {
        // front next 임시 저장 후
        Node *temp = list->front->next;
        // front의 next를 끊어주고 해제
        list->front->next = NULL;
        free(list->front);

        // 저장해놓은 front의 next는 front가 됨
        list->front = temp;
    }
    list->size--;
    printf("dequeue %d\n", deleted_val);
}

int isEmpty(Queue *list)
{
    if (list->size == 0) // size가 0이면 1
        return 1;
    else
        return 0;
}

void printQueue(Queue *list)
{
    // 현재 리스트 출력
    Node *curr = list->front;
    if (curr == NULL)
    {
        printf("\nEMPTY\n");
        return;
    }

    printf("\n <- \n"); // 방향 표시
    while (curr != NULL)
    {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n <- \n");
}