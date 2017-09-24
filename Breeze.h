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
	Breeze ();
	void equalize  (int canal, int nivel) ;
	void reset ();
	void volume (int nivel);
    void TDA7317 (byte parte_A, byte parte_B, byte parte_C);

};

extern Breeze Breeze;

#endif
