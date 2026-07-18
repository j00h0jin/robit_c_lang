// 동일한 문자가 여러 번 있는 경우 구간마다 표시
// ex abab12ab12
// subStr 12
// 첫번째 12는 5~6번째(인덱스 4~5), 두번째 12는 9~10번째

#include <stdio.h>

void main()
{
    char inputStr[100] = {
        '\0',
    };
    char subStr[100] = {
        '\0',
    };
    int inptLen = 0, subLen = 0;

    printf("최대 99개 문자 입력 <inputStr> : ");
    // [^\n] => [] 괄호 안에 문자를 읽기 + ^(Not)\n(줄바꿈)
    // = 줄바꿈 외 문자 읽기
    scanf(" %[^\n]", &inputStr);

    for (int i = 0; i < 100; i++)
    {
        if (inputStr[i] == '\0')
            break;
        inptLen += 1;
    }

    printf("찾는 문자열 <subStr> : ");
    scanf(" %[^\n]", &subStr);

    for (int i = 0; i < 100; i++)
    {
        if (subStr[i] == '\0')
            break;
        printf("%c", subStr[i]);
        subLen += 1;
    }

    // 찾을 문자열이 입력 문자열보다 긴 경우 ERROR
    if (subLen > inptLen)
    {
        printf("\nERROR: subStr lentgh > inputStr lenth\n");
        return;
    }

    printf("의 위치 : ");

    for (int i = 0; i < inptLen; i++)
    {
        int cnt = 0;
        // 찾는 문자열의 처음 글자가 맞을 경우 탐색 시작
        if (inputStr[i] == subStr[0])
        {
            // 찾는 문자열의 길이가 1인 경우 추가 탐색 필요 없으므로 continue
            if (subLen == 1)
            {
                printf("%d번째 ", i + 1);
                continue;
            }
            for (int j = 1; j < subLen; j++)
                if (subStr[j] == inputStr[i + j])
                {
                    cnt += 1;
                }
            if (cnt + 1 == subLen)
            {
                printf("%d~%d번째 ", i + 1, (i + 1) + cnt);
                // 이미 찾은 문자열을 또 탐색하지 않도록 방지
                // ex) asdasdasd 입력, sub asdasd인 경우
                // 아래 코드가 없으면 위치가 1~6, 4~9로 중복되어 나옴
                i = i + cnt;
            }
        }
    }
}