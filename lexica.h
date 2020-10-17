#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>


/* protótipos */
void init();
void nextChar();
void error(char *fmt, ...);
void fatal(char *fmt, ...);
void expected(char *fmt, ...);
void match(char c);
char getName();
char getNum();
void emit(char *fmt, ...);

void skipWhite();
void scan();
void newLine();

int isOp(char c);
void getOp();

void skipComma();
int lookup(char *s, char *list[], int size);