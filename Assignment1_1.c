#include <stdio.h>

void HanoiTowerMove(int num, char from, char by, char to)
{
    if (num == 1) {     //�̵��� ������ �� 1���� ���
        printf("����1�� %c���� %c�� �̵�\n", from, to);
    }
    else {
        HanoiTowerMove(num - 1, from, to, by);      //����Լ�, to�� by ���� �ٲ�
        printf("����%d�� %c���� %c�� �̵�\n", num, from, to);
        HanoiTowerMove(num - 1, by, from, to);      //����Լ�, from�� by ���� �ٲ�
    }
}

int main() 
{
    HanoiTowerMove(4, 'A', 'B', 'C');       //4���� ������ 'A'���� 'C'�� �̵�
    return 0;
}