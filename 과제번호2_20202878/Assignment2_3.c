#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100

typedef char element;
element stack[MAX_STACK_SIZE];
int top;

void init_stack() {
    top = -1;
}

int is_Empty() {
    return(top == -1);
}

int is_Full() {
    return(top) == (MAX_STACK_SIZE - 1);
}

void push(element item) {

    stack[++top] = item;
}

element pop() {
    return stack[top--];
}

element peek() {
    return stack[top];
}

//연산자의 우선순위 반환
int prec(char op) {     
    switch(op) {
        case '(': case ')':
            return 0;
        case '+': case'-':
            return 1;
        case '*': case'/':
            return 2;
    }
    return -1;
}

//수식을 역순으로 변경
void reverse_exp(char exp[]) {
    int i = 0, j = 0;
    int len = strlen(exp);
    char *a = (char*)malloc(sizeof(char) * (len + 1));

    init_stack();
    //exp에 들어있는 요소를 배열 a에 옮김
    for (i = 0; i < len; i++) {
        a[i] = exp[i];
    }

    //스택에 배열 a의 요소들 push
    for (i = 0; i < len; i++) {
        if (a[i] == '(')
            push(')');
        else if (a[i] == ')')
            push('(');
        else
            push(a[i]);
    }

    //exp에 스택에 있는 요소들을 pop하여 나온 원소들 삽입
    for (i = 0; i < len; i++) {
        exp[i] = pop();
    }
}

//수식 변환
element* infix_to_postfix(char exp[]) {
    int i, idx = 0;
    char ch, op;
    int len = strlen(exp);
    element* postfix_arr = (element*)malloc(MAX_STACK_SIZE);

    init_stack();
    for (i = 0; i < len; i++) {
        ch = exp[i];

        //일반 숫자의 경우
        if ('0' <= ch && ch <= '9') {
            postfix_arr[idx++] = ch;
        }
        //연산자 +, -, *, /의 경우
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!is_Empty() && (prec(ch) <= prec(peek()))) {
                postfix_arr[idx++] = peek();
                pop();
            }
            push(ch);
        }
        //'('의 경우 무조건 스택에 추가
        else if (ch == '(') {
            push(ch);
        }
        //')'의 경우 '('가 나올 때까지 스택에서 pop하여 추가
        else if (ch == ')') {
            op = pop();
            while (op != '(') {
                postfix_arr[idx++] = op;
                op = pop();
            }
        }
    }

    while (!is_Empty()) {    //스택에 저장된 연산자들 출력
        op = peek();
        pop();
        postfix_arr[idx++] = op;
    }
    postfix_arr[idx] = '\0';        //문자열의 끝 지정
    return postfix_arr;
}

int main() {
    char expr[MAX_STACK_SIZE];


    printf("중위 표기식: ");
    scanf("%s", expr);
    reverse_exp(expr);      //역순 변경
    element *result = infix_to_postfix(expr);       //후위표기식으로 변환
    reverse_exp(result);        //후위표기식을 역순으로 변경
    printf("전위 표기식: %s\n", result);

    return 0;
}