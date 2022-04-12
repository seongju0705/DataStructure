#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    float coef;
    int expon;
    struct node* link;
} listnode;

//노드 연결
listnode* insert(listnode* head, float coef, int expon) {
    listnode* temp = (listnode*) malloc(sizeof(listnode));
    temp->coef = coef;
    temp->expon = expon;
    temp->link = NULL;
    if (head == NULL || expon > head->expon) {
        temp->link = head;
        head = temp;
    }
    else {
        listnode* temp2;
        temp2 = head;
        while (temp2->link != NULL && temp2->link->expon > expon)
            temp2 = temp2->link;
        temp->link = temp2->link;
        temp2->link = temp;
    }
    return head;
}

void poly_print(listnode* head) {
    listnode* temp = head;
    while(temp != NULL) {
        printf("%3.1fx^%d", temp->coef, temp->expon);
        temp = temp->link;
        if (temp != NULL)
            printf(" + ");
        else printf("\n");
    }  
}

void poly_add(listnode* head1, listnode* head2) {
    listnode* a = head1;
    listnode* b = head2;
    listnode* head3 = NULL;

    while (a != NULL && b != NULL) {
        if (a->expon == b -> expon) {       //A의 차수 == B의 차수 -> 덧셈 진행
            head3 = insert(head3, a->coef + b->coef, a->expon);
            a = a->link;
            b = b->link;
        }
        else if (a -> expon > b -> expon) {         //A의 차수 > B의 차수 -> A만 이동
            head3 = insert(head3, a->coef, a->expon);
            a = a->link;
        }
        else if (a -> expon < b -> expon) {         //A의 차수 < B의 차수 -> B만 이동
            head3 = insert(head3, b -> coef, b -> expon);
            b = b->link;
        }
    }

    while(a != NULL) {
        head3 = insert(head3, a->coef, a->expon);
        a = a->link;
    }
    while (b != NULL) {
        head3 = insert(head3, b->coef, b->expon);
        b = b->link;
    }
    poly_print(head3);
}

int main() {
    listnode* head1 = NULL;
    listnode* head2 = NULL;
    listnode* head3 = NULL;

    //head1 연결리스트 생성
    head1 = insert(head1, 3, 14);
    head1 = insert(head1, 2, 8);
    head1 = insert(head1, 1, 0);

    //head2 연결리스트 생성
    head2 = insert(head2, 8, 14);
    head2 = insert(head2, -3, 10);
    head2 = insert(head2, 10, 6);

    poly_print(head1);
    poly_print(head2);
    poly_add(head1, head2);
    return 0;
}