// comedi specific init, open device, get daq refs
#include <comedilib.h>

#ifndef COMEDI_INITIALIZATION
#define COMEDI_INITIALIZATION

class Comedi{
	comedi_t* comediDev;
public:
	Comedi(){
	}
	int open(){
		comediDev = comedi_open("/dev/comedi0");
		if(comediDev == NULL)
			return -1;
		return 0;	
	}
	int open(const char *dispPath){
		comediDev = comedi_open(dispPath);
		if(comediDev == NULL)
			return -1;
		return 0;	
	}
	comedi_t *daqRef(){
		return this->comediDev;
	}		
	int close(){
		return comedi_close(comediDev);
	}
};
#endif
