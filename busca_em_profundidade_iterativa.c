#include<stdio.h>

//defines 
#define tam 5
#define estado_max 100
#define estado_min 1
#define ESQ (-2)
#define DIR (+5)
// variaveis globais
int caminho[tam]; //caminho da raiz ate o atual 
int prof_final = -1; //em qual camada de profundidade a solucao foi achada
int dados = 0; // em caso de dados <1 ou >100
int estouro = 0; // em caso de estouro de memoria
int limite = 1;
int cortou = 0;
// funcao verifica primo 
int eh_primo(int x){
    int primos[25] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 
        41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    for(int i = 0; i<25; i++){
        if( x == primos[i]){
            return 1;
        }
    }
    return 0;
}
// funcao verifica o caminho visidado para adicionar um novo numero 
int caminhovisitado(int estado, int profundidade){
    for (int i = 0; i<profundidade; i++){
        if(caminho[i] == estado){
            return 1; //ja esta no caminho nao adicionar 
        }
    }
    return 0; //ainda nao esta no caminho adicionar 
}
//funcao imprime o caminho percorrido ate o objetivo 
void imprimecaminho(int profundidade){
    printf("[");
    for (int i = 0; i <= profundidade; i ++){
        printf("%d", caminho[i]);
        if(i<profundidade){
            printf(" -> ");
        }
    }
    printf("]");
}


/*algoritimo da busca recursiva (no final chama ela mesma assim, entrando em loop), 
retorna o estado do primo ou -1 se falhou em alguma coisa ao longo do processo do algoritimo.*/
int buscaprofundidade(int estado, int profundidade){
    int resultado, filhos[2];
    // verificando se da pra inserir algo sem estourar a memoria 
    if (profundidade >= tam){
        estouro = 1;
        printf("\nnao foi possivel adicionar %d ao programa devido ao estouro da memoria (profundidade = %d , tam = %d)", estado, profundidade, tam);
        return -1;
    }
    //adiciona ao caminho profundidade x o estado y
    caminho[profundidade] = estado;

    printf("\nprofundidade: %d, visitando: %d, caminho: ", profundidade, estado);
    imprimecaminho(profundidade);
    printf("\n");

    // testando para ver se o objetivo foi alcançado
    if (eh_primo(estado)){
        prof_final = profundidade;
        return estado;
    }

    //se o limite da profundidade (limite) for atingido entao volta e expande o antecessor 
    if(profundidade >= limite){
        cortou = 1;
        printf("limite de profundidade (%d) atingido tentando expandir (%d), voltando ao no antecessor..." ,limite, estado);
        return -1;
    }    

    //gerando filhos do no expandido 
    filhos[0] = estado + ESQ;
    filhos[1] =  estado + DIR;

    // validacao dos dados para que dir ou esq <1 ou >100, nao podera acontecer
    for (int i = 0; i < 2; i++){

        if(filhos[i] > estado_max || filhos[i] < estado_min){
            dados = 1; 
            printf("erro! transicao de dados invalida: %d -> %d (fora de %d-%d) descartando \n", estado, filhos[i], estado_min, estado_max);
            continue;
        } 
        // verifica se o no filho a ser adicionado eh repetido, caso seja repetido nao adiciona
        if (caminhovisitado(filhos[i], profundidade+1)){
            printf("%d ja esta no caminho, descartando...\n", filhos[i]);
            continue;
        }
        resultado = buscaprofundidade(filhos[i], profundidade+1);
        if (resultado != -1){
            return resultado; // solucao encontrada!
        }    

    }
    return -1; //nenhum filho levou a solucao
}
int main(){
    int estado_ini, resultado = -1;
    //insercao de dados para expansao 
    printf("Insira um numero em um intervalo de %d-%d: ", estado_min, estado_max);
    scanf("%d", &estado_ini);

    if (estado_ini < estado_min || estado_ini > estado_max){
        printf("estado inicial fora do intervalo valido!");
        return 1;
    }
    
    //resultado = buscaprofundidade(estado_ini, 0);

    do {
        cortou = 0;                                    // <-- linha nova
        printf("\n=== rodada com limite %d ===", limite);
        resultado = buscaprofundidade(estado_ini, 0);
        printf("\n");
        limite ++;
    } while(resultado == -1 && estouro == 0 && cortou == 1);
        
    if (resultado != -1){
        printf("solucao encontrada na profundidade %d, resultado = %d\n", prof_final, resultado);
        printf("caminho final: \n");
        imprimecaminho(prof_final);
        printf("\n");
    } else {
        printf("solucao nao encontrada...\n");
    }

    if (dados){
        printf("Aviso: a busca tentou gerar nos fora do intervalo %d-%d.\n", estado_min, estado_max);
    }
    if (estouro){
                printf("Aviso: houve estouro de memoria. \n");
    }
    return 0;
}