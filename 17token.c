#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int tokens[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return (q->front == -1 || q->front > q->rear);
}

int isFull(Queue *q) {
    return (q->rear == MAX - 1);
}

void enqueue(Queue *q, int token) {
    if (isFull(q)) {
        printf("Queue is full! Cannot issue more tokens.\n");
        return;
    }
    if (q->front == -1) q->front = 0;
    q->tokens[++q->rear] = token;
    printf("Token %d issued.\n", token);
}

void dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("No tokens to serve.\n");
        return;
    }
    printf("Now serving Token %d.\n", q->tokens[q->front]);
    q->front++;
}

void display(Queue *q) {
    if (isEmpty(q)) {
        printf("No customers in queue.\n");
        return;
    }
    printf("Tokens waiting: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->tokens[i]);
    }
    printf("\n");
}

int main() {
    Queue q;
    initQueue(&q);

    int choice, token = 1;

    while (1) {
        printf("\n--- Token System Menu ---\n");
        printf("1. Issue New Token\n");
        printf("2. Serve Next Token\n");
        printf("3. Display Waiting Tokens\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (token > 0) {
                    enqueue(&q, token++);
                } else {
                    printf("Token counter overflow! Cannot issue more tokens.\n");
                }
                break;
            case 2:
                dequeue(&q);
                break;
            case 3:
                display(&q);
                break;
            case 4:
                printf("Exiting Token System.\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
