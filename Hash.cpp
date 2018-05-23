#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
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
        int** mLocalizacao;
        char* mArquivoBloco;
        char* mArquivoLocalizacao;
        int mCapacidade = 16;
        int mBlocosRegistrados;
        void registerBlock(Block* boroco, int key);
};
TabelaHash::TabelaHash(const char* ArquivoBloco, const char* ArquivoLocalizacao){
    mArquivoBloco = new char[strlen(ArquivoBloco)];
    strcpy(mArquivoBloco, ArquivoBloco);
    mArquivoLocalizacao = new char[strlen(ArquivoLocalizacao)];
    mLocalizacao = new int*[mCapacidade];
    for(int i=0; i<16; ++i){
        mLocalizacao[i] = NULL;
    }
}
void registerBlock(Block* boroco, int key){
    int posicao = mLocalizacao[key];
    if(posicao == -1){
        ifstream arquivo(mArquivoBloco, ios::binary);
        int tamanho = arquivo.tellg();
        arquivo,seekg(0, arquivo.beg);
        posicao = tamanho/sizeof(Block);
        arquivo.close();
        ofstream arquivo(mArquivoBloco, ios::binary);
    }
    else{
        ofstream arquivo(mArquivoBloco, ios::binary);
        arquivo.seekp(mLocalizacao[key]*sizeof(Block));
    }
    arquivo.write(reinterpret_cast<const char*> Block, sizeof(Block));
}
void TabelaHash::Insere(CorposCelestes& CorpoC){
    int key = funcaoHash();
    Block boroco;
    if(mMapeamento[key] == NULL)
        boroco = new Block();
    else{
        boroco = getBlock(key);
    }
    boroco->Insere(CorpoC);
    registerBlock(boroco);
}
int main(){
    return 0;
}
