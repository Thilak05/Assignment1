#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10
#define MAX_LEN 50

typedef struct {
    char operations[MAX][MAX_LEN];
    int top;
} UndoStack;

void initStack(UndoStack *stack) {
    stack->top = -1;
}

int isFull(UndoStack *stack) {
    return stack->top == MAX - 1;
}

int isEmpty(UndoStack *stack) {
    return stack->top == -1;
}

void push(UndoStack *stack, char *operation) {
    if (isFull(stack)) {
        printf("Error: Undo stack is full! Cannot save more operations.\n");
        return;
    }
    stack->top++;
    strcpy(stack->operations[stack->top], operation);
    printf("Saved: \"%s\"\n", operation);
}

void pop(UndoStack *stack) {
    if (isEmpty(stack)) {
        printf("Nothing to undo.\n");
        return;
    }
    printf("Undo: \"%s\" removed.\n", stack->operations[stack->top]);
    stack->top--;
}

void display(UndoStack *stack) {
    if (isEmpty(stack)) {
        printf("No operations to show.\n");
        return;
    }
    printf("\nCurrent Operations:\n");
    for (int i = 0; i <= stack->top; i++) {
        printf("%d. %s\n", i + 1, stack->operations[i]);
    }
}

int main() {
    UndoStack stack;
    initStack(&stack);
    
    int choice;
    char operation[MAX_LEN];

    while (1) {
        printf("\nUndo System Menu:\n");
        printf("1. Enter New Operation\n");
        printf("2. Undo Last Operation\n");
        printf("3. Show All Operations\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf(" %[^\n]", operation);
        
        choice = atoi(operation);

        switch (choice) {
            case 1:
                printf("Enter operation: ");
                scanf(" %[^\n]", operation);
                push(&stack, operation);
                break;
            case 2:
                pop(&stack);
                break;
            case 3:
                display(&stack);
                break;
            case 4:
                printf("Exiting undo system.\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    
    return 0;
}
