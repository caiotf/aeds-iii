/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: caio
 *
 * Created on 9 de Janeiro de 2018, 03:15
 */

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

#define TAM_REG 1000000
#define MAX_STR_SIZE	1000
#define MIN_STR_SIZE	5

using namespace std;

char* geraStringAleatoria(){
    
  	char *validchars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *novastr;
	register int i;
	int str_len;

	// novo tamanho
	str_len = (rand() % MAX_STR_SIZE );

	// checa tamanho
	str_len += ( str_len < MIN_STR_SIZE ) ? MIN_STR_SIZE : 0;

	// aloca memoria
	novastr = ( char * ) malloc ( (str_len + 1) * sizeof(char));
	if ( !novastr ){
		printf("[*] Erro ao alocar memoria.\n" );
		exit ( EXIT_FAILURE );
	}
	
	// gera string aleatória
	for ( i = 0; i < str_len; i++ ) {
		novastr[i] = validchars[ rand() % strlen(validchars) ];
		novastr[i + 1] = 0x0;
	}
        
        return novastr;

}

int comparaCrescente(const void* a, const void* b){
    if(*(int*)a == *(int*)b)
        return 0;//iguais
    else
        if(*(int*)a < *(int*)b)
            return -1;//vem antes
        else
            return 1;//vem depois
}

int comparaDecrescente(const void* a, const void* b){
    if(*(int*)a == *(int*)b)
        return 0;//iguais
    else
        if(*(int*)a < *(int*)b)
            return 1;//vem depois
        else
            return -1;//vem antes
}

int escreverArquivo(){
 
  FILE* info = fopen("arquivo[100000L].txt", "w");
  
  int i=0;
  while(i<TAM_REG){
    fprintf(info,"%d %ld %s\n", (rand() % INT_MAX), (rand() % LONG_MAX), geraStringAleatoria());
    ++i;
  } 
}

int escreverArquivoCres(){
  
  int *chave = (int*) malloc (TAM_REG * sizeof (int));
  for(int i=0; i<TAM_REG ;++i)
    chave[i] = rand() % INT_MAX;
  
  qsort(chave, TAM_REG, sizeof(int), comparaCrescente);
  
  FILE* info = fopen("arquivoCres[100000L].txt", "w");
  
  int i=0;
  while(i<TAM_REG){
    fprintf(info,"%d %ld %s\n", chave[i], (rand() % LONG_MAX), geraStringAleatoria());
    ++i;
  } 
}

int escreverArquivoDecres(){
  
  int *chave = (int*) malloc (TAM_REG * sizeof (int));
  for(int i=0; i<TAM_REG ;++i)
    chave[i] = rand() % INT_MAX;
  
  qsort(chave, TAM_REG, sizeof(int), comparaDecrescente);
  
  FILE* info = fopen("arquivoDecres[100000L].txt", "w");
  
  int i=0;
  while(i<TAM_REG){
    fprintf(info,"%d %ld %s\n", chave[i], (rand() % LONG_MAX), geraStringAleatoria());
    ++i;
  } 
}

int main() {
    
    srand ( time(NULL ));
    //escreverArquivo();
    //escreverArquivoCres();
    escreverArquivoDecres();
            
  return 0;
}

