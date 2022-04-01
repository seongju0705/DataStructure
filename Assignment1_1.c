#include <stdio.h>

void HanoiTowerMove(int num, char from, char by, char to)
{
    if (num == 1) {     //이동할 원판의 수 1개인 경우
        printf("원판1을 %c에서 %c로 이동\n", from, to);
    }
    else {
        HanoiTowerMove(num - 1, from, to, by);      //재귀함수, to와 by 원판 바꿈
        printf("원판%d을 %c에서 %c로 이동\n", num, from, to);
        HanoiTowerMove(num - 1, by, from, to);      //재귀함수, from과 by 원판 바꿈
    }
}

int main() 
{
    HanoiTowerMove(4, 'A', 'B', 'C');       //4개의 원판을 'A'에서 'C'로 이동
    return 0;
}