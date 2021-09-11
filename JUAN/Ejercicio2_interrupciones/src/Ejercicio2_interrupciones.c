/*
===============================================================================
 Name        : Ejercicio2_interrupciones.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : Realizar un programa que configure el puerto P0.0 y P2.0
 para que provoquen una interrupción por flanco de subida.
 Si la interrupción es por P0.0 guardar el valor binario 100111 en la
 variable "auxiliar", si es por P2.0 guardar el
 valor binario 111001011010110.
===============================================================================
*/

#include "LPC17xx.h"

void confGPIO();
void confIntGPIO();

uint16_t auxiliar = 0;

int main(void) {
	confGPIO();
	confGPIO();
    while(1) {
    }
    return 0 ;
}

void confGPIO() {
	//Por defecto los puertos están en gpio.
	LPC_GPIO0 -> FIODIR0 &= ~0x1;
	LPC_GPIO0 -> FIOMASK0 |= 0xFE;
	LPC_GPIO2 -> FIODIR2 &= ~0x1;
	LPC_GPIO0 -> FIOMASK2 |= 0xFE;
	//por defecto están en pullups
	return;
}

void confIntGPIO() {
	LPC_GPIOINT -> IO0IntEnR |= 0x1; //seteo las interrupciones del bit 0 de los puertos
	LPC_GPIOINT -> IO0IntClr |= 0x1; //limpio la flag
	LPC_GPIOINT -> IO2IntEnR |= 0x1; //por flanco de subida
	LPC_GPIOINT -> IO2IntClr |= 0x1; //limpio la flag
	NVIC_EnableIRQ(EINT3_IRQn); //habilito las int ext
	return;
}

void EINT3_IRQHandler() {
	//pregunto que puerto generó la interrupción
	if (LPC_GPIOINT -> IntStatus & 0x1) { //pregunto si fue el port0
		//Ahora voy a preguntar si el bit 0 generó la interrupción
		if (LPC_GPIOINT -> IO0IntStatR & 0x1) {
			auxiliar = 0b100111;
		}
		LPC_GPIOINT -> IO0IntClr |= 0x1; //limpio la flag
	} else if(LPC_GPIOINT -> IntStatus & (0x1 << 2)) {
		//pregunto si el bit 0 del port2 generó la interrupción
		if (LPC_GPIOINT -> IO2IntStatR & 0x1) {
			auxiliar = 0b111001011010110;
		}
		LPC_GPIOINT -> IO2IntClr |= 0x1; //limpio la flag
	}
	return;
}
