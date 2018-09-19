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

#define TAM_REG 1000

using namespace std;

typedef struct registro{
    int chave;
    long int dado1;
    char dado2[1000];
}Registro;

int buscaSequencial(Registro *vetor, int chave, int *p) {
    for (int i = 0; i < TAM_REG; ++i) {
        if (vetor[i].chave == chave){
            *p = i +1;
            return vetor[i].chave;
        }
        *p = i + 1;    
    }

    return -1;
}

int main(int argc, char** argv) {
    
    Registro *vetor = (Registro *)malloc(TAM_REG * sizeof(Registro));

    int i = 0;   
    FILE* arq = fopen("//home//caio//Área de Trabalho//Arquivos_TP1//arquivoCres[1000L].txt", "r");
    if(arq!=NULL){
        while(fscanf(arq, "%d %ld %[^\n]s", &vetor[i].chave, &vetor[i].dado1, vetor[i].dado2) != EOF) {
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
    
    buscaR[i] = buscaSequencial(vetor, valorBusca[i], &p[i]);

    gettimeofday(&tempo_fim, NULL);
    tf = (double) tempo_fim.tv_usec + ((double) tempo_fim.tv_sec * (1000000.0));
    ti = (double) tempo_inicio.tv_usec + ((double) tempo_inicio.tv_sec * (1000000.0));
    tempo[i] = (tf - ti) / 1000;
    //===FimMedirTempo===

        if (buscaR[i] == -1) {
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
    
    
    
    return 0;
}

