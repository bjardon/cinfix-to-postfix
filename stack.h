//
// Created by bruno on 30/05/16.
//

#ifndef STACKEXPRESSIONCONVERTER_STACK_H
#define STACKEXPRESSIONCONVERTER_STACK_H

#include "stdlib.h"
#include "stdio.h"

/** Data type definitions */
typedef struct _node {
    int value;
    struct _node *next;
} Node;

typedef Node *NodePointer;
typedef Node *Stack;
typedef Node **StackPointer;

/** Method prototypes **/
StackPointer stackinit(StackPointer s);
void push(StackPointer s, int v);
NodePointer pop(StackPointer s);
NodePointer top(StackPointer s);

int isempty(Stack s);
int count(Stack s);

void flushstack(StackPointer s);
void showall(Stack s);

/**
	* Initializes a given Stack
	*/
StackPointer stackinit(StackPointer stack){
    *stack = NULL;
    return stack;
}

/**
	* Inserts a node to the end of the stack
	*/
void push(StackPointer stack, int v)
{
    NodePointer newnode;
    newnode = (NodePointer)malloc(sizeof(Node));
    newnode->value = v;

    newnode->next = *stack;
    *stack = newnode;
}

NodePointer pop(StackPointer stack)
{
    if(isempty(*stack)){
        return NULL;
    }
    else
    {
        NodePointer aux = *stack;
        *stack = aux->next;
        return aux;
    }
}

NodePointer top(StackPointer stack)
{
    return *stack;
}

/**
	* Checks if the stack is empty
	*/
int isempty(Stack stack)
{
    if(stack == NULL)
    {
        return 1;
    }
    return 0;
}

int count(Stack stack)
{
    NodePointer aux;
    aux = stack;
    int i = 0;
    while (aux)
    {
        aux = aux->next;
        i++;
    }
    return i;
}

/**
	* Removes all elements in the stack
	*/
void flushstack(StackPointer stack)
{
    NodePointer node;

    while(*stack)
    {
        node = *stack;
        *stack = node->next;
        free(node);
    }
}

/**
	* Prints to stdout all nodes, indicating its HEX RAM address
	*/
void showall(Stack stack)
{
    NodePointer node = stack;

    if(isempty(stack))
    {
        printf("Pila vacia\n");
    }
    else
    {
        int i = 0;
        while(node)
        {
            printf("Nodo #%d en RAM{%p}: %d\n", i, node, node->value);
            node = node->next;
            i++;
        }
        printf("\n");
    }
}

#endif //STACKEXPRESSIONCONVERTER_STACK_H
