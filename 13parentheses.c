#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char items[MAX];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, char c) {
    if (!isFull(s)) {
        s->items[++(s->top)] = c;
    }
}

char pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    }
    return '\0';
}

int isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

int isBalanced(char *expr) {
    Stack stack;
    initStack(&stack);
    
    for (int i = 0; expr[i] != '\0'; i++) {
        char current = expr[i];
        
        if (current == '(' || current == '{' || current == '[') {
            push(&stack, current);
        } else if (current == ')' || current == '}' || current == ']') {
            if (isEmpty(&stack)) {
                return 0;
            }
            char popped = pop(&stack);
            if (!isMatchingPair(popped, current)) {
                return 0;
            }
        }
    }

    return isEmpty(&stack);
}

int main() {
    char expr[MAX];

    printf("Enter an expression: ");
    scanf("%s", expr);

    if (isBalanced(expr)) {
        printf("Balanced Parentheses\n");
    } else {
        printf("Unbalanced Parentheses\n");
    }

    return 0;
}
