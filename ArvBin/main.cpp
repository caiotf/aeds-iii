#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Programa para manipulação de um arquivo (Modo TEXTO), contendo dados de um 
dicionário de palavras e criando uma arvore binária para a manipulação de 
palavras e significados correspondentes.

O arquivo deve estar no formato a seguir:  (no programa usamos dic.txt)
----------------------
gato#sm#bicho do mato#
cao#sm#bicho domestico#
leao#sm#bicho da selva#
canguru#sm#bicho que pula#
foca#sf#bicho da agua#%
------------------------

*/

typedef struct vocabulo{
   char palavra[40];
   char cg[10];
   char def[100];     
}VOCAB;

typedef struct nodo{ 
   VOCAB e; 
   struct nodo *esq; 
   struct nodo *dir; 
} NO; 
  
typedef NO *ARV; 
  
 
// Função para criar uma nova arvore
ARV nova_arv() 
{ 
    return NULL; 
} 
  
int EMPTY (ARV a)
{ return (a == NULL);}  
  
  
//  Função para inserir um novo elemento 'b' na arvore 'a'
ARV insere (ARV a, VOCAB b) 
{ ARV nova; 
  if (EMPTY(a))
    { 
      nova = (ARV) malloc (sizeof(NO)); 
      nova->esq = NULL; 
      nova->dir = NULL;
      nova->e = b; 
      return nova; 
    } 
  else 
    { if ( strcmp(a->e.palavra,b.palavra) < 0 ) 
        a->dir = insere(a->dir, b); 
      else 
        a->esq = insere(a->esq, b);  /* Repeticoes sao inseridas na esquerda! */ 
      return a; 
    } 
} 

// Função para procurar um elemento numa arvore  
ARV procura (ARV a , char *b) 
{ 
  VOCAB c;
  if (EMPTY(a))          return NULL; 
  else 
    if ( strcmp(a->e.palavra,b) == 0 )  return a; 
    else 
      if ( strcmp(a->e.palavra,b) < 0 ) 
                      return procura (a->dir, b); 
      else            return procura (a->esq, b); 
} 

  
//Função para percorrer a arvore binária com critério pre-ordem
void preorder (ARV a) 
{ 
  if (! EMPTY(a) ) 
    { printf("%s ",a->e.palavra); 
      preorder(a->esq); 
      preorder(a->dir); 
    } 
}   

//Função para percorrer a arvore binária com critério em-ordem
void inorder (ARV a) 
{ 
  if (! EMPTY(a) ) 
    { inorder(a->esq);
      fflush(stdin);
      printf("%s ",a->e.palavra);
      inorder(a->dir); 
    } 
} 

//Função para percorrer a arvore binária com critério pós-ordem
void posorder (ARV a) 
{ 
  if (! EMPTY(a) ) 
    { posorder(a->esq);
      posorder(a->dir); 
      printf("%s ",a->e.palavra);
    } 
} 
  
 

int main(){
    
    FILE *arquivo;
    ARV a=NULL,b;
    VOCAB e;
    int i=0;
    char rem[40];
    char continua='s';
    char item[100];
    int f1=0,f2=0,f3=0;
    

    
    arquivo = fopen("dic.txt","r");
    printf("\n--------------Inicio da leitura do arquivo");
    while (!feof(arquivo)){
        continua=fgetc(arquivo);
        if(continua != '%'){   
           i=0;
           while(continua!='#'){
               if (continua!='\n')
                   {item[i]=continua; i++;}
               continua=fgetc(arquivo);
           }   
           item[i]='\0';  
           
           if (f1==0) {strcpy(e.palavra,item); f1=1;} 
           else if (f2==0) {strcpy(e.cg,item); f2=1;}  
                else if (f3==0) {strcpy(e.def,item); f3=1;} 
           if((f1==1)&&(f2==1)&&(f3==1)) {
               printf("\n\nVocabulo: %s \nClassificacao Gramatical: %s \nDefinicao: %s",e.palavra,e.cg,e.def);
               a=insere(a,e); f1=0;f2=0;f3=0;}
        }
        else {printf("\n\n--------------Fim da leitura do arquivo");  break;}
    }
    
    fclose(arquivo);
    
    printf("\n\n Lista de Palavras\nEm ordem: ");
    inorder(a);
    printf("\nPre ordem: ");
    preorder(a);
    printf("\nPos ordem: ");
    posorder(a);


    
    
    
    system("pause>>null");
    return 0;    
    
    }