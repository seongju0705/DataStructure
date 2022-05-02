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
    return (top == -1);
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

//후위 표기법 수식 계산
int evalPostfix(char exp[]) {       
    int opr1, opr2, value, i = 0;
    int length = strlen(exp);
    char symbol;
    
    init_stack();    
    for (i = 0; i < length; i++) {
        symbol = exp[i];
        if (symbol != '+' && symbol != '-' && symbol != '*' && symbol != '/') {
            value = symbol - '0';   //char형 숫자로 변환
            push(value);
        }
        else {
            opr2 = pop();
            opr1 = pop();
            switch(symbol) {        //변수 opr1과 opr2에 대해 symbol에 저장된 연산자를 연산
                case '+': push(opr1 + opr2); break;
                case '-': push(opr1 - opr2); break;
                case '*': push(opr1 * opr2); break;
                case '/': push(opr1 / opr2); break;
            }
        }
    }

    return pop();       //수식에 대한 처리를 마친 후 스택에 남아있는 결과값을 반환
}

int main() {
    char expr[MAX_STACK_SIZE];


    printf("중위 표기식: ");
    scanf("%s", expr);
    element *result = infix_to_postfix(expr);
    printf("후위 표기식: %s\n", result);
    printf("계산 값: %d\n", evalPostfix(result));

    return 0;
}