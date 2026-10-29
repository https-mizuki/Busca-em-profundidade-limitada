#include<stdio.h>
#include<stdlib.h>
//defines 
#define tam 5
#define limite 4
//var global 
int caminho[tam];
int prof_final = -1;
int eh_primo(int x){
    primos = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 
        41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97];
    for(int i = 0; i<25; i++){
        if( x == primos[i]){
            return 0;
        }
    }
    return 1;
}

int caminhovisitado(int estado, int profundidade){
    for (int i = 0; i<profundidade; i++){
        if(caminho[i] == estado){
            printf("estado = %d ja esta no caminho = %d", estado, caminho[i]);
            return 1; //ja esta no caminho nao adicionar 
        }
    }
    return 0; //ainda nao esta no caminho adicionar 
}


int main(){
    int vet[tam], nmr;
    printf("insria um numero de 1-100: ");
    scanf("%d", &nmr);

    if (eh_primo(nmr) == 0){
        printf("numero primo encontrado!");
    }

    return 0;
}