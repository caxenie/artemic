
/*
	Interfata pentru accelerometru 3D. Informatia de acceleratie
	este integrata in informatie de positie utila la fuziunea
	senzorilor pentru pozitionarea globala a robotului mobil 
*/

#include "accelerometer_interface.h"
// TODO Revizuire porul ADC pentru utilizare ACCelerometru

/*
	Configuratia utilizata pt accelerometru : 
  -> bit 13:12 conf 0:1 AD1.7 pin P0.22 -> Accelerometru axa X
  -> bit 11:10 conf 1:0 AD1.6 pin P0.21 -> Accelerometru axa Y
*/

/* Functie de citire a axei X */
unsigned int read_accel_x(void){
     // valoarea tensiunii de la iesirea X a accelerometrului
	 unsigned int value;
	// activare functie ADC pt P0.22 in PINSEL1
	PINSEL1 |= (1<<12);
	PINSEL1 &=~(1<<13);
     value = read_adc1(7);
	 // returneaza valoarea citita 
	 return (value);
}

/* Functie de citire a axei Y */
unsigned int read_accel_y(void){ 
     // valoarea tensiunii de la iesirea Y a accelerometrului
	 unsigned int value;
	// activare functie ADC pt P0.22 in PINSEL1
	PINSEL1 |= (1<<11);
	PINSEL1 &=~(1<<10);
      value = read_adc1(6);
	 // returneaza valoarea citita 
	 return (value);
}
