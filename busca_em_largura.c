#include <stdio.h>

//defines
#define tam 5
#define estado_max 100
#define estado_min 1
#define ESQ (-2)
#define DIR (+5)
//var globais
int dados = 0;
int estouro = 0;
int sem_solucao = 0;
int hist[101], count = 0; 

int eh_primo(int numero){
    int primos[25] = {
    2, 3, 5, 7, 11,
    13, 17, 19, 23, 29,
    31, 37, 41, 43, 47,
    53, 59, 61, 67, 71, 73,
    79, 83, 89, 97
    };
    for (int i=0; i<25; i++){
        if(primos[i] == numero){
            return 1; // primo�
        }
    }
    return 0; // n o primo� �
}
//verifica os dados
int verifica(int no){
    if(no > estado_max || no < estado_min){
        dados = 1;
        printf("no nao pode ser adicionado %d pois <1 ou >100\n", no);
        return 1;
    } 
    return 0;
}
//adiciona ao vetor hist 
void historico(int no){
        hist[count] = no;
        count++;
        
}
//verifica se o no ja foi visitado
int ja_visitado(int no){
    for(int i = 0; i< count; i++){
        if (hist[i] == no){
            return 1;
        }
    }
    return 0;
}
//main
int main(){
    //variaveis
    int estado_inicial, i;
    int vet[tam] ;
    int esq, dir;
    // inicializando vetor 
    for (i = 0; i<tam; i++){
        vet [i] = -1;
    }
    // definir estado inicial
    do{//nao deixa inserir fora do intervalo 
        printf("defina um numero de 1 a 100: ");
        scanf("%d", &estado_inicial);
    }while(estado_inicial < estado_min || estado_inicial > estado_max);
    
    vet[0] = estado_inicial;
    // verifica se condiz c/ objetivo
        while(eh_primo(vet[0]) == 0){
            // verificar se a fila est vazia --> encerra (break)�
            if (vet[0] == -1){
                printf("\nfila vazia, solucao nao encontrada...\n");
                sem_solucao = 1;
                break;
            }
            // produzir nos filhos
            esq = vet[0] + ESQ;
            dir = vet[0] + DIR;
            // verificar se algum filho gerado esta abaixo de 1 ou acima de 100, e nao adicionar
            if (verifica(esq) == 0){
                if (ja_visitado(esq)){
                    printf("%d ja foi visitado... proximo!\n", esq);
                } else {
                    for (i = 0; i<tam; i++){
                        if (vet[i] == esq){
                            printf("%d ja esta na fila... proximo!\n", esq);
                            break;
                        }
                        else if (vet[i] == -1){
                            vet[i] = esq;
                            break;
                        }
                    }
                    if (i >= tam){
                        estouro = 1;
                        printf("... %d nao coube na fila\n", esq);
                    }
                }
            }
                
            
            if (verifica(dir) == 0){
                if (ja_visitado(dir)){
                    printf("%d ja foi visitado... proximo!\n", dir);
                } else {
                    for (i = 0; i<tam; i++){
                        if (vet[i] == dir){
                            printf("%d ja esta na fila... proximo!\n", dir);
                            break;
                        }
                        else if (vet[i] == -1){
                            vet[i] = dir;
                            break;
                        }
                    }
                    if (i >= tam){
                        estouro = 1;
                        printf("... %d nao coube na fila\n", dir);
                    }
                }
            }
           historico(vet[0]);
            // remover o n visitado da fila + gerenciar a fila�
            for (i = 0 ; i<tam-1; i++){
                vet[i] = vet[i+1];
                
                }
            vet[tam-1] = -1;

            printf("[");

            for (i = 0; i < tam; i++) {
                    printf("%d", vet[i]);

                    if (i < tam-1) {
                        printf("|");
                    }   
            }

            printf("]\n");


        }

        // se sim, acabou
        if (dados == 1 ){
            printf("flag: erro na transic de dados...\n");
        } if (estouro == 1){
            printf("flag: erro de esgotamento de memoria...\n");
        } 
        if (sem_solucao == 0){
            printf("\nsolucao encontrada: %d\n", vet[0]);
        }
        
        for(int i=0; i<tam; i++){
            printf("vet[%d] = %d\n", i+1,vet[i]);
        }
        
}
