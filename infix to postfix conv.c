#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 
#define MAX_SIZE 100 
typedef struct { 
 char *arr; 
 int top; 
 int capacity; 
} Stack; 
void initialize(Stack *stack, int capacity) { 
 stack->arr = (char *)malloc(sizeof(char) * capacity); 
 stack->top = -1; 
 stack->capacity = capacity; 
} 
int isEmpty(Stack *stack) { 
 return stack->top == -1; 
} 
int isFull(Stack *stack) { 
 return stack->top == stack->capacity - 1; 
} 
void push(Stack *stack, char item) { 
 if (isFull(stack)) { 
 printf("Stack overflow!\n"); 
 exit(1); 
 } 
 stack->arr[++stack->top] = item; 
} 
char pop(Stack *stack) { 
 if (isEmpty(stack)) { 
 printf("Stack underflow!\n"); 
 exit(1); 
 } 
 return stack->arr[stack->top--]; 
} 
char peek(Stack *stack) { 
 if (isEmpty(stack)) { 
 return '\0'; 
 } 
 return stack->arr[stack->top]; 
} 
int precedence(char op) { 
 if (op == '+' || op == '-') return 1; 
 if (op == '*' || op == '/' || op == '%') return 2; 
 if (op == '^') return 3; 
 return 0; 
} 
void infixToPostfix(char *infix, char *postfix) {
	Stack stack; 
 initialize(&stack, MAX_SIZE); 
 int i, j; 
 char c, temp; 
 for (i = 0, j = 0; infix[i] != '\0'; i++) { 
 c = infix[i]; 
 if (isalpha(c) || isdigit(c)) { 
 postfix[j++] = c; 
 } else if (c == '(') { 
 push(&stack, c); 
 } else if (c == ')') { 
 while ((temp = pop(&stack)) != '(') { 
 postfix[j++] = temp; 
 } 
 } else { 
 while (!isEmpty(&stack) && precedence(peek(&stack)) >= precedence(c)) { 
 postfix[j++] = pop(&stack); 
 } 
 push(&stack, c); 
 } 
 } 
 while (!isEmpty(&stack)) { 
 postfix[j++] = pop(&stack); 
 } 
 postfix[j] = '\0'; 
} 
int main() { 
 char infix[MAX_SIZE], postfix[MAX_SIZE]; 
 printf("Enter an infix expression: "); 
 fgets(infix, sizeof(infix), stdin); 
 infixToPostfix(infix, postfix); 
 printf("Postfix expression: %s\n", postfix); 
 return 0; 
} 
