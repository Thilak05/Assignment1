#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

typedef struct Song {
    char name[MAX_LEN];
    char album[MAX_LEN];
    char artist[MAX_LEN];
    char language[MAX_LEN];
    struct Song *next;
} Song;

Song* createSong(char *name, char *album, char *artist, char *language);
void addSong(Song **head);
void removeSong(Song **head, char *name);
void sortPlaylist(Song **head);
void displayPlaylist(Song *head);
void freePlaylist(Song *head);

int main() {
    Song *playlist = NULL;
    int choice;
    char songName[MAX_LEN];

    do {
        printf("\n===== Music Playlist Menu =====\n");
        printf("1. Add Song\n");
        printf("2. Remove Song\n");
        printf("3. Sort Playlist\n");
        printf("4. Display Playlist\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                addSong(&playlist);
                break;
            case 2:
                printf("Enter the song name to remove: ");
                fgets(songName, MAX_LEN, stdin);
                songName[strcspn(songName, "\n")] = 0; 
                removeSong(&playlist, songName);
                break;
            case 3:
                sortPlaylist(&playlist);
                printf("Playlist sorted successfully!\n");
                break;
            case 4:
                displayPlaylist(playlist);
                break;
            case 5:
                printf("Exiting program...\n");
                freePlaylist(playlist);
                break; 
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

Song* createSong(char *name, char *album, char *artist, char *language) {
    Song *newSong = (Song*)malloc(sizeof(Song));
    if (!newSong) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    strcpy(newSong->name, name);
    strcpy(newSong->album, album);
    strcpy(newSong->artist, artist);
    strcpy(newSong->language, language);
    newSong->next = NULL;
    return newSong;
}

void addSong(Song **head) {
    char input[MAX_LEN * 4], name[MAX_LEN], album[MAX_LEN], artist[MAX_LEN], language[MAX_LEN];

    printf("Enter song details (NAME,ALBUM,ARTIST,LANGUAGE): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; 

    if (sscanf(input, "%[^,],%[^,],%[^,],%s", name, album, artist, language) != 4) {
        printf("Invalid format! Please enter in NAME,ALBUM,ARTIST,LANGUAGE format.\n");
        return;
    }

    Song *newSong = createSong(name, album, artist, language);
    if (!newSong) return;

    newSong->next = *head;
    *head = newSong;
    printf("Song added successfully!\n");
}

void removeSong(Song **head, char *name) {
    Song *temp = *head, *prev = NULL;

    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Song not found!\n");
        return;
    }

    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Song removed successfully!\n");
}

void sortPlaylist(Song **head) {
    if (*head == NULL) return;

    int swapped;
    Song *ptr1;
    Song *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->name, ptr1->next->name) > 0) {
                char tempName[MAX_LEN], tempAlbum[MAX_LEN], tempArtist[MAX_LEN], tempLanguage[MAX_LEN];

                strcpy(tempName, ptr1->name);
                strcpy(tempAlbum, ptr1->album);
                strcpy(tempArtist, ptr1->artist);
                strcpy(tempLanguage, ptr1->language);

                strcpy(ptr1->name, ptr1->next->name);
                strcpy(ptr1->album, ptr1->next->album);
                strcpy(ptr1->artist, ptr1->next->artist);
                strcpy(ptr1->language, ptr1->next->language);

                strcpy(ptr1->next->name, tempName);
                strcpy(ptr1->next->album, tempAlbum);
                strcpy(ptr1->next->artist, tempArtist);
                strcpy(ptr1->next->language, tempLanguage);

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
void displayPlaylist(Song *head) {
    if (head == NULL) {
        printf("Playlist is empty!\n");
        return;
    }

    printf("\n===== Playlist =====\n");
    Song *current = head;
    while (current != NULL) {
        printf("Song: %s | Album: %s | Artist: %s | Language: %s\n",
               current->name, current->album, current->artist, current->language);
        current = current->next;
    }
}

void freePlaylist(Song *head) {
    Song *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
