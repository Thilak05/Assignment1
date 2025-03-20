#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int data[MAX];
    int top;
} Stack;

void initStack(Stack *stack) {
    stack->top = -1;
}

int isFull(Stack *stack) {
    return stack->top == MAX - 1;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, int value) {
    if (isFull(stack)) {
        printf("Error: Stack Overflow! Cannot push %d.\n", value);
        return;
    }
    stack->data[++stack->top] = value;
    printf("Pushed: %d\n", value);
}

int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Error: Stack Underflow! Nothing to pop.\n");
        return -1;
    }
    int value = stack->data[stack->top--];
    printf("Popped: %d\n", value);
    return value;
}

void display(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Current Stack: ");
    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->data[i]);
    }
    printf("\n");
}

void functionCall(Stack *stack, int callID) {
    printf("\nFunction %d called.\n", callID);
    push(stack, callID);
    display(stack);
    printf("Processing in function %d...\n", callID);
    int restored = pop(stack);
    printf("Function %d returns, restoring data: %d\n", callID, restored);
}

int main() {
    Stack stack;
    initStack(&stack);

    printf("Simulating function calls using stack:\n");

    functionCall(&stack, 1);
    functionCall(&stack, 2);
    functionCall(&stack, 3);

    printf("\nFinal stack state:\n");
    display(&stack);

    return 0;
}
