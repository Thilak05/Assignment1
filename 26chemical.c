#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHEMICALS 100
#define MAX_NAME_LENGTH 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    int hazardLevel;
} Chemical;

int readChemicals(Chemical chemicals[]) {
    FILE *file = fopen("chemicals.txt", "r");
    if (file == NULL) {
        printf("No chemical list found.\n");
        return 0;
    }

    int count = 0;
    while (count < MAX_CHEMICALS && fscanf(file, " %[^,], %d", chemicals[count].name, &chemicals[count].hazardLevel) == 2) {
        count++;
    }

    fclose(file);
    return count;
}

void writeChemicals(Chemical chemicals[], int count) {
    FILE *file = fopen("chemicals.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s, %d\n", chemicals[i].name, chemicals[i].hazardLevel);
    }

    fclose(file);
}

int partition(Chemical chemicals[], int low, int high) {
    int pivot = chemicals[high].hazardLevel;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (chemicals[j].hazardLevel >= pivot) {
            i++;
            Chemical temp = chemicals[i];
            chemicals[i] = chemicals[j];
            chemicals[j] = temp;
        }
    }

    Chemical temp = chemicals[i + 1];
    chemicals[i + 1] = chemicals[high];
    chemicals[high] = temp;

    return i + 1;
}

void quickSort(Chemical chemicals[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(chemicals, low, high);
        quickSort(chemicals, low, pivotIndex - 1);
        quickSort(chemicals, pivotIndex + 1, high);
    }
}

void addChemical() {
    Chemical chemicals[MAX_CHEMICALS];
    int count = readChemicals(chemicals);

    if (count >= MAX_CHEMICALS) {
        printf("Chemical list is full!\n");
        return;
    }

    printf("Enter chemical name: ");
    scanf(" %[^\n]s", chemicals[count].name);
    printf("Enter hazard level (higher value means more hazardous): ");
    scanf("%d", &chemicals[count].hazardLevel);
    count++;

    quickSort(chemicals, 0, count - 1);

    writeChemicals(chemicals, count);

    printf("Chemical added and sorted successfully!\n");
}

void displayChemicals() {
    Chemical chemicals[MAX_CHEMICALS];
    int count = readChemicals(chemicals);

    if (count == 0) {
        printf("No chemicals available.\n");
        return;
    }

    printf("\nSorted Hazardous Chemical List (Highest Hazard First):\n");
    for (int i = 0; i < count; i++) {
        printf("%s - Hazard Level: %d\n", chemicals[i].name, chemicals[i].hazardLevel);
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nHazardous Chemical Management System\n");
        printf("1. Add Chemical\n");
        printf("2. Display Sorted Chemicals\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addChemical();
                break;
            case 2:
                displayChemicals();
                break;
            case 3:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
