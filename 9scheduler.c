#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Task {
    int taskId;
    int executionTime;
    struct Task* next;
} Task;

typedef struct Scheduler {
    Task* front;
    Task* rear;
} Scheduler;

Task* createTask(int taskId, int executionTime) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    newTask->taskId = taskId;
    newTask->executionTime = executionTime;
    newTask->next = NULL;
    return newTask;
}

Scheduler* createScheduler() {
    Scheduler* scheduler = (Scheduler*)malloc(sizeof(Scheduler));
    scheduler->front = scheduler->rear = NULL;
    return scheduler;
}

void addTask(Scheduler* scheduler, int taskId, int executionTime) {
    Task* newTask = createTask(taskId, executionTime);

    if (scheduler->rear == NULL) {
        scheduler->front = scheduler->rear = newTask;
        return;
    }

    scheduler->rear->next = newTask;
    scheduler->rear = newTask;
}

void executeTask(Scheduler* scheduler) {
    if (scheduler->front == NULL) {
        printf("No tasks in the queue!\n");
        return;
    }

    Task* temp = scheduler->front;
    printf("Executing Task ID: %d, Execution Time: %d seconds\n", temp->taskId, temp->executionTime);

    scheduler->front = scheduler->front->next;
    if (scheduler->front == NULL) {
        scheduler->rear = NULL;
    }

    free(temp);
}

void displayTasks(Scheduler* scheduler) {
    if (scheduler->front == NULL) {
        printf("No tasks in the queue.\n");
        return;
    }

    Task* temp = scheduler->front;
    printf("Task Queue:\n");
    while (temp != NULL) {
        printf("[Task ID: %d, Execution Time: %d] -> ", temp->taskId, temp->executionTime);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    Scheduler* scheduler = createScheduler();
    int choice, taskId, executionTime;

    while (1) {
        printf("\nScheduler Menu:\n");
        printf("1. Add Task\n");
        printf("2. Execute Task\n");
        printf("3. Display Tasks\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Task ID: ");
                scanf("%d", &taskId);
                printf("Enter Execution Time: ");
                scanf("%d", &executionTime);
                addTask(scheduler, taskId, executionTime);
                break;
            case 2:
                executeTask(scheduler);
                break;
            case 3:
                displayTasks(scheduler);
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
