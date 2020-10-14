#include <stdio.h>
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

int newLabel();
int postLabel(int lbl);

void condition();
void expression();

void other();
void doIf(int exitLabel);
void doWhile();
void doLoop();
void doRepeat();
void doFor();
void doDo();
void block(int exitLabel);
void program();

//Analisador bolean
void greater();
void relation();
int isRelOp(char c);
void boolFactor();
void notFactor();
void boolTerm();
void boolExpression();
void boolXor();
void boolOr();
void equals();
void notEquals();
void less();
void greater();
void ident();
void signedFactor();
void factor();
void term();
int getBoolean();
int isBoolean(char c);
int isOrOp(char c);

void subtract();
void add();
void divide();
void multiply();
int isAddOp(char c);
int isMulOp(char c);

void block(int exitLabel);
void newLine();

void assignment();