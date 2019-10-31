/*

Breeze.cpp

Autor: Eng. Christian Caldas
Projetado no Apê
Observação: no código os números foram tradatos como binários para 
facilitar a observação da posição do bit

----------------------------------------------------------------------------------
  FREQ(Hz)	 BANDA 	   CI 	  POSIÇÃO 	BITS
----------------------------------------------------------------------------------
	32			1		2		5		B100
	64			2		1		5		B100
   	125			3		2		2		B001
	250			4		1		2		B001
	500			5		2		3		B010
	1K 			6		1		3		B010
	2K			7		2		4		B011
	4K			8		1		4		B011
	8K			9		2		1		B000
	16K			10		1		1		B000

*/

#include "Wire.h"						//chama a biblioteca de comunicação I2C 
#include "Breeze.h"						

Breeze::Breeze() { }						//a função 'Construtor de Objeto' não é utilizada pelo Breeze

void Breeze::equalize (uint8_t banda, int8_t nivel_banda) {	//função de equalização. recebe o n° e nível do banda a ser ajustado
	uint8_t endereco = B0000000;				//1°byte: ENDEREÇO (preenche máscara de bits com zeros)
	uint8_t comando  = B00000000;				//3°byte: BANDA + NÍVEL (preenche máscara bits com zeros)
	uint8_t posicao[11] = {0, 				//a posição das bandas é dada pelo fabricante do TDA7317 para manter a distorção harmônica (THD) baixa
		B11000000, B11000000, 				/*BANDAS 1 e 2: ENDEREÇO n°B100 corresponde ao BANDA n°5 */
		B10010000, B10010000, 				/*BANDAS 3 e 4: ENDEREÇO n°B001 corresponde ao BANDA n°2 */
		B10100000, B10100000, 				/*BANDAS 5 e 6: ENDEREÇO n°B010 corresponde ao BANDA n°3 */
		B10110000, B10110000,				/*BANDAS 7 e 8: ENDEREÇO n°B011 corresponde ao BANDA n°4 */
		B10000000, B10000000};				/*BANDAS 9 e 10: ENDEREÇO n°B000 corresponde ao BANDA n°1 */
	const uint8_t CI1 = B1000010;				//endereço do CI-1 0x84(hexa)
	const uint8_t CI2 = B1000011;				//endereço do CI-2 0x86(hexa)

	if (banda % 2 == 0) endereco = CI1; 			//bandas pares são tratadas pelo CI-1;
	else endereco = CI2;					//bandas ímpares são tratadas pelo CI-2;

	if (nivel_banda < 0) {					//valor inferior a 0 indica atenuação
		comando = comando | B10001000;			//concatena parte_C com byte 1 na posição 4 indicando atenuação usando função 'OU' (|)
		nivel_banda = abs(nivel_banda);			//módulo do valor, para não enviar valor negativo
	}

	comando = comando | posicao [banda] | nivel_banda;	//concatena bits a serem enviados no byte C com a função 'OU' (|)
	TDA7317 (endereco, comando);				//chama a função que envia os bytes
}

void Breeze::reset() {
	for (uint8_t banda = 1; banda <= 10; banda++) equalize (banda, 0);	//ajusta nível zero para todas as bandas e volume na metade
	TDA7317 (B1000010, B00011100);		//seta volume di CI-1 no valor médio = 24;
	TDA7317 (B1000011, B00000000);		//zera volume do CI-2
}


void Breeze::volume (int8_t nivel_vol) {			//função volume. recebe o nível do volume
	nivel_vol = abs(nivel_vol);				//módulo do valor, para não enviar valor negativo
	uint8_t endereco = B1000010;				//para manter qualidade de áudio apenas o CI-1 controla o volume
	uint8_t comando = nivel_vol;
	TDA7317 (B1000010, comando);
}


void Breeze::TDA7317 (uint8_t endereco, uint8_t comando) {	//função avançada: envia as 3 partes do byte A, B, C ao Breeze
	Wire.beginTransmission(endereco);			//inicia enviando o endereço do CircuitoIntegrado que irá atuar
	Wire.write(comando);					//envia nível de volume
	Wire.endTransmission();					//finaliza a transmissão
}
