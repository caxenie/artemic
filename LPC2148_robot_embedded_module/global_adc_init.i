#line 1 "global_adc_init.c"



 

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



#line 7 "global_adc_init.c"











 
void init_adc(void){
	
	(*((volatile unsigned long *) 0xE002C000)) |= ((1<<24) | (1<<25) | (1<<26) | (1<<27));
    
	(*((volatile unsigned long *) 0xE002C004)) |= ((1<<11) | (1<<12) | (1<<24));
	(*((volatile unsigned long *) 0xE002C004)) &=~((1<<10) | (1<<13) | (1<<25));
	
	(*((volatile unsigned long *) 0xE01FC0C4)) |= ((1<<12)|(1<<20)); 
	
	(*((volatile unsigned long *) 0xE0034000)) = 0x0;	
	(*((volatile unsigned long *) 0xE0060000)) = 0x0;	
	
	
	
	(*((volatile unsigned long *) 0xE0034000)) |=((1<<9) | (1<<10));
	(*((volatile unsigned long *) 0xE0060000)) |=((1<<9) | (1<<10));
	
	(*((volatile unsigned long *) 0xE0034000)) &=~(1<<16);
	(*((volatile unsigned long *) 0xE0060000)) &=~(1<<16);
}

 
unsigned int read_adc0(unsigned char channel)
{
   
   unsigned int i;
   
   init_adc();
   
   (*((volatile unsigned long *) 0xE0034000)) &= ~((1<<24) | (1<<25) | (1<<26));
   
   (*((volatile unsigned long *) 0xE0034000)) |= (1<<channel);
   
   (*((volatile unsigned long *) 0xE0034000)) |= (1<<21); 
   
   (*((volatile unsigned long *) 0xE0034000)) |= (1<<24);
   do
   {
   switch(channel)	 
   {
   case 0:
		   i=(*((volatile unsigned long *) 0xE0034010)); 
		   break;
   case 1:
		   i=(*((volatile unsigned long *) 0xE0034014)); 
		   break;
   case 2:
		   i=(*((volatile unsigned long *) 0xE0034018)); 
		   break;
   case 3:
		   i=(*((volatile unsigned long *) 0xE003401C)); 
		   break;
   case 4:
		   i=(*((volatile unsigned long *) 0xE0034020)); 
		   break;
   case 5:
		   i=(*((volatile unsigned long *) 0xE0034024)); 
		   break;
   case 6:
		   i=(*((volatile unsigned long *) 0xE0034028)); 
		   break;
   case 7:
		   i=(*((volatile unsigned long *) 0xE003402C)); 
		   break;
   default:
   		   break;
   } 
   } 
   
   while (((*((volatile unsigned long *) 0xE0034004)) & 0x80000000) == 0); 
   
   return ((i >> 6) & 0x03FF);		    
}

unsigned int read_adc1(unsigned char channel)
{

   unsigned int i;
   
   init_adc();
   
   (*((volatile unsigned long *) 0xE0060000)) &= ~((1<<24) | (1<<25) | (1<<26));
   
   (*((volatile unsigned long *) 0xE0060000)) |= (1<<channel);
   
   (*((volatile unsigned long *) 0xE0060000)) |= (1<<21); 
   
   (*((volatile unsigned long *) 0xE0060000)) |= (1<<24);
   do
   {
   switch(channel)	 
   {
   case 0:
		   i=(*((volatile unsigned long *) 0xE0060010)); 
		   break;
   case 1:
		   i=(*((volatile unsigned long *) 0xE0060014)); 
		   break;
   case 2:
		   i=(*((volatile unsigned long *) 0xE0060018)); 
		   break;
   case 3:
		   i=(*((volatile unsigned long *) 0xE006001C)); 
		   break;
   case 4:
		   i=(*((volatile unsigned long *) 0xE0060020)); 
		   break;
   case 5:
		   i=(*((volatile unsigned long *) 0xE0060024)); 
		   break;
   case 6:
		   i=(*((volatile unsigned long *) 0xE0060028)); 
		   break;
   case 7:
		   i=(*((volatile unsigned long *) 0xE006002C)); 
		   break;
   default:
   		   break;
   } 
   } 
   
   while (((*((volatile unsigned long *) 0xE0060004)) & 0x80000000) == 0);  
   
   return ((i >> 6) & 0x03FF);		   
}


