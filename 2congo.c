#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME 100

typedef struct Dancer {
    char name[MAX_NAME];
    struct Dancer *next;
} Dancer;

Dancer* createDancer(char *name);
void addDancer(Dancer **head, char *name);
void removeDancer(Dancer **head, char *name);
void displayCongaLine(Dancer *head);
void shuffleCongaLine(Dancer **head);
void freeCongaLine(Dancer *head);

int main() {
    Dancer *congaLine = NULL;
    int choice;
    char name[MAX_NAME];

    srand(time(NULL)); 

    do {
        printf("\n===== Conga Line Menu =====\n");
        printf("1. Add Dancer\n");
        printf("2. Remove Dancer\n");
        printf("3. Display Conga Line\n");
        printf("4. Shuffle Conga Line\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                printf("Enter dancer's name: ");
                fgets(name, MAX_NAME, stdin);
                name[strcspn(name, "\n")] = 0; 
                addDancer(&congaLine, name);
                break;
            case 2:
                printf("Enter dancer's name to remove: ");
                fgets(name, MAX_NAME, stdin);
                name[strcspn(name, "\n")] = 0;
                removeDancer(&congaLine, name);
                break;
            case 3:
                displayCongaLine(congaLine);
                break;
            case 4:
                shuffleCongaLine(&congaLine);
                printf("Conga Line shuffled!\n");
                break;
            case 5:
                printf("Exiting program...\n");
                freeCongaLine(congaLine);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

Dancer* createDancer(char *name) {
    Dancer *newDancer = (Dancer*)malloc(sizeof(Dancer));
    if (!newDancer) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    strcpy(newDancer->name, name);
    newDancer->next = NULL;
    return newDancer;
}

void addDancer(Dancer **head, char *name) {
    Dancer *newDancer = createDancer(name);
    if (!newDancer) return;

    if (*head == NULL) {
        *head = newDancer;
    } else {
        Dancer *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newDancer;
    }
    printf("Dancer '%s' joined the Conga Line!\n", name);
}

void removeDancer(Dancer **head, char *name) {
    if (*head == NULL) {
        printf("Conga Line is empty!\n");
        return;
    }

    Dancer *temp = *head, *prev = NULL;

    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Dancer '%s' not found in the Conga Line!\n", name);
        return;
    }

    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Dancer '%s' removed from the Conga Line!\n", name);
}

void displayCongaLine(Dancer *head) {
    if (head == NULL) {
        printf("Conga Line is empty!\n");
        return;
    }

    printf("\n===== Conga Line =====\n");
    Dancer *temp = head;
    while (temp != NULL) {
        printf("%s -> ", temp->name);
        temp = temp->next;
    }
    printf("END\n");
}

void shuffleCongaLine(Dancer **head) {
    if (*head == NULL || (*head)->next == NULL) {
        printf("Not enough dancers to shuffle!\n");
        return;
    }

    int count = 0;
    Dancer *temp = *head;
    
    while (temp) {
        count++;
        temp = temp->next;
    }

    Dancer **arr = (Dancer **)malloc(count * sizeof(Dancer *));
    temp = *head;
    for (int i = 0; i < count; i++) {
        arr[i] = temp;
        temp = temp->next;
    }

    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Dancer *tempDancer = arr[i];
        arr[i] = arr[j];
        arr[j] = tempDancer;
    }

    for (int i = 0; i < count - 1; i++) {
        arr[i]->next = arr[i + 1];
    }
    arr[count - 1]->next = NULL;
    *head = arr[0];

    free(arr);
}

void freeCongaLine(Dancer *head) {
    Dancer *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
