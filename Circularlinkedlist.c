#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // For INT_MIN and INT_MAX

// Node structure for the circular queue
struct Node {
    int data;
    struct Node *next;
};

// Circular queue structure with header node
struct CircularQueue {
    int count;
    int largest;
    int smallest;
    struct Node *header;
};

// Function to initialize an empty circular queue
void initializeQueue(struct CircularQueue **queue) {
    *queue = (struct CircularQueue *)malloc(sizeof(struct CircularQueue));
    if (*queue == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    (*queue)->count = 0;
    (*queue)->largest = INT_MIN; // Initialize largest to minimum possible integer
    (*queue)->smallest = INT_MAX; // Initialize smallest to maximum possible integer
    (*queue)->header = NULL;
}

// Function to enqueue an element into the circular queue
void enqueue(struct CircularQueue *queue, int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = value;
    if (queue->header == NULL) {
        newNode->next = newNode; // Circular linking for the first node
        queue->header = newNode;
    } else {
        newNode->next = queue->header->next;
        queue->header->next = newNode;
    }

    // Update count
    queue->count++;

    // Update largest and smallest values
    if (value > queue->largest)
        queue->largest = value;
    if (value < queue->smallest)
        queue->smallest = value;
}

// Function to dequeue an element from the circular queue
int dequeue(struct CircularQueue *queue, int *status) {
    *status = 0; // Initialize status to indicate deletion failure
    if (queue->header == NULL) {
        printf("Queue is empty.\n");
        return INT_MIN; // Return minimum possible integer if queue is empty
    }

    struct Node *temp = queue->header->next;
    int deletedValue = temp->data;

    if (temp == queue->header) { // Only one node in the queue
        free(temp);
        queue->header = NULL;
    } else {
        queue->header->next = temp->next;
        free(temp);
    }

    // Update count
    queue->count--;

    // Update largest and smallest values if queue becomes empty
    if (queue->count == 0) {
        queue->largest = INT_MIN;
        queue->smallest = INT_MAX;
    } else { // Recalculate largest and smallest values if queue is not empty
        struct Node *current = queue->header->next;
        queue->largest = current->data;
        queue->smallest = current->data;
        for (int i = 0; i < queue->count; ++i) {
            if (current->data > queue->largest)
                queue->largest = current->data;
            if (current->data < queue->smallest)
                queue->smallest = current->data;
            current = current->next;
        }
    }

    *status = 1; // Update status to indicate successful deletion
    return deletedValue;
}

// Function to retrieve the largest value from the circular queue
int getLargestValue(struct CircularQueue *queue) {
    return queue->largest;
}

// Function to retrieve the smallest value from the circular queue
int getSmallestValue(struct CircularQueue *queue) {
    return queue->smallest;
}

// Function to display the elements of the circular queue
void displayQueue(struct CircularQueue *queue) {
    if (queue->header == NULL) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Circular Queue Elements: ");
    struct Node *temp = queue->header->next;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != queue->header->next);
    printf("\n");
}

// Main function for demonstration
int main() {
    struct CircularQueue *queue;
    initializeQueue(&queue);

    int choice, value, deletedValue, status;
    while (1) {
        printf("\n1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Get Largest Value\n");
        printf("4. Get Smallest Value\n");
        printf("5. Display Queue\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to enqueue: ");
                scanf("%d", &value);
                enqueue(queue, value);
                break;
            case 2:
                deletedValue = dequeue(queue, &status);
                if (status)
                    printf("Deleted element: %d\n", deletedValue);
                break;
            case 3:
                printf("Largest value in queue: %d\n", getLargestValue(queue));
                break;
            case 4:
                printf("Smallest value in queue: %d\n", getSmallestValue(queue));
                break;
            case 5:
                displayQueue(queue);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}

