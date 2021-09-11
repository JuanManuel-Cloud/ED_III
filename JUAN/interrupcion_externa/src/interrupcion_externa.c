/*
===============================================================================
 Name        : interrupcion_externa.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : Configurar la interrupción externa EINT1 para que interrumpa por
 flanco de bajada y EINT2 por flanco de subida. En la interrupción por flanco de bajada
 configurar el systick para desbordar cada 25 mseg, mientras que en la interrupcion
 por flanco de subida configurarlo para que desborde cada 60 mseg.
 Las EINT1 debe tener una prioridad mayor a la EINT2
===============================================================================
*/

#include "LPC17xx.h"

void confPin();
void confIntExt();

int main(void) {
	confPin();
	confIntExt();
    while(1) { }
    return 0;
}

void confPin() {
	//tengo que poner 1 en el bit 22 y en el 24 y 0 en el bit 23 y 25, para config
	//como eint
	LPC_PINCON -> PINSEL4 |= (0b101 << 22); //estoy poniendo los 1
	LPC_PINCON -> PINSEL4 &= ~(0b101 << 23); //estoy poniendo los 0
}

void confIntExt() {
	//SC = System Control
	LPC_SC -> EXTMODE |= 0x6; //seteo el bit 1 y 2 como flanco
	LPC_SC -> EXTPOLAR &= ~0x2; //seteo como flanco de bajada el bit 1
	LPC_SC -> EXTPOLAR |= 0x4; //seteo como flanco de subida el bit 2
	LPC_SC -> EXTINT |= 0x6; //limpios las flags, en flanco se limpian poniendo 1
	NVIC_EnableIRQ(EINT1_IRQn); //habilito las interrupciones externas 1
	NVIC_EnableIRQ(EINT2_IRQn); //habilito las interurpciones externas 2
	NVIC_SetPriority(EINT1_IRQn, 3); //le doy una prioridad 3 a eint1, por lo que va a ser mayor que la de eint2
	NVIC_SetPriority(EINT2_IRQn, 5); //le doy una prioridad 5 a eint2
	return;
}

void EINT1_IRQHandler() {
	SysTick -> LOAD = SystemCoreClock * 0.025;
	LPC_SC -> EXTINT |= 0x2; //limpio la flag de interrupción del eint1
	return;
}

void EINT2_IRQHandler() {
	SysTick -> LOAD = SystemCoreClock * 0.06;
	LPC_SC -> EXTINT |= 0x4; //limpio la flag de interrupción del eint2
	return;
}
