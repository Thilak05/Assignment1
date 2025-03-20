#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CarNode {
    char name[50];
    char manufacturer[50];
    char type[50];
    struct CarNode* left;
    struct CarNode* right;
} CarNode;

CarNode* createCarNode(const char* name, const char* manufacturer, const char* type) {
    CarNode* newNode = (CarNode*)malloc(sizeof(CarNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    strcpy(newNode->name, name);
    strcpy(newNode->manufacturer, manufacturer);
    strcpy(newNode->type, type);
    newNode->left = NULL;
    newNode->right = NULL;
    
    return newNode;
}

CarNode* insertCarNode(CarNode* root, const char* name, const char* manufacturer, const char* type) {
    if (root == NULL) {
        return createCarNode(name, manufacturer, type);
    }

    if (strcmp(name, root->name) < 0) {
        root->left = insertCarNode(root->left, name, manufacturer, type);
    }
    else {
        root->right = insertCarNode(root->right, name, manufacturer, type);
    }
    
    return root;
}

void searchCar(CarNode* root, const char* name) {
    if (root == NULL) {
        printf("Car '%s' not found in the database.\n", name);
        return;
    }
    
    int comparison = strcmp(name, root->name);
    
    if (comparison == 0) {
        printf("Car found!\n");
        printf("Name: %s\n", root->name);
        printf("Manufacturer: %s\n", root->manufacturer);
        printf("Type: %s\n", root->type);
    } else if (comparison < 0) {
        searchCar(root->left, name);
    } else {
        searchCar(root->right, name);
    }
}

void freeCarTree(CarNode* root) {
    if (root != NULL) {
        freeCarTree(root->left);
        freeCarTree(root->right);
        free(root);
    }
}

void displayAllCars(CarNode* root) {
    if (root != NULL) {
        displayAllCars(root->left);
        printf("%-20s %-20s %-20s\n", root->name, root->manufacturer, root->type);
        displayAllCars(root->right);
    }
}

int main() {
    CarNode* root = NULL;
    root = insertCarNode(root, "Civic", "Honda", "Sedan");
    root = insertCarNode(root, "Accord", "Honda", "Sedan");
    root = insertCarNode(root, "CR-V", "Honda", "SUV");
    root = insertCarNode(root, "Corolla", "Toyota", "Sedan");
    root = insertCarNode(root, "Camry", "Toyota", "Sedan");
    root = insertCarNode(root, "RAV4", "Toyota", "SUV");
    root = insertCarNode(root, "Model 3", "Tesla", "Electric Sedan");
    root = insertCarNode(root, "Model Y", "Tesla", "Electric SUV");
    root = insertCarNode(root, "F-150", "Ford", "Pickup Truck");
    root = insertCarNode(root, "Mustang", "Ford", "Sports Car");
    
    int choice;
    char carName[50];
    
    do {
        printf("\n==== Car Identification System ====\n");
        printf("1. Search for a car\n");
        printf("2. Display all cars\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter car name to search: ");
                scanf(" %[^\n]", carName);
                searchCar(root, carName);
                break;
                
            case 2:
                printf("\n%-20s %-20s %-20s\n", "Car Name", "Manufacturer", "Type");
                printf("--------------------------------------------------------\n");
                displayAllCars(root);
                break;
                
            case 3:
                printf("Exiting program. Goodbye!\n");
                break;
                
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 3);

    freeCarTree(root);
    
    return 0;
}