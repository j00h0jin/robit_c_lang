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
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _Address
{
    char country;
    char state; // 도
    char city;  // 시
    char ward;  // 구
} Address;

typedef struct _Student
{
    int s_num;
    char name;
    Address ADDRESS;
    int gpa; // gpa/4.5
} Student;

void main()
{
    printf("test");
}