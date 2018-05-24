#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;
int ConverteDecimal(int numero, int& tam){
    
    int n = numero;
    int i = 0;
    int binario=0;
    int b[tam];
    while(n!=0 ){
        b[i] = n%2;
        n = n/2;
        i++;           
    }
    for(int i=0; i < tam; i++){
		if(b[i] == 1){
			binario = binario + pow(10,i);
		}
	}
	return binario;
}


int ConverteBinario(int binario){
    int decimal=0;
    int copia=binario;
    int tam = 0;
    while(copia != 0){
		copia =copia/10;
		tam++;
	}	
    int b[tam];
    int i=0;
    while(binario != 0){
		if(binario%10 == 0){
			b[i] = 0;
		}
		else{
			b[i] = 1;
		}
		binario = binario/10;
		i++;
	}
	for(int i = 0; i < tam; i++){
		if(b[i] == 1){
			decimal = decimal + pow(2,i);
		}
	}
     return decimal;
    
}

int main (){

	int binary = 1011;
	cout << ConverteBinario(binary) << endl;
	
    return 0;
}
