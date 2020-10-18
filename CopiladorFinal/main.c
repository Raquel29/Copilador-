/* main.c */

#include <stdio.h>
#include "input.h"
#include "output.h"
#include "erros.h"
#include "scanner.h"
#include "parser.h"

int main(){
	char name[MAXNAME+1], num[MAXNUM+1];

    initInput();
    getName(name);
    printf("%s", name);
    match('=');
    getNum(num);
    printf("%s", num);
    match('+');
    getName(name);
    printf("%s", name);



    return 0;
}