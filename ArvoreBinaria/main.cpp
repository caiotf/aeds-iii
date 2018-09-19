/* 
 * File:   main.cpp
 * Author: caio
 *
 * Created on 19 de Dezembro de 2017, 18:08
 */

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "ArvoreBinaria.h"

#define TAM_REG 100

using namespace std;

struct registro {
    int chave;
    long int dado1;
    char dado2[1000];
};

struct NO {
    Registro info;
    struct NO *esq;
    struct NO *dir;
};

ArvBin* cria_ArvBin() {
    ArvBin* raiz = (ArvBin*) malloc(sizeof (ArvBin));
    if (raiz != NULL) {
        *raiz = NULL;
    }
    return raiz;
}

void libera_NO(struct NO* no) {
    if (no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvBin(ArvBin *raiz) {
    if (raiz == NULL)
        return;
    libera_NO(*raiz); //libera cada nó
    free(raiz); //libera a raiz

}

void posOrdem_ArvBin(ArvBin *raiz) {
    if (raiz == NULL)//se existe a arvore
        return;
    if (*raiz != NULL) {
        posOrdem_ArvBin(&((*raiz)->esq));
        posOrdem_ArvBin(&((*raiz)->dir));
        printf("%d %ld %s\n", (*raiz)->info.chave, (*raiz)->info.dado1, (*raiz)->info.dado2);
    }
}

int insere_ArvBin(ArvBin *raiz, Registro valor) {
    if (raiz == NULL)
        return 0;
    struct NO* novo;
    novo = (struct NO*) malloc(sizeof (struct NO));
    if (novo == NULL)//se deu erro na alocação
        return 0;
    novo->info = valor;
    novo->dir = NULL;
    novo->esq = NULL;
    //procura onde inserir!
    if (*raiz == NULL)//se minha arvore é uma arvore vazi, se for so inserir
        *raiz = novo;
    else {
        struct NO* atual = *raiz;
        struct NO* ant = NULL;
        //navega nos nós da arvore até chegar em um nó folha
        while (atual != NULL) {
            ant = atual;
            if (valor.chave == atual->info.chave) {
                free(novo);
                return 0; //elemento já existe
            }
            if (valor.chave > atual->info.chave)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        //insere como filho desse nó folha
        if (valor.chave > ant->info.chave)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}

//função responsável por tratar os 3 tipos de remoção

struct NO* remove_atual(struct NO* atual) {
    struct NO *no1, *no2;
    //sem filho da esquerda. Aponta para o filho da direita (trata nó folha e nó com 1 filho)
    if (atual->esq == NULL) {
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    //procura filho mais a direita na sub-arvore da esquerda
    no1 = atual;
    no2 = atual->esq;
    while (no2->dir != NULL) {
        no1 = no2;
        no2 = no2->dir;
    }
    //copia o filho mais a direita na sub-arvore da esquerda para o lugar do nó removido
    if (no1 != atual) {
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}

//função responsável pela busca do nó a ser removido

int remove_ArvBin(ArvBin *raiz, int valor) {
    if (raiz == NULL) return 0;
    struct NO* ant = NULL;
    struct NO* atual = *raiz;
    while (atual != NULL) {
        //achou o nó a ser removido. tratar o lado da remoção
        if (valor == atual->info.chave) {
            if (atual == *raiz)
                *raiz = remove_atual(atual);
            else {
                if (ant->dir == atual)
                    ant->dir = remove_atual(atual);
                else
                    ant->esq = remove_atual(atual);
            }
            return 1;
        }
        //continua andando na árvore a procura do nó a ser 
        ant = atual;
        if (valor > atual->info.chave)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
}

//consultas

int consulta_ArvBin(ArvBin *raiz, int valor, int *p) {
    *p = 0;
    if (raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while (atual != NULL) {
        if (valor == atual->info.chave) {
            (*p) += 1;
            return atual->info.chave;
        }
        if (valor > atual->info.chave) {
            atual = atual->dir;
            ++(*p);
        }
        else {
            atual = atual->esq;
            ++(*p);
        }
    }
    return 0;
}

int main(int argc, char** argv) {
    Registro *valor = (Registro *) malloc(TAM_REG * sizeof (Registro));

    ArvBin* raiz = cria_ArvBin();
    int i = 0;
    FILE* arq = fopen("//home//caio//Área de Trabalho//Arquivos_TP1//arquivoCres[100L].txt", "r");
    if (arq != NULL) {
        while (fscanf(arq, "%d %ld %[^\n]s", &valor[i].chave, &valor[i].dado1, valor[i].dado2) != EOF) {
            insere_ArvBin(raiz, valor[i]);
            ++i;
        }
    }

    int valorBusca[10], p[10], buscaR[10];
    for (int i = 0; i < 10; ++i) {
        printf("Entre com o valor de busca %d: ", i + 1);
        scanf("%d", &valorBusca[i]);
    }

    double ti, tf, tempo[10]; // ti = tempo inicial // tf = tempo final
    for (int i = 0; i < 10; ++i) {
        //===InicioMedirTempo====
        ti = tf = tempo[i] = 0;
        timeval tempo_inicio, tempo_fim;
        gettimeofday(&tempo_inicio, NULL);

        buscaR[i] = consulta_ArvBin(raiz, valorBusca[i], &p[i]);

        gettimeofday(&tempo_fim, NULL);
        tf = (double) tempo_fim.tv_usec + ((double) tempo_fim.tv_sec * (1000000.0));
        ti = (double) tempo_inicio.tv_usec + ((double) tempo_inicio.tv_sec * (1000000.0));
        tempo[i] = (tf - ti) / 1000;
        //===FimMedirTempo===

        if (buscaR[i] == 0) {
            printf("--------------------------------------------------\n");
            printf("Não encontrado o valor %d: %d\n", i + 1, valorBusca[i]);
            printf("Número de comparações: %d\n", p[i]);
        } else {
            printf("--------------------------------------------------\n");
            printf("Encontrado o valor %d: %d\n", i + 1, buscaR[i]);
            printf("Número de comparações: %d\n", p[i]);
        }
        printf("Tempo gasto da busca em milissegundos: %.3f\n", tempo[i]);
        printf("--------------------------------------------------\n");
    }

    double mediaTemp, somaTemp, mediaComp, somaComp;
    somaComp = 0;
    somaTemp = 0;

    for (int i = 0; i < 10; ++i) {
        somaTemp += tempo[i];
        somaComp += p[i];
    }

    mediaComp = somaComp / 10;
    mediaTemp = somaTemp / 10;

    printf("\n=========================================\n");
    printf("MEDIA DE COMPARAÇÕES: %.4f\n", mediaComp);
    printf("MEDIA DO TEMPO(ms): %.4f\n", mediaTemp);


    //posOrdem_ArvBin(raiz);
    libera_ArvBin(raiz);

    return 0;
}

