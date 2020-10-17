#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include "lexica.h"
#define MAXNAME 30
#define MAXNUM 5
#define MAXTOKEN 10
#define MAXOP 5
#define SYMTBL_SZ 1000
#define KWLIST_SZ 4

char look; /* O caracter lido "antecipadamente" (lookahead) */
int token;
char value[MAXTOKEN+1];
char name[MAXNAME+1];
char *symtbl[SYMTBL_SZ];
char *kwlist[KWLIST_SZ] = {"IF", "ELSE", "ENDIF", "END"};
//enum { KW_IF, KW_ELSE, KW_ENDIF, KW_END, TK_IDENT,TK_NUMBER, TK_OPERATOR };
 const char *kwcode = "ilee";

/* PROGRAMA PRINCIPAL */
int main(){

    init();

    do {
        scan();
        switch (token) {
            case 'x':
                printf("Ident: ");
                break;
            case '#':
                printf("Number: ");
                break;
            case 'i':
            case 'l':
            case 'e':
                printf("Keyword: ");
                break;
            default:
                printf("Operator: ");
                break;
            }
            printf("%s\n", value);
            if (value[0] == '\n')
                newLine();
    } while (strcmp(value, "END") == 0);
        return 0;
}
/*    */
int lookup(char *s, char *list[], int size){

    int i;
    for (i = 0; i < size; i++) {
        if (strcmp(list[i], s) == 0)
            return i;
    }
        return -1;
}
/*Reconhece espaços e virgulas*/
void skipComma(){

    skipWhite();
    if (look == ',') {
        nextChar();
        skipWhite();
    }
}

/*Reconhecedor de operadores*/
int isOp(char c){
    return (strchr("+-*/<>:=", c) != NULL);

}
void getOp(){
     
    int i;
    if (!isOp(look))
        expected("Operator");
    for (i = 0; isOp(look) && i < MAXOP; i++) {
        value[i] = look;
        nextChar();
    }
    value[i] = '\0';
    if (strlen(value) == 1)
        token = value[0];
    else
        token = '?';
}
/* pula caracteres de espaço */
void skipWhite(){

 while (look == ' ' || look == '\t')
  nextChar();

}
/* reconhece uma linha em branco */
void newLine()
{
    if (look == '\n')
        nextChar();
}
void scan(){
    
    int kw;
    while (look == '\n')
        newLine();
        if (isalpha(look))
            getName();
        else if (isdigit(look))
            getNum();
        else if (isOp(look))
            getOp();
        else {
            value[0] = look;
            value[1] = '\0';
            token = '?';
            nextChar();
        }
        skipWhite();
}

/* inicialização do compilador */
void init()
{
    nextChar();
}

/* lê próximo caracter da entrada */
void nextChar()
{
    look = getchar();
}

/* exibe uma mensagem de erro formatada */
void error(char *fmt, ...)
{
    va_list args;

    fputs("Error: ", stderr);

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fputc('\n', stderr);
}

/* exibe uma mensagem de erro formatada e sai */
void fatal(char *fmt, ...)
{
    va_list args;

    fputs("Error: ", stderr);

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fputc('\n', stderr);

    exit(1);
}

/* alerta sobre alguma entrada esperada */
void expected(char *fmt, ...)
{
    va_list args;

    fputs("Error: ", stderr);

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fputs(" expected!\n", stderr);

    exit(1);
}

/* verifica se entrada combina com o esperado */
void match(char c)
{
    if (look != c)
        expected("'%c'", c);
    nextChar();
}

/* recebe o nome de um identificador */
char getName()
{
    int i, kw;

    if (!isalpha(look))
        expected("Name");
    for (i = 0; isalnum(look) && i < MAXNAME; i++) {
        value[i] = toupper(look);
        nextChar();
    }
    value[i] = '\0';
    kw = lookup(value, kwlist, KWLIST_SZ);
    if (kw == -1)
        token = 'x';
    else
        token = kwcode[kw];
    
}

/* recebe um número inteiro */
char getNum()
{
      int i;

 

                if (!isdigit(look))

                               expected("Integer");

                for (i = 0; isdigit(look) && i < MAXNUM; i++) {

                               value[i] = look;

                               nextChar();

                }

                value[i] = '\0';

        token = '#';
}

/* emite uma instrução seguida por uma nova linha */
void emit(char *fmt, ...)
{
    va_list args;

    putchar('\t');

    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    putchar('\n');
}