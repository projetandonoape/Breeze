/*

Breeze.h

Autor: Eng. Christian Caldas
Projetando no Apê

*/

#ifndef Breeze_h
#define Breeze_h

#include "Arduino.h"

class Breeze
{

public:
	Breeze ();							//função construtor não utilizada
	void equalize  (int banda, int nivel) ;				//função para atuar nos níveis das bandas
	void reset ();							//função zerar todas as bandas e volume
	void volume (int nivel);					//função de atuar apenas no volume
    	void TDA7317 (byte parte_A, byte parte_B, byte parte_C);	//função avançada para enviar bytes ao CircuitoIntegrado

};

extern Breeze Breeze;							

#endif
