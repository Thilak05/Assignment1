#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_NAME_LENGTH 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    int priority;
    int burst_time;
} Process;

void swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Process processes[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && processes[left].priority > processes[largest].priority)
        largest = left;

    if (right < n && processes[right].priority > processes[largest].priority)
        largest = right;

    if (largest != i) {
        swap(&processes[i], &processes[largest]);
        heapify(processes, n, largest);
    }
}

void heapSort(Process processes[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(processes, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(&processes[0], &processes[i]);
        heapify(processes, i, 0);
    }
}

int readProcesses(Process processes[]) {
    FILE *file = fopen("processes.txt", "r");
    if (file == NULL) {
        printf("No process list found.\n");
        return 0;
    }

    int count = 0;
    while (count < MAX_TASKS && fscanf(file, " %[^,], %d, %d", 
           processes[count].name, &processes[count].priority, &processes[count].burst_time) == 3) {
        count++;
    }

    fclose(file);
    return count;
}

void writeProcesses(Process processes[], int count) {
    FILE *file = fopen("processes.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s, %d, %d\n", processes[i].name, processes[i].priority, processes[i].burst_time);
    }

    fclose(file);
}

void addProcess() {
    Process processes[MAX_TASKS];
    int count = readProcesses(processes);

    if (count >= MAX_TASKS) {
        printf("Process list is full!\n");
        return;
    }

    printf("Enter process name: ");
    scanf(" %[^\n]s", processes[count].name);
    printf("Enter priority (higher value = higher priority): ");
    scanf("%d", &processes[count].priority);
    printf("Enter burst time (execution time in ms): ");
    scanf("%d", &processes[count].burst_time);
    count++;

    heapSort(processes, count);
    writeProcesses(processes, count);

    printf("Process added and sorted successfully!\n");
}

void displayProcesses() {
    Process processes[MAX_TASKS];
    int count = readProcesses(processes);

    if (count == 0) {
        printf("No processes available.\n");
        return;
    }

    printf("\nScheduled Processes (Highest Priority First):\n");
    printf("-------------------------------------------------\n");
    printf("Process Name\tPriority\tBurst Time (ms)\n");
    printf("-------------------------------------------------\n");

    for (int i = count - 1; i >= 0; i--) {
        printf("%s\t\t%d\t\t%d\n", processes[i].name, processes[i].priority, processes[i].burst_time);
    }
    printf("-------------------------------------------------\n");
}

void executeProcesses() {
    Process processes[MAX_TASKS];
    int count = readProcesses(processes);

    if (count == 0) {
        printf("No processes available for execution.\n");
        return;
    }

    printf("\nExecuting Processes (Highest Priority First):\n");
    for (int i = count - 1; i >= 0; i--) {
        printf("Executing process: %s (Priority: %d, Burst Time: %d ms)\n", 
               processes[i].name, processes[i].priority, processes[i].burst_time);
    }

    FILE *file = fopen("processes.txt", "w");
    fclose(file);

    printf("\nAll processes executed successfully!\n");
}

int main() {
    int choice;

    while (1) {
        printf("\nPriority-Based Process Scheduler\n");
        printf("1. Add Process\n");
        printf("2. Display Sorted Processes\n");
        printf("3. Execute Processes\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProcess();
                break;
            case 2:
                displayProcesses();
                break;
            case 3:
                executeProcesses();
                break;
            case 4:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
