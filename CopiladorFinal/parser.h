/* parser.h */

#ifndef _PARSER_H
#define _PARSER_H

#define MAXNAME 30
#define MAXNUM 5
#include <ctype.h>

void factor();/* analisa e traduz um fator matemático */
void signedTerm();/* analisa e traduz um fator com um sinal opcional */
void expression();/* analisa e traduz uma expressão */
void add();/* analisa e traduz uma operação de soma */
void subtract();/* analisa e traduz uma operação de subtração */
void term();/* analisa e traduz um termo */
void assignment();/* analisa e traduz um comando de atribuição */
void boolXor();/* analisa e traduz uma operação OU-exclusivo booleana */
void boolOr();/* analisa e traduz uma operação OU booleana */
void boolAnd();/* analisa e traduz uma operação AND */
void notFactor();/* analisa e traduz um fator com NOT opcional */
#endif