#line 1 "serial.c"

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

#line 3 "serial.c"
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

#line 4 "serial.c"






 

  
unsigned char lonib0, hinib0, lonib1, hinib1;

 

void init_system(void){
 
  







 
  (*((volatile unsigned char *) 0xE01FC084)) = 0x24;	 

  
 
  (*((volatile unsigned char *) 0xE01FC08C)) = 0xAA;
  (*((volatile unsigned char *) 0xE01FC08C)) = 0x55;
  
   







 
  (*((volatile unsigned char *) 0xE01FC080)) = 0x01;
   
  (*((volatile unsigned char *) 0xE01FC08C)) = 0xAA;
  (*((volatile unsigned char *) 0xE01FC08C)) = 0x55;

   
  while(!((*((volatile unsigned short*) 0xE01FC088)) & 0x400));   

  


 
  (*((volatile unsigned char *) 0xE01FC080)) = 0x03;
   
  (*((volatile unsigned char *) 0xE01FC08C)) = 0xAA;
  (*((volatile unsigned char *) 0xE01FC08C)) = 0x55;

   
   
  (*((volatile unsigned char *) 0xE01FC000)) = 0x2;
  (*((volatile unsigned char *) 0xE01FC004)) = 0x4;
   
  (*((volatile unsigned char *) 0xE01FC100)) = 0x02; 
}

 
void init_uart0(void){

   


  
   int div =  30000000/(16*9600);	

   






 
   (*((volatile unsigned long *) 0xE002C000)) |= 0x5;

    
   (*((volatile unsigned char *) 0xE000C008))=0x7;
   








 
   (*((volatile unsigned char *) 0xE000C00C)) = 0x83; 

   
 

   (*((volatile unsigned char *) 0xE000C000)) = div & 0xFF;
   (*((volatile unsigned char *) 0xE000C004)) = (div>>8); 

   
 
   (*((volatile unsigned char *) 0xE000C00C)) = 0x03;
}

 
void init_uart1(void)
{
   int div =  30000000/(16*9600);	
    
   (*((volatile unsigned long *) 0xE002C000)) |= 0x00050000;
   (*((volatile unsigned char *) 0xE001000C)) = 0x83; 
   (*((volatile unsigned char *) 0xE0010000)) = div & 0xFF;
   (*((volatile unsigned char *) 0xE0010004)) = (div>>8); 
   (*((volatile unsigned char *) 0xE001000C)) = 0x03;
}


 
int putchar_uart0 (int ch){
	  
	 while(!((*((volatile unsigned char *) 0xE000C014)) & 0x20));
	  
	 	return ((*((volatile unsigned char *) 0xE000C000)) = ch);
}

 
void puts_uart0(char *ch)
{
   while(*ch){
		putchar_uart0(*ch++);
   }
}

 
int putchar_uart1 (int ch){
	  
	 while(!((*((volatile unsigned char *) 0xE0010014)) & 0x20));
	  
	 	return ((*((volatile unsigned char *) 0xE0010000)) = ch);
}

 
void puts_uart1(char *ch)
{
   while(*ch){
		putchar_uart1(*ch++);
   }
}

 
int getchar_uart0 (void){
	 
	while(!((*((volatile unsigned char *) 0xE000C014)) & 0x01));
	 
 	return ((*((volatile unsigned char *) 0xE000C000)));
}


 
int getchar_uart1 (void){
	 
	while(!((*((volatile unsigned char *) 0xE0010014)) & 0x01));
	 
 	return ((*((volatile unsigned char *) 0xE0010000)));
}

 
 
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
