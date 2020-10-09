#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

void init();
void nextChar();
void error(char *fmt, ...);
void fatal(char *fmt, ...);
void expected(char *fmt, ...);
void match(char c);
char getName();
char getNum();
void emit(char *fmt, ...);
void expression();
void add();
void subtract();
void term();
void factor();
void multiply();
void divide();
int isAddOp(char c);
