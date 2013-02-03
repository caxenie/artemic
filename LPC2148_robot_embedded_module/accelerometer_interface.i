#line 1 "accelerometer_interface.c"





 

#line 1 "accelerometer_interface.h"




 

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



#line 8 "accelerometer_interface.h"

 
unsigned int read_accel_x(void);
 
unsigned int read_accel_y(void);
#line 9 "accelerometer_interface.c"






 

 
unsigned int read_accel_x(void){
     
	 unsigned int value;
	
	(*((volatile unsigned long *) 0xE002C004)) |= (1<<12);
	(*((volatile unsigned long *) 0xE002C004)) &=~(1<<13);
     value = read_adc1(7);
	 
	 return (value);
}

 
unsigned int read_accel_y(void){ 
     
	 unsigned int value;
	
	(*((volatile unsigned long *) 0xE002C004)) |= (1<<11);
	(*((volatile unsigned long *) 0xE002C004)) &=~(1<<10);
      value = read_adc1(6);
	 
	 return (value);
}
