#include<lpc214x.h>

/* Prototipurile functiilor modulului uart */

/* Variabile globale si macro */

#define OSCILLATOR_CLOCK_FREQUENCY  12000000 // 12 MHz
#define BAUD 9600
#define PCLK 30000000 // PCLK = ceas periferice 30 MHz

/* Functii specifice */
void init_uart0 (void);
void init_uart1 (void);
int putchar_uart0 (int);
int putchar_uart1 (int);
int getchar_uart0 (void);
int getchar_uart1 (void);

/* Functii auxiliare */
void init_system(void);

/* Functie de conversie un octet binar la doua caractere ascii hiniob, lonib */
void ascii_convert0(unsigned char);
void ascii_convert1(unsigned char);

/* Functii care transmit pe linia seriala datele formatate ASCII */
void uart0_send_ascii(unsigned char);
void uart1_send_ascii(unsigned char);

