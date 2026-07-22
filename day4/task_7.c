/*
연결 리스트 구현
insert: 원하는 위치에 node 추가
insert_back: 맨 끝에 추가
insert_first: 맨 앞에 추가

delete: 원하는 요소 삭제
back, first: 맨 앞, 뒤 삭제

get_entry: 요소 찾기(data로 찾을 시 index 반환, index -> data 반환)

get_length: 리스트 길이
print_list: 리스트 모든 요소 출력

reverse: 리버스

자료형 자유 -> int형

빈 연결 리스트부터
*/

#include <stdio.h>
#include <stdlib.h>

// 노드
typedef struct Node
{
    int data;
    struct Node *next; // 다음 노드의 주소
} Node;

// 연결 리스트
typedef struct LinkedList
{
    Node *head; // first
    Node *tail; // end
    Node *cur;  // current?
    int size;
} LinkedList;

int my_strcmp(char *s1, char *s2);
void init_list(LinkedList *list);
void insert_first(LinkedList *list, int data);
void insert_back(LinkedList *list, int data);
void insert(LinkedList *list, int index, int data);
void delete_first(LinkedList *list);
void delete_back(LinkedList *list);
void delete(LinkedList *list, int index);
void get_entry(LinkedList *list);
void reverse(LinkedList *list);
void print_list(LinkedList *list);

void main()
{
    // 선언 후 빈 값 초기화
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    init_list(list);

    char str[30];

    printf("get_entry 시 idx 또는 data 입력\n");
    printf("ex) get_entry idx 3\n");

    while (1)
    {
        printf("입력: ");
        scanf(" %s", str);

        if (my_strcmp(str, "insert_first") == 0)
        {
            int val; // value
            scanf("%d", &val);
            insert_first(list, val);
        }
        else if (my_strcmp(str, "insert_back") == 0)
        {
            int val;
            scanf("%d", &val);
            insert_back(list, val);
        }
        else if (my_strcmp(str, "insert") == 0)
        {
            int idx, val;
            scanf("%d %d", &idx, &val);
            insert(list, idx, val);
        }
        else if (my_strcmp(str, "delete_first") == 0)
        {
            delete_first(list);
        }
        else if (my_strcmp(str, "delete_back") == 0)
        {
            delete_back(list);
        }
        else if (my_strcmp(str, "delete") == 0)
        {
            int idx;
            scanf("%d", &idx);
            delete(list, idx);
        }
        else if (my_strcmp(str, "get_entry") == 0)
        {
            get_entry(list);
        }
        else if (my_strcmp(str, "get_length") == 0)
        {
            printf("길이: %d\n", list->size);
        }
        else if (my_strcmp(str, "print_list") == 0)
        {
            print_list(list);
        }
        else if (my_strcmp(str, "reverse") == 0)
        {
            reverse(list);
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
void init_list(LinkedList *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->cur = NULL;
    list->size = 0;
}

void insert_first(LinkedList *list, int data)
{
    // 새 노드 생성
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    // 리스트의 head를 가리킴(맨 앞으로 오게 되었으므로 기존의 head를 가리킴)
    new_node->next = list->head;

    // 맨 앞에 위치하므로 head는 자기 자신
    list->head = new_node;
    if (list->tail == NULL)
    { // 빈 리스트였던 경우 head이자 tail이므로 tail 지정
        list->tail = new_node;
    }
    // list에 data가 들어갔으므로 size++
    list->size++;
    printf("맨 앞 %d 삽입\n", data);
}

void insert_back(LinkedList *list, int data)
{
    // 새 노드 생성
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    // 마지막이므로 next 존재 X
    new_node->next = NULL;

    // 빈 노드의 경우 tail이자 head
    if (list->head == NULL)
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else // 빈 노드가 아니면
    {
        // 기존의 tail은 다음 노드가 생기기 때문에 next 지정
        list->tail->next = new_node;
        // 새 노드가 tail이 됨
        list->tail = new_node;
    }
    list->size++;
    printf("맨 뒤 %d 삽입\n", data);
}

void insert(LinkedList *list, int index, int data)
{
    if (index < 0 || index > list->size) // index 0 ~ size까지
    {
        printf("잘못된 인덱스");
        return;
    }
    if (index == 0) // 맨 앞
    {
        insert_first(list, data);
        return;
    }
    if (index == list->size) // 맨 뒤
    {
        insert_back(list, data);
        return;
    }

    // 새 노드 생성
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;

    // 받아온 index 자리를 찾음
    Node *curr = list->head;
    for (int i = 0; i < index - 1; i++)
    // idx - 1에 삽입해야 함(사이에 들어가니까)
    // ex) 0(0) 200(1) 300(2)
    // index 1에 100 삽입
    // curr은 100(0)까지만 이동
    {
        curr = curr->next;
    }
    // 새 노드의 next 연결(기존의 curr가 가리키는 next)
    // ex) 100의 next = 0의 next(200)
    new_node->next = curr->next;
    // 기존의 next는 새 노드를 가리킴
    // 0의 next = 100
    curr->next = new_node;
    list->size++;
    printf("인덱스 %d에 %d 삽입\n", index, data);
}

void delete_first(LinkedList *list)
{
    // 리스트에 아무 것도 없는 경우
    if (list->head == NULL)
    {
        printf("리스트가 비어있음\n");
        return;
    }

    // 리스트의 head(first) 값을 받아옴
    Node *temp = list->head;
    int deleted_val = temp->data;

    // first에 first의 next를 넣음(first는 삭제할 것이기 떄문에)
    list->head = list->head->next;
    // 만약 list->head->next가 없었던 경우(리스트 1개만 있었던 경우)
    if (list->head == NULL)
    {
        // 빈 리스트가 되므로 tail도 초기화
        list->tail = NULL;
    }
    // 메모리 해제
    free(temp);
    list->size--;
    printf("맨 앞 %d 삭제\n", deleted_val);
}

void delete_back(LinkedList *list)
{
    if (list->head == NULL)
    {
        printf("리스트가 비어있음\n");
        return;
    }
    int deleted_val = list->tail->data;

    // 노드가 1개만 있는 경우
    if (list->head == list->tail)
    {
        // 메모리 해제
        free(list->head);
        list->head = NULL; // 빈 값
        list->tail = NULL; // 빈 값
    }
    else
    {
        Node *curr = list->head;
        // tail의 앞 부분까지 curr 이동
        while (curr->next != list->tail)
        {
            curr = curr->next;
        }
        // 원래 tail은 메모리 해제
        free(list->tail);
        // tail의 앞 부분을 tail로 만들어줌
        list->tail = curr;
        list->tail->next = NULL;
    }
    list->size--;
    printf("맨 뒤 %d 삭제\n", deleted_val);
}

void delete(LinkedList *list, int index)
{
    if (index < 0 || index >= list->size) // !(0 ~ size - 1)
    {
        printf("범위를 벗어난 인덱스");
        return;
    }
    if (index == 0) // 맨 앞
    {
        delete_first(list);
        return;
    }
    if (index == list->size - 1) // 맨 뒤
    {
        delete_back(list);
        return;
    }

    // 삭제할 노드의 앞 노드까지 이동
    Node *curr = list->head;
    for (int i = 0; i < index - 1; i++)
    {
        curr = curr->next;
    }
    // 삭제할 노드
    Node *target = curr->next;
    int deleted_val = target->data;
    // 삭제할 노드의 앞 노드의 next를 삭제할 노드의 뒷 노드에 연결해줌
    curr->next = target->next;
    // 삭제할 노드는 메모리 해제
    free(target);
    list->size--;
    printf("인덱스 %d의 %d 삭제\n", index, deleted_val);
}

void get_entry(LinkedList *list)
{
    char type[10];
    int val;
    scanf("%s %d", type, &val);
    // type으로 idx와 data 구분
    if (my_strcmp(type, "idx") == 0) // index 경우
    {
        if (val < 0 || val >= list->size)
        {
            printf("인덱스 범위를 벗어남\n");
            return;
        }
        // head부터 입력받은 idx까지 이동
        Node *curr = list->head;
        for (int i = 0; i < val; i++)
            curr = curr->next;
        printf("Index %d의 값: %d\n", val, curr->data);
    }
    else if (my_strcmp(type, "data") == 0) // data 경우
    {
        // head부터 입력 받은 data가 있을 때까지 탐색
        Node *curr = list->head;
        int idx = 0;
        while (curr != NULL)
        {
            if (curr->data == val)
            {
                // 값을 찾았다면 return
                printf("값 %d의 Index: %d\n", val, idx);
                return;
            }
            curr = curr->next;
            idx++;
        }
        // while문이 끝까지 돈 경우 data가 일치하는 경우가 없으므로 메세지 출력
        printf("값 %d를 찾을 수 없음\n", val);
    }
    else
    {
        printf("get_entry (idx/data) n 형식으로 입력\n");
    }
}

void reverse(LinkedList *list)
{
    // 빈 리스트 or 리스트 노드 1개일 때는 뒤집을 필요 X
    if (list->head == NULL || list->head == list->tail)
    {
        printf("완료\n");
        return;
    }

    Node *prev = NULL;       // 이전 노드 저장할 곳
    Node *curr = list->head; // 현재 위치(시작점)
    Node *next = NULL;       // 다음 노드 저장할 곳

    list->tail = list->head; // 기존 head가 tail이 됨(뒤집으면)

    while (curr != NULL)
    {
        next = curr->next; // next에 다음 노드 저장
        curr->next = prev; // 현재 노드의 next를 이전 노드를 향하게 함
        prev = curr;       // (다음 노드의 이전 노드)는 (현재 노드)이므로 prev에 현재 노드를 넣어줌
        curr = next;       // 현재 노드를 while문 첫줄에 저장된 다음 노드로 지정
    }

    list->head = prev; // 뒤집힌 후 첫 노드가 head가 됨

    /*
    ex) [10] -> [20] -> [30] // reverse 하기
    curr = [10]

    list -> tail = [10]

    while 1회차
    next = [20]([10]->next)
    [10]->next = NULL
    prev = [10]
    curr = [20]

    NULL <- (tail)[10](prev) (끊어짐) [20](curr) -> [30] -> NULL

    2회차 curr = [20], prev = [10]
    next = [30]([20]->next)
    [20]->next = [10]
    prev = [20]
    curr = [30]

    NULL <- (tail)[10] <- [20](prev) (끊어짐) [30](curr) -> NULL

    3회차 curr = [30], prev = [20]
    next = NULL([30]->next)
    [30]->next = [20]
    prev = [30]
    curr = NULL

    NULL <- (tail)[10] <- [20] <- [30](prev) (끊어짐) NULL(curr)

    4회차 조건 성립 X

    list->head = [30]

    NULL <- (tail)[10] <- [20] <- (head)[30](prev) (끊어짐) NULL(curr)

    */
    printf("완료\n");
}

void print_list(LinkedList *list)
{
    // 현재 리스트 출력
    // 빈 리스트의 경우 head = NULL이므로 출력값 없음
    Node *curr = list->head;
    printf("\n[ ");
    while (curr != NULL)
    {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("]");
}