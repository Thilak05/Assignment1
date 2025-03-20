#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100

int binarySearch(char files[][100], int left, int right, char *target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(files[mid], target);

        if (cmp == 0) {
            return mid;
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

void bubbleSort(char files[][100], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(files[j], files[j + 1]) > 0) {
                char temp[100];
                strcpy(temp, files[j]);
                strcpy(files[j], files[j + 1]);
                strcpy(files[j + 1], temp);
            }
        }
    }
}

int main() {
    int n;
    char files[MAX_FILES][100];
    char searchName[100];

    printf("Enter the number of files/directories: ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        printf("Enter name of file/directory %d: ", i + 1);
        fgets(files[i], sizeof(files[i]), stdin);
        files[i][strcspn(files[i], "\n")] = 0;
    }

    bubbleSort(files, n);

    printf("\nEnter the file/directory name to search: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0;

    int result = binarySearch(files, 0, n - 1, searchName);

    if (result != -1) {
        printf("\nFile/Directory Found: %s\n", files[result]);
    } else {
        printf("\nFile/Directory not found!\n");
    }

    return 0;
}
