#line 1 "sonar_interface.c"



 

#line 1 "sonar_interface.h"



 

#line 1 "global_adc_init.h"




 
#line 1 "C:\\Program Files\\Keil\\ARM\\INC\\Philips\\lpc214x.h"
 
 
 
 
 
 
 
 




 
#line 57 "C:\\Program Files\\Keil\\ARM\\INC\\Philips\\lpc214x.h"

 




 
#line 90 "C:\\Program Files\\Keil\\ARM\\INC\\Philips\\lpc214x.h"

 




 





 





 


 



 





 


 


 


 
#line 148 "C:\\Program Files\\Keil\\ARM\\INC\\Philips\\lpc214x.h"

 
#line 167 "C:\\Program Files\\Keil\\ARM\\INC\\Philips\\lpc214x.h"

 
#line 184 "C:\\Program Files\\Keil\\ARM\\INC\\Philips\\lpc214x.h"

 
#line 201 "C:\\Program Files\\Keil\\ARM\\INC\\Philips\\lpc214x.h"

 
#line 218 "C:\\Program Files\\Keil\\ARM\\INC\\Philips\\lpc214x.h"

 
#line 227 "C:\\Program Files\\Keil\\ARM\\INC\\Philips\\lpc214x.h"

 
#line 236 "C:\\Program Files\\Keil\\ARM\\INC\\Philips\\lpc214x.h"

 






 
#line 254 "C:\\Program Files\\Keil\\ARM\\INC\\Philips\\lpc214x.h"

 
#line 282 "C:\\Program Files\\Keil\\ARM\\INC\\Philips\\lpc214x.h"

 
#line 296 "C:\\Program Files\\Keil\\ARM\\INC\\Philips\\lpc214x.h"

 
#line 310 "C:\\Program Files\\Keil\\ARM\\INC\\Philips\\lpc214x.h"

 


 


 





 
#line 363 "C:\\Program Files\\Keil\\ARM\\INC\\Philips\\lpc214x.h"

#line 7 "global_adc_init.h"

 
void init_adc(void);
 
unsigned int read_adc0(unsigned char);
unsigned int read_adc1(unsigned char);



#line 7 "sonar_interface.h"

 
unsigned int read_sonar(int sonar);
 
void enable_sonar_chain(void);
 
void delay_us(int);
 
void sonar_strobe(void);


 
void format_sonar_data_and_send(unsigned int data);
#line 7 "sonar_interface.c"
#line 1 "serial.h"

#line 3 "serial.h"

 

 





 
void init_uart0 (void);
void init_uart1 (void);
int putchar_uart0 (int);
int putchar_uart1 (int);
int getchar_uart0 (void);
int getchar_uart1 (void);

 
void init_system(void);

 
void ascii_convert0(unsigned char);
void ascii_convert1(unsigned char);

 
void uart0_send_ascii(unsigned char);
void uart1_send_ascii(unsigned char);

#line 8 "sonar_interface.c"









 













 

 
unsigned int read_sonar(int sonar){
	 
 	unsigned int val;	
	 
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
	 
	return (unsigned int)(((val*3300)/1024)/3.36f);
}



 
void enable_sonar_chain(void){
	  
	  (*((volatile unsigned long *) 0xE0028018)) |= ((1<<16) | (1<<17) | (1<<18) | (1<<19) | (1<<20) | (1<<21));
	  
	  (*((volatile unsigned long *) 0xE0028014)) |= ((1<<16) | (1<<17) | (1<<18) | (1<<19) | (1<<20));
	  
	  (*((volatile unsigned long *) 0xE0028014)) |= (1<<21);
 	  delay_us(50);
      (*((volatile unsigned long *) 0xE002801C)) |= (1<<21); 
	  
	  (*((volatile unsigned long *) 0xE0028018)) &=~(1<<21);
}

 
void sonar_strobe(void){
	   (*((volatile unsigned long *) 0xE0028014)) |= (1<<21);
 	   delay_us(50);
       (*((volatile unsigned long *) 0xE002801C)) |= (1<<21); 
	   delay_us(50);
}

 
void delay_us(int x){
   int a,b;
   for(a=0;a<x;a++)
      for(b=0;b<4;b++);
}



 
void format_sonar_data_and_send(unsigned int data){
	
	unsigned char data_l, data_h;
	
	data_h = (data&0x300)>>8;
	
	data_l = data&0xff;
	
	uart0_send_ascii(data_h);
	uart0_send_ascii(data_l);
	
	putchar_uart0(',');
}
