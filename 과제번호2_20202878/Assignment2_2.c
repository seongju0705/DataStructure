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

//�������� �켱���� ��ȯ
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

//���� ��ȯ
element* infix_to_postfix(char exp[]) {
    int i, idx = 0;
    char ch, op;
    int len = strlen(exp);
    element* postfix_arr = (element*)malloc(MAX_STACK_SIZE);

    init_stack();
    for (i = 0; i < len; i++) {
        ch = exp[i];

        //�Ϲ� ������ ���
        if ('0' <= ch && ch <= '9') {
            postfix_arr[idx++] = ch;
        }
        //������ +, -, *, /�� ���
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!is_Empty() && (prec(ch) <= prec(peek()))) {
                postfix_arr[idx++] = peek();
                pop();
            }
            push(ch);
        }
        //'('�� ��� ������ ���ÿ� �߰�
        else if (ch == '(') {
            push(ch);
        }
        //')'�� ��� '('�� ���� ������ ���ÿ��� pop�Ͽ� �߰�
        else if (ch == ')') {
            op = pop();
            while (op != '(') {
                postfix_arr[idx++] = op;
                op = pop();
            }
        }
    }

    while (!is_Empty()) {    //���ÿ� ����� �����ڵ� ���
        op = peek();
        pop();
        postfix_arr[idx++] = op;
    }
    postfix_arr[idx] = '\0';        //���ڿ��� �� ����
    return postfix_arr;
}

//���� ǥ��� ���� ���
int evalPostfix(char exp[]) {       
    int opr1, opr2, value, i = 0;
    int length = strlen(exp);
    char symbol;
    
    init_stack();    
    for (i = 0; i < length; i++) {
        symbol = exp[i];
        if (symbol != '+' && symbol != '-' && symbol != '*' && symbol != '/') {
            value = symbol - '0';   //char�� ���ڷ� ��ȯ
            push(value);
        }
        else {
            opr2 = pop();
            opr1 = pop();
            switch(symbol) {        //���� opr1�� opr2�� ���� symbol�� ����� �����ڸ� ����
                case '+': push(opr1 + opr2); break;
                case '-': push(opr1 - opr2); break;
                case '*': push(opr1 * opr2); break;
                case '/': push(opr1 / opr2); break;
            }
        }
    }

    return pop();       //���Ŀ� ���� ó���� ��ģ �� ���ÿ� �����ִ� ������� ��ȯ
}

int main() {
    char expr[MAX_STACK_SIZE];


    printf("���� ǥ���: ");
    scanf("%s", expr);
    element *result = infix_to_postfix(expr);
    printf("���� ǥ���: %s\n", result);
    printf("��� ��: %d\n", evalPostfix(result));

    return 0;
}