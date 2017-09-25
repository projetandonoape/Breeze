/*

Breeze.cpp

Autor: Eng. Christian Caldas
Projetado no Apê
Observação: os números foram tradatos como binários para a observação da posição do bit

----------------------------------------------------------------------------------
     FREQ(Hz)	      CANAL 	        CI 	     POSIÇÃO 		BITS
----------------------------------------------------------------------------------
	32		1		2		5		B100
	64		2		1		5		B100
   	125		3		2		2		B001
	250		4		1		2		B001
	500		5		2		3		B010
	1K 		6		1		3		B010
	2K		7		2		4		B011
	4K		8		1		4		B011
	8K		9		2		1		B000
	16K		10		1		1		B000

*/

#include "Wire.h"						//chama a biblioteca de comunicação I2C 
#include "Breeze.h"						

Breeze::Breeze() 						//a função 'Construtor de Objeto' não é utilizada pelo Breeze
{
}

void Breeze::equalize (int canal, int nivel) {			//função de equalização. recebe o n° e nível do canal a ser ajustado

	byte parte_A = B0000000;				//1°byte: ENDEREÇO (preenche máscara de bits com zeros)
	byte parte_B = B10000000;				//2°byte: VOLUME (nesta função não altera o volume)
	int parte_C = B00000000;				//3°byte: CANAL + NÍVEL (preenche máscara bits com zeros)
	int posicao[11] = {0, 					//a posição dos canais é dada pelo fabricante do TDA7317 para manter a distorção harmônica (THD) baixa
		B11000000, B11000000, 				/*BANDAS 1 e 2: ENDEREÇO n°B100 corresponde ao CANAL n°5 */
		B10010000, B10010000, 				/*BANDAS 3 e 4: ENDEREÇO n°B001 corresponde ao CANAL n°2 */
		B10100000, B10100000, 				/*BANDAS 5 e 6: ENDEREÇO n°B010 corresponde ao CANAL n°3 */
		B10110000, B10110000,				/*BANDAS 7 e 8: ENDEREÇO n°B011 corresponde ao CANAL n°4 */
		B10000000, B10000000};				/*BANDAS 9 e 10: ENDEREÇO n°B000 corresponde ao CANAL n°1 */
	const byte CI1 = B1000010;				//endereço do CI-1 0x84(hexa)
	const byte CI2 = B1000011;				//endereço do CI-2 0x86(hexa)

	if (canal % 2 == 0) parte_A = CI1; 			//canais pares são tratadas pelo CI-1;
	else parte_A = CI2;					//canais ímpares são tratadas pelo CI-2;

	if (nivel < 0) {					//valor inferior a 0 indica atenuação
		parte_C = parte_C | B10001000;			//concatena parte_C com byte 1 na posição 4 indicando atenuação usando função 'OU' (|)
		nivel = abs(nivel);				//módulo do valor, para não enviar valor negativo
	}

	parte_C = parte_C | posicao [canal] | nivel;		//concatena os dados a serem enviados no byte C com a função 'OU' (|)

	TDA7317 (parte_A, parte_B, parte_C);			//chama a função que envia os bytes

}

void Breeze::reset() {						//função reset

for (byte canal = 1; canal <= 10; canal++) equalize (canal, 0);	//envia nível zero para todos os canais
TDA7317 (B1000010, B00000000, B00000000);			//zera volume do CI-1
TDA7317 (B1000011, B00000000, B00000000);			//zera volume do CI-2
}


void Breeze::volume (int nivel) {				//função volume. recebe o nível do volume

	nivel = abs(nivel);					//módulo do valor, para não enviar valor negativo
	byte parte_A = B1000010;				//para manter qualidade de áudio apenas o CI-1 controla o volume
	int parte_B = B00000000 | nivel;			//2ºbyte: VOLUME (0 OR nivel) 
	byte parte_C = B00000000; 				//3°byte: CANAL + NIVEL (Não altera nível nesta função)
	TDA7317 (parte_A, parte_B, parte_C);			//chama a função que envia os bytes

}


void Breeze::TDA7317 (byte parte_A, byte parte_B, byte parte_C) {//função avançada: envia as 3 partes do byte A, B, C ao Breeze

Wire.beginTransmission(parte_A);				//inicia enviando o endereço do CircuitoIntegrado que irá atuar
Wire.write(parte_B);						//envia nível de volume
Wire.write(parte_C);						//envia canal e nível de atuação
Wire.endTransmission();						//finaliza a transmissão

}
