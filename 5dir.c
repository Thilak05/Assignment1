#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char directory[256];
    struct Node* prev;
    struct Node* next;
} Node;

Node* createNode(const char* directory) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->directory, directory);
    newNode->prev = newNode->next = NULL;
    return newNode;
}

void addDirectory(Node** current, const char* directory) {
    Node* newNode = createNode(directory);
    
    if (*current == NULL) {
        *current = newNode;
    } else {
        (*current)->next = newNode;
        newNode->prev = *current;
        *current = newNode;  
    }
}

void moveBackward(Node** current) {
    if (*current && (*current)->prev) {
        *current = (*current)->prev;
        printf("Moved to previous directory: %s\n", (*current)->directory);
    } else {
        printf("No previous directory available.\n");
    }
}

void moveForward(Node** current) {
    if (*current && (*current)->next) {
        *current = (*current)->next;
        printf("Moved to next directory: %s\n", (*current)->directory);
    } else {
        printf("No next directory available.\n");
    }
}

void displayHistory(Node* head) {
    printf("\nHistory of visited directories:\n");
    while (head) {
        printf("%s\n", head->directory);
        head = head->next;
    }
    printf("\n");
}

int main() {
    Node* history = NULL;  
    Node* current = NULL;  

    int choice;
    char dir[256];

    while (1) {
        printf("\nOptions:\n");
        printf("1. Visit new directory\n");
        printf("2. Move to previous directory\n");
        printf("3. Move to next directory\n");
        printf("4. Display history\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();  

        switch (choice) {
            case 1:
                printf("Enter directory path: ");
                fgets(dir, sizeof(dir), stdin);
                dir[strcspn(dir, "\n")] = 0; 
                addDirectory(&current, dir);
                if (history == NULL) {
                    history = current;
                }
                break;

            case 2:
                moveBackward(&current);
                break;

            case 3:
                moveForward(&current);
                break;

            case 4:
                displayHistory(history);
                break;

            case 5:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice, try again.\n");
        }
    }

    return 0;
}
