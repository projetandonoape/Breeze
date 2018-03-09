/*
Breeze.cpp
Autor: Eng. Christian Caldas
Projetado no Apê
---------------------
FREQ(Hz)  BANDA 	 
---------------------
  32	    1
  64	    2
  125	    3
  250       4
  500	    5
  1K 	    6
  2K	    7
  4K	    8
  8K	    9
 16K	   10
  
-------------------------
NÍVEL GANHO/ATENUAÇÃO(dB) 	 
-------------------------
  7         +6,0
  6         +5,2
  5         +4,4
  4         +3,6
  3         +2,8
  2         +1,9
  1	    +1,1
  0	      0
  -1        -1,1
  -2	    -1,9
  -3        -2,8
  -4        -3,6
  -5        -4,4
  -6        -5,2
  -7        -6,0
  
-------------------------
VOLUME  ATENUAÇÃO(dB) 	 
-------------------------
 0              0
-1           -0,375
-2           -0,750 
...             ...
-46         -17,250
-47         -17,625


*/

#include <Wire.h>         //Biblioteca do Arduino para comunicação I2C
#include "Breeze.h"       //Biblioteca para controlar o Breeze


void setup() {
  Wire.begin();           //Inicia a Interface I2C
  Breeze.reset();         //Zera volume e níveis das bandas
}


void loop() {
  Breeze.equalize(1,7);   //Exemplo de reforço da banda 1 (32Hz) para nível 7 [+6dB] 
  Breeze.equalize(6,-7);  //Exemplo de atenuação da banda 6 (1KHz) para nível -7 [-6dB]
  Breeze.volume (-2);     //Exemplo de atenuação do volume para nível -2
}
