/*
===============================================================================
 Name        : Ejercicio2_salida.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : En los pines P2.0 a P2.7 se encuentra conectado un display de 7 segmentos.
 Utilizando la variable numDisplay [10] ={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67}
  que codifica los números del 0 a 9 para ser mostrados en el display, realizar un programa que muestre
   indefinidamente la cuenta de 0 a 9 en dicho display.
===============================================================================
*/

#include "LPC17xx.h"
void retardo( uint32_t );

int main(void) {

	uint32_t numDisplay [10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67};
	uint32_t t_retardo = 100000;
	//Pongo como GPIO los pines del 0 al 7 del puerto 2, y tomo solo el primer byte del puerto2 y lo pongo como salida
	LPC_PINCON -> PINSEL4 = 0xFFF0;
	LPC_GPIO2 -> FIODIR0 = 0x7;

    while(1) {
    	for(uint8_t i = 0; i < 10; i++) {
    		LPC_GPIO2 -> FIOPIN0 = numDisplay[i];
    		retardo(t_retardo);
    	}
    }
    return 0 ;
}

void retardo(uint32_t t_retardo) {
	for(uint32_t contador = 0 ; contador < t_retardo; contador++){};
}
