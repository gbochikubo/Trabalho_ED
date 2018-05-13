#include "Corpos_Celestes.hpp"
#include <iostream>
#include <cstring>
using namespace std;

CorposCelestes :: CorposCelestes(unsigned int id, const char nome[50]){
	this->_id = id;
	strcpy(_nome,nome);

}

void CorposCelestes :: insereTipo(const char tipo[50]){
	strcpy(_tipo,tipo);
	
}

void CorposCelestes :: insereDistancia( double distancia){
	this->_distancia = distancia;
}

void CorposCelestes :: insereLocalizacao(const char localizacao[20]){
	strcpy(_localizacao,localizacao);
}

void CorposCelestes :: insereDescricao (const char descricao[200]){
	strcpy(_descricao,descricao);
}

void CorposCelestes :: imprime (){
	cout << _id << endl << _nome << endl << _tipo << endl;
	cout << _distancia << endl << _localizacao << endl <<_descricao << endl;
}

