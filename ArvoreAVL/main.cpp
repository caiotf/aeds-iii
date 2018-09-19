/* 
 * File:   main.cpp
 * Author: caio
 *
 * Created on 20 de Dezembro de 2017, 03:16
 */

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "ArvoreAVL.h"

#define TAM_REG 100

using namespace std;

struct registro{
    int chave;
    long int dado1;
    char dado2[1000];
};

struct NO{
    Registro info;
    int altura;
    struct NO *esq;
    struct NO *dir;
};

ArvAVL* cria_ArvAVL(){
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvAVL(ArvAVL* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada nó
    free(raiz);//libera a raiz
}

int altura_NO(struct NO* no){
    if(no == NULL)
        return -1;
    else
    return no->altura;
}

int fatorBalanceamento_NO(struct NO* no){
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

int altura_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvAVL(&((*raiz)->esq));
    int alt_dir = altura_ArvAVL(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

void posOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        posOrdem_ArvAVL(&((*raiz)->esq));
        posOrdem_ArvAVL(&((*raiz)->dir));
        printf("%d %ld %s\n", (*raiz)->info.chave, (*raiz)->info.dado1, (*raiz)->info.dado2);
    }
}

int consulta_ArvAVL(ArvAVL *raiz, int valor, int *p){
    *p=0;
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info.chave){
            (*p) += 1;
            return atual->info.chave;
        }
        if(valor > atual->info.chave){
            atual = atual->dir;
            ++(*p);
        }    
        else{
            atual = atual->esq;
            ++(*p);
        }
    }
    return 0;
}

//=================================
void RotacaoLL(ArvAVL *A){//LL *A: nó que foi desbalanceado e que eu quero balancear 
    //printf("RotacaoLL\n");
    struct NO *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
    *A = B;
}

void RotacaoRR(ArvAVL *A){//RR
    //printf("RotacaoRR\n");
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

void RotacaoLR(ArvAVL *A){//LR
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

void RotacaoRL(ArvAVL *A){//RL
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

int insere_ArvAVL(ArvAVL *raiz, Registro valor){
    int res;
    if(*raiz == NULL){//árvore vazia ou nó folha
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;

        novo->info = valor;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    if(valor.chave < atual->info.chave){//inserção a esquerda
        if((res = insere_ArvAVL(&(atual->esq), valor)) == 1){//se inserção funcionou =1
            if(fatorBalanceamento_NO(atual) >= 2){
                if(valor.chave < (*raiz)->esq->info.chave ){
                    RotacaoLL(raiz);
                }else{
                    RotacaoLR(raiz);
                }
            }
        }
    }else{
        if(valor.chave > atual->info.chave){//insercao a direita
            if((res = insere_ArvAVL(&(atual->dir), valor)) == 1){//se inserção funcionou =1
                if(fatorBalanceamento_NO(atual) >= 2){
                    if((*raiz)->dir->info.chave < valor.chave){
                        RotacaoRR(raiz);
                    }else{
                        RotacaoRL(raiz);
                    }
                }
            }
        }else{
            //elemento ja existe
            return 0;
        }
    }

    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return res;
}

struct NO* procuraMenor(struct NO* atual){
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int remove_ArvAVL(ArvAVL *raiz, int valor){
	if(*raiz == NULL){// valor não existe
	    printf("valor não existe!!\n");
	    return 0;
	}

    int res;
	if(valor < (*raiz)->info.chave){
	    if((res = remove_ArvAVL(&(*raiz)->esq,valor)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
	    }
	}

	if((*raiz)->info.chave < valor){
	    if((res = remove_ArvAVL(&(*raiz)->dir, valor)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq) )
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
	    }
	}

	if((*raiz)->info.chave == valor){
	    if(((*raiz)->esq == NULL || (*raiz)->dir == NULL)){// nó tem 1 filho ou nenhum
			struct NO *oldNode = (*raiz);
			if((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
			free(oldNode);
		}else { // nó tem 2 filhos
			struct NO* temp = procuraMenor((*raiz)->dir);
			(*raiz)->info = temp->info;
			remove_ArvAVL(&(*raiz)->dir, (*raiz)->info.chave);
            if(fatorBalanceamento_NO(*raiz) >= 2){
				if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}
		if (*raiz != NULL)
            (*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;
		return 1;
	}

	(*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;

	return res;
}

int main(int argc, char** argv) {
    Registro *valor = (Registro *)malloc(TAM_REG * sizeof(Registro));

    ArvAVL* raiz = cria_ArvAVL();
    int i = 0;   
    FILE* arq = fopen("//home//caio//Área de Trabalho//Arquivos_TP1//arquivoCres[100L].txt", "r");
    if(arq!=NULL){
        while(fscanf(arq, "%d %ld %[^\n]s", &valor[i].chave, &valor[i].dado1, valor[i].dado2) != EOF) {
            insere_ArvAVL(raiz, valor[i]);
            ++i;
        }
    }
    
    int valorBusca[10], p[10], buscaR[10];
    for (int i=0; i < 10; ++i) {
        printf("Entre com o valor de busca %d: ", i+1);
        scanf("%d", &valorBusca[i]);
    }
    
    double ti, tf, tempo[10]; // ti = tempo inicial // tf = tempo final
    for(int i=0; i<10; ++i){
    //===InicioMedirTempo====
    ti = tf = tempo[i] = 0;
    timeval tempo_inicio, tempo_fim;    
    gettimeofday(&tempo_inicio, NULL);
    
    buscaR[i] = consulta_ArvAVL(raiz, valorBusca[i], &p[i]);

    gettimeofday(&tempo_fim, NULL);
    tf = (double) tempo_fim.tv_usec + ((double) tempo_fim.tv_sec * (1000000.0));
    ti = (double) tempo_inicio.tv_usec + ((double) tempo_inicio.tv_sec * (1000000.0));
    tempo[i] = (tf - ti) / 1000;
    //===FimMedirTempo===

        if (buscaR[i] == 0) {
            printf("--------------------------------------------------\n");
            printf("Não encontrado o valor %d: %d\n", i+1, valorBusca[i]);
            printf("Número de comparações: %d\n", p[i]);
        } else {
            printf("--------------------------------------------------\n");
            printf("Encontrado o valor %d: %d\n", i+1, buscaR[i]);
            printf("Número de comparações: %d\n", p[i]);
        }
        printf("Tempo gasto da busca em milissegundos: %.3f\n", tempo[i]);
        printf("--------------------------------------------------\n");
    }
    
    double mediaTemp, somaTemp, mediaComp, somaComp;
    somaComp = 0;
    somaTemp = 0;
    
    for(int i=0; i<10; ++i){
        somaTemp += tempo[i];
        somaComp += p[i];
    }
    
    mediaComp = somaComp / 10;
    mediaTemp = somaTemp / 10;
    
    printf("\n=========================================\n");
    printf("MEDIA DE COMPARAÇÕES: %.4f\n", mediaComp);
    printf("MEDIA DO TEMPO(ms): %.4f\n", mediaTemp);
    
    //posOrdem_ArvAVL(raiz);
    libera_ArvAVL(raiz);

    return 0;
}

