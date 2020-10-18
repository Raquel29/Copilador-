/* codegen.h */

#ifndef _CODEGEN_H
#define _CODEGEN_H

void asmLoadConstant(char *s);/* carrega uma constante no registrador primário */
void asmLoadVariable(char *s);/* carrega uma variável no registrador primário */
void asmNegate();/* inverte sinal de reg. prim. */
void asmPush();/* coloca registrador primário na pilha */
void asmPopAdd();/* adiciona topo da pilha a reg. primário */
void asmPopSub();/* subtrari do topo da pilha o reg. primário */
void asmPopMul();/* adiciona topo da pilha a reg. primário */
void asmPopDiv();/* subtrari do topo da pilha o reg. primário */
void asmStoreVariable(char *name);/* armazena valor do registrador primário em variável */
void asmPopOr();/* aplica OU com topo da pilha a reg. primário */
void asmPopXor();/* aplica OU-exclusivo com topo da pilha a reg. primário */
void asmPopAnd();/* aplica AND com topo da pilha a reg. primário */
void asmNot();/* aplica NOT a reg. primário */


#endif