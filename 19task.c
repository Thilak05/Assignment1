#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Task {
    int taskID;
    char description[100];
    struct Task* next;
} Task;

typedef struct {
    Task* front;
    Task* rear;
} TaskQueue;

void initQueue(TaskQueue* q) {
    q->front = q->rear = NULL;
}

int isEmpty(TaskQueue* q) {
    return (q->front == NULL);
}

void enqueue(TaskQueue* q, int id, char* desc) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    if (!newTask) {
        printf("Memory allocation failed!\n");
        return;
    }
    newTask->taskID = id;
    strcpy(newTask->description, desc);
    newTask->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newTask;
    } else {
        q->rear->next = newTask;
        q->rear = newTask;
    }
    printf("Task %d added: %s\n", id, desc);
}

void dequeue(TaskQueue* q) {
    if (isEmpty(q)) {
        printf("No tasks to process!\n");
        return;
    }
    Task* temp = q->front;
    printf("Processing Task %d: %s\n", temp->taskID, temp->description);
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
}

void displayQueue(TaskQueue* q) {
    if (isEmpty(q)) {
        printf("No pending tasks.\n");
        return;
    }
    Task* temp = q->front;
    printf("Pending Tasks:\n");
    while (temp) {
        printf("Task %d: %s\n", temp->taskID, temp->description);
        temp = temp->next;
    }
}

int main() {
    TaskQueue q;
    initQueue(&q);

    int choice, taskID = 1;
    char desc[100];

    while (1) {
        printf("\n--- Task Queue System ---\n");
        printf("1. Add Task\n");
        printf("2. Process Task\n");
        printf("3. View Pending Tasks\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter Task Description: ");
                fgets(desc, sizeof(desc), stdin);
                desc[strcspn(desc, "\n")] = 0;
                enqueue(&q, taskID++, desc);
                break;
            case 2:
                dequeue(&q);
                break;
            case 3:
                displayQueue(&q);
                break;
            case 4:
                printf("Exiting Task Queue System.\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
