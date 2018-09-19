/* 
 * File:   ArvoreBinaria.h
 * Author: caio
 *
 * Created on 19 de Dezembro de 2017, 18:16
 */

#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H

typedef struct registro Registro;
typedef struct NO* ArvBin;
ArvBin* cria_ArvBin();
void libera_ArvBin(ArvBin *raiz);
void posOrdem_ArvBin(ArvBin *raiz);
int insere_ArvBin(ArvBin *raiz, Registro valor);
int remove_ArvBin(ArvBin *raiz, int valor);
int consulta_ArvBin(ArvBin *raiz, int valor);

#endif /* ARVOREBINARIA_H */

