/* 
	Header pentru interfata generala de initializare a 
	convertoarelor analog digitale adc0/1 ale LPC2148 
	pentru interfatarea cu senzorii 
*/
#include<lpc214x.h>

/* Functie de initializare a adc0 si adc1*/
void init_adc(void);
/* Functii de citire ADC functie de canal */
unsigned int read_adc0(unsigned char);
unsigned int read_adc1(unsigned char);



