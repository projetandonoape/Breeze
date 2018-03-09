
#include <Wire.h>         //Biblioteca do Arduino para comunicação I2C
#include "Breeze.h"       //Biblioteca para controlar o Breeze


void setup() {
  Wire.begin();           //Inicia a Interface I2C
  Breeze.reset();         //Zera volume e níveis das bandas (Breeze não zera bandas e volume quando energizado)
}


void loop() {
  Breeze.equalize(1,7);   //Exemplo de reforço da banda 1 (32Hz) para nível 7 [+6dB] 
  Breeze.equalize(6,-7);  //Exemplo de atenuação da banda 6 (1KHz) para nível -7 [-6dB]
  Breeze.volume (-2);     //Exemplo de atenuação do volume para nível -2 (Breeze permite atenuação de volume 0 a -47)
}
