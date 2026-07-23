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
    Node *front;
    Node *rear; // 나가는 쪽이 rear
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
        else if (my_strcmp(str, "front") == 0)
        {
            if (list->front == NULL) // top이 없으면 비어 있다고 출력하고 continue
            {
                printf("EMPTY\n");
                continue;
            }
            printf("front: %d\n", list->front->data);
        }
        else if (my_strcmp(str, "rear") == 0)
        {
            if (list->rear == NULL) // top이 없으면 비어 있다고 출력하고 continue
            {
                printf("EMPTY\n");
                continue;
            }
            printf("rear: %d\n", list->rear->data);
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
    list->front = NULL;
    list->rear = NULL;
    list->size = 0;
}

void enqueue(Queue *list, int data)
{
    // 새 노드 생성
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;

    // 첫번째 노드의 next는 없음
    if (list->front == NULL)
    {
        // queue에서 노드가 하나인 경우 front이자 rear가 될 것
        list->front = new_node;
        list->rear = new_node;
        new_node->next = NULL;
    }
    else // 첫번째 노드가 아니라면
    {
        // 새 노드의 next를 기존의 front와 연결해주고 새 노드를 front으로 지정
        new_node->next = list->front;
        list->front = new_node;
    }
    list->size++;
    printf("enqueue %d\n", data);
}

void dequeue(Queue *list)
{
    if (list->front == NULL)
    {
        printf("스택이 비어있음\n");
        return;
    }
    int deleted_val = list->rear->data;

    // 노드가 1개만 있는 경우
    if (list->front->next == NULL)
    {
        // 메모리 해제
        free(list->front); // == free(list->rear)
        // front와 rear은 둘 다 지정되어 있으므로 둘 다 해제
        list->front = NULL;
        list->rear = NULL;
    }
    else
    {
        free(list->rear);
        // 현재 rear를 front에 지정
        Node *curr = list->front;

        // queue의 front에서 size-1번 next로 이동하면 rear임
        // rear은 지워줄 것이므로 rear 앞부분까지 이동한다면 (size - 1)-1번 이동
        for (int i = 0; i < (list->size - 1) - 1; i++)
        {
            curr = curr->next;
        }
        // rear의 앞 부분을 rear로 지정해주고 next는 NULL
        list->rear = curr;
        list->rear->next = NULL;
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

    printf("\n -> \n"); // 방향 표시
    while (curr != NULL)
    {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n -> \n");
}