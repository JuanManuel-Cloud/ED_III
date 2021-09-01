//Configurar el pin P0.4 como entrada digital con resistencia de pull up
//y utilizarlo para decidir si el valor representado por los pines P0.0
//al P0.3 van a ser sumados o restados al valor guardado en la variable
//"acumulador".El valor inicial de "acumulador" es 0.

#include "LPC17xx.h"

int main() {
	int32_t acumulador = 0;
	LPC_PINCON -> PINMODE0 &= ~(3 << 8);//tengo que poner en 0 el bit 8 y nueve para que sean pull ups
	LPC_GPIO0 -> FIODIR0 = 0xF;
	LPC_GPIO0 -> FIOMASK0 = 0xE0;

	while(1) {
		if(LPC_GPIO0 -> FIOPIN0 & (1 << 5)) { //testeo que el estado del bit 4
			acumulador += LPC_GPIO0 -> FIOPIN0 & (0xF); //me quedo solo con el valor de los 4 primeros bits
		} else
		{
			acumulador -= LPC_GPIO0 -> FIOPIN & (0xF);
		}
	}
	return 0;
}
