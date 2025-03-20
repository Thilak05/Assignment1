#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Process {
    int pid;
    char name[50];
    struct Process* next;
} Process;

typedef struct {
    Process* front;
    Process* rear;
} FCFSQueue;

void initQueue(FCFSQueue* q) {
    q->front = q->rear = NULL;
}

int isEmpty(FCFSQueue* q) {
    return (q->front == NULL);
}

void enqueue(FCFSQueue* q, int pid, char* pname) {
    Process* newProcess = (Process*)malloc(sizeof(Process));
    if (!newProcess) {
        printf("Memory allocation failed!\n");
        return;
    }
    newProcess->pid = pid;
    strcpy(newProcess->name, pname);
    newProcess->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newProcess;
    } else {
        q->rear->next = newProcess;
        q->rear = newProcess;
    }
    printf("Process %d (%s) added to queue.\n", pid, pname);
}

void allocateResource(FCFSQueue* q) {
    if (isEmpty(q)) {
        printf("No processes in queue to allocate resources!\n");
        return;
    }
    Process* temp = q->front;
    printf("Allocating resource to Process %d (%s)...\n", temp->pid, temp->name);
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
}

void displayQueue(FCFSQueue* q) {
    if (isEmpty(q)) {
        printf("No pending processes in queue.\n");
        return;
    }
    Process* temp = q->front;
    printf("Pending Process Queue:\n");
    while (temp) {
        printf("Process %d: %s\n", temp->pid, temp->name);
        temp = temp->next;
    }
}

int main() {
    FCFSQueue queue;
    initQueue(&queue);

    int choice, pid = 1;
    char pname[50];

    while (1) {
        printf("\n--- Shared Resource Allocation (FCFS) ---\n");
        printf("1. Request Resource (Add Process)\n");
        printf("2. Allocate Resource (Process Request)\n");
        printf("3. View Waiting Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter Process Name: ");
                fgets(pname, sizeof(pname), stdin);
                pname[strcspn(pname, "\n")] = 0;
                enqueue(&queue, pid++, pname);
                break;
            case 2:
                allocateResource(&queue);
                break;
            case 3:
                displayQueue(&queue);
                break;
            case 4:
                printf("Exiting Shared Resource Allocation System.\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
