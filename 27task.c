#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_NAME_LENGTH 100

// Structure to store task details
typedef struct {
    char name[MAX_NAME_LENGTH];
    int priority;
} Task;

// Function to swap two tasks
void swap(Task *a, Task *b) {
    Task temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify function for Heap Sort
void heapify(Task tasks[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && tasks[left].priority > tasks[largest].priority)
        largest = left;

    if (right < n && tasks[right].priority > tasks[largest].priority)
        largest = right;

    if (largest != i) {
        swap(&tasks[i], &tasks[largest]);
        heapify(tasks, n, largest);
    }
}

// Heap Sort function
void heapSort(Task tasks[], int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(tasks, n, i);

    // Extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        swap(&tasks[0], &tasks[i]);
        heapify(tasks, i, 0);
    }
}

// Function to read tasks from file
int readTasks(Task tasks[]) {
    FILE *file = fopen("tasks.txt", "r");
    if (file == NULL) {
        printf("No task list found.\n");
        return 0;
    }

    int count = 0;
    while (count < MAX_TASKS && fscanf(file, " %[^,], %d", tasks[count].name, &tasks[count].priority) == 2) {
        count++;
    }

    fclose(file);
    return count;
}

// Function to write sorted tasks to file
void writeTasks(Task tasks[], int count) {
    FILE *file = fopen("tasks.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s, %d\n", tasks[i].name, tasks[i].priority);
    }

    fclose(file);
}

// Function to add a new task and sort the list
void addTask() {
    Task tasks[MAX_TASKS];
    int count = readTasks(tasks);

    if (count >= MAX_TASKS) {
        printf("Task list is full!\n");
        return;
    }

    printf("Enter task name: ");
    scanf(" %[^\n]s", tasks[count].name);
    printf("Enter priority (higher value means higher priority): ");
    scanf("%d", &tasks[count].priority);
    count++;

    // Sort the tasks by priority (Descending order)
    heapSort(tasks, count);

    // Write sorted tasks back to file
    writeTasks(tasks, count);

    printf("Task added and sorted successfully!\n");
}

// Function to display sorted tasks
void displayTasks() {
    Task tasks[MAX_TASKS];
    int count = readTasks(tasks);

    if (count == 0) {
        printf("No tasks available.\n");
        return;
    }

    printf("\nSorted Task List (Highest Priority First):\n");
    for (int i = 0; i < count; i++) {
        printf("%s - Priority: %d\n", tasks[i].name, tasks[i].priority);
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nTask Scheduler\n");
        printf("1. Add Task\n");
        printf("2. Display Sorted Tasks\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                displayTasks();
                break;
            case 3:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
