#include <iostream>
#include <cstring>
using namespace std; 

class CorposCelestes{
    private:
        unsigned int _id;
        //tamanho 50
        char* _nome;
        //tamanho 50
        char* _tipo;
        double _distancia;
        //tamanho 20
        char* _localizacao;
        //tamanho 200
        char* _descricao;
        
    public:
        CorposCelestes();
        CorposCelestes(const CorposCelestes& outro);
        ~CorposCelestes();
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
    this->_distancia = 0;
    
    // inicializa as strings
    this->_nome = new char[50];
    this->_tipo = new char[50];
    this->_localizacao = new char[20];
    this->_descricao = new char[200];
    
    // define o valor vazio '\0' para as strings
    strcpy(this->_nome, "\0");
    strcpy(this->_tipo, "\0");
    strcpy(this->_localizacao, "\0");
    strcpy(this->_descricao, "\0");
    
}

CorposCelestes :: CorposCelestes (const CorposCelestes& outro){
    this->_id = outro._id;
    cout << "Construtor de copia do CorpoCeleste" << endl;
    this->_nome = new char[50];
    this->_tipo = new char[50];
    this->_localizacao = new char[20];
    this->_descricao = new char[200];
    
    cout << "Inicializou os ponteiros" << endl;
    
    cout << "Vai definir vazio com os ponteiros" << endl;
    strcpy(_nome,outro._nome);
    strcpy(_tipo,outro._tipo);
    strcpy(_descricao,outro._descricao);
    strcpy(_localizacao,outro._localizacao);
    this->_distancia = outro._distancia;
    
    cout << "Fim do construtor de Copia" << endl;
}

CorposCelestes::~CorposCelestes() {
    cout << "Endereco de quem vai apagar: " << this << endl;
    
    cout << "Destrutor do Corpo Celeste" << endl;
    if (this->_nome != NULL) {
        cout << "Apagando o nome" << endl;
        delete [] this->_nome;
    }
    if (this->_tipo != NULL) {
        cout << "Apagando o tipo" << endl;
        delete [] this->_tipo;
    }
    if (this->_localizacao != NULL) {
        cout << "Apagando a localizacao" << endl;
        delete [] this->_localizacao;
    }
    if (this->_descricao != NULL) {
        cout << "Apagando a descricao" << endl;
        delete [] this->_descricao;
    }
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
    cout << "inicio: CorposCelestes::imprime()" << endl;
    cout <<  _id << endl << _nome<< endl;
    cout << _distancia << endl << _localizacao << endl <<_descricao << endl;
    cout << "fim   : CorposCelestes::imprime()" << endl << endl;
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
    cout << "Destrutor do bloco" << endl;
    for(int i = 0; i < 4 ; i++){
        if (_elemento[i] != NULL) {
            cout << "Destruindo a posicao " << i << " com endereco " << _elemento[i] << endl;
            delete _elemento[i];
        }
    }
    delete [] _elemento;
}

inline bool Block :: vazio(){
    return (_tamanho == 0);
}

void Block :: insere(CorposCelestes& elemento){
    cout << "inicio: CorposCelestes::insere()" << endl;

    if(_tamanho < 4){
        CorposCelestes *copia = new CorposCelestes(elemento);
        cout << "Elemento será inserido: vai criar uma copia" << endl;
        _elemento[_tamanho] = copia;
        cout << &copia << endl;
        _tamanho++;
        cout << "Elemento foi inserido e vai voltar para o main" << endl;
    }
    cout << "fimanl" << endl;
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
    cout << "*****************************" << endl;
    terra.imprime();
    cout << "*****************************" << endl;
    
    cout << "Endereço do objeto criado no main: " << &terra << endl;
    
    Block primeiro;
    cout << "*****************************" << endl;
    primeiro.insere(terra);
    cout << "*****************************" << endl;
    cout << "Fim da execução do main" << endl;
    return 0;
}
