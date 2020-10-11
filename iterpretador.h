#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

void init();
void nextChar();
void error(char *fmt, ...);
void fatal(char *fmt, ...);
void expected(char *fmt, ...);
void match(char c);
void getName(char *name);
int getNum();
void emit(char *fmt, ...);
int expression();
void add();
void subtract();
int term();
int factor();
void multiply();
void divide();
int isAddOp(char c);
int isMulOp(char c);
void ident();
void assignment();
void skipWhite();
void newLine();
void input();
void output();