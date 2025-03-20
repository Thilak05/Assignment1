#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100  

typedef struct {
    int top;
    char arr[MAX];
} Stack;

void initStack(Stack* stack) {
    stack->top = -1;
}

int isFull(Stack* stack) {
    return stack->top == MAX - 1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, char ch) {
    if (isFull(stack)) {
        printf("Stack Overflow!\n");
        return;
    }
    stack->arr[++stack->top] = ch;
}

char pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow!\n");
        return '\0';
    }
    return stack->arr[stack->top--];
}

void reverseString(char str[]) {
    Stack stack;
    initStack(&stack);

    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        push(&stack, str[i]);
    }

    for (int i = 0; i < len; i++) {
        str[i] = pop(&stack);
    }
}

int main() {
    char str[MAX];

    printf("Enter a string: ");
    fgets(str, MAX, stdin);
    
    size_t len = strlen(str);
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

    reverseString(str);

    printf("Reversed string: %s\n", str);

    return 0;
}
