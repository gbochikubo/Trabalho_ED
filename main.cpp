#include "Corpos_Celestes.hpp"
#include <iostream>

using namespace std;

int main () {

	CorposCelestes terra(1,"earth");
	terra.insereDescricao("Tem agua");
	terra.insereDistancia(0);
	terra.insereLocalizacao("sistem solar");
	terra.insereTipo("planeta");
	
	terra.imprime();
	return 0;
}
