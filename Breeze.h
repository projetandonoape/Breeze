/*

Breeze.h

Autor: Eng. Christian Caldas
Projetando no Apê

*/

#ifndef Breeze_h
#define Breeze_h

#include "Arduino.h"

class Breeze {

public:
	Breeze ();												//função construtor não utilizada
	void equalize  (uint8_t banda, int8_t nivel_banda) ;	//função para atuar nos níveis das bandas
	void reset ();											//função zerar todas as bandas e volume
	void volume (int8_t nivel_vol);							//função de atuar apenas no volume
    void TDA7317 (uint8_t endereco, uint8_t comando);		//função avançada para enviar bytes ao CircuitoIntegrado
};

extern Breeze Breeze;							

#endif
