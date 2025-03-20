#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define MAX_NAMES 1000
#define NUM_THREADS 2

typedef struct {
    char **names;
    char *target;
    int left;
    int right;
    int thread_id;
} SearchArgs;

int result = -1;
pthread_mutex_t lock;

void *binarySearch(void *arg) {
    SearchArgs *args = (SearchArgs *)arg;
    int left = args->left, right = args->right;
    char **names = args->names;
    char *target = args->target;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(names[mid], target);

        if (cmp == 0) {
            pthread_mutex_lock(&lock);
            result = mid;
            pthread_mutex_unlock(&lock);
            pthread_exit(NULL);
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    pthread_exit(NULL);
}

int main() {
    int n;
    char target[50];
    char *names[MAX_NAMES];
    pthread_t threads[NUM_THREADS];
    SearchArgs args[NUM_THREADS];

    pthread_mutex_init(&lock, NULL);

    printf("Enter the number of names: ");
    scanf("%d", &n);
    
    printf("Enter %d names (sorted order):\n", n);
    for (int i = 0; i < n; i++) {
        names[i] = (char *)malloc(50 * sizeof(char));
        scanf("%s", names[i]);
    }

    printf("Enter the name to search: ");
    scanf("%s", target);

    int part_size = n / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].names = names;
        args[i].target = target;
        args[i].left = i * part_size;
        args[i].right = (i == NUM_THREADS - 1) ? n - 1 : (i + 1) * part_size - 1;
        args[i].thread_id = i;
        pthread_create(&threads[i], NULL, binarySearch, (void *)&args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    if (result != -1) {
        printf("Name '%s' found at index %d\n", target, result);
    } else {
        printf("Name '%s' not found\n", target);
    }

    for (int i = 0; i < n; i++) {
        free(names[i]);
    }

    pthread_mutex_destroy(&lock);
    return 0;
}
