#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

void ConverteDecimal(int numero,int* binario, int& tam){
    
    int n = numero;
    int i = 3;
    while(n!=0 ){
        binario[i] = n%2;
        n = n/2;
        i--;
    }
    int cont = 0;
    while((binario[0] == 0) and (cont < 3)){
        for(int i = 0; i < tam-1; i++){
            binario[i] = binario[i+1];
        }
        tam--;
        cont++;
    }
}


int ConverteBinario(int *binario, int tam){
    int cont = tam-1;
    int i = 0;
    int decimal = 0;
    while(i < tam ){
        if(binario[i] == 1){
            decimal = decimal + pow(2,cont);
        }
        cont--;
        i++;
    }
    return decimal;
}
    





int main (){
    int tam = 4;
    int* binary = new int[tam];
    
    ConverteDecimal(10,binary,tam);
    cout << ConverteBinario(binary,tam);
    
    delete binary;
    
    return 0;
}
