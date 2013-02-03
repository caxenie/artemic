
#include<lpc214x.h>
#include "gps_odometry.h"
#include <math.h>


char rxbuf[256]; 	// bufferul RX
char txbuf[256];	// bufferul TX 
char rxdata;		// caracterul primit in bufferul RX
int idx;     	// pointer catre elementul curent din buffer RX
int idxsav; 		// aux pentru retine pointer catre buffer RX
int rbfull;     // var care retine starea bufferului de receptie

unsigned char packet_name[6];	 				 // antet nume pachet
/* Pachetele alese pentru extragerea informatiei sunt GPGLL (Geographic Position Latitude/Longitude) */
unsigned char name1[6]={'G','P','G','L','L',0};	// necesar filtrarii (doar pachete cu acest header)

/* informatie GPS (NMEA) */
int latitude_degrees;
int latitude_minutes;
double latitude_seconds;

int longitude_degrees;
int longitude_minutes;
double longitude_seconds;

/* coordonatele in plan */
long x_origin, y_origin;
long current_x, current_y;

/* 
   Functii pentru extragerea informatiei de pozitie din datele GPS 
   necesare pentru calculul odometriei robotului si pentru a realiza 
   corectia traiectoriei robotului. 
*/

/* Functie care parseaza pachetele GPS (NMEA) receptionate */
int parse_gps_packet(void){
  int a;
  get_gps_packet_name();
  a=compare_strings(packet_name, name1);
    if(a==1)
    {
    get_latitude_degrees();
    get_latitude_minutes();
    get_latitude_seconds();
    get_longitude_degrees();
    get_longitude_minutes();
    get_longitude_seconds();
    return(1);
    }
  else return(0);
}


/* Functie de conversie a doi octeti in int */
int bytes2int(unsigned char ch1, unsigned char ch2){
   unsigned int val;
   ch1=ch1&0x0F;
   ch2=ch2&0x0F;
   val=ch1*10+ch2;;
   return(val);
}


/* Functie care preia numele (tipul) unui pachet */
void get_gps_packet_name(void){
  int i;
  for(i=1;i<6;i++) packet_name[i-1] = rxbuf[i];
  packet_name[i]=0;
}


/* Functie de comparare a doua stringuri util in filtrarea pachetelor receptionate */
int compare_strings(unsigned char buffer1[], unsigned char buffer2[]){
  int i;
  i=0;
  while(buffer1[i]!=0)
    {
    if(buffer1[i]!=buffer2[i]) return(0);
    else i++;
    }
  return(1);
}


/* Functii de extragere a informatiei de latitudine din pachetele GPS */ 
void get_latitude_degrees(void){
	latitude_degrees=bytes2int(rxbuf[7],rxbuf[8]);
}

void get_latitude_minutes(void){
	latitude_minutes=bytes2int(rxbuf[9],rxbuf[10]);
}

void get_latitude_seconds(void){
	int seconds;
	int decimals;
	
	seconds=bytes2int(rxbuf[12],rxbuf[13]);
	decimals=bytes2int(rxbuf[14],rxbuf[15]);
	latitude_seconds=(double)seconds+(double)decimals/100.0;
}


/* Functii de extragere a informatiei de longitudine din pachetele GPS */
void get_longitude_degrees(void){
	longitude_degrees=bytes2int(rxbuf[22],rxbuf[23]);
	if(rxbuf[21]=='1') longitude_degrees=longitude_degrees+100;
}

void get_longitude_minutes(void){
	longitude_minutes=bytes2int(rxbuf[24],rxbuf[25]);
}

void get_longitude_seconds(void){
	int seconds;
	int decimals;

	seconds=bytes2int(rxbuf[27],rxbuf[28]);
	decimals=bytes2int(rxbuf[29],rxbuf[30]);
	longitude_seconds=(double)seconds+(double)decimals/100.0;
}


/* Functii de conversie a informatiei de pozitie in plan din informatia GPS */
/* Conversie din informatia de latitudine */
long convert_lat(void){
   double temp;
   long i;

   temp=latitude_degrees*111132+(double)latitude_minutes*(111132.0/60.0);
   temp=temp+latitude_seconds*(111132.0/3600.0);
   i=floor(temp);
   return(i);
}


/* Conversie din informatia de longitudine */
long convert_long(void){
   double temp;
   long i;

   temp=longitude_degrees*78847+(double)longitude_minutes*(78847.0/60.0);
   temp=temp+longitude_seconds*(78847.0/3600.0);
   i=floor(temp);
   return(i);
}


/* Functie care seteaza o pozitie de referinta pentru miscarea in plan */
void save_origin(void){
   x_origin=convert_long();
   y_origin=convert_lat();
}

/* Functii care returneaza pozitia in plan */
long get_x_position(void){
 		 current_x=convert_long();
		 current_x=current_x-x_origin;
	 return current_x;
}

long get_y_position(void){
 		 current_y=convert_lat();
		 current_y=current_y-y_origin;
	 return current_y;
}


