
#include <Wire.h>
#include "Breeze.h"


void setup() {
  Serial.begin(57600);
  Wire.begin();         //Inicia a Interface I2C 
  Breeze.reset();      //RESETA VOLUME E BANDAS PARA ZERO
  //delay(250);
 
Breeze.equalize(1,7);  
Breeze.equalize(2,7);

Breeze.equalize(5,7);
Breeze.equalize(6,7);

Breeze.equalize(9,7);
Breeze.equalize(10,7);

}


void loop() {
 //Breeze.equalize(2,7);
   delay(1000);
//for (int i = 1 ; i <= 4; i++) Breeze.equalize (i, 7);   //TODOS OS CANAIS NO NÌVEL +7 (MÁXIMO)
  delay(25000);
}
