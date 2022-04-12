#include <stdio.h>

typedef struct{
    int row;
    int col;
    int value;
} term;

void smTranspose(term a[], term b[]) {
    int m, n, v, i, j, p;
    m = a[0].row;       //희소행렬 a의 행 수
    n = a[0].col;       //희소행렬 a의 열 수
    v = a[0].value;     //희소행렬 a에서 0이 아닌 원소 수
    b[0].row = n;       //전치행렬 b의 행 수
    b[0].col = m;       //전치행렬 b의 열 수
    b[0].value = v;     //전치행렬 b의 원소 수
    if (v > 0) {        //0이 아닌 원소가 있는 경우에만 전치 연산 수행
        p = 1;
        for (i = 0; i < n; i++) {
            //희소행렬 a의 열별로 전치 반복 수행
            for (j = 1; j <= v; j++) {
                //0이 아닌 원소 수에 대해서만 반복 수행
                if (a[j].col == i) {
                    //현재의 열에 속하는 원소가 있으면 b[]에 삽입
                    b[p].row = a[j].col;
                    b[p].col = a[j].row;
                    b[p].value = a[j].value;
                    p++;
                }
            }
        }
    }
}

int main() {
    //파일 오픈
    FILE *ifp;
    FILE *ofp;
    ifp = fopen("input.txt", "r");
    ofp = fopen("output.txt", "w");

    int i, j;
    term a[9];
    term b[9];

    //fscanf를 통해 input.txt에서 값 받아오기
    for (i = 0; i < 9; i++) {
        fscanf(ifp, "%d", &a[i].row);
        fscanf(ifp, "%d", &a[i].col);
        fscanf(ifp, "%d", &a[i].value);
    }


    smTranspose(a, b);  

    //fprintf를 통해 output.txt에 출력하기
    for (i = 0; i < 9; i++)
        fprintf(ofp, "%d %d %d\n", b[i].row, b[i].col, b[i].value);

    fclose(ifp);
    fclose(ofp);
    return 0;
}
