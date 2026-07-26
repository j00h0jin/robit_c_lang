<img width="677" height="762" alt="image" src="https://github.com/user-attachments/assets/21a1177c-d813-44c3-ac36-e3f6ef93ae2a" />


---

## 검 강화하기 실행 방법

```terminal
cd final
gcc main.c -o main.exe -lgdi32 -lmsimg32
start conhost main.exe
```

혹은 main.c가 있는 파일로 이동하여

```terminal
gcc main.c -o main.exe -lgdi32 -lmsimg32
start conhost main.exe
```

<img width="707" height="94" alt="image" src="https://github.com/user-attachments/assets/ab6bd1bb-4c3f-4306-91e8-1459567c9c03" />

<img width="1443" height="841" alt="image" src="https://github.com/user-attachments/assets/13af48c1-b862-4fc3-9bc0-e45b902f9fd3" />

시간이 없어서 반응형으로 짜지 않았다. 만약 노트북 화면이 작다면 모니터가 좀 더 큰 환경에서 돌려야 문제가 없을 듯하다.

---



## AI활용 보고서

### gemini, copliot

주제 구현 가능성 검증 및 windows.h 예제 학습

https://share.gemini.google/Fw1Mg0gsBm9d

https://share.gemini.google/AcZ6oUaPVJYp

https://share.gemini.google/IINvyl8cDyLs

디버깅 위주

https://share.gemini.google/SqjtYooeph87

https://share.gemini.google/flUUlRpAso3q

https://share.gemini.google/qLKEq0CJudL1

https://share.gemini.google/19meFiFf17d2

https://share.gemini.google/bME1SISWM0md

[copliot.txt](https://github.com/user-attachments/files/30388732/copliot.txt)

---

windows.h로 GUI를 구성하는 듯 싶어서 관련 자료를 찾아보았는데 관련 자료가 빈약한 것 같아 AI, [유튜브 강의](https://www.youtube.com/watch?v=lKQbupTlXTU) 보면서 기초적인 부분만 숙지하였다.

2.5일이라는 짧은 시간에 깊게 파고들긴 힘들 것이라 판단하고 아주 기본적인 것만 숙지한 상태에서 나머지는 필요할 때마다 AI에게 물어보고 사용하기로 하였다.

주제가 [검 강화하기](https://namu.wiki/w/%EA%B2%80%20%EA%B0%95%ED%99%94%ED%95%98%EA%B8%B0#rfn-1)인만큼 고증을 철저히 따라가고 싶었으나 콘솔창에서 폰트 크기를 지정할 수 없다는 사실에 주요한 기능만 구현하기로 했다.

해당 게임 안에 사용한 이미지는 [FFDEC](https://github.com/jindrapetrik/jpexs-decompiler)이라는 프로그램을 통해 게임을 언팩하여 사용했고, 이미지 하나 직접 캡쳐를 따서 다른 사진을 가져왔다.

키입력은 다양하진 않지만 [여기](https://devshovelinglife.tistory.com/795)와 [여기](https://devshovelinglife.tistory.com/795)를 참조하였다.

시간이 부족해서 AI에게 코드 구조를 짜달라고 한 경우가 꽤 많은데 이 경우에는 1. 일단 코드를 받고 2. 실행 3. 동작 확인 4. 코드 리뷰 5. 주석 달면서 학습 순으로 공부하였다.

주석이 빈약한 함수의 경우 윗부분에 동일한 코드 구조에서 설명한 경우가 아니면 [손대기가 너무 어려워서 이해를 포기하고 가져다 쓴 경우](https://cafe.naver.com/f-e/cafes/29225931/articles/262?menuid=32&referrerAllArticles=false&page=5)도 몇 있다. 이 경우 해당 함수가 어떤 기능을 하는지 정도만 이해하고 사용하였다.

솔직히 마우스 이벤트 구현에서 너무 시간을 오래 잡아먹어서 못 만들 줄 알았는데 어찌하다보니 완성은 하게 되었다.








