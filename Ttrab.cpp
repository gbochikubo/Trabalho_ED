//~ ARQUIVOS BINARIOS
//~ http://dcm.ffclrp.usp.br/~augusto/teaching/ici/Arquivos-Binarios-CPP.pdf


#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>

using namespace std;


class CorposCelestes{
    friend class TabelaHash;
    friend class Block;
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
     
        void imprime();
        int EspiaId();
};


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

int CorposCelestes :: EspiaId(){
    return _id;
}


class Block {
    friend class TabelaHash;
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
        if (_elemento[i] != NULL) {
            delete _elemento[i];
        }
    }
    delete [] _elemento;
}

inline bool Block :: vazio(){
    return (_tamanho == 0);
}

void Block :: insere(CorposCelestes& elemento){
    if(_tamanho < 4){
        CorposCelestes *copia = new CorposCelestes(elemento);
        _elemento[_tamanho] = copia;
        _tamanho++;
    }
}

void Block :: remove(CorposCelestes& elemento){
    bool existe = false;
    int posicao=0;
    for(int i = 0; i < _tamanho; i++){
        if(_elemento[i]->EspiaId() == elemento.EspiaId()){
            existe = true;
            posicao = i;
        }
    }
    if(existe){
        if(_tamanho == 1){
            delete _elemento[posicao];
            _tamanho--;
        }
        else{
            while((posicao < 3) and (_elemento[posicao+1]!= NULL)){
                swap(_elemento[posicao],_elemento[posicao+1]);
                posicao = posicao+1;
            }
         delete _elemento[posicao];
        _tamanho--;
        }
    }
    
    //FAZER TRATAMENTO DE ERRO PARA O CASO DE NÃO EXISTIR
}


//**************************************************************************************************************//
//**************************************************************************************************************//
//**************************************************************************************************************//
//**************************************************************************************************************//

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

const int valor = 104729;
int funcaoHash(string c){
    long h = 0;
    for(unsigned int i=0; i<c.length(); ++i){
        h = (valor*h + c[i]) % 16; 
    }
    return h;
}

class TabelaHash{
    public:
        TabelaHash(const char* ArquivoBloco, const char* ArquivoLocalizacao);
        void Insere(CorposCelestes& CorpoC);
    private:
        void Localizando(const char* ArquivoLocalizacao);
        int* mLocalizacao;
        char* mArquivoBloco;
        char* mArquivoLocalizacao;
        int mCapacidade;
        Block* getBlock(int key);
        void registerBlock(Block* boroco, int key);
};
TabelaHash::TabelaHash(const char* ArquivoBloco, const char* ArquivoLocalizacao){
    mArquivoBloco = new char[strlen(ArquivoBloco)];
    strcpy(mArquivoBloco, ArquivoBloco);
    mArquivoLocalizacao = new char[strlen(ArquivoLocalizacao)];
    mCapacidade = 16;
    mLocalizacao = new int[mCapacidade];
    for(int i=0; i<16; ++i){
        mLocalizacao[i] = -1;
    }
}
void TabelaHash::Localizando(const char* ArquivoLocalizacao){
    
    ifstream leitor(mArquivoLocalizacao, ios::binary);
    int PosHash, PosArq;
    
    if(leitor){
        
    
    
    
    
    
    
    
    
    }
void TabelaHash::registerBlock(Block* boroco, int key){
    int posicao = mLocalizacao[key];
    if(posicao == -1){
        ifstream leitor(mArquivoBloco, ios::binary);
        leitor.seekg(0, leitor.end);
        int tamanho = leitor.tellg();
        leitor.seekg(0, leitor.beg);
        posicao = tamanho/sizeof(Block);
        leitor.close();
    }
    ofstream gravador(mArquivoBloco, ios::binary);
    gravador.seekp(posicao*sizeof(Block));
    gravador.write(reinterpret_cast<const char*> (boroco), sizeof(Block));
}
void TabelaHash::Insere(CorposCelestes& CorpoC){
    int key = funcaoHash(CorpoC._nome);
    Block* boroco;
    if(mLocalizacao[key] == -1)
        boroco = new Block();
    else{
        boroco = getBlock(key);
    }
    boroco->insere(CorpoC);
    registerBlock(boroco, key);
}   

ofstream gravadorMapa (nomeArq , ios::binary | ios::out);
gravador.write (reinterpret_cast<const char*> (hash), sizeof(int));
gravador.write (reinterpret_cast<const char*> (bloco), sizeof(int));

int main(){
    return 0;
}
