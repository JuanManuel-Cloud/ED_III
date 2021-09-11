/*
===============================================================================
 Name        : systick_interrupt_1.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description :1.- Configure el Systick Timer de modo que genere una forma de onda
 llamada PWM tal como la que se muestra en la figura adjunta. Esta señal debe ser
 sacada por el pin P0.22 para que controle la intensidad de brillo del led.
 El periodo de la señal debe ser de 10 mseg con un duty cycle de 10%.
 Configure la interrupción externa EINT0 de modo que cada vez que se entre en una rutina
 de interrupción externa el duty cycle incremente en un 10% (1 mseg).
 Esto se repite hasta llegar al 100%, luego, si se entra nuevamente a la interrupción
 externa, el duty cycle volverá al 10%.
2.- Modificar los niveles de prioridad para que la interrupción por systick tenga mayor
prioridad que la interrupción externa.
3. Adjuntar el .C  del código generado.
===============================================================================
*/

#include "LPC17xx.h"

uint8_t duty_cycle = 1;
uint8_t mili_cont = 0;

void confGPIO();
void confIntExt();
void confSysTick();
void delay( uint32_t );

int main(void) {
	confGPIO();
	confIntExt();
	confSysTick();

    while(1) {
    	//el if lo que hace es evaluar el valor del ciclo de trabajo y compararlo contra
    	//la cantidad de milis sucedidos de los 10ms que tiene en total el ciclo,
    	//si todavía no cumplió con el ciclo de trabajo se mantiene prendido el led,
    	//cuando cumple con el ciclo de trabajo se apaga por el resto de los ms restantes.
    	if (mili_cont < duty_cycle) {
    		LPC_GPIO0 -> FIOPIN2 |= (0x1 << 6); //enciendo el led
    	} else {
    		LPC_GPIO0 -> FIOPIN2 &= ~(0x1 << 6); //apago el led
    	}
    }
    return 0 ;
}

void EINT0_IRQHandler() {
	delay(500000); //anti rebote
	LPC_SC -> EXTINT |= 1; //limpio el flag
	duty_cycle ++; //aumento en 10% el duty_cycle
	if (duty_cycle > 10) {
		duty_cycle = 1; //si el duty_cycle llega al 100% lo vuelvo al 10%
	}
	return;
}

void SysTick_Handler() {
	mili_cont ++;
	if (mili_cont == 10) {
		mili_cont = 0; //divido los 10ms en intervalos de 1ms, y voy contando entonces
						//con eso puedo definir el porcentaje del ciclo, dependiendo
						//de los ms que tenga prendido, cuando llegue a los 10ms apago
	}
	SysTick -> CTRL &= SysTick -> CTRL; //realizo una dummy operation para limpiar el registro
	return;
}

void confGPIO() {
	LPC_PINCON -> PINSEL1 &= ~(0x3 << 12); //pongo como gpio el port0 bit 22
	LPC_GPIO0 -> FIODIR2 |= (0x1 << 6); //pongo como salida el port0 bit 22
	LPC_GPIO0 -> FIOMASK2 = ~(0x1 << 6);//mask para el led
	LPC_GPIO2 -> FIOMASK1 = ~(0x1 << 2);//mask para la ext int.
	return;
}

void confIntExt() {
	LPC_PINCON -> PINSEL4  |= (0x1 << 20);
	LPC_SC -> EXTINT |= 0x1;//limpio el flag de eint0
	LPC_SC -> EXTMODE |= 0x1;//pongo que sea activa por flanco
	LPC_SC -> EXTPOLAR |= 0x1;//pongo que sea activa por flanco de subida
	NVIC_SetPriority(EINT0_IRQn, 0);//el systick tiene prioridad -1, entonces con 0 ya tengo menos
	NVIC_EnableIRQ(EINT0_IRQn);
	return;
}

void confSysTick() {
	SysTick -> LOAD = SystemCoreClock / 1000;//divido por 1000 y no por 10000 porque voy a ir tomando de a 1ms
	return;
}

void delay(uint32_t demora) {
	for (uint32_t i = 0; i < demora; i++) {}
}
