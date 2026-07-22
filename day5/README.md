# 포인터, 이중 포인터, 함수 포인터, 구조체 포인터 개념 정리

## 포인터

포인터는 메모리 주소를 가리킨다. (Byte 단위) 
변수의 자료형에 따라 메모리 공간이 달라진다.

char -> 1 Byte, int -> 4 Byte, double -> 8 Byte...

초기화되지 않은 포인터에 접근하면 세그폴트(Segmentation Fault)가 뜸 (포인터로 NULL을 참조하면 세그폴트)

```C
#include <stdio.h>

int main()
{
	int *p = NULL;  // int* p == int * p 모두 같음
	int num = 15;

	p = &num;

	printf("포인터 p의 값 : %d \n", p);
	printf("int 변수 num의 주소 : %d \n", &num); // p = &num

	return 0;
}
```
 ### [ * ]

어떤 변수를 선언할 때 참조 연산자를 붙이면 포인터 타입이라고 지정해주는 것이다. (포인터 지정 *)

포인터에 참조 연산자가 붙으면 포인터가 가리키는 주소에 저장된 값을 반환한다. (역참조 *)

포인터를 봐도봐도 이해가 안 가는 건 이 두 개가 마구 섞여있기 때문이 아닐까... 싶다.


```C
#include <stdio.h>

int main()
{
	int *p = NULL;  // 포인터 지정
	int num = 15;

	p = &num; 

	printf("int 변수 num의 주소 : %d \n", &num); // 주소 값
	printf("포인터 p의 값 : %d \n", p);          // 주소 값
	printf("포인터 p가 가리키는 값 : %d \n", *p); // 역참조, 15

	return 0;
}
```

p = num의 주소

*p = p(num의 주소)가 가리키는 값 = 15

---

> 증감 연산자와 사용
>
> 증감 연산자가 참조 연산자보다 우선 순위가 높아 먼저 계산된다.

```C
#include <stdio.h>

int main()
{
	int *p = NULL; 
	int num = 15;

  p = &num;

	(*p)++;
	printf("포인터 p가 가리키는 값 : %d\n", *p); // 16
	printf("num 값 : %d\n\n", num);             // 16

	*p++; // 증감 연산자가 우선
	printf("포인터 p가 가리키는 값 : %d\n", *p);  // 주소값 + 1
	printf("num 값 : %d\n", num);                // 16

	return 0;
}
```

---

### call by value, call by reference (함수에서의 포인터)

call by value -> 값을 복사해서 전달(함수 내에서만 유효, 함수가 끝나면 소멸)

call by reference -> 주소값을 전달

```c
#include <stdio.h>

// reference
void swap(int *a, int *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

// value
void swap2(int a, int b)
{
    int temp;

    temp = a;
    a = b;
    b = temp;

    printf("%d %d", a, b); // 10 20
    // 함수에서 사용된 a, b, temp는 함수 종료와 함께 소멸
}

int main()
{
    int a, b;

    a = 10;
    b = 20;

    printf("swap 전 : %d %d\n", a, b); // 10 20

    swap(&a, &b);

    printf("swap 후 : %d %d\n", a, b); // 20 10

    swap2(a, b);

    printf("%d %d", a, b); // 20 10

    return 0;
}
```


배열은 주소값을 가지기 때문에 포인터처럼 넘겨지게 된다.

---

### 포인터와 배열

배열의 이름은 포인터 변수와 같은 기능을 하고, 배열의 첫번째 요소의 주소값을 가리킨다.

scanf로 값을 입력받을 때 주소(&)를 써야 하는데 문자열을 입력받을 때는 &을 붙여주지 않아도 되는 이유가 문자열(배열) 자체가 주소값을 지니고 있기 때문
```c
#include <stdio.h>

int main()
{
    int arr[5] = {10, 20, 30, 40, 50};

    int *arrPtr = arr;

    // arr 주소값 1000이라 가정
    printf("포인터 주소 : %d %d\n", arrPtr, arrPtr + 1); // 1000 1004
    printf("변수 값 : %d %d\n", *arrPtr + 1, *(arrPtr + 1)); // 11  20
    // * 연산이 +-보다 우선이므로 괄호 유무에 따라 값이 다름

    arrPtr += 2;

    printf("증가 연산 후 : %d\n", arrPtr); // 1008
    printf("변수 값 : %d\n", *arrPtr);     // 30

    return 0;
}
```

위 예시처럼 주소값에 연산을 하면 주소값 + 1이 아니라 주소값 + 1*(자료형 Byte)처럼 늘어난다.

따라서 *(arr+i) = arr[i]와 같이 사용할 수 있다.

---

## 이중 포인터

이중 for문이 있듯, 포인터도 이중 포인터가 있다.

포인터도 주소값을 담는 '변수'이기 때문에 포인터 자체의 주소값이 존재한다.

이 주소를 한번 더 가리키면 이중 포인터가 되는 것이다. (변수를 가리키는 포인터를 가리키는 포인터)


<img width="400" height="500" alt="image" src="https://github.com/user-attachments/assets/5f237baf-3d4b-46ca-a1ab-2f3c0cccbb8a" />

사실 이중 포인터 말고 n중으로도 가능하다. 이중 포인터 이상으로 사용을 잘 안하는 것뿐이라고 한다. ([[변수를 가리키는 포인터]를 가리키는 포인터]를 가리키는...)

```c
#include <stdio.h>

int main()
{
	int num = 10; // 주소값 1000이라고 가정
	int *ptr;
	int **pptr;

	ptr = &num; // 1000
	pptr = &ptr; // 주소값 1004라고 가정(num의 주소값 1000을 저장하는 주소)

	printf("num : %d, *ptr : %d, **ptr : %d\n", num, *ptr, **pptr);
  // 10(값)
  // 10( *ptr = 주소(ptr값=1000)에 저장된 값 = 10)
  // 10( **pptr = *(*pptr) = *(주소(pptr값=1004)에 저장된 값)  = *(1000) = 주소 1000에 저장된 값 = 10 )
	printf("num 주소 : %d, ptr 값 : %d, **ptr 값 : %d\n", &num, ptr, *pptr);
  // 1000(주소값) 1000(값) 1000(주소(pptr값=1004)에 저장된 값  = 1000)
	printf("ptr 주소 : %d, pptr 값 : %d", &ptr, pptr);
  // 1004(주소값) 1004(값)


	return 0;
}
```

<img width="1268" height="1634" alt="image" src="https://github.com/user-attachments/assets/b0501b9b-01bc-4d7a-a3e9-5e1ba8018ac0" />

이중 포인터를 사용하는 경우

> 함수 안에서 포인터 값을 변경할 때
```c
#include <stdio.h>
#include <stdlib.h>

void allocateMemory(int **p) 
{
    *p = (int *)malloc(sizeof(int));
    // 
}

int main()
{
    int *ptr = NULL;
    allocateMemory(&ptr); // ptr의 주소를 넘김
    *ptr = 10;            
}
```

> 2차원 배열 동적 할당

```c
#include <stdio.h>
#include <stdlib.h>

void main()
{
    int **arr;
    int x, y;

    printf("input x : ");
    scanf(" %d", &x);
    printf("input y : ");
    scanf(" %d", &y);

    arr = (int **)malloc(sizeof(int *) * y); // 배열의 주소들을 담은 포인터
    for (int i = 0; i < y; i++)
    {
        arr[i] = (int *)malloc(sizeof(int) * x);
    }

	// 동적할당을 한 뒤에는 마지막에 동적할당을 한 순서의 역순으로 메모리 해제를 해준
	for (int i = 0; i < y; i++)
    {
        free(arr[i)
    }
	free(arr)
}
```

<img width="1292" height="1514" alt="image" src="https://github.com/user-attachments/assets/67c65cd1-6291-4ba7-922a-7609b2a431c8" />



> 문자열 배열을 다룰 때(문자열이 이미 배열이기 때문에 배열을 담은 배열) 등...
<img width="1324" height="1393" alt="image" src="https://github.com/user-attachments/assets/4a78b830-6426-473a-834c-907366ca7e2b" />


---

## 함수 포인터

함수도 메모리 상의 주소값을 가지게 되며 이를 가리키는 것을 함수 포인터라고 한다.

```c
#include <stdio.h> 
 
void fun(int num) {
    printf("%d\n", num); // 3
}
 
int main() {
    // 함수 포인터 선언
	// 함수의 반환형 타입(*[함수 포인터의 이름])(함수의 매개변수 타입)
    void (*fun_ptr)(int);   
    fun_ptr = &fun; // 함수 주소값 할당
 
    (*fun_ptr)(3); // 함수 포인터로 함수 호출
 
    return 0;
}
```

함수 포인터는 참조(reference)나 역참조(dereference)해도 동일하게 함수 주소를 가리키는 포인터 역할을 한다.

```c
	// 다 똑같음
    fun_ptr = &fun;
    fun_ptr = fun;
    fun_ptr = *fun;
    fun_ptr = **fun;
	fun_ptr = *********************************fun;
```
사실 함수를 호출할 때 쓰는 함수 이름도 주소를 가리키는 포인터 역할을 한다고 한다.

>그럼 왜 함수 포인터를 쓰는 건지?
>
>· 여러 함수를 사용할 때 배열로 관리할 수 있다
>
>· [콜백 함수](https://velog.io/@ko1586/Callback%ED%95%A8%EC%88%98%EB%9E%80-%EB%AD%94%EB%8D%B0)를 사용할 때 함수 포인터를 사용한다

함수 이름은 사실 해당 함수의 주소만을 가리키는 고정적(const) 포인터라고 볼 수 있다.

함수 포인터를 사용하면 해당 포인터에 다른 함수를 가리키면 가변할 수 있기 때문에 이러한 점이 다르다고 할 수 있다.

---

## 구조체 포인터

구조체도 변수를 담은 구조이기 때문에 주소값이 존재한다. 따라서 구조체를 가리키는 포인터를 선언할 수 있다.

```c
#include <stdio.h>

typedef struct _Student{
	int s_id;
	int age;
} Student;

int main(){
	Student a;
	Student *ptr; // == struct _Student *ptr
	
	ptr = &a;

  
	(*ptr).s_id = 1004;
	(*ptr).age = 20;
  // . 연산이 * 연산보다 높으므로 괄호가 없으면 *(ptr.s_id)로 인식하여 오류
  // ->(간접맴버참조연산자라고 한다) 기호를 사용하면 괄호가 있는 것처럼 연산된다.
  // ex) ptr -> age = 20; == (*ptr).age = 20;
	
	printf("학생 a의 학번 : %d, 나이: %d\n", a.s_id, a.age); // 1004 20
}
```

> 그래서 왜 쓰는 건가
>
> · 메모리 관리를 위해서
> > 구조체는 변수들의 묶음이다 보니 구조체 안에 들어있는 변수들의 크기들의 합이 곧 구조체의 크기이다.
> > 함수에서 구조체의 특정 값을 읽어오고 싶을 때 포인터를 쓰지 않고 call by value로 읽어오면 구조체 전체를 복사한 뒤 맴버참조를 하므로 메모리를 많이 차지하게 된다.
> > 구조체 포인터를 통해 call by reference로 읽는다면 해당 구조체의 주소가 담긴 포인터의 메모리 + 읽어올 값의 메모리만 차지하기 때문에 훨씬 효율적




 
