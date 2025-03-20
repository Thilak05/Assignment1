#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 1000

typedef struct {
    int id;
    char title[100];
    char author[100];
} Book;

int linearSearch(Book books[], int n, char *target) {
    for (int i = 0; i < n; i++) {
        if (strcmp(books[i].title, target) == 0) {
            return i;
        }
    }
    return -1;
}

int binarySearch(Book books[], int left, int right, char *target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(books[mid].title, target);

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

int main() {
    int n, choice;
    char searchTitle[100];
    Book books[MAX_BOOKS];

    printf("Enter the number of books in the library: ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        books[i].id = i + 1;
        printf("Enter title of book %d: ", i + 1);
        fgets(books[i].title, sizeof(books[i].title), stdin);
        books[i].title[strcspn(books[i].title, "\n")] = 0;

        printf("Enter author of book %d: ", i + 1);
        fgets(books[i].author, sizeof(books[i].author), stdin);
        books[i].author[strcspn(books[i].author, "\n")] = 0;
    }

    printf("\nChoose search method:\n1. Linear Search (Unsorted Books)\n2. Binary Search (Sorted Books)\nEnter choice: ");
    scanf("%d", &choice);
    getchar();

    printf("\nEnter the book title to search: ");
    fgets(searchTitle, sizeof(searchTitle), stdin);
    searchTitle[strcspn(searchTitle, "\n")] = 0;

    int result = -1;
    if (choice == 1) {
        result = linearSearch(books, n, searchTitle);
    } else if (choice == 2) {
        result = binarySearch(books, 0, n - 1, searchTitle);
    } else {
        printf("Invalid choice!\n");
        return 1;
    }

    if (result != -1) {
        printf("\nBook Found:\nID: %d\nTitle: %s\nAuthor: %s\n", books[result].id, books[result].title, books[result].author);
    } else {
        printf("\nBook not found in the library!\n");
    }

    return 0;
}
