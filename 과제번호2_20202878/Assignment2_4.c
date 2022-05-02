#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define EXIT_ROW 14
#define EXIT_COL 15

typedef struct {
    short int x;
    short int y;

} offsets;
offsets move[8] = {{-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}};

typedef struct {
    short int row;
    short int col;
    short int dir;
} element;
element stack[MAX_STACK_SIZE];

//미로 생성
int maze[EXIT_ROW+2][EXIT_COL+2] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,1,0,0,1,1,0,0,0,0,1,0,0,1},
    {1,0,1,0,1,0,0,0,0,0,1,0,0,0,0,1,1},
    {1,0,1,1,1,0,0,1,0,1,1,1,0,1,0,1,1},
    {1,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1},
    {1,0,1,0,0,0,1,1,1,0,1,0,1,1,1,0,1},
    {1,0,1,0,0,1,1,0,1,0,1,0,0,0,0,0,1},
    {1,0,1,1,1,1,0,0,1,0,0,1,0,1,1,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0},
    {1,0,1,1,0,1,0,0,0,1,0,0,1,1,0,0,1},
    {1,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,1,1},
    {1,1,0,0,0,1,0,0,1,1,1,0,0,0,0,0,1},
    {1,1,0,1,1,0,0,0,0,1,0,0,0,1,1,0,1},
    {1,0,0,0,0,0,0,1,0,0,0,1,0,0,1,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};
int mark[EXIT_ROW+2][EXIT_COL+2];
int top;

void push(element item) {

    stack[++top] = item;
}

element pop() {
    return stack[top--];
}

element peek() {
    return stack[top];
}

void path() {
    int i, row, col, next_row, next_col, dir;
    int found = 0;
    element position;
    mark[1][1] = 1;
    top = 0;
    stack[0].row = 1;
    stack[0].col = 1;
    stack[0].dir = 2;
    while (top > -1 && !found) {
        position = pop();
        row = position.row;
        col = position.col;
        dir = position.dir;

        while (dir < 8 && !found) {
            next_row = row + move[dir].x;
            next_col = col + move[dir].y;
            if (next_row == EXIT_ROW && next_col == EXIT_COL)
                found = 1;
            else if (!maze[next_row][next_col] && !mark[next_row][next_col]) {
                mark[next_row][next_col] = 1;
                position.row = row;
                position.col = col;
                position.dir = ++dir;
                push(position);
                //갱신
                row = next_row;
                col = next_col;
                dir = 0;
            }
                else  
                ++dir;
        }
    }

    if (found) {
        printf("The path is:\n");
        printf("row col\n");
        for (i = 0; i <= top; i++)
            printf("%2d%5d", stack[i].row, stack[i].col);   //스택 경로 출력
        printf("%2d%5d\n", row, col);
        printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
    }
    else printf("The maze does not have a path\n");
}

int main() {
    path();
    return 0;
}

