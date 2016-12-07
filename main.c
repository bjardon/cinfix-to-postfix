#include "util.h"

int main(int argc, char const *argv[]) {
    String input;
    String expr;
    String post;
    Stack stack;
    StackPointer stackpointer;
    int i;
    char value;

    stringinit(&input, 255);
    stringinit(&expr, 255);
    stringinit(&post, 255);
    stackpointer = stackinit(&stack);

    printf("Ingrese una expresion\n  $>> ");
    scanf("%[^\n]s", input);
    printf("\n");
    trimstring(input, expr);
    lowerstring(expr);
    printf("Expresion introducida:\n   %s\n\n", expr);
    printf("Verificando la expresion...\n\n");
    if(validateexpression(expr)){
        printf("La expresion es valida.\n   Se convertira a notacion posfija\n\n");
        for (i = 0; i < lengthstr(expr); i++)
        {
            if(isalpha(expr[i]))
                appendstrchar(post, expr[i]);
            else
                mop(stackpointer, expr[i], post);
        }
        while(!isempty(stack))
        {
            value = pop(stackpointer)->value;
            if(!isopeningpar(value) && !isclosingpar(value))
                appendstrchar(post, value);
        }
        printf("El resultado en notacion posfija es:\n   %s\n\n", post);
        savetofile(post);
    }
    else
        printf("La expresion [ %s ] contiene errores.\n   Verifique los parentesis de apertura y cierre.\n", expr);

    return 0;
}