#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int id;
    int size;
} MemoryBlock;

typedef struct {
    MemoryBlock blocks[MAX];
    int top;
} MemoryStack;

void initStack(MemoryStack *stack) {
    stack->top = -1;
}

int isFull(MemoryStack *stack) {
    return stack->top == MAX - 1;
}

int isEmpty(MemoryStack *stack) {
    return stack->top == -1;
}

void push(MemoryStack *stack, int id, int size) {
    if (isFull(stack)) {
        printf("Error: Memory stack is full! No more memory can be allocated.\n");
        return;
    }
    stack->top++;
    stack->blocks[stack->top].id = id;
    stack->blocks[stack->top].size = size;
    printf("Memory Block %d of %d KB allocated.\n", id, size);
}

void pop(MemoryStack *stack) {
    if (isEmpty(stack)) {
        printf("Error: No memory blocks to free.\n");
        return;
    }
    printf("Memory Block %d of %d KB freed.\n", stack->blocks[stack->top].id, stack->blocks[stack->top].size);
    stack->top--;
}

void display(MemoryStack *stack) {
    if (isEmpty(stack)) {
        printf("Memory Stack is empty. No allocations.\n");
        return;
    }
    printf("\nCurrent Memory Allocations:\n");
    for (int i = stack->top; i >= 0; i--) {
        printf("Block ID: %d, Size: %d KB\n", stack->blocks[i].id, stack->blocks[i].size);
    }
}

int main() {
    MemoryStack memory;
    initStack(&memory);
    
    int choice, id = 1, size;
    
    while (1) {
        printf("\nMemory Management Options:\n");
        printf("1. Allocate Memory (Push)\n");
        printf("2. Free Last Memory Block (Pop)\n");
        printf("3. Display Memory Stack\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter memory size (in KB): ");
                scanf("%d", &size);
                push(&memory, id++, size);
                break;
            case 2:
                pop(&memory);
                break;
            case 3:
                display(&memory);
                break;
            case 4:
                printf("Exiting Memory Manager.\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    
    return 0;
}
