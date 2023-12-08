#include <stdio.h> 
#include <stdlib.h> 
// Define the Node structure 
struct Node { 
 int data; 
 struct Node* next; 
};
// Define the Stack structure 
struct Stack { 
 struct Node* top; 
}; 
// Initialize the stack 
void initialize(struct Stack* stack) { 
 stack->top = NULL; 
} 
// Push operation 
void push(struct Stack* stack, int value) { 
 struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); 
 if (newNode == NULL) { 
 printf("Memory allocation failed.\n"); 
 return; 
 } 
 newNode->data = value; 
 newNode->next = stack->top; 
 stack->top = newNode; 
 printf("%d pushed onto the stack.\n", value); 
} 
// Pop operation 
int pop(struct Stack* stack) { 
 if (stack->top == NULL) { 
 printf("Stack underflow.\n"); 
 return -1; 
 } 
 struct Node* temp = stack->top; 
 int value = temp->data; 
 stack->top = temp->next; 
 free(temp); 
 return value; 
} 
// Peek operation 
int peek(struct Stack* stack) { 
 if (stack->top == NULL) { 
 printf("Stack is empty.\n"); 
 return -1; 
 } 
 return stack->top->data; 
} 
// Check if the stack is empty 
int isEmpty(struct Stack* stack) { 
 return stack->top == NULL; 
} 
// Display the stack 
void display(struct Stack* stack) { 
 if (isEmpty(stack)) { 
 printf("Stack is empty.\n"); 
 return; 
 } 
 struct Node* current = stack->top; 
 printf("Stack elements from top to bottom:\n"); 
 while (current != NULL) { 
 printf("%d\n", current->data); 
 current = current->next; 
 } 
} 
int main() { 
 struct Stack stack; 
 initialize(&stack); 
int choice, value; 
 do { 
 printf("\nStack Menu:\n"); 
 printf("1. Push\n"); 
 printf("2. Pop\n"); 
 printf("3. Peek\n"); 
 printf("4. Display\n"); 
 printf("5. Exit\n"); 
 printf("Enter your choice: "); 
 scanf("%d", &choice); 
 switch (choice) { 
 case 1: 
 printf("Enter value to push: "); 
 scanf("%d", &value); 
 push(&stack, value); 
 break; 
 case 2: 
 value = pop(&stack); 
 if (value != -1) 
 printf("Popped value: %d\n", value); 
 break; 
 case 3: 
 value = peek(&stack); 
 if (value != -1) 
 printf("Top value: %d\n", value); 
 break; 
 case 4: 
 display(&stack); 
 break; 
 case 5: 
 printf("Exiting...\n"); 
 break; 
 default: 
 printf("Invalid choice. Please try again.\n"); 
 } 
 } while (choice != 5); 
 return 0; 
}
