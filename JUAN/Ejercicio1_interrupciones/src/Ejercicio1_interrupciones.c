/*
===============================================================================
 Name        : Ejercicio1_interrupciones.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : Realizar un programa que configure el puerto P2.0 y P2.1
 para que provoquen una interrupción por flanco de subida para el primer
 pin y por flanco de bajada para el segundo. Cuando la interrupción sea
 por P2.0 se enviará por el pin P0.0 la secuencia de bits 010011010.
 Si la interrupción es por P2.1 se enviará por el pin P0.1 la secuencia
 011100110. Las secuencias se envían únicamente cuando se produce una
 interrupción, en caso contrario la salida de los pines tienen
 valores 1 lógicos. ¿que prioridad tienen configuradas por defecto
 estas interrupciones? creo que las prioridades por defecto son 0, por ende
 la más alta
===============================================================================
*/

#include "LPC17xx.h"

void confGPIO();
void confIntGPIO();
void retardo(uint32_t);

int main(void) {

	confGPIO();
	confIntGPIO();

    while(1) {
    	LPC_GPIO0 -> FIOSET0 = 0x3; //prendo el led de los bits 0 y 1 del puerto0
    }
    return 0 ;
}

void confGPIO(){
	LPC_PINCON -> PINSEL0 &= ~0x3; //pongo como gpio el bit 0 y 1 del puerto 0
	LPC_PINCON -> PINSEL4 &= ~0x3; //pongo como gpio el bit 0 y 1 del puerto 2
	LPC_GPIO0 -> FIODIR |= 0x3; //pongo como salida los bit 0 y 1 del puerto 0
	LPC_GPIO0 -> FIOMASK0 = 0xFC; //enmascaro el primer byte del puerto 0 para usar solo el bit 0 y 1
	LPC_GPIO2 -> FIODIR &= ~0x3; //pongo 0 en el bit 0 y 1 del puerto 2, entonces están como entrada
	LPC_GPIO2 -> FIOMASK0 = 0xFC; //enmascaro el primer byte del puerto 2 para usar solo el bit 0 y 1
	return;
}

void confIntGPIO() {
	LPC_GPIOINT -> IO2IntEnR |= 0x1; //habilita interrupciones por flanco de subida en el bit 0
	LPC_GPIOINT -> IO2IntEnF |= 0x2; //habilita interrupciones por flanco de bajada en el bit 1
	LPC_GPIOINT -> IO2IntClr &= ~0x3; //limpio el flag del bit 0 y 1
	NVIC_EnableIRQ(EINT3_IRQn); // habilita las interrupciones externas 3, ya que GPIO0 y GPIO2
	return;						//interrumpen en la misma dirección de mem que IntExt3.
}

void EINT3_IRQHandler() {
	uint8_t secuencia_1[9] = {0,1,0,0,1,1,0,1,0}, secuencia_2[9] = {0,1,1,1,0,0,1,1,0};
	uint32_t t_retardo = 1000000;
	//Lo primero que tengo que hacer es consultar que puerto interrumpió.
	//después pregunto que bit fue el que interrumpió. Para eso uso el status
	if (LPC_GPIOINT -> IntStatus & 0x1) {
		//si esto es verdadero es porque la interurpción fue por puerto0
		//En este caso no hay nada para hacer con el puerto0
		LPC_GPIOINT -> IO0IntClr |= 0x1;
	} else if(LPC_GPIOINT -> IntStatus & (0x1 << 2)) {
		//si esto es verdadero es porque la interrupción fue por puerto2
		//Ahora consulto que bit generó la interrupción
		//fue el bit 0?
		if (LPC_GPIOINT -> IO2IntStatR & 0x1) {
			for (uint8_t i = 0; i < sizeof(secuencia_1); i++) {
				LPC_GPIO0 -> FIOSET0 |= secuencia_1[i]; //seteo el bit 0 del puerto 0 con el valor de la secuencia
				retardo(t_retardo);
				LPC_GPIO0 -> FIOCLR0 = 0x1;
			}
		}
		//fue el bit 1?
		if (LPC_GPIOINT -> IO2IntStatR & (0x1 << 1)) {
			for (uint8_t i = 0; i < sizeof(secuencia_1); i++) {
				LPC_GPIO0 -> FIOSET0 |= (secuencia_2[i] << 1); //seteo el bit 1 del puerto 0 con el valor de la secuencia
				retardo(t_retardo);
				LPC_GPIO0 -> FIOCLR0 = 0x2;
			}
		}
		LPC_GPIOINT -> IO2IntClr |= (0x1 << 2);
	}
}

void retardo(uint32_t t_retardo) {
	for(uint32_t contador = 0 ; contador < t_retardo; contador++){};
}


