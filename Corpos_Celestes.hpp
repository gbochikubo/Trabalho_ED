#ifndef CORPOS_CELESTES_H

#define CORPOS_CELESTESS_H

class CorposCelestes{
	private:
		unsigned int _id;
		char _nome[50];
		char _tipo[50];
		 double _distancia;
		char _localizacao[20];
		char _descricao[200];
	public:
		CorposCelestes(unsigned int _id, const char nome[50]);
		//~CorposCelestes();
		void insereTipo( const char tipo[50]);
		void insereDistancia( double distancia);
		void insereLocalizacao(const char localizacao[20]);
		void insereDescricao(const char descricao[200]);
		//~ void alteraNome(int id, char nome[50]);
		//~ void alteraDistancia(int id, double distancia);
		//~ void alteraTipo(int id, char tipo[50]);
		//~ void alteraDescricao(int id, char descricao[200]);
		void imprime();
};

#endif

