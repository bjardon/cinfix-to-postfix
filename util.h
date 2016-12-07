//
// Created by bruno on 30/05/16.
//

#ifndef STACKEXPRESSIONCONVERTER_UTIL_H
#define STACKEXPRESSIONCONVERTER_UTIL_H

#include "stack.h"
#include "stdlib.h"
#include "ctype.h"

/*****************************************************
 *													 *
 *		Manejo de cadenas 							 *
 *													 *
 *****************************************************/

/*
 * Define un alias String para una cadena de texto
 */
typedef char * String;

/*
 * Declaraciones de funciones
 */

// Manejo de cadenas
void stringinit(String * str, int len);
void lowerstring(String str);
int trimstring(String str, String dest);
void appendstrchar(String str, char character);
int lengthstr(String str);
// Manejo de expresiones
int getprecedence(char character);
int isopeningpar(char c);
int isclosingpar(char c);
int isoperator(char c);
int validateexpression(String str);
void mop(StackPointer stack, char character, String destination);
void savetofile(String str);
int operate(int a, int b, char c);

/*
 * Inicializa una cadena de caracteres
 */
void stringinit(String * str, int len)
{
    *str = (String)malloc(len * sizeof(char));
}

/*
 * Convierte una cadena a minusculas
 */
void lowerstring(String str)
{
    int i = 0;
    int len = lengthstr(str);
    for (i = 0; i < len; i++)
    {
        if (isalpha(*(str + i))){
            *(str + i) = tolower(*(str+i));
        }
    }
}

int trimstring(String str, String dest)
{
    int i, occur = 0;
    int len = lengthstr(str);
    for (i = 0; i < len; ++i)
    {
        if(*(str + i) != 32)
        {
            *(dest + i - occur) = *(str + i);
        }
        else
        {
            occur++;
        }
    }
    return occur;
}

void appendstrchar(String str, char character)
{
    *(str + lengthstr(str)) = character;
    *(str + lengthstr(str)) = 0;
}

int lengthstr(String str)
{
    int length = 0;
    while(*(str + length))
    {
        length++;
    }
    return length;
}

/*****************************************************
 *		Manejo de operadores						 *
 *****************************************************/

int getprecedence(char character)
{
    switch(character)
    {
        case '^':
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        case '(':
            return 0;
        case ')':
            return -1;
        default:
            return character;
    }
}

int isopeningpar(char c)
{
    if(c == '(')
        return 1;
    return 0;
}

int isclosingpar(char c)
{
    if(c == ')')
        return 1;
    return 0;
}

int isoperator(char c)
{
    if(getprecedence(c) != c && !isclosingpar(c) && !isopeningpar(c))
    {
        return 1;
    }
    return 0;
}

int validateexpression(String str)
{
    Stack stack;
    StackPointer sp = stackinit(&stack);
    int i, ob = 0, cb = 0;

    for (i = 0; i < lengthstr(str); i++) {
        if(isopeningpar(*(str + i))){
            push(sp, 1);
        } else if(isclosingpar(*(str + i))){
            if(pop(sp) == NULL) {
                cb++;
            }
        }
    }

    if(isempty(stack) && cb == 0 && ob == 0){
        return 1;
    } else {
        return 0;
    }
}

void mop(StackPointer stack, char character, String destination)
{
    int repeat = 1;
    char value;
    if(isempty(*stack))
    {
        push(stack, character);
    }
    else
    {
        if(isopeningpar(character)){
            push(stack, character);
        }
        else if(getprecedence(character) > getprecedence(top(stack)->value))
        {
            push(stack, character);
        }
        else
        {
            while(repeat){
                value = pop(stack)->value;
                if(!isopeningpar(value) && !isclosingpar(value)){
                    appendstrchar(destination, value);
                }
                if(isempty(*stack))
                {
                    repeat = 0;
                }
                else if(getprecedence(character) < getprecedence(top(stack)->value)) {
                    repeat = 1;
                }
            }
            push(stack, character);
        }
    }
}

void savetofile(String str)
{
    FILE * file = fopen("postfix.txt", "w+");
    fprintf(file, "%s\n", str);
    fclose(file);
}


#endif //STACKEXPRESSIONCONVERTER_UTIL_H
