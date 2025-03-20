#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FLIGHTS 100
#define MAX_LENGTH 50

typedef struct {
    char flightNo[MAX_LENGTH];
    char arrivalTime[MAX_LENGTH];
    char destination[MAX_LENGTH];
} Flight;

int readFlights(Flight flights[]) {
    FILE *file = fopen("arrivals.txt", "r");
    if (file == NULL) {
        return 0;
    }

    int count = 0;
    while (count < MAX_FLIGHTS && fscanf(file, "%s %s %s", flights[count].flightNo, flights[count].arrivalTime, flights[count].destination) == 3) {
        count++;
    }

    fclose(file);
    return count;
}

void writeFlights(Flight flights[], int count) {
    FILE *file = fopen("arrivals.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s %s\n", flights[i].flightNo, flights[i].arrivalTime, flights[i].destination);
    }

    fclose(file);
}

void bubbleSort(Flight flights[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(flights[j].arrivalTime, flights[j + 1].arrivalTime) > 0) {
                Flight temp = flights[j];
                flights[j] = flights[j + 1];
                flights[j + 1] = temp;
            }
        }
    }
}

void addFlight() {
    Flight flights[MAX_FLIGHTS];
    int count = readFlights(flights);

    if (count >= MAX_FLIGHTS) {
        printf("Arrival table is full!\n");
        return;
    }

    printf("Enter Flight Number: ");
    scanf("%s", flights[count].flightNo);
    printf("Enter Arrival Time (HH:MM): ");
    scanf("%s", flights[count].arrivalTime);
    printf("Enter Destination: ");
    scanf("%s", flights[count].destination);

    count++;

    bubbleSort(flights, count);

    writeFlights(flights, count);

    printf("Flight added and sorted successfully!\n");
}

void displayFlights() {
    Flight flights[MAX_FLIGHTS];
    int count = readFlights(flights);

    if (count == 0) {
        printf("No flight arrivals recorded yet.\n");
        return;
    }

    printf("\nFlight Arrivals:\n");
    printf("Flight No   Arrival Time   Destination\n");
    printf("--------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%s        %s        %s\n", flights[i].flightNo, flights[i].arrivalTime, flights[i].destination);
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nFlight Arrival System\n");
        printf("1. Add Flight\n");
        printf("2. Display Flights\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addFlight();
                break;
            case 2:
                displayFlights();
                break;
            case 3:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
