#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

typedef struct {
    int ticketNumber;
    char name[50];
} Customer;

typedef struct {
    Customer queue[MAX];
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

void enqueue(Queue *q, int ticket, char name[]) {
    if (isFull(q)) {
        printf("Queue is full! Cannot book more tickets.\n");
        return;
    }
    if (q->front == -1) q->front = 0;
    q->rear++;
    q->queue[q->rear].ticketNumber = ticket;
    strcpy(q->queue[q->rear].name, name);
    printf("Ticket booked successfully! Token No: %d, Name: %s\n", ticket, name);
}

void dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("No tickets to serve.\n");
        return;
    }
    printf("Serving Ticket No: %d, Name: %s\n", q->queue[q->front].ticketNumber, q->queue[q->front].name);
    q->front++;
}

void display(Queue *q) {
    if (isEmpty(q)) {
        printf("No customers in queue.\n");
        return;
    }
    printf("Waiting List:\n");
    for (int i = q->front; i <= q->rear; i++) {
        printf("Token No: %d, Name: %s\n", q->queue[i].ticketNumber, q->queue[i].name);
    }
}

int main() {
    Queue q;
    initQueue(&q);

    int choice, ticket = 1;
    char name[50];

    while (1) {
        printf("\n--- Ticket Reservation System ---\n");
        printf("1. Book Ticket\n");
        printf("2. Serve Next Ticket\n");
        printf("3. Display Waiting List\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter Name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                enqueue(&q, ticket++, name);
                break;
            case 2:
                dequeue(&q);
                break;
            case 3:
                display(&q);
                break;
            case 4:
                printf("Exiting Ticket System.\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
