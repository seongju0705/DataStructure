#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int element;    //스택 원소(element)의 자료형을 int로 정의

typedef struct stackNode {      //스택의 노드를 구조체로 정의
    element data;
    struct stackNode *link;
} stackNode;

void push(element item, stackNode **top1) {
    stackNode* temp = (stackNode*) malloc(sizeof(stackNode));
    temp->data = item;
    temp->link = *top1;     //삽입 노드를 top의 위에 연결
    *top1 = temp;   //top 위치를 삽입 노드로 이동
}

element pop(stackNode **top1) {
    element item;
    stackNode* temp = *top1;
    item = temp->data;
    *top1 = (*top1)->link;
    free(temp);     //temp 공간 해제
    return item;
}

void reverse_stack(stackNode **top0) {
    stackNode *top1 = NULL;
    stackNode *top2 = NULL;

    while(*top0 != NULL) {
        push(pop(top0), &top1);
    }
    while(top1 != NULL) {
        push(pop(&top1), &top2);
    }
    while(top2 != NULL) {
        push(pop(&top2), top0);
    }
}

void printStack(stackNode **top) {      
    stackNode* p = *top;
    printf("STACK [ ");
    while (p) {
        printf("%d ", p->data);
        p = p->link;
    }
    printf("] ");
}

int main() {
    int data;
    stackNode *top = NULL;
    push(1, &top);
    push(2, &top);
    push(3, &top);
    
    reverse_stack(&top);    //push, pop 과정을 함축
    printStack(&top);       //스택의 원소를 top에서 bottom 순서로 출력
    return 0;
}