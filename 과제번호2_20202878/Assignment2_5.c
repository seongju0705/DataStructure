#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_QUEUE_SIZE 100

typedef struct {
    int id;
    int arrival_time;
    int service_time;
} element;

typedef struct {
    int front;
    int rear;
    element data[MAX_QUEUE_SIZE];
} QueueType;

void init_queue(QueueType *q) {
    q->rear = -1;
    q->front = -1;
}

int is_empty(QueueType *q) {
    if (q->front == q->rear)
        return 1;
    else return 0;
}

int is_full(QueueType *q) {
    if (q->rear == MAX_QUEUE_SIZE - 1)
        return 1;
    else return 0;
}

void enqueue(QueueType *q, element item) {
    if (is_full(q)) {
        printf("큐가 포화상태");
        exit(1);
    }
    q->data[++(q->rear)] = item;
}

element dequeue(QueueType *q) {
    if (is_empty(q)) {
        printf("큐가 공백상태");
        exit(1);
    }
    element item = q->data[++(q->front)];
    return item;
}

element peek(QueueType *q) {
    if (is_empty(q))
        exit(1);
    else
        return q->data[q->front + 1];
}

int bank_simul() {
    int minutes = 60;
    int total_wait = 0;
    int total_customers = 0;
    int a_service_time = 0;
    int b_service_time = 0;
    int a_service_customer;
    int b_service_customer;
    bool aCounter = true;
    bool bCounter = true;
    QueueType q;
    init_queue(&q);
    srand(time(NULL));

    for (int clock = 0; clock < minutes; clock++) {
        printf("현재시각 = %d\n", clock);
        if ((rand() % 10) < 3) {
            element customer;
            customer.id = total_customers++;
            customer.arrival_time = clock;
            customer.service_time = rand() % 3 + 1;
            enqueue(&q, customer);
            printf("고객 %d이 %d분에 들어옵니다. 업무처리시간 = %d분\n", customer.id, customer.arrival_time, customer.service_time);
        }

        if (a_service_time > 0) {
            printf("고객 %d이 A창구에서 업무처리중입니다.\n", a_service_customer);
            a_service_time--;
            if (a_service_time == 0) {
                aCounter = true;
            }
        }
        else if (aCounter) {
            if (!is_empty(&q)) {
                element customer = dequeue(&q);
                a_service_customer = customer.id;
                a_service_time = customer.service_time;
                printf("고객 %d이 %d분에 A창구에서 업무를 시작합니다. 대기시간은 %d분이었습니다.\n", customer.id, clock, clock - customer.arrival_time);
                aCounter = false;
                total_wait += clock - customer.arrival_time;
            }
        }

        if (b_service_time > 0) {
            printf("고객 %d이 B창구에서 업무처리중입니다.\n", b_service_customer);
            b_service_time--;
            if (b_service_time == 0) {
                bCounter = true;
            }
        }
        else if (!is_empty(&q)) {
            element customer = dequeue(&q);
            b_service_customer = customer.id;
            b_service_time = customer.service_time;
            printf("고객 %d이 %d분에 B창구에서 업무를 시작합니다. 대기시간은 %d분이었습니다.\n", customer.id, clock, clock - customer.arrival_time);
            bCounter = false;
            total_wait += clock - customer.arrival_time;
        }
    }

    printf("전체 대기 시간 = %d분 \n", total_wait);
    return 0;
}

int main() {
    bank_simul();
    return 0;
}