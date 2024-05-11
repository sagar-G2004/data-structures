#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Definition of stack ADT
typedef struct node
{
    void *data_ptr;
    struct node *next;
} NODE;

typedef struct stack
{
    NODE *top;
    int count;
} STACK;

// Function declarations
STACK *createstack();
bool pushstack(STACK *, void *);
void *popstack(STACK *);
void *stacktop(STACK *);
bool emptystack(STACK *);
bool stackfull();
int stackcount(STACK *);
void displaystack(STACK *, void (*printdata)(void *));
bool destroystack(STACK *);

// Creation of STACK
STACK *createstack()
{
    STACK *s;
    s = (STACK *)malloc(sizeof(STACK));
    if (s)
    {
        s->top = NULL;
        s->count = 0;
    }
    return s;
}

// Push operation
bool pushstack(STACK *head, void *data_ptr_in)
{
    NODE *newnode;
    newnode = (NODE *)malloc(sizeof(NODE));
    if (newnode)
    {
        newnode->data_ptr = data_ptr_in;
        newnode->next = head->top;
        head->top = newnode;
        head->count++;
        return true;
    }
    return false;
}
// Pop operation
void *popstack(STACK *head)
{
    void *data_ptr_out;
    NODE *pout;
    if (!head->count)
    {
        return NULL;
    }
    pout = head->top;
    head->top = pout->next;
    head->count--;
    data_ptr_out = pout->data_ptr;
    free(pout);
    return data_ptr_out;
}

// Stack top operation
void* stacktop(STACK *head)
{
    if (!head->count)
    {
        return NULL;
    }
    return head->top->data_ptr;
}

// Operation to empty condition
bool emptystack(STACK *head)
{
    return (!head->count);
}

// Operation to full condition
bool stackfull()
{
    NODE *temp;
    temp = (NODE *)malloc(sizeof(NODE));
    if (temp)
    {
        free(temp);
        return false;
    }
    return true;
}

//stack count
int stackcount(STACK *head)
{
    return(head->count);
}

// Display function
void displaystack(STACK *head, void (*printdata)(void *))
{
    NODE *temp;
    for (temp = head->top; temp != NULL; temp = temp->next)
    {
        printdata(temp->data_ptr);
    }
}

// Destroy stack function
bool destroystack(STACK *head)
{
    void *data_ptr_out;
    NODE *temp, *delnode;
    if (!head)
        return false;
    for (temp = head->top; temp != NULL;)
    {
        delnode = temp;
        temp = temp->next;
        data_ptr_out = delnode->data_ptr;
        free(data_ptr_out);
        free(delnode);
    }
    free(head); // Free the stack itself after freeing all nodes
    return true;
}
