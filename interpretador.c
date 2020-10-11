#include <stdio.h>
#include "iterpretador.h"
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#define MAXNAME 30
#define MAXNUM 5

char look; /* O caracter lido "antecipadamente" (lookahead) */
#define MAXVAR 26
int var[MAXVAR];

/* inicializa variáveis */
void initVar()
{
    int i;

    for (i = 0; i < MAXVAR; i++)
        var[i] = 0;
}

/* inicialização do compilador */
void init(){

 nextChar();
 skipWhite();
}

/* lê próximo caracter da entrada */
void nextChar(){
    look = getchar();
}

/* exibe uma mensagem de erro formatada */
void error(char *fmt, ...){
    va_list args;

    fputs("Error: ", stderr);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fputc('\n', stderr);
}

/* exibe uma mensagem de erro formatada e sai */
void fatal(char *fmt, ...){
    va_list args;

    fputs("Error: ", stderr);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fputc('\n', stderr);

    exit(1);
}
/* alerta sobre alguma entrada esperada */
void expected(char *fmt, ...){
    va_list args;

    fputs("Error: ", stderr);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fputs(" expected!\n", stderr);
    exit(1);
}
/* verifica se entrada combina com o esperado */
void match(char c){

 if (look != c)
  expected("'%c'", c);

 nextChar();
 skipWhite();

}
/* recebe o nome de um identificador */
void getName(char *name){
	int i;

 if (!isalpha(look))
  expected("Name");

 for (i = 0; isalnum(look); i++) {
  if (i >= MAXNAME)
   fatal("Identifier too long!");

  name[i] = toupper(look);
  nextChar();

 }

 name[i] = '\0';
 skipWhite();

}
/* recebe um número inteiro */
int getNum(){
   int i;

    i = 0;
    if (!isdigit(look))
        expected("Integer");

    while (isdigit(look)) {
        i *= 10;
        i += look - '0';
        nextChar();
    }

    return i;
}

/* emite uma instrução seguida por uma nova linha */
void emit(char *fmt, ...){
    va_list args;

    putchar('\t');
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    putchar('\n');
}
/* avalia um termo */
int term(){
    int val;

    val = getNum();
    while (isMulOp(look)) {
            switch (look) {
                case '*':
                    match('*');
                    val *= getNum();
                    break;
                case '/':
                    match('/');
                    val /= getNum();
                    break;
            }
    }
        return val;
}
/* analisa e traduz um identificador */
void ident(){
	char name[MAXNAME+1];

    getName(name);
    if (look == '(') {
        match('(');
        match(')');
        emit("CALL %s", name);
        } else
			emit("MOV AX, [%s]", name);
}
/* analisa e traduz um fator */
int factor(){
	int val;

    if (look == '(') {
        match('(');
        val = expression();
        match(')');
    } else if (isalpha(look))
        val = var[getName() - 'A'];
    else
    val = getNum();

    return val;
}
/* avalia o resultado de uma expressão */
int expression(){
    int val;

    if (isAddOp(look))
        val = 0;
    else
        val = term();

    while (isAddOp(look)) {
        switch (look) {
            case '+':
                match('+');
                val += term();
                break;
            case '-':
                match('-');
                val -= term();
                break;
        }
    }

        return val;
}
 
/* reconhece operador aditivo */
int isAddOp(char c){
   return (c == '+' || c == '-');
}
/* reconhece operador aditivo */
int isMulOp(char c){
   return (c == '*' || c=='/');
}
/* reconhece e traduz uma adição */
void add(){
    match('+');
    term();
    emit("POP BX");
    emit("ADD AX, BX");
}
/* pula caracteres de espaço */
void skipWhite(){

 while (look == ' ' || look == '\t')
  nextChar();

}
/* captura um caracter de nova linha */
void newLine()
{
        if (look == '\n')
                nextChar();
}

/* analisa e traduz um comando de atribuição */
void assignment(){

char name;

    name = getName();
    match('=');
    var[name - 'A'] = expression();
}

/* reconhece e traduz uma subtração */
void subtract(){
     match('-');
        term();
        emit("POP BX");
        emit("SUB AX, BX");
        emit("NEG AX");;
}
/* reconhece e traduz uma multiplicação */
void multiply(){
        match('*');
        factor();
        emit("POP BX");
        emit("IMUL BX");
}

/* reconhece e traduz uma divisão */
void divide(){
        match('/');
        factor();
        emit("POP BX");
        emit("XCHG AX, BX");
        emit("CWD");
        emit("IDIV BX");
}
/* interpreta um comando de entrada */
void input()
{
        char name;
        char buffer[20];

        match('?');
        name = getName();
        printf("%c? ", name);
        fgets(buffer, 20, stdin);
        var[name - 'A'] = atoi(buffer);
}

/* interpreta um comando de saída */
void output()
{
        char name;

        match("!");
        name = getName();
        printf("%c -> %d", name, var[name - 'A']);
}

/* PROGRAMA PRINCIPAL */
int main(){
      init();
        do {
            assignment();
            newLine();
        } while (look != '.');

        return 0;
    return 0;
}