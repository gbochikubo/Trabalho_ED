#include <iostream>
#include <cstring>
using namespace std; 


		
class CorposCelestes{
	private:
		unsigned int _id;
		char _nome[50];
		char _tipo[50];
		 double _distancia;
		char _localizacao[20];
		char _descricao[200];
		
	public:
		CorposCelestes();
		CorposCelestes(const CorposCelestes& outro);
		//~CorposCelestes();
		void Id(int id);
		void insereNome(const char nome[50]);
		void insereTipo(const char tipo[50]);
		void insereDistancia( double distancia);
		void insereLocalizacao(const char localizacao[20]);
		void insereDescricao(const char descricao[200]);
		void alteraNome(int id, char nome[50]);
		void alteraDistancia(int id, double distancia);
		void alteraTipo(int id, char tipo[50]);
		void alteraDescricao(int id, char descricao[200]);
		void imprime();
		int EspiaId();
		
};
CorposCelestes :: CorposCelestes(){
	this->_id = 0;
	strcpy(_nome," ");
	strcpy(_tipo," ");
	strcpy(_localizacao," ");
	strcpy(_descricao," ");
	//this->_nome = "";
	//this->_tipo = " ";
	this->_distancia = 0;
	//this->_localizacao = " ";
	//this->_descricao = " ";
	

}

CorposCelestes :: CorposCelestes (const CorposCelestes& outro){
	this->_id = outro._id;
	strcpy(_nome,outro._nome);
	strcpy(_tipo,outro._tipo);
	strcpy(_descricao,outro._descricao);
	strcpy(_localizacao,outro._localizacao);
	this->_distancia = outro._distancia;
}


void CorposCelestes :: insereNome(const char nome[50]){
	strcpy(_nome,nome);
}

void CorposCelestes :: Id(int id){
	this->_id = id;
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
	cout <<  _id<< endl << _nome<< endl;
	cout << _distancia << endl << _localizacao << endl <<_descricao << endl;
}
int CorposCelestes :: EspiaId(){
	return _id;
}

class Block {
	private:
		CorposCelestes** _elemento;
		int _tamanho;
	public:
		Block();
		~Block();
		inline bool vazio();
		void insere(CorposCelestes& elemento);
		void remove(CorposCelestes& elemento);
};

Block :: Block(){
	this->_elemento = new CorposCelestes*[4];
	this->_tamanho = 0;
	for(int i = 0; i < 4; i++){
		this->_elemento[i] = NULL;
	}
}

Block :: ~Block (){
	for(int i = 0; i < 4 ; i++){
		delete _elemento[i];
	}
	delete [] _elemento;
}

inline bool Block :: vazio(){
	return (_tamanho == 0);
}

void Block :: insere (CorposCelestes& elemento){
	//~ cout << "ENTROU" << endl;
	//~ if(_tamanho < 4){
		//~ bool nulo = false;
		//~ int posicao = 0;
		//~ int i = 0;
		//~ do{
			//~ if(_elemento[i] == NULL){
				//~ posicao = i;
				//~ nulo = true;
			//~ }
			//~ i++;
		//~ }while((_elemento[i] != NULL) and (nulo == false));
		//~ if(nulo){
		//~ //	_elemento[posicao] = new CorposCelestes(id, nome);
			//~ CorposCelestes copia(elemento);
			//~ _elemento[posicao] = &copia;
			
			//~ _tamanho++;
		//~ }
	//~ }
	//~ else {
		//~ cout << "ERRO" << endl;
	//~ }
		if(_tamanho < 4){
			cout << "AQUI" << endl;
			CorposCelestes copia(elemento);
			_elemento[_tamanho] = &copia;
			cout << "ADICIONOU" << endl;
			_tamanho++;
		}
	// adicionar tratamento de erro nessa parte
}

void Block :: remove(CorposCelestes& elemento){
	bool existe = false;
	int posicao;
	//char name[50];
	for(int i = 0; i < _tamanho; i++){
		//name = _elemento->EspiaNome();
		if(_elemento[i]->EspiaId() == elemento.EspiaId()){
			existe = true;
			posicao = i;
		}
	}
	if(existe){
		delete _elemento[posicao];
		_tamanho--;
	}
}
		
	
	
	

int main (){
	CorposCelestes terra;
	terra.Id(1);
	terra.insereNome("earth");
	terra.insereDescricao("Tem agua");
	terra.insereDistancia(0);
	terra.insereLocalizacao("sistem solar");
	terra.insereTipo("planeta");
	terra.imprime();
	cout << endl << endl;
	//~ CorposCelestes marte(12,"marte");
	//~ marte.insereDescricao("nao tem agua");
	//~ marte.insereDistancia(20);
	//~ marte.insereLocalizacao("sistema solar");
	//~ marte.insereTipo("outro planeta");
	//~ marte.imprime();
	
	cout << &terra << endl;
	//~ cout << &marte << endl;
	
	Block primeiro;
	primeiro.insere(terra);
	//~ primeiro.insere(marte);
	//primeiro.remove(terra);
	//~ terra.insereDistancia(0);
	//~ terra.insereLocalizacao("sistem solar");
	//~ terra.insereTipo("planeta");
	//~ terra.imprime();
	
	cout << "XX" << endl;
	return 0;
}
