#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_LENGTH 100

int readMediaFiles(char mediaFiles[][MAX_LENGTH]) {
    FILE *file = fopen("media.txt", "r");
    if (file == NULL) {
        printf("No media files found.\n");
        return 0;
    }

    int count = 0;
    while (count < MAX_FILES && fgets(mediaFiles[count], MAX_LENGTH, file)) {
        mediaFiles[count][strcspn(mediaFiles[count], "\n")] = '\0';
        count++;
    }

    fclose(file);
    return count;
}

void writeMediaFiles(char mediaFiles[][MAX_LENGTH], int count) {
    FILE *file = fopen("media.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\n", mediaFiles[i]);
    }

    fclose(file);
}

void insertionSort(char mediaFiles[][MAX_LENGTH], int count) {
    for (int i = 1; i < count; i++) {
        char temp[MAX_LENGTH];
        strcpy(temp, mediaFiles[i]);
        int j = i - 1;

        while (j >= 0 && strcmp(mediaFiles[j], temp) > 0) {
            strcpy(mediaFiles[j + 1], mediaFiles[j]);
            j--;
        }
        strcpy(mediaFiles[j + 1], temp);
    }
}

void addMediaFile() {
    char mediaFiles[MAX_FILES][MAX_LENGTH];
    int count = readMediaFiles(mediaFiles);

    if (count >= MAX_FILES) {
        printf("Media storage is full!\n");
        return;
    }

    printf("Enter new media file name (e.g., song.mp3, video.mp4): ");
    scanf(" %[^\n]s", mediaFiles[count]);
    count++;

    insertionSort(mediaFiles, count);
    writeMediaFiles(mediaFiles, count);

    printf("Media file added and sorted successfully!\n");
}

void displayMediaFiles() {
    char mediaFiles[MAX_FILES][MAX_LENGTH];
    int count = readMediaFiles(mediaFiles);

    if (count == 0) {
        printf("No media files available.\n");
        return;
    }

    printf("\nSorted Media Files:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", mediaFiles[i]);
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nMedia File Sorting System\n");
        printf("1. Add Media File\n");
        printf("2. Display Sorted Media Files\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addMediaFile();
                break;
            case 2:
                displayMediaFiles();
                break;
            case 3:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
