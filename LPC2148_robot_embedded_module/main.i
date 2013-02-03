#line 1 "main.c"



 
#line 1 "C:\\Program Files\\Keil\\ARM\\RV31\\INC\\math.h"




 





 












 







 










#line 52 "C:\\Program Files\\Keil\\ARM\\RV31\\INC\\math.h"












 
#line 73 "C:\\Program Files\\Keil\\ARM\\RV31\\INC\\math.h"











 





extern __softfp unsigned __ARM_dcmp4(double  , double  );
extern __softfp unsigned __ARM_fcmp4(float  , float  );
    




 

extern __declspec(__nothrow) __softfp int __ARM_fpclassifyf(float  );
extern __declspec(__nothrow) __softfp int __ARM_fpclassify(double  );
     
     

__inline __declspec(__nothrow) __softfp int __ARM_isfinitef(float __x)
{
    return (((*(unsigned *)&(__x)) >> 23) & 0xff) != 0xff;
}
__inline __declspec(__nothrow) __softfp int __ARM_isfinite(double __x)
{
    return (((*(1 + (unsigned *)&(__x))) >> 20) & 0x7ff) != 0x7ff;
}
     
     

__inline __declspec(__nothrow) __softfp int __ARM_isinff(float __x)
{
    return ((*(unsigned *)&(__x)) << 1) == 0xff000000;
}
__inline __declspec(__nothrow) __softfp int __ARM_isinf(double __x)
{
    return (((*(1 + (unsigned *)&(__x))) << 1) == 0xffe00000) && ((*(unsigned *)&(__x)) == 0);
}
     
     

__inline __declspec(__nothrow) __softfp int __ARM_islessgreaterf(float __x, float __y)
{
    unsigned __f = __ARM_fcmp4(__x, __y) >> 28;
    return (__f == 8) || (__f == 2);  
}
__inline __declspec(__nothrow) __softfp int __ARM_islessgreater(double __x, double __y)
{
    unsigned __f = __ARM_dcmp4(__x, __y) >> 28;
    return (__f == 8) || (__f == 2);  
}
    


 

__inline __declspec(__nothrow) __softfp int __ARM_isnanf(float __x)
{
    return (0x7f800000 - ((*(unsigned *)&(__x)) & 0x7fffffff)) >> 31;
}
__inline __declspec(__nothrow) __softfp int __ARM_isnan(double __x)
{
    unsigned __xf = (*(1 + (unsigned *)&(__x))) | (((*(unsigned *)&(__x)) == 0) ? 0 : 1);
    return (0x7ff00000 - (__xf & 0x7fffffff)) >> 31;
}
     
     

__inline __declspec(__nothrow) __softfp int __ARM_isnormalf(float __x)
{
    unsigned __xe = ((*(unsigned *)&(__x)) >> 23) & 0xff;
    return (__xe != 0xff) && (__xe != 0);
}
__inline __declspec(__nothrow) __softfp int __ARM_isnormal(double __x)
{
    unsigned __xe = ((*(1 + (unsigned *)&(__x))) >> 20) & 0x7ff;
    return (__xe != 0x7ff) && (__xe != 0);
}
     
     

__inline __declspec(__nothrow) __softfp int __ARM_signbitf(float __x)
{
    return (*(unsigned *)&(__x)) >> 31;
}
__inline __declspec(__nothrow) __softfp int __ARM_signbit(double __x)
{
    return (*(1 + (unsigned *)&(__x))) >> 31;
}
     
     








#line 191 "C:\\Program Files\\Keil\\ARM\\RV31\\INC\\math.h"



   
  typedef float float_t;
  typedef double double_t;
#line 206 "C:\\Program Files\\Keil\\ARM\\RV31\\INC\\math.h"







extern __declspec(__nothrow) double acos(double  );
    
    
    
extern __declspec(__nothrow) double asin(double  );
    
    
    
    

extern __declspec(__nothrow) __pure double atan(double  );
    
    

extern __declspec(__nothrow) double atan2(double  , double  );
    
    
    
    

extern __declspec(__nothrow) double cos(double  );
    
    
    
    
extern __declspec(__nothrow) double sin(double  );
    
    
    
    

extern void __use_accurate_range_reduction(void);
    
    

extern __declspec(__nothrow) double tan(double  );
    
    
    
    

extern __declspec(__nothrow) double cosh(double  );
    
    
    
    
extern __declspec(__nothrow) double sinh(double  );
    
    
    
    
    

extern __declspec(__nothrow) __pure double tanh(double  );
    
    

extern __declspec(__nothrow) double exp(double  );
    
    
    
    
    

extern __declspec(__nothrow) double frexp(double  , int *  );
    
    
    
    
    
    

extern __declspec(__nothrow) double ldexp(double  , int  );
    
    
    
    
extern __declspec(__nothrow) double log(double  );
    
    
    
    
    
extern __declspec(__nothrow) double log10(double  );
    
    
    
extern __declspec(__nothrow) double modf(double  , double *  );
    
    
    
    

extern __declspec(__nothrow) double pow(double  , double  );
    
    
    
    
    
    
extern __declspec(__nothrow) double sqrt(double  );
    
    
    
#line 326 "C:\\Program Files\\Keil\\ARM\\RV31\\INC\\math.h"
    __inline double _sqrt(double __x) { return sqrt(__x); }
    __inline float _sqrtf(float __x) { return (float)sqrt(__x); }


extern __declspec(__nothrow) __pure double ceil(double  );
    
    
extern __declspec(__nothrow) __pure double fabs(double  );
    
    

extern __declspec(__nothrow) __pure double floor(double  );
    
    

extern __declspec(__nothrow) double fmod(double  , double  );
    
    
    
    
    

    









 



extern __declspec(__nothrow) double acosh(double  );
    

 
extern __declspec(__nothrow) double asinh(double  );
    

 
extern __declspec(__nothrow) double atanh(double  );
    

 
extern __declspec(__nothrow) double cbrt(double  );
    

 
__inline __declspec(__nothrow) double copysign(double __x, double __y)
    

 
{
    (*(1 + (unsigned *)&(__x))) = ((*(1 + (unsigned *)&(__x))) & 0x7fffffff) | ((*(1 + (unsigned *)&(__y))) & 0x80000000);
    return __x;
}
__inline __declspec(__nothrow) float copysignf(float __x, float __y)
    

 
{
    (*(unsigned *)&(__x)) = ((*(unsigned *)&(__x)) & 0x7fffffff) | ((*(unsigned *)&(__y)) & 0x80000000);
    return __x;
}
extern __declspec(__nothrow) double erf(double  );
    

 
extern __declspec(__nothrow) double erfc(double  );
    

 
extern __declspec(__nothrow) double expm1(double  );
    

 



    

 






extern __declspec(__nothrow) double gamma(double  );
    


 
extern __declspec(__nothrow) double gamma_r(double  , int *  );
    


 
extern __declspec(__nothrow) double hypot(double  , double  );
    




 
extern __declspec(__nothrow) int ilogb(double  );
    

 
extern __declspec(__nothrow) int ilogbf(float  );
    

 
extern __declspec(__nothrow) int ilogbl(long double  );
    

 







    

 





    



 





    



 





    

 





    



 





    



 





    



 





    

 





    

 





    


 

extern __declspec(__nothrow) double j0(double  );
    


 
extern __declspec(__nothrow) double j1(double  );
    


 
extern __declspec(__nothrow) double jn(int  , double  );
    


 
extern __declspec(__nothrow) double lgamma (double  );
    


 
extern __declspec(__nothrow) double lgamma_r(double  , int *  );
    


 
extern __declspec(__nothrow) double log1p(double  );
    

 
extern __declspec(__nothrow) double logb(double  );
    

 
extern __declspec(__nothrow) float logbf(float  );
    

 
extern __declspec(__nothrow) long double logbl(long double  );
    

 
extern __declspec(__nothrow) double nextafter(double  , double  );
    


 
extern __declspec(__nothrow) float nextafterf(float  , float  );
    


 
extern __declspec(__nothrow) long double nextafterl(long double  , long double  );
    


 
extern __declspec(__nothrow) double nexttoward(double  , long double  );
    


 
extern __declspec(__nothrow) float nexttowardf(float  , long double  );
    


 
extern __declspec(__nothrow) long double nexttowardl(long double  , long double  );
    


 
extern __declspec(__nothrow) double remainder(double  , double  );
    

 
extern __declspec(__nothrow) double rint(double  );
    

 

extern __declspec(__nothrow) double scalb(double  , double  );
    


 

extern __declspec(__nothrow) double scalbln(double  , long int  );
    

 
extern __declspec(__nothrow) float scalblnf(float  , long int  );
    

 
extern __declspec(__nothrow) long double scalblnl(long double  , long int  );
    

 
extern __declspec(__nothrow) double scalbn(double  , int  );
    

 
extern __declspec(__nothrow) float scalbnf(float  , int  );
    

 
extern __declspec(__nothrow) long double scalbnl(long double  , int  );
    

 




    

 
extern __declspec(__nothrow) double significand(double  );
    


 
extern __declspec(__nothrow) double y0(double  );
    


 
extern __declspec(__nothrow) double y1(double  );
    


 
extern __declspec(__nothrow) double yn(int  , double  );
    


 



 
extern __declspec(__nothrow) __pure float _fabsf(float);  
__inline __declspec(__nothrow) __pure float fabsf(float __f) { return _fabsf(__f); }
extern __declspec(__nothrow) float sinf(float  );
extern __declspec(__nothrow) float cosf(float  );
extern __declspec(__nothrow) float tanf(float  );
extern __declspec(__nothrow) float acosf(float  );
extern __declspec(__nothrow) float asinf(float  );
extern __declspec(__nothrow) float atanf(float  );
extern __declspec(__nothrow) float atan2f(float  , float  );
extern __declspec(__nothrow) float sinhf(float  );
extern __declspec(__nothrow) float coshf(float  );
extern __declspec(__nothrow) float tanhf(float  );
extern __declspec(__nothrow) float expf(float  );
extern __declspec(__nothrow) float logf(float  );
extern __declspec(__nothrow) float log10f(float  );
extern __declspec(__nothrow) float powf(float  , float  );
extern __declspec(__nothrow) float sqrtf(float  );
extern __declspec(__nothrow) float ldexpf(float  , int  );
extern __declspec(__nothrow) float frexpf(float  , int *  );
extern __declspec(__nothrow) __pure float ceilf(float  );
extern __declspec(__nothrow) __pure float floorf(float  );
extern __declspec(__nothrow) float fmodf(float  , float  );
extern __declspec(__nothrow) float modff(float  , float *  );

 
 













 
__declspec(__nothrow) long double acosl(long double );
__declspec(__nothrow) long double asinl(long double );
__declspec(__nothrow) long double atanl(long double );
__declspec(__nothrow) long double atan2l(long double , long double );
__declspec(__nothrow) long double ceill(long double );
__declspec(__nothrow) long double cosl(long double );
__declspec(__nothrow) long double coshl(long double );
__declspec(__nothrow) long double expl(long double );
__declspec(__nothrow) long double fabsl(long double );
__declspec(__nothrow) long double floorl(long double );
__declspec(__nothrow) long double fmodl(long double , long double );
__declspec(__nothrow) long double frexpl(long double , int* );
__declspec(__nothrow) long double ldexpl(long double , int );
__declspec(__nothrow) long double logl(long double );
__declspec(__nothrow) long double log10l(long double );
__declspec(__nothrow) long double modfl(long double  , long double *  );
__declspec(__nothrow) long double powl(long double , long double );
__declspec(__nothrow) long double sinl(long double );
__declspec(__nothrow) long double sinhl(long double );
__declspec(__nothrow) long double sqrtl(long double );
__declspec(__nothrow) long double tanl(long double );
__declspec(__nothrow) long double tanhl(long double );

#line 839 "C:\\Program Files\\Keil\\ARM\\RV31\\INC\\math.h"





#line 928 "C:\\Program Files\\Keil\\ARM\\RV31\\INC\\math.h"







#line 981 "C:\\Program Files\\Keil\\ARM\\RV31\\INC\\math.h"





#line 1188 "C:\\Program Files\\Keil\\ARM\\RV31\\INC\\math.h"



 
#line 6 "main.c"
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

#line 7 "main.c"
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

#line 8 "main.c"
#line 1 "gps_odometry.h"

#line 3 "gps_odometry.h"

 

 
int parse_gps_packet(void);
 
int bytes2int(unsigned char, unsigned char);
 
void get_gps_packet_name(void);
 
int compare_strings(unsigned char buffer1[], unsigned char buffer2[]);
  
void get_latitude_degrees(void);
void get_latitude_minutes(void);
void get_latitude_seconds(void);
 
void get_longitude_degrees(void);
void get_longitude_minutes(void);
void get_longitude_seconds(void);
 
long convert_long(void);
long convert_lat(void);
 
void save_origin(void);
long get_y_position(void);
long get_x_position(void);


#line 9 "main.c"
#line 1 "sonar_interface.h"



 

#line 1 "global_adc_init.h"




 
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
#line 10 "main.c"
#line 1 "accelerometer_interface.h"




 

#line 1 "global_adc_init.h"




 
#line 7 "global_adc_init.h"

 
void init_adc(void);
 
unsigned int read_adc0(unsigned char);
unsigned int read_adc1(unsigned char);



#line 8 "accelerometer_interface.h"

 
unsigned int read_accel_x(void);
 
unsigned int read_accel_y(void);
#line 11 "main.c"

 

extern char rxbuf[256];   
extern char txbuf[256];	  
extern char rxdata;		  
extern int idx; 	      
extern int rbfull;        
int state; 			      
int cnt;				  
int rx_cnt;			  	  
int is_origin_set;	      
int is_valid_packet;	  
int is_gpgll;			  
int is_active;            
int s1val = 0, s2val = 0, s3val = 0, s4val = 0, s5val = 0; 
int i = 0; 
int div = 15; 

int main(void){
      
	 init_system();
   	  
	 init_uart0();
	 init_uart1();
	   
	 idx = 0;
	 rbfull = 0;
	 rx_cnt = 0;
	  
	 is_origin_set = 0;
	 state = 0;
	 is_valid_packet = 0;
	 
 
 init_adc();
 
 enable_sonar_chain();
 
  while(1){

#line 62 "main.c"
	    
	   i++;
	    
	   s1val += read_sonar(1);
	   s2val += read_sonar(2);
	   s3val += read_sonar(3);
	   s4val += read_sonar(4);
	   s5val += read_sonar(5);
	   if(i%div==0){
	    
	   putchar_uart0('>');
	   putchar_uart0(',');
	    	   
	   format_sonar_data_and_send(s1val/div);

	   format_sonar_data_and_send(s2val/div);
	   format_sonar_data_and_send(s3val/div);
	   format_sonar_data_and_send(s4val/div);
	   format_sonar_data_and_send(s5val/div);
	 
	   putchar_uart0(0x0D); 
	    
	   s1val = s2val = s3val = s4val = s5val = 0;
	   i = 0;
	   }

	 


 









 
  }	 
} 
