
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// The array will store the items in the stack, first in
// index 0, then 1, etc. top will represent the index
// to the top element in the stack. If the stack is
// empty top will be -1.
//
#define SIZE 20
#define EMPTY -1

struct stack
{

    char items[SIZE];

    int top;

};

void initialize(struct stack* stackPtr);
int full(struct stack* stackPtr);
int push(struct stack* stackPtr, char value);
int empty(struct stack* stackPtr);
char pop(struct stack* stackPtr);
int top(struct stack* stackPtr);
void display(struct stack* stackPtr);
int checkBalance(char exp[]);
char* infixToPostfix(char infix[]);
int priority(char ch);
int isOperator(char ch);
int isParentheses(char ch1);

int checkBalance(char exp[])
{
    int valid = 1;
    struct stack mine;

    initialize(&mine);

    printf("\nChecking balance...\n");
    for(int i = 0; exp[i]!='\0' ; i++)
    {
        if(exp[i]== '{' || exp[i]== '[' || exp[i]== '(')
        {
            push(&mine, exp[i]);
        }
        else if(exp[i]== ')')
        {
            char a = pop(&mine);

            if(a == 'I' || a != '(')
            {
                valid = 0;
                printf("INVALID for )!!!!\n");
                return valid;
            }
        }else if(exp[i]== ']')
        {
            char a = pop(&mine);

            if(a == 'I' || a != '[')
            {
                valid = 0;
                printf("INVALID for ]!!!!\n");
                return valid;
            }
        }else if(exp[i]== '}')
        {
            char a = pop(&mine);

            if(a == 'I' || a != '{')
            {
                valid = 0;
                printf("INVALID for }!!!!\n");
                return valid;
            }
        }
    }
    if(pop(&mine) != 'I')
    {
        valid = 0;
        printf("INVALID. You have extra!!!\n");
    }
    if(valid == 1)
    {
        printf("VALID\n");
    }
    return valid;
}

int priority(char ch)
{
    if(ch == '^')
    {
        return 3;
    }
    else if(ch == '/' || ch == '*' || ch == '%')
    {
        return 2;
    }
    else if(ch == '+' || ch == '-')
    {
        return 1;
    }
    else if(ch == '(' || ch == '{' || ch == '[')
    {
        return 0;
    }
}

char* infixToPostfix(char infix[])
{
    struct stack operators;
    initialize(&operators);

    int count = 0;

    char* postfix = (char*)malloc(sizeof(char) * (2 * strlen(infix) + 1));

    for(int i = 0;  i < strlen(infix); i++)
    {
        if(isdigit(infix[i]))
        {
            while(isdigit(infix[i]))
            {
                postfix[count] = infix[i];
                i++;
                count++;
            }
            i--;

            postfix[count] = ' ';
            count++;
        }
        else if(isOperator(infix[i]))
        {
            if(empty(&operators))
            {
                push(&operators, infix[i]);
            }

            else if(priority(infix[i]) > priority(top(&operators)))
            {
                push(&operators, infix[i]);
            }
            else
            {
                while(!empty(&operators) && priority(infix[i]) <= priority(top(&operators)) && !isParentheses(top(&operators)))
                {

                    postfix[count] = pop(&operators);
                    count++;
                    postfix[count] = ' ';
                    count++;
                }
                push(&operators,infix[i]);
            }
        }
        else if(infix[i] == '(' || infix[i] == ')')
        {
            if(infix[i] == '(')
                push(&operators, infix[i]);
            else
            {
                while(top(&operators) != '(')
                {
                    postfix[count] = pop(&operators);
                    count++;
                    postfix[count] = ' ';
                    count++;

                }
                pop(&operators);
            }
        }
        else if(infix[i] == '[' || infix[i] == ']')
        {
            if(infix[i] == '[')
                push(&operators, infix[i]);
            else
            {
                while(top(&operators) != '[')
                {
                    postfix[count] = pop(&operators);
                    count++;
                    postfix[count] = ' ';
                    count++;

                }
                pop(&operators);
            }
        }
        else if(infix[i] == '{' || infix[i] == '}')
        {
            if(infix[i] == '{')
                push(&operators, infix[i]);
            else
            {
                while(top(&operators) != '{')
                {
                    postfix[count] = pop(&operators);
                    count++;
                    postfix[count] = ' ';
                    count++;

                }
                pop(&operators);
            }
        }

    }
    //pop all operators left in the stack and add space between them.
    while(operators.top != -1)
    {
        postfix[count] = pop(&operators);
        count++;
        postfix[count] = ' ';
        count++;
    }
    return postfix;
}

int isOperator(char ch)
{
    if(ch == '/' || ch == '*' || ch == '+' || ch == '-' || ch == '^' || ch == '%')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isParentheses(char ch1)
{
    if(ch1== '{' || ch1== '[' || ch1== '(')
    {

        return 1;
    }
    else
    {

        return 0;
    }
}


int main() {
    int ch;
    char exp[SIZE], c;

    int valid;

    printf("\nEnter Expression :");
    scanf("%[^\n]s",exp);

    printf("Your input expression: %s", exp);

    valid = checkBalance(exp);

    if(valid)
    {
        char* postfix = infixToPostfix(exp);
        printf("The postfix is: %s\n", postfix);
        free(postfix);
    }
}

void initialize(struct stack* stackPtr)
{
    stackPtr->top = -1;
}

// If the push occurs, 1 is returned. If the
// stack is full and the push can't be done, 0 is
// returned.
int push(struct stack* stackPtr, char value)
{

    // Check if the stack is full.
    if (full(stackPtr))
        return 0;

    // Add value to the top of the stack and adjust the value of the top.
    stackPtr->items[stackPtr->top+1] = value;
    (stackPtr->top)++;
    return 1;
}

// Returns true iff the stack pointed to by stackPtr is full.
int full(struct stack* stackPtr)
{
    return (stackPtr->top == SIZE - 1);
}

// Returns true iff the stack pointed to by stackPtr is empty.
int empty(struct stack* stackPtr)
{
    return (stackPtr->top == -1);
}

// Pre-condition: The stack pointed to by stackPtr is NOT empty.
// Post-condition: The value on the top of the stack is popped and returned.
// Note: If the stack pointed to by stackPtr is empty, -1 is returned.
char pop(struct stack* stackPtr)
{

    char retval;

    // Check the case that the stack is empty.
    if (empty(stackPtr))
        return 'I';

    // Retrieve the item from the top of the stack, adjust the top and return
    // the item.
    retval = stackPtr->items[stackPtr->top];
    (stackPtr->top)--;
    return retval;
}

// Pre-condition: The stack pointed to by stackPtr is NOT empty.
// Post-condition: The value on the top of the stack is returned.
// Note: If the stack pointed to by stackPtr is empty, -1 is returned.
int top(struct stack* stackPtr)
{

    // Take care of the empty case.
    if (empty(stackPtr))
        return EMPTY;

    // Return the desired item.
    return stackPtr->items[stackPtr->top];
}


void display(struct stack* stackPtr)
{
    for(int i=0; i<=stackPtr->top; i++)
        printf("%c-->", stackPtr->items[i]);

    printf("\n");
}