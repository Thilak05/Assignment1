#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 100

typedef struct Clue {
    char hint[MAX_LEN];
    struct Clue *next;
} Clue;

Clue* createClue(char *hint);
void addClue(Clue **head, char *hint);
void removeClue(Clue **head, char *hint);
void displayHunt(Clue *head);
void shuffleHunt(Clue **head);
void freeHunt(Clue *head);

int main() {
    Clue *hunt = NULL;
    int choice;
    char hint[MAX_LEN];

    srand(time(NULL)); 

    do {
        printf("\n===== Scavenger Hunt Menu =====\n");
        printf("1. Add Clue\n");
        printf("2. Remove Clue\n");
        printf("3. Display Clues\n");
        printf("4. Shuffle Clues\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                printf("Enter a new clue: ");
                fgets(hint, MAX_LEN, stdin);
                hint[strcspn(hint, "\n")] = 0; 
                addClue(&hunt, hint);
                break;
            case 2:
                printf("Enter the clue to remove: ");
                fgets(hint, MAX_LEN, stdin);
                hint[strcspn(hint, "\n")] = 0;
                removeClue(&hunt, hint);
                break;
            case 3:
                displayHunt(hunt);
                break;
            case 4:
                shuffleHunt(&hunt);
                printf("Clues shuffled!\n");
                break;
            case 5:
                printf("Exiting program...\n");
                freeHunt(hunt);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

Clue* createClue(char *hint) {
    Clue *newClue = (Clue*)malloc(sizeof(Clue));
    if (!newClue) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    strcpy(newClue->hint, hint);
    newClue->next = NULL;
    return newClue;
}

void addClue(Clue **head, char *hint) {
    Clue *newClue = createClue(hint);
    if (!newClue) return;

    if (*head == NULL) {
        *head = newClue;
    } else {
        Clue *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newClue;
    }
    printf("Clue added: \"%s\"\n", hint);
}

void removeClue(Clue **head, char *hint) {
    if (*head == NULL) {
        printf("No clues to remove!\n");
        return;
    }

    Clue *temp = *head, *prev = NULL;

    while (temp != NULL && strcmp(temp->hint, hint) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Clue not found!\n");
        return;
    }

    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Clue removed successfully!\n");
}

void displayHunt(Clue *head) {
    if (head == NULL) {
        printf("No clues available!\n");
        return;
    }

    printf("\n===== Scavenger Hunt Clues =====\n");
    int count = 1;
    Clue *temp = head;
    while (temp != NULL) {
        printf("Clue %d: %s\n", count++, temp->hint);
        temp = temp->next;
    }
}

void shuffleHunt(Clue **head) {
    if (*head == NULL || (*head)->next == NULL) {
        printf("Not enough clues to shuffle!\n");
        return;
    }

    int count = 0;
    Clue *temp = *head;

    while (temp) {
        count++;
        temp = temp->next;
    }

    Clue **arr = (Clue **)malloc(count * sizeof(Clue *));
    temp = *head;
    for (int i = 0; i < count; i++) {
        arr[i] = temp;
        temp = temp->next;
    }

    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Clue *tempClue = arr[i];
        arr[i] = arr[j];
        arr[j] = tempClue;
    }

    for (int i = 0; i < count - 1; i++) {
        arr[i]->next = arr[i + 1];
    }
    arr[count - 1]->next = NULL;
    *head = arr[0];
    free(arr);
}

void freeHunt(Clue *head) {
    Clue *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
