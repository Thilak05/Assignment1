#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 10000
#define MAX_WORD_LEN 50

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordFreq;

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void removePunctuation(char *word) {
    int len = strlen(word);
    if (ispunct(word[len - 1])) {
        word[len - 1] = '\0';
    }
}

int findWord(WordFreq words[], int wordCount, char *word) {
    for (int i = 0; i < wordCount; i++) {
        if (strcmp(words[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

void addWord(WordFreq words[], int *wordCount, char *word) {
    if (*wordCount >= MAX_WORDS) {
        return;
    }

    int index = findWord(words, *wordCount, word);
    if (index != -1) {
        words[index].count++;
    } else {
        strcpy(words[*wordCount].word, word);
        words[*wordCount].count = 1;
        (*wordCount)++;
    }
}

int partition(WordFreq words[], int low, int high) {
    int pivot = words[high].count;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (words[j].count > pivot) {
            i++;
            WordFreq temp = words[i];
            words[i] = words[j];
            words[j] = temp;
        }
    }

    WordFreq temp = words[i + 1];
    words[i + 1] = words[high];
    words[high] = temp;

    return i + 1;
}

void quickSort(WordFreq words[], int low, int high) {
    if (low < high) {
        int pi = partition(words, low, high);
        quickSort(words, low, pi - 1);
        quickSort(words, pi + 1, high);
    }
}

void processFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    WordFreq words[MAX_WORDS] = {0};
    int wordCount = 0;
    char word[MAX_WORD_LEN];

    while (fscanf(file, "%s", word) == 1) {
        toLowerCase(word);
        removePunctuation(word);
        addWord(words, &wordCount, word);
    }

    fclose(file);

    quickSort(words, 0, wordCount - 1);

    printf("\nTop 10 Most Frequent Words:\n");
    printf("--------------------------------\n");
    printf("Word\t\tFrequency\n");
    printf("--------------------------------\n");

    for (int i = 0; i < 10 && i < wordCount; i++) {
        printf("%s\t\t%d\n", words[i].word, words[i].count);
    }
    printf("--------------------------------\n");
}

int main() {
    char filename[100];
    printf("Enter the file name: ");
    scanf("%s", filename);
    
    processFile(filename);

    return 0;
}
