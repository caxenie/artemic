/*
	Interfata pentru accelerometru 3D. Informatia de acceleratie
	este integrata in informatie de positie utila la fuziunea
	senzorilor pentru pozitionarea globala a robotului mobil 
*/

#include "global_adc_init.h"

/* Functie de citire a axei X */
unsigned int read_accel_x(void);
/* Functie de citire a axei Y */
unsigned int read_accel_y(void);
