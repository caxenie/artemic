/* 	
	Interfata de conectare a senzorilor ultrasonici pentru 
	detectia obstacolelor si maparea topologica a mediului 
*/

#include "sonar_interface.h"
#include "serial.h"

/*
 Determinarea iesirii pentru Uin = 4V

 Uin=5V -> out=~9.8mV/in. si Uin=3.3V -> out=~6.4mV/in.
 Uin=4.3V -> out = ?
  
 (x-6.4)/(9.8-6.4) = (4.3-3.3)/(5-3.3)=> x = 8.4mV/in =  3.36mV/cm

 */
#define SCALE 3.36f   // 3.36mV
#define V_SUPPLY 4300 // 4300mV
#define MAX_ADC 1024  // ADC 10 biti
/*
	Configuratia utilizata pt sonare : 

  PINSEL0 
  -> bit 25:24 conf 1:1 AD1.3 pin P0.12	-> sonar1
  -> bit 27:26 conf 1:1 AD1.4 pin P0.13	-> sonar2

  PINSEL1
//  -> bit 11:10 conf 1:0 AD1.6 pin P0.21 -> sonar3
//  -> bit 13:12 conf 0:1 AD1.7 pin P0.22 -> sonar4
//  -> bit 25:24 conf 0:1 AD0.1 pin P0.28 -> sonar5
*/

/*Functie de citire a ADC conectate la sonare */
unsigned int read_sonar(int sonar){
	/* valoarea tensiunii de la iesirea sonarului */
 	unsigned int val;	
	/* citeste valoarea corespunzatoare sonarului */
	switch(sonar){						   
	 		case 1: val = read_adc1(3);
					break;
			case 2: val = read_adc1(4);
					break;
			case 3: val = read_adc1(6);
					break;
			case 4: val = read_adc1(7);
					break;
			case 5: val = read_adc0(1);
					break;
	}
	/* returneaza distanta in cm pana la primul obstacol */
	return (unsigned int)(((val*V_SUPPLY)/MAX_ADC)/SCALE);
}

/* Functie de activarea a modului de operare in chaining pentru 
   sonare.
*/
void enable_sonar_chain(void){
	  // seteaza pinii pentru BW (bandwidth)
	  IO1DIR |= ((1<<16) | (1<<17) | (1<<18) | (1<<19) | (1<<20) | (1<<21));
	  // BW este mentinut High (1)
	  IO1SET |= ((1<<16) | (1<<17) | (1<<18) | (1<<19) | (1<<20));
	  // conecteaza RX la 1 logic pt 50 us
	  IO1SET |= (1<<21);
 	  delay_us(50);
      IO1CLR |= (1<<21); 
	  // comuta pinul RX in high-Z0
	  IO1DIR &=~(1<<21);
}

/* Functie de strobe pentru activarea citirilor de la sonare */
void sonar_strobe(void){
	   IO1SET |= (1<<21);
 	   delay_us(50);
       IO1CLR |= (1<<21); 
	   delay_us(50);
}

/* Functie care introduce intraziere la achizitia datelor ADC */
void delay_us(int x){
   int a,b;
   for(a=0;a<x;a++)
      for(b=0;b<4;b++);
}

/* Functie care formateaza datele primite de la sonare si 
 * trimite un pachet pe linia seriala.
 */
void format_sonar_data_and_send(unsigned int data){
	// octeti ascii corespunzatori valorii citite
	unsigned char data_l, data_h;
	// se extrage octetul mai semnificativ al valorii
	data_h = (data&0x300)>>8;
	// se extrage octetul mai putin semnificativ
	data_l = data&0xff;
	// trimite octetii pe linia seriala dupa conversia ascii
	uart0_send_ascii(data_h);
	uart0_send_ascii(data_l);
	// separator 
	putchar_uart0(',');
}
