/* 	
	interfata de conectare a senzorilor ultrasonici pentru 
	detectia obstacolelor si maparea topologica a mediului 
*/

#include "global_adc_init.h"

/* Functie de citire a unui sonar */
unsigned int read_sonar(int sonar);
/* Functie de activarea a operarii in daisy-chaining pentru sonare */
void enable_sonar_chain(void);
/* Functie care introduce o intarziere la achizitia datelor ADC */
void delay_us(int);
/* Functie de strobe pentru activarea citirilor de la sonare */
void sonar_strobe(void);
/* Functie care formateaza datele primite de la sonare si 
 * trimite un pachet pe linia seriala.
 */
void format_sonar_data_and_send(unsigned int data);
