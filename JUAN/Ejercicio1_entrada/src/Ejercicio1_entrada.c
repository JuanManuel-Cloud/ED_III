//Configurar el pin P0.4 como entrada digital con resistencia de pull up
//y utilizarlo para decidir si el valor representado por los pines P0.0
//al P0.3 van a ser sumados o restados al valor guardado en la variable
//"acumulador".El valor inicial de "acumulador" es 0.

#include "LPC17xx.h"
void confGPIO();
int main() {
	int32_t acumulador = 0;
	confGPIO();

	while(1) {

		if (LPC_GPIO0 -> FIOPIN0 & (1 << 5)) { //puede que sea 4 acá?
			acumulador += LPC_GPIO0 -> FIOPIN0 & (0xF); //me quedo con el valor de los primeros 4 bits
		} else {
			acumulador -= LPC_GPIO0 -> FIOPIN0 & (0xF);
		}

	}
	return 0;
}

void confGPIO() {
	LPC_PINCON -> PINSEL0 = ~0x1FF; //seteo como gpio los puertos 0,1,2,3,4
	LPC_PINCON -> PINMODE0 &= ~(3 << 8); //pongo en 0 el pin 8 y 9, para que sean pull up
	LPC_GPIO0 -> FIODIR0 = 0xF; //pongo p0.4 como entrada y p0 0-3 como slaida
	LPC_GPIO0 -> FIOMASK0 = 0xE0; //enmascaro los bits que no voy a usar
}
