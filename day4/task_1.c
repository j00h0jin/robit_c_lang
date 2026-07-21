/*
학생(학년, 성적, 이름) -> 5명

학년 오름차순 정렬

학년이 같으면 성적 순서

성적이 같으면 이름 순서
*/

typedef struct _Student
{
    int grade;
    float gpa;
    char name[20];
} Student;

char lower(char c);

#include <stdio.h>

void main()
{
    Student list[5];

    for (int i = 0; i < 5; i++)
    {
        scanf(" %d %f %s", &list[i].grade, &list[i].gpa, list[i].name);
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            // 학년이 높은 경우 변경
            if (list[i].grade > list[j].grade)
            {
                Student temp;
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
            // 학년이 동일한 경우에서
            else if (list[i].grade == list[j].grade)
            {
                // 성적이 높은 경우 변경
                if (list[i].gpa > list[j].gpa)
                {
                    Student temp;
                    temp = list[i];
                    list[i] = list[j];
                    list[j] = temp;
                }
                // 학년 + 성적이 동일한 경우에서
                else if (list[i].gpa == list[j].gpa)
                {
                    // 이름 정렬
                    // ASCII
                    // A(65) ~ Z(90)
                    // a(97) ~ z(122)
                    int k = 0;
                    while (lower(list[i].name[k]) == lower(list[j].name[k]) && list[i].name[k] != '\0')
                    {
                        k++; // 이름 철자가 다른 곳까지 k++
                    }
                    // abc 순서 정렬(ASCII)
                    if (lower(list[i].name[k]) < lower(list[j].name[k]))
                    {
                        Student temp;
                        temp = list[i];
                        list[i] = list[j];
                        list[j] = temp;
                    }
                }
            }
        }
    }

    printf("\n");

    for (int i = 0; i < 5; i++)
    {
        printf("%d %.1f %s\n", list[i].grade, list[i].gpa, list[i].name);
    }
}

char lower(char c)
{
    if (c >= 'A' || c <= 'Z')
        return c + 32;
}