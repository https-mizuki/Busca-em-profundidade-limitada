#include<stdio.h>
#include<stdlib.h>

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

int main(){
    
    return 0;
}