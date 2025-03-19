#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int player;
    struct Node* next;
} Node;

Node* createCircularList(int N) {
    Node *head = NULL, *temp, *newNode;
    
    for (int i = 1; i <= N; i++) {
        newNode = (Node*)malloc(sizeof(Node));
        newNode->player = i;
        newNode->next = NULL;
        
        if (head == NULL) {
            head = newNode;
            head->next = head;  // Circular link
        } else {
            temp->next = newNode;
            newNode->next = head;
        }
        temp = newNode;
    }
    return head;
}

int findLastPlayer(Node* head, int k) {
    Node *temp = head, *prev = NULL;
    
    while (temp->next != temp) {  
        for (int count = 1; count < k; count++) {
            prev = temp;
            temp = temp->next;
        }

        printf("Eliminating player: %d\n", temp->player);
        prev->next = temp->next;
        free(temp);
        temp = prev->next;
    }
    
    int lastPlayer = temp->player;
    free(temp);
    return lastPlayer;
}

int main() {
    int N, k;
    
    printf("Enter the number of players (N): ");
    scanf("%d", &N);
    
    printf("Enter the elimination number (k): ");
    scanf("%d", &k);
    
    Node* head = createCircularList(N);
    
    int lastPlayer = findLastPlayer(head, k);
    printf("The last remaining player is: %d\n", lastPlayer);
    
    return 0;
}
