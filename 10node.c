#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DeviceNode {
    int deviceId;
    char deviceName[50];
    struct DeviceNode* next;
} DeviceNode;

DeviceNode* createDevice(int deviceId, char* deviceName) {
    DeviceNode* newNode = (DeviceNode*)malloc(sizeof(DeviceNode));
    newNode->deviceId = deviceId;
    strcpy(newNode->deviceName, deviceName);
    newNode->next = NULL;
    return newNode;
}

void addDevice(DeviceNode** head, int deviceId, char* deviceName) {
    DeviceNode* newNode = createDevice(deviceId, deviceName);
    
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    DeviceNode* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

void deleteDevice(DeviceNode** head, int deviceId) {
    if (*head == NULL) {
        printf("No devices found!\n");
        return;
    }

    DeviceNode* temp = *head;
    DeviceNode* prev = NULL;

    if (temp != NULL && temp->deviceId == deviceId) {
        *head = temp->next;
        free(temp);
        printf("Device ID %d removed successfully.\n", deviceId);
        return;
    }

    while (temp != NULL && temp->deviceId != deviceId) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Device ID %d not found.\n", deviceId);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Device ID %d removed successfully.\n", deviceId);
}

void displayDevices(DeviceNode* head) {
    if (head == NULL) {
        printf("No devices in the list.\n");
        return;
    }

    printf("\nDevice List:\n");
    while (head != NULL) {
        printf("[Device ID: %d, Device Name: %s] -> ", head->deviceId, head->deviceName);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    DeviceNode* head = NULL;
    int choice, deviceId;
    char deviceName[50];

    while (1) {
        printf("\nDevice Manager Menu:\n");
        printf("1. Add Device\n");
        printf("2. Delete Device\n");
        printf("3. Display Devices\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Device ID: ");
                scanf("%d", &deviceId);
                printf("Enter Device Name: ");
                scanf(" %[^\n]s", deviceName);
                addDevice(&head, deviceId, deviceName);
                break;
            case 2:
                printf("Enter Device ID to delete: ");
                scanf("%d", &deviceId);
                deleteDevice(&head, deviceId);
                break;
            case 3:
                displayDevices(head);
                break;
            case 4:
                printf("Exiting...\n");
                DeviceNode* temp;
                while (head != NULL) {
                    temp = head;
                    head = head->next;
                    free(temp);
                }
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
