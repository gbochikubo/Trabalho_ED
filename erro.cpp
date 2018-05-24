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
        void Imprime(const char* ArquivoBloco);
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
void Block::Imprime(const char* ArquivoBloco){
    ifstream leitor(ArquivoBloco, ios::binary);
    leitor.seekg(0,leitor.end);
    int bytes = leitor.tellg();
    leitor.seekg(0,leitor.beg);
    bytes = bytes/sizeof(Block);
    cout << "BYTES " << bytes << endl;
   // int i = 0;

    Block auxImprime;
    for(int j = 0; j < bytes; j++){
        //~ cout << "Bloco" << " " << i << endl;
        leitor.read((char*)(&auxImprime),sizeof(Block));
       cout << " AUX TAM " << auxImprime._tamanho << endl;
        for(int i = 0; i < (auxImprime._tamanho); i++){
            auxImprime._elemento[i]->imprime();
        }
    }
}


//**************************************************************************************************************//
//**************************************************************************************************************//
//**************************************************************************************************************//
//**************************************************************************************************************//

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
        void imprimeNaHash();
    private:
        void Localizando(const char* ArquivoLocalizacao);
        int* mLocalizacao;          //Hash
        char* mArquivoBloco;        //nome do arquivo dos blocos    
        char* mArquivoLocalizacao;  //nome do arquivo hash
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
    leitor.seekg(0,leitor.end);
    int bytes = leitor.tellg();
    leitor.seekg(0,leitor.beg);
    if(leitor){
        for(int i = 0; i < bytes/4; i++){
            leitor.read((char*)(&PosHash),sizeof(int));
            leitor.read((char*)(&PosArq),sizeof(int));
            mLocalizacao[PosHash] = PosArq;
        }
    }
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

Block* TabelaHash::getBlock (int key){
 
    ifstream leitor(mArquivoBloco, ios::binary);
    int ChaveHash = mLocalizacao[key];
    Block Temp;
    Block* Procurado;
    int i = 0;
    while(leitor){
            if(ChaveHash == i){
                leitor.read((char*)(&Procurado),sizeof(CorposCelestes));
            }
            else{
                leitor.read((char*)(&Temp),sizeof(CorposCelestes));
            }
            i++;
        }
        return Procurado;
                
}

void TabelaHash :: imprimeNaHash(){
    Block K;
    K.Imprime(mArquivoBloco);
}
//~ ofstream gravadorMapa (nomeArq , ios::binary | ios::out);
//~ gravador.write (reinterpret_cast<const char*> (hash), sizeof(int));
//~ gravador.write (reinterpret_cast<const char*> (bloco), sizeof(int));

int main(){
    //~ CorposCelestes terra(1,"Earth");
    //~ terra.insereDescricao("Tem agua");
    //~ terra.insereDistancia(0);
    //~ terra.insereLocalizacao("sistema solar");
    //~ terra.insereTipo("planeta");
    
     //~ CorposCelestes marte(2,"Mars");
    //~ marte.insereDescricao("Tem agua nao");
    //~ marte.insereDistancia(200);
    //~ marte.insereLocalizacao("sistema solar");
    //~ marte.insereTipo("planeta");
    
    
    //~ ofstream ArqBloco("Blocos.dat", ios::binary);
    //~ ofstream ArqLocalizacao("Localizacao.dat", ios::binary);
    //~ TabelaHash tabela("ArqBloco", "ArqLocalizacao");
    //~ tabela.Insere(terra);
    //tabela.Insere(marte);
    //~ tabela.imprimeNaHash();
    cout << sizeof(Block) << endl;
    cout << sizeof(CorposCelestes) << endl;
    return 0;
}
