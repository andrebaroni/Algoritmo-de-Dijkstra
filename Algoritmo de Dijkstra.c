#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define vertMax 100

void algDijkstra(int destino, int origem, int *custos, int vertices){  //cria função do algoritimo, passando o destino, origem, custo e seus vertices como parametro//
     int i, vetAnt[vertMax], camMin[vertMax]; /*vetor de antecessores, vetor caminho minimo*/
     double vetCust[vertMax]; /*vetor com os custos*/
     
     /*é necessario subtrair 1 pois o programa começa por 0 nas matrizes*/             
     /*começo*/ 
     for(i=0; i<vertices; i++){ /*um looping para rodar 'vertice' vezes*/
              if(custos[(origem-1)*vertices+i]!=-1){ // se o valor da origem -1, vezes o valor do vertice mais i, então://
                                                    vetAnt[i] = origem-1; /*anterior é igual a origem*/
                                                    vetCust[i] = custos[(origem-1)*vertices+i];/*adiciona os valores de custo ao vetor*/
                                                    }else{ 
                                                          vetAnt[i] = -1; // o vetor antecessor recebe -1
                                                          vetCust[i] = HUGE_VAL;
                                                          }
                                                          camMin[i] = 0; // o caminho minimo recebe 0//
              }
     camMin[origem-1] = 1; // o caminho minimo (origem -1) recebe 1//
     vetCust[origem-1] = 0; // o custo (origem -1) recebe 0//
     
     int a; // variavel 
     double minimo; // variavel
     
     /*principal*/
     do{
        /*encontra o vertice que entra em a*/
        minimo = HUGE_VAL;
        for(i=0; i<vertices ;i++){ // inicia um loop
             if(!camMin[i]){ // se não for o caminho minimo na posição i //
                    if(vetCust[i] >= 0 && vetCust[i] < minimo){ // se não for o caminho minimo na posição i //
                          minimo = vetCust[i];	/* minimo recebe o custo na posição i */
                              a = i; /* variavel 'a' recebe i */
                    }
                    if(minimo!= HUGE_VAL && a != destino-1){ /* se o minimo for diferente do HUGE_VAL e 'a' for diferente do destino -1, então: */
                           camMin[a]=1; /* o caminho minimo em 'a' recebe 1 */
                               for(i=0; i<vertices;i++){ /* segundo loop */
                                     if(!camMin[i]){ /* caso diferente do caminho na posição i */
                                            if(custos[a*vertices+i] != -1 && vetCust[a] + custos[a*vertices+i] < vetCust[i]){
                                                     vetCust[i]= vetCust[a]+custos[a*vertices+i];
                                                           vetAnt[i]=a;
                                            }
                                     }
                               }
                   }
              }
        }
     }while(a!=destino-1 && minimo!=HUGE_VAL);  /* fazer todo os paços a partir do 'do'  enquanto 'a' for diferente do destino -1, e o minimo for diferente de HUGE_VAL */
     
     
     /*----------------*/
     if(minimo==HUGE_VAL){ /* Se o minimo for igual o HUGE_VAL: */
              printf("\nParece que não existe caminho entre os vertices %d e %d !\n",origem,destino); /* mostra a mensagem na tela, mostrando o valor de origem e destino */
     }else{
           printf("\nO caminho de custo minimo entre os vertices %d e %d  e (na ordem reversa):\n",origem,destino); /* mostra a mensagem na tela, passando a origem e o destino */
           i=destino; /* 'i' recebe destino */
           printf("%d", i); // mostra 'i'
           i = vetAnt[i-1]; // 'i' recebe antecessor na posição 'i' -1
           while(i!=-1){ /* enquanto 'i' for diferente de -1: */
                        printf("< %d", i+1); // mostra 'i'+1
                        i=vetAnt[i]; // 'i' recebe antecessor na posição 'i'
                        }
           printf("\nO custo desse caminho e: %d\n", (int) vetCust[destino-1]); /* mostra a mensagem, passando o valor inteiro do custo (destino-1) */
           }
}

main(int argc, char **argv) { // função main

char lixo[50];   /* variáveis auxiliares */
int custo, opcao,           /* variáveis auxiliares */
    vertices=0,        /* número de vértices do grafo */
    origem,            /* vértice origem */
    destino,           /* vértice destino */
    *custos=NULL;      /* matriz de incidência */
    
    int i=0;
    char c;
    char enter;
    FILE *f = fopen("matriz.txt", "r");
    
    while(1){
    fscanf(f, "%c", &c);
    if(feof(f)) break;
    i++;
    fscanf(f, "%c", &enter);
    }
    printf("Num de caracteres: %d\n", i);

do {

  /* Menu principal */

  printf("==========Bem Vindo!==========\n");
  printf("Escolha sua opcao:\n");
  printf("==========================================\n");
  printf("|1 - Adicionar um Grafo                  |\n");
  printf("|2 - Procura Os Menores Caminhos no Grafo|\n");
  printf("|3 - Sair do programa                    |\n");
  printf("==========================================\n");
  printf("Opcao: ");
  scanf("%i",&opcao); /* recebe o valor da opção */

  /*opcao 1 -------- digitar novo grafo */

  if (opcao==1) { /* se a opção for igual a 1 */
    do { // faz...
      printf("\nDigite o numero de vertices (entre 2 e %d): ",vertMax); /* mostra a mensagem, passando o valor do vertice maximo */
      scanf("%d",&vertices); /* recebe o valor da quantidade de vertices */
    } while (vertices<2 || vertices>vertMax); /* ... enquanto vertices for menor que 2, ou vertices for maior que o valor de vertices maxima */

    if (!custos) /* caso diferente de custos: */
      free(custos); /* libera a memoria reservada para custos */
    custos=(int *) malloc(sizeof(int)*vertices*vertices); /* custos reserva uma parte da memoria com uma matriz de vertices por vertices */
    for (i=0;i<=vertices*vertices;i++) /* loop */
    custos[i]=-1; /* custos na posição 'i' recebe -1 */
    printf("Digite as arestas\n");
    do { //faz...

      do { // faz...
        printf("Digite a origem da aresta (entre 1 e %d ou 0 para sair): ",vertices); /* mostra a mensagem, passando as vertices */
        scanf("%d",&origem); // recebe origem
      } while (origem<0 || origem>vertices); /* ... enquanto origem menor que 0 ou origem maior que vertices */

      if (origem) { // caso origem:

        do { // faz...
          printf("Digite o destino da aresta (entre 1 e %d, menos %d): ",vertices,origem); /* mostra a mensagem, passando vertices e origem */
          scanf("%d",&destino); // recebe destino
        } while (destino<1 || destino>vertices || destino==origem); /* ... enquanto destino menor que 1, ou destino maior que vertices. ou destino igual origem */

        do { // faz...
          printf("Digite o custo (positivo) da aresta do vertice %d para o vertice %d: ",origem,destino); /* mostra a mensagem, passando a origem e destino */
          scanf("%d",&custo); // recebe custo
	} while (custo<0); /* ... enquanto custo menor que 0 */
      custos[(origem-1)*vertices+destino-1]=custo; /* custos em ((origem -1) vezes vertices + destino-1) recebe custo */
      }

    } while (origem); /* ...enquanto origem */
    gets(lixo);
  }

  /*opcao 2 -------- achar caminho mínimo entre 2 vértices */

  if (opcao==2 && vertices>0) { /* caso opção for igual a 2 e vertices maior que 0 */
    printf("\nDigite os vertices origem e destino do caminho\n");
    do { // faz...
      printf("Vertice origem (entre 1 e %d): ",vertices); /* mostra a mensagem, passando vertices */
      scanf("%d",&origem); // recebe origem
    } while (origem<1 || origem>vertices); /* ...enquanto origem menor que 1 ou origem maior que vertices */
  
    do { // faz...
      printf("Vertice destino (entre 1 e %d, menos %d): ",vertices,origem); /* mostra a mensagem, passando vertices e origem */
      scanf("%d",&destino); // recebe destino
    } while (destino<1 || destino>vertices || destino==origem); /* ...enquanto destino menor que 1, ou destino maior que vertices ou destino igual origem */

    
    algDijkstra(destino,origem,custos,vertices); // chama a função do algoritmo 
    gets(lixo);
  }

} while (opcao!=3); /* ...enquanto opção diferente de 3 */

}

