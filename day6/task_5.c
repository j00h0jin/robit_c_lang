/*
과제 5

출석부 프로그램
• Student 구조체 : 번호, 이름, 주소(format : 나라,도,시,구), 성적 // 중첩
• 구조체 배열, 구조체 포인터를 이용한 함수 이용
• 모든 항목 예외처리(ex 숫자, 문자) • 필수 기능)

1. 학생 정렬 기능
: 번호순, 이름순, 주소순(나라,도,시,구에 따라 따로 진행), 성적순 출력 모두 가능

2. 학생 찾기 기능
: 번호or주소(나라,도,시,구에 따라 따로 진행)or성적을 입력하면 해당하는 모든 학생 이름 출력

3. 학생 추가, 삭제 기능
: 번호, 이름, 주소, 성적 입력하면 출석부에서 해당 학생 추가/삭제. 중복된 경우 선택하여 삭제

4. 출석부 저장 및 불러오기
: 파일 입출력을 이용해 출석부를 저장하고 불러 옴

a+
읽기 추가 쓰기, 파일 끝에 추가
쓰기 -> 커서 맨 끝
읽을 때 다시 커서 맨 앞 지정

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _Address
{
    char country[30];
    char state[30]; // 도
    char city[30];  // 시
    char ward[30];  // 구
} Address;

typedef struct _Student
{
    int s_num;
    char name[30];
    Address ADDRESS;
    int gpa; // gpa/4.5
} Student;

void my_strcpy(char dest[], char src[]);
int my_strcmp(char s1[], char s2[]);
char lower(char c);

void add(Student **list, int *count, int *capacity, Student s);
void printStudent(Student *list, int count);

void main()
{
    int count = 0;
    int capacity = 100;
    Student *list = (Student *)malloc(sizeof(Student) * capacity);

    printf("출석부 프로그램\n\n");
    printf("명령어\n");
    printf("sort [{번호, 이름, 나라, 도, 시, 구, 성적}] <- 택 1\n");
    printf("add [번호] [이름] [나라] [도] [시] [구] [성적]\n");
    printf("remove [번호] [이름] [나라] [도] [시] [구] [성적]\n");
    printf("print\n");
    printf("save_file\n");
    printf("load_file\n\n");

    char str[100];

    while (1)
    {
        printf("입력: ");
        scanf(" %s", &str);

        if (my_strcmp(str, "sort") == 0)
        {
        }
        else if (my_strcmp(str, "add") == 0)
        {
            Student temp;
            if (scanf("%d %s %s %s %s %s %d", &temp.s_num, temp.name, temp.ADDRESS.country, temp.ADDRESS.state,
                      temp.ADDRESS.city, temp.ADDRESS.ward, &temp.gpa) == 7)
            {
                add(&list, &count, &capacity, temp);
                printf("add\n");
            }
            else
            {
                printf("잘못된 형식\n");
                while (getchar() != '\n')
                    ;
            }
        }
        else if (my_strcmp(str, "remove") == 0)
        {
        }
        else if (my_strcmp(str, "print") == 0)
        {
            printStudent(list, count);
        }
        else if (my_strcmp(str, "save_file") == 0)
        {
        }
        else if (my_strcmp(str, "load_file") == 0)
        {
        }

        else // 명령어 예외
        {
            printf("존재하지 않는 명령어\n");
        }
    }
}

// 문자열 복사
void my_strcpy(char dest[], char src[])
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
int my_strcmp(char s1[], char s2[])
{
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
        i++;
    }
    return s1[i] - s2[i];
}

char lower(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 32;
}

void sort()
{
}

void add(Student **list, int *count, int *capacity, Student s)
{
    if (*count >= *capacity)
    {
        *capacity *= 2;
        Student *temp = (Student *)realloc(*list, sizeof(Student) * (*capacity));
        if (temp == NULL)
        {
            return;
        }
        *list = temp;
    }
    (*list)[*count] = s;
    (*count)++;
}

void remv()
{
}

void printStudent(Student *list, int count)
{
    if (count == 0)
    {
        printf("EMPTY\n");
        return;
    }

    printf("\n번호 이름 나라 도 시 구 성적 순\n");

    for (int i = 0; i < count; i++)
    {
        printf("%d %s %s %s %s %s %d\n", list[i].s_num, list[i].name, list[i].ADDRESS.country, list[i].ADDRESS.state,
               list[i].ADDRESS.city, list[i].ADDRESS.ward, list[i].gpa);
    }

    printf("\n학생 수: %d명\n\n", count);
}

void saveFile()
{
}

void loadFile()
{
}