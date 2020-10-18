/* scanner1.h */

#ifndef _SCANNER_H
#define _SCANNER_H

#define MAXNAME 30
#define MAXNUM 5


int isAddOp(char c);/* reconhece um operador aditivo */
int isMulOp(char c);/* reconhece um operador multiplicativo */

void match(char c);/* verifica se caracter combina com o esperado */
char getName(char *name);/* retorna um identificador */
char getNum(char *num);/* retorna um número */
void nextChar();/* lê próximo caracter da entrada */

#endif