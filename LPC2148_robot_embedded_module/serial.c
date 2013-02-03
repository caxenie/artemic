
#include<lpc214x.h>
#include "serial.h"

/* Modul uart
  - initializare uart0
  - initializare uart1
  - functie citire uart0/uart1
  - functie scriere uart0/uart1
*/

 /* utile in conversia in reprezentare ASCII */
unsigned char lonib0, hinib0, lonib1, hinib1;

/* Functie de initializare a PLL */

void init_system(void){
 
  /* PLL Configuration Register
  - contine valorile de multiplicare si divizare pentru PLL
  - modificarile in acest registru au loc dupa o secventa de 
    feed a buclei PLL
  -----------------------------------------------------------------------
  Valori biti:
   MSEL -->	00100 (bit 0:4) Multiplicare
   PSEL --> 01	  (bit 6:5) Divizare
   */
  PLL0CFG = 0x24;	 

  /* Pentru a asigura modificarea valorilor in registrle de control si
  configurare a buclei PLL se impune o secventa de feed a buclei PLL*/
  PLL0FEED = 0xAA;
  PLL0FEED = 0x55;
  
   /* PLL Control Register 
  - registru utilizat pentru a modifica biti de control ai PLL
  - se activeaza PLL si se conecteaza MCU la frecventa de iesire PLL
  - PLL0 este utilizata pentru a genera CLK pt procesor, 
    PLL1 e dedicata USB
 ------------------------------------------------------------------------
  Valori biti :	 (PLL Enable) 
   PLLE --> 1 (bit 0)
  */
  PLL0CON = 0x01;
  /* secventa de feed a PLL */
  PLL0FEED = 0xAA;
  PLL0FEED = 0x55;

  /* asteapta pana cand PLL este locked pe faza */
  while(!(PLL0STAT & 0x400));   

  /* PLL connect
   Valori biti :
   PLLC --> 1 (bit 1)
  */
  PLL0CON = 0x03;
  /* secventa de feed a PLL */
  PLL0FEED = 0xAA;
  PLL0FEED = 0x55;

  /* numar de cicli de ceas de acces la memoria Flash */
  /* 4 CLK */
  MAMCR = 0x2;
  MAMTIM = 0x4;
  /* divizor freceventa periferice */
  VPBDIV = 0x02; // PCLK = 30MHz
}

/* Functie de initializare uart0 */
void init_uart0(void){

   /*
   Pentru stabilirea baudrateului pentru uart0 se determina valoarea 
   care va fi scrisa in registrul latch divisor LSB si MSB
   */ 
   int div =  PCLK/(16*BAUD);	

   /* Pin Function Select Register 0  - PINSEL0 
   are rolul de a controla functiile pinilor MCU
   - se activeaza liniile de TX si RX pentru uart0
   -----------------------------------------------
   Valori biti :
   P0.0 --> 01 (bit 1:0)
   P0.1 --> 01 (bit 3:2) 
   */
   PINSEL0 |= 0x5;

   /* elibereaza FIFO urile */
   U0FCR=0x7;
   /* Line Control Register - U0LCR
   are rolul de a set aparametri de comunicatie pe uart
   - activeaza numarul de biti, paritate si biti de stop
   -----------------------------------------------------
   Valori biti : 
   Word Length Select            --> 11 (bit 1:0) 8bit char
   Stop bit Select               --> 0  (bit 2)   1 stop bit
   Parity Select                 --> 0  (bit 3)   Paritate dezactivata
   Divisor Latch Acces Bit(DLAB) --> 1 (bit 7) pentru a accesa 
   registrele latch divizor U0DLL, U0DLM */
   U0LCR = 0x83; 

   /* Generarea baudrateului dorit se realizeaza prin utilizarea
   registrelor latch divizoare U0DLL, U0DLM (16 bit LSB,MSB) */

   U0DLL = div & 0xFF;
   U0DLM = (div>>8); // 9600 Baud Rate 

   /* Pentru a accesa registrele U0RBR, U0THR (bufferele de date Rx/Tx)
   bitul DLAB trebuie resetat */
   U0LCR = 0x03;
}

/* Functie de initializare uart1 */
void init_uart1(void)
{
   int div =  PCLK/(16*BAUD);	
   /* se activeaza liniile de TX si RX pentru uart0 */
   PINSEL0 |= 0x00050000;
   U1LCR = 0x83; 
   U1DLL = div & 0xFF;
   U1DLM = (div>>8); 
   U1LCR = 0x03;
}


/* Functie de scriere a unui carcater pe uart0 */
int putchar_uart0 (int ch){
	 /* cat timp nu avem data in buffer asteapta */
	 while(!(U0LSR & 0x20));
	 /* altfel plaseaza in buffer caracterul de trimis */
	 	return (U0THR = ch);
}

/* Functie de scriere a unui sir de caractere pe uart0 */
void puts_uart0(char *ch)
{
   while(*ch){
		putchar_uart0(*ch++);
   }
}

/* Functie de scriere a unui caracter pe uart1 */
int putchar_uart1 (int ch){
	 /* cat timp nu avem data in buffer asteapta */
	 while(!(U1LSR & 0x20));
	 /* altfel plaseaza in buffer caracterul de trimis */
	 	return (U1THR = ch);
}

/* Functie de scriere a unui sir de caractere pe uart1 */
void puts_uart1(char *ch)
{
   while(*ch){
		putchar_uart1(*ch++);
   }
}

/* Functie de citire a unui caracter primit pe uart0 */
int getchar_uart0 (void){
	/* cat timp nu avem date in registrul de receptie U0RBR asteapta */
	while(!(U0LSR & 0x01));
	/* cand avem date disponibile in buffer se preiau */
 	return (U0RBR);
}


/* Functie de citire a unui caracter primit pe uart1 */
int getchar_uart1 (void){
	/* cat timp nu avem date in registrul de receptie U1RBR asteapta */
	while(!(U1LSR & 0x01));
	/* cand avem date disponibile in buffer se preiau */
 	return (U1RBR);
}

/* Functii de conversie un octet binar la doua caractere ascii hiniob, lonib */
/* Valorile rezultate sunt in hexazecimal */
void ascii_convert0(unsigned char ch)
{	
   hinib0=(ch&0xf0)>>4;
   lonib0=ch&0x0f;
   if(hinib0>9) hinib0=hinib0+'7';
   else hinib0=hinib0+'0';
   if(lonib0>9) lonib0=lonib0+'7';
   else lonib0=lonib0+'0';

}

void ascii_convert1(unsigned char ch)
{	
   hinib1=(ch&0xf0)>>4;
   lonib1=ch&0x0f;
   if(hinib1>9) hinib1=hinib1+'7';
   else hinib1=hinib1+'0';
   if(lonib1>9) lonib1=lonib1+'7';
   else lonib1=lonib1+'0';

}

/* Functii care transmit pe linia seriala datele formatate ASCII */
void uart0_send_ascii(unsigned char ch)
{
    ascii_convert0(ch);
    putchar_uart0(hinib0);
    putchar_uart0(lonib0);
    
}
void uart1_send_ascii(unsigned char ch)
{
    ascii_convert1(ch);
    putchar_uart1(hinib1);
    putchar_uart1(lonib1);
}
