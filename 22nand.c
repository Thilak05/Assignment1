#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAMES 100
#define NAME_LENGTH 50

int readFromNANDFlash(char names[MAX_NAMES][NAME_LENGTH]) {
    FILE *file = fopen("nand.txt", "r");
    if (file == NULL) {
        printf("Error opening NAND Flash file!\n");
        return 0;
    }

    int count = 0;
    while (count < MAX_NAMES && fgets(names[count], NAME_LENGTH, file)) {
        names[count][strcspn(names[count], "\n")] = 0;
        count++;
    }

    fclose(file);
    return count;
}

void writeToNANDFlash(char names[MAX_NAMES][NAME_LENGTH], int count) {
    FILE *file = fopen("nand.txt", "w");
    if (file == NULL) {
        printf("Error opening NAND Flash file for writing!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\n", names[i]);
    }

    fclose(file);
    printf("Names successfully written to NAND Flash.\n");
}

void selectionSort(char names[MAX_NAMES][NAME_LENGTH], int count) {
    for (int i = 0; i < count - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < count; j++) {
            if (strcmp(names[j], names[minIndex]) < 0) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            char temp[NAME_LENGTH];
            strcpy(temp, names[i]);
            strcpy(names[i], names[minIndex]);
            strcpy(names[minIndex], temp);
        }
    }
}

int main() {
    char names[MAX_NAMES][NAME_LENGTH];
    int count = readFromNANDFlash(names);
    if (count == 0) {
        printf("No data found in NAND Flash.\n");
        return 1;
    }

    selectionSort(names, count);
    writeToNANDFlash(names, count);

    printf("Names sorted and stored back to NAND Flash successfully!\n");

    return 0;
}
