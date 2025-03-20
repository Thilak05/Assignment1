#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 10

typedef struct Node {
    int key;
    char value[100];
    struct Node* next;
} Node;

Node* hashTable[TABLE_SIZE];

int hashFunction(int key) {
    return key % TABLE_SIZE;
}

void insert(int key, const char* value) {
    int index = hashFunction(key);
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    strcpy(newNode->value, value);
    newNode->next = NULL;
    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        newNode->next = hashTable[index];
        hashTable[index] = newNode;
    }

    printf("Inserted key: %d, value: %s at index %d\n", key, value, index);
}

void search(int key) {
    int index = hashFunction(key);
    Node* temp = hashTable[index];

    while (temp) {
        if (temp->key == key) {
            printf("Key %d found with value: %s\n", key, temp->value);
            return;
        }
        temp = temp->next;
    }
    
    printf("Key %d not found.\n", key);
}

void deleteKey(int key) {
    int index = hashFunction(key);
    Node* temp = hashTable[index];
    Node* prev = NULL;

    while (temp) {
        if (temp->key == key) {
            if (prev == NULL) {
                hashTable[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Key %d deleted successfully.\n", key);
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("Key %d not found for deletion.\n", key);
}

void display() {
    printf("\nHash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        Node* temp = hashTable[i];
        while (temp) {
            printf("(%d, %s) -> ", temp->key, temp->value);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int choice, key;
    char value[100];

    while (1) {
        printf("\nOptions:\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key (integer): ");
                scanf("%d", &key);
                printf("Enter value (string): ");
                scanf("%s", value);
                insert(key, value);
                break;

            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                search(key);
                break;

            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                deleteKey(key);
                break;

            case 4:
                display();
                break;

            case 5:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
