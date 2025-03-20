#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Message {
    char data[256];
    struct Message* next;
} Message;

typedef struct {
    Message* front;
    Message* rear;
} Queue;

void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

int isEmpty(Queue* q) {
    return (q->front == NULL);
}

void enqueue(Queue* q, char* msg) {
    Message* newMsg = (Message*)malloc(sizeof(Message));
    if (!newMsg) {
        printf("Memory allocation failed!\n");
        return;
    }
    strcpy(newMsg->data, msg);
    newMsg->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newMsg;
    } else {
        q->rear->next = newMsg;
        q->rear = newMsg;
    }
}

char* dequeue(Queue* q) {
    if (isEmpty(q)) {
        return NULL;
    }
    Message* temp = q->front;
    char* msg = strdup(temp->data);
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return msg;
}

void bufferedIO(Queue* buffer) {
    char input[256];
    printf("Buffered I/O - Enter a message: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    enqueue(buffer, input);
}

void pipeCommunication(Queue* pipeQueue) {
    if (isEmpty(pipeQueue)) {
        printf("Pipe is empty. No messages to read.\n");
        return;
    }
    char* msg = dequeue(pipeQueue);
    printf("Pipe Output: %s\n", msg);
    free(msg);
}

void displayQueue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    Message* temp = q->front;
    printf("Message Queue:\n");
    while (temp) {
        printf("> %s\n", temp->data);
        temp = temp->next;
    }
}

int main() {
    Queue messageQueue, bufferQueue, pipeQueue;
    initQueue(&messageQueue);
    initQueue(&bufferQueue);
    initQueue(&pipeQueue);

    int choice;
    char message[256];

    while (1) {
        printf("\n--- IPC Model: Message Queue, Buffered I/O, Pipes ---\n");
        printf("1. Send Message (Message Queue)\n");
        printf("2. Read Message (Message Queue)\n");
        printf("3. Buffered I/O (Write to Buffer)\n");
        printf("4. Read Buffered Data\n");
        printf("5. Simulate Pipe Communication\n");
        printf("6. View Message Queue\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter message: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = 0;
                enqueue(&messageQueue, message);
                printf("Message sent successfully!\n");
                break;
            case 2:
                if (!isEmpty(&messageQueue)) {
                    char* msg = dequeue(&messageQueue);
                    printf("Received Message: %s\n", msg);
                    free(msg);
                } else {
                    printf("No messages in queue.\n");
                }
                break;
            case 3:
                bufferedIO(&bufferQueue);
                break;
            case 4:
                if (!isEmpty(&bufferQueue)) {
                    char* msg = dequeue(&bufferQueue);
                    printf("Buffered Data Read: %s\n", msg);
                    free(msg);
                } else {
                    printf("Buffer is empty.\n");
                }
                break;
            case 5:
                printf("Enter message to send via pipe: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = 0;
                enqueue(&pipeQueue, message);
                printf("Message written to pipe. Reading now...\n");
                pipeCommunication(&pipeQueue);
                break;
            case 6:
                displayQueue(&messageQueue);
                break;
            case 7:
                printf("Exiting IPC Model Simulation.\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
