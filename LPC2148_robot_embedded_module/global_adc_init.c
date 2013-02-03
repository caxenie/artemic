/* 
	Interfata generala de initializare a convertoarelor analog
    digitale ADC0/1 ale LPC2148 pentru interfatarea cu senzorii 
*/

#include "global_adc_init.h"

// Configuratia sonarelor 
//  PINSEL0 
//  -> bit 25:24 conf 1:1 AD1.3 pin P0.12	-> sonar1
//  -> bit 27:26 conf 1:1 AD1.4 pin P0.13	-> sonar2

//  PINSEL1
//  -> bit 11:10 conf 1:0 AD1.6 pin P0.21 -> sonar3
//  -> bit 13:12 conf 0:1 AD1.7 pin P0.22 -> sonar4
//  -> bit 25:24 conf 0:1 AD0.1 pin P0.28 -> sonar5

/* Functie de initializare a convertoarelor ADC0/1 */
void init_adc(void){
	// activarea functiei ADC pentru pini (ADC1)
	PINSEL0 |= ((1<<24) | (1<<25) | (1<<26) | (1<<27));
    // activarea functiei ADC pentru pini (ADC0)
	PINSEL1 |= ((1<<11) | (1<<12) | (1<<24));
	PINSEL1 &=~((1<<10) | (1<<13) | (1<<25));
	// power control pentru periferice
	PCONP |= ((1<<12)|(1<<20)); // activare power ADC1/0
	// resetare conversii si biti de control
	AD0CR = 0x0;	// reg control ADC0
	AD1CR = 0x0;	// reg control ADC1
	// setare clock conversie CLKDIV fct de VPB CLK
	// aici se considera 6 factor de divizare la 30Mhz
	// freccventa MCU 30/(6+1) = 4.2MHz <= 4.5MHz (impus)
	AD0CR |=((1<<9) | (1<<10));
	AD1CR |=((1<<9) | (1<<10));
	// dezactivare mod BURST, operare in mod controlat software
	AD0CR &=~(1<<16);
	AD1CR &=~(1<<16);
}

/* Functii globale de citire a unui canal ADC */
unsigned int read_adc0(unsigned char channel)
{
   // rezultatul conversiei
   unsigned int i;
   // initializare adc
   init_adc();
   // opreste conversiile anterioare si reseteaza canalele
   AD0CR &= ~((1<<24) | (1<<25) | (1<<26));
   // selecteaza canalul primit la intrare
   AD0CR |= (1<<channel);
   // seteaza ADC0 operational; bit PDN=1
   AD0CR |= (1<<21); 
   // start conversie
   AD0CR |= (1<<24);
   do
   {
   switch(channel)	 // determina canalul 
   {
   case 0:
		   i=AD0DR0; // preia valoarea din reg de date canal 0
		   break;
   case 1:
		   i=AD0DR1; // preia valoarea din reg de date canal 1
		   break;
   case 2:
		   i=AD0DR2; // preia valoarea din reg de date canal 2
		   break;
   case 3:
		   i=AD0DR3; // preia valoarea din reg de date canal 3
		   break;
   case 4:
		   i=AD0DR4; // preia valoarea din reg de date canal 4
		   break;
   case 5:
		   i=AD0DR5; // preia valoarea din reg de date canal 5
		   break;
   case 6:
		   i=AD0DR6; // preia valoarea din reg de date canal 6
		   break;
   case 7:
		   i=AD0DR7; // preia valoarea din reg de date canal 7
		   break;
   default:
   		   break;
   } //end switch
   } 
   //asteapta final conversie(bit DONE=1 in reg global de date)
   while ((AD0GDR & 0x80000000) == 0); 
   // izoleaza rezultatul si revine
   return ((i >> 6) & 0x03FF);		    
}

unsigned int read_adc1(unsigned char channel)
{
// rezultatul conversiei
   unsigned int i;
   // initializare adc
   init_adc();
   // opreste conversiile anterioare si reseteaza canalele
   AD1CR &= ~((1<<24) | (1<<25) | (1<<26));
   // selecteaza canalul primit la intrare
   AD1CR |= (1<<channel);
   // seteaza ADC1 operational; bit PDN=1
   AD1CR |= (1<<21); 
   // start conversie
   AD1CR |= (1<<24);
   do
   {
   switch(channel)	 // determina canalul 
   {
   case 0:
		   i=AD1DR0; // preia valoarea din reg de date canal 0
		   break;
   case 1:
		   i=AD1DR1; // preia valoarea din reg de date canal 1
		   break;
   case 2:
		   i=AD1DR2; // preia valoarea din reg de date canal 2
		   break;
   case 3:
		   i=AD1DR3; // preia valoarea din reg de date canal 3
		   break;
   case 4:
		   i=AD1DR4; // preia valoarea din reg de date canal 4
		   break;
   case 5:
		   i=AD1DR5; // preia valoarea din reg de date canal 5
		   break;
   case 6:
		   i=AD1DR6; // preia valoarea din reg de date canal 6
		   break;
   case 7:
		   i=AD1DR7; // preia valoarea din reg de date canal 7
		   break;
   default:
   		   break;
   } //end switch
   } 
   //asteapta final conversie(bit DONE=1 in reg global de date)
   while ((AD1GDR & 0x80000000) == 0);  
   // izoleaza rezultatul si revine
   return ((i >> 6) & 0x03FF);		   
}


