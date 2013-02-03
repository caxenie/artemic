
#include<lpc214x.h>

/* Prototipurile functiilor */

/* Functie care parseaza pachetele GPS (NMEA) receptionate */
int parse_gps_packet(void);
/* Functie de conversie a doi octeti in int */
int bytes2int(unsigned char, unsigned char);
/* Functie care preia numele (tipul) unui pachet */
void get_gps_packet_name(void);
/* Functie de comparare a doua stringuri util in filtrarea pachetelor receptionate */
int compare_strings(unsigned char buffer1[], unsigned char buffer2[]);
/* Functii de extragere a informatiei de latitudine din pachetele GPS */ 
void get_latitude_degrees(void);
void get_latitude_minutes(void);
void get_latitude_seconds(void);
/* Functii de extragere a informatiei de longitudine din pachetele GPS */
void get_longitude_degrees(void);
void get_longitude_minutes(void);
void get_longitude_seconds(void);
/* Functii de conversie a informatiei de pozitie in plan din informatia GPS */
long convert_long(void);
long convert_lat(void);
/* Functie care seteaza o pozitie de referinta pentru miscarea in plan */
void save_origin(void);
long get_y_position(void);
long get_x_position(void);


