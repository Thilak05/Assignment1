#include <stdio.h>
#include <stdlib.h>

#define ROWS 5
#define COLS 5

typedef struct {
    int x, y;
} Position;

typedef struct {
    Position positions[ROWS * COLS];
    int top;
} Stack;

void initStack(Stack* stack) {
    stack->top = -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, int x, int y) {
    stack->top++;
    stack->positions[stack->top].x = x;
    stack->positions[stack->top].y = y;
}

Position pop(Stack* stack) {
    return stack->positions[stack->top--];
}

int isValidMove(int maze[ROWS][COLS], int visited[ROWS][COLS], int x, int y) {
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS && maze[x][y] == 0 && !visited[x][y]);
}

void solveMaze(int maze[ROWS][COLS], int startX, int startY, int endX, int endY) {
    Stack stack;
    initStack(&stack);
    int visited[ROWS][COLS] = {0};
    push(&stack, startX, startY);
    while (!isEmpty(&stack)) {
        Position pos = pop(&stack);
        int x = pos.x, y = pos.y;
        visited[x][y] = 1;
        printf("(%d, %d) -> ", x, y);
        if (x == endX && y == endY) {
            printf("Reached the destination!\n");
            return;
        }
        if (isValidMove(maze, visited, x, y + 1)) push(&stack, x, y + 1);
        if (isValidMove(maze, visited, x + 1, y)) push(&stack, x + 1, y);
        if (isValidMove(maze, visited, x, y - 1)) push(&stack, x, y - 1);
        if (isValidMove(maze, visited, x - 1, y)) push(&stack, x - 1, y);
    }
    printf("No path found!\n");
}

int main() {
    int maze[ROWS][COLS] = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };
    int startX = 0, startY = 0;
    int endX = 4, endY = 4;
    printf("Solving Maze using Backtracking:\n");
    solveMaze(maze, startX, startY, endX, endY);
    return 0;
}
