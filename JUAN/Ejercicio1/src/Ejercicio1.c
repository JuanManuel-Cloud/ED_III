/*
===============================================================================
 Name        : Ejercicio1.c
 Author      : $Juan Manuel Gil
 Version     :
 Copyright   : $(copyright)
 Description : Una famosa empresa de calzados a incorporado a sus zapatillas 10 luces leds comandadas por
  un microcontrolador LPC1769 y ha pedido a su grupo de ingenieros que diseñen 2 secuencias de luces que
  cada cierto tiempo se vayan intercalando (secuencia A - secuencia B- secuencia A- ... ).
  Como todavía no se ha definido la frecuencia a la cual va a funcionar el CPU del microcontrolador,
  las funciones de retardos que se incorporen deben tener como parametros de entrada variables que
  permitan modificar el tiempo de retardo que se vaya a utilizar finalmente. Se pide escribir el código
  que resuelva este pedido, considerando que los leds se encuentran conectados en los puertos
  P0,0 al P0.9. Adjuntar el archivo .c bajo el nombre "eje1ApellidoDelEstudiante.c"
===============================================================================
*/

#include "LPC17xx.h"
#include <stdio.h>

void toggleLed();
void retardo( uint32_t );

int main(void) {
	uint32_t t_retardo = 100000;

	LPC_PINCON -> PINSEL0 &= ~0xFFFFF; //de está manera pongo como GPIO los puertos de 0 a 9
	LPC_GPIO0 -> FIODIRL |= 0x3FF;
	LPC_GPIO0 -> FIOMASKL |= 0xFC00;

    while(1) {
    	toggleLed(t_retardo);
    }
    return 0 ;
}

void toggleLed(uint32_t t_retardo) {
	LPC_GPIO0 -> FIOPINL |= 0x3FF;
	retardo(t_retardo);
	LPC_GPIO0 -> FIOPINL &= ~0x3FF;
}

void retardo(uint32_t t_retardo) {
	for(uint32_t contador = 0 ; contador < t_retardo; contador++){};
}
