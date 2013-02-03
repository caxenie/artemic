/* sensor network and actuators specific interface 
   classes used to ensure communication through Comedi API
   with the robot hardware in real-time through the PCI NI-6024E
   data aquisition board */
   
#ifndef SENSOR_ACTUATOR_INTERFACE
#define SENSOR_ACTUATOR_INTERFACE

#include <comedilib.h>
#include "comedi.h"

#define SUBDEV_ANALOG_OUTPUT 1  
#define SUBDEV_ANALOG_INPUT 0 
#define SUBDEV_DIGITAL_IO   2 
#define SCALE 10.0		
#define PI 3.14159265
#define TO_NS 1000000000
#define COUNT_OFFSET 8388608; 
#define CH(a) (a)
#define SUBDEV_COUNTER 4	


// Sensor class 
// offers a generic interface to access the sensors
class Sensor{
	int state;
	double frequency;
	float value;
	
public:
	Sensor(){}
	virtual ~Sensor(){}
	virtual float get() {return value;}
	void enable(int newState) {state = newState;}
	virtual void control() = 0;
};

class AnalogSensor:public Sensor{
	int channel;
	int range, aref;
	comedi_t* comediDev;
	float physicalDataToVolts(unsigned int value, float scale){
		return (((float)value * 2.0 * scale) / 4095.0) - scale;
	}

public:
	AnalogSensor(int analogChannel, Comedi* newComediDev, long period = 0, int newRange = 0, int newAref = AREF_GROUND){
		comediDev = newComediDev->daqRef();
		channel = analogChannel;
		range = newRange;
		aref = newAref;
	}
	virtual ~AnalogSensor(){
		comediDev = NULL;
	}
	virtual float get(){
		lsampl_t physicalValue;
		comedi_data_read(comediDev, SUBDEV_ANALOG_INPUT, channel, range, aref, &physicalValue);
		return physicalDataToVolts(physicalValue, SCALE);
	}
	void control(){
	}
};

class DigitalSensor:public Sensor{
	int channel;
	comedi_t* comediDev;
	
public:
	DigitalSensor(int digitalChannel, Comedi* newComediDev){
		channel = digitalChannel;
		comediDev = newComediDev->daqRef();
		comedi_dio_config(comediDev, SUBDEV_DIGITAL_IO, channel, COMEDI_INPUT); 
	}
	virtual ~DigitalSensor(){
		comediDev = NULL;
	}
	float get(){
		unsigned int value;
		comedi_dio_read(comediDev, SUBDEV_DIGITAL_IO, channel, &value);
		return value;
	}
	void control(){
	}
};


// Actuator class 
// offers a generic interface to access the actuators
class Actuator{
	int state;
	double value, frequency;
	
public:
	Actuator(){}
	virtual ~Actuator(){}
	virtual void set(float newValue){value = newValue;}
	void enable(int newState) {state = newState;}
	virtual void control() = 0;
};

class AnalogActuator:public Actuator{
	int channel;
	int range, aref;
	comedi_t* comediDev;
	float vMax;
	unsigned int voltsToPhysicalData(float volts, float scale)
	{
		return (unsigned int)(((volts + scale) * 4095.0) / (2.0 * scale));
	}

public:
	AnalogActuator(int analogChannel, Comedi* newComediDev, float maxVoltage = 10.0, int newRange = 0, int newAref = AREF_GROUND){
		comediDev = newComediDev->daqRef();
		channel = analogChannel;
		range = newRange;
		aref = newAref;
		vMax = maxVoltage;
	}
	virtual ~AnalogActuator(){
		comediDev = NULL;
	}
	void set(float newValue){
		if(newValue > 10.0)
			newValue = 10.0;
		else if(newValue < -10.0)
			newValue = -10.0;
			
		comedi_data_write(comediDev, SUBDEV_ANALOG_OUTPUT, channel, range, aref, voltsToPhysicalData(newValue, SCALE));
	}
	void control(){
	}
};

class DigitalActuator:public Actuator{
	int channel;
	comedi_t* comediDev;
	
public:
	DigitalActuator(int digitalChannel, Comedi* newComediDev){
		channel = digitalChannel;
		comediDev = newComediDev->daqRef();
		comedi_dio_config(comediDev, SUBDEV_DIGITAL_IO, channel, COMEDI_OUTPUT); 	
	}
	virtual ~DigitalActuator(){
		comediDev = NULL;
	}
	void set(float newValue){
		unsigned int value = 0;
		if(newValue != 0)
			value = 1;
		comedi_dio_write(comediDev, SUBDEV_DIGITAL_IO, channel, value);
	}
	void control(){
	}
};

// Counter class 
// offers a generic interface to access the counter registers (encoder data)
class Counter{
	int channel;
	comedi_t* comediDev;
	
	
public:
	Counter(int canalCounter, Comedi* newComediDev){
		channel = canalCounter;
		comediDev = newComediDev->daqRef();
		reset();
	}

virtual void reset(){		
		ComediCounterReset(comediDev,SUBDEV_COUNTER,channel);
		ComediCounterSetZero(comediDev,SUBDEV_COUNTER,channel);
		ComediCounterSetSource(comediDev,SUBDEV_COUNTER,channel,GPCT_EXT_PIN);
		ComediCounterSetGate(comediDev,SUBDEV_COUNTER,channel,GPCT_NO_GATE);
		ComediCounterSetDirection(comediDev,SUBDEV_COUNTER,channel,GPCT_UP);
		ComediCounterSetOperation(comediDev,SUBDEV_COUNTER,channel,GPCT_SIMPLE_EVENT, 1);
		ComediCounterArm(comediDev,SUBDEV_COUNTER,channel);
	}
	
	
	virtual ~Counter(){
            comediDev=NULL;
		 }


     int ComediCounterReset(comedi_t *dev, int subdev, int channel){
	    comedi_insn insn;
	    lsampl_t params[]= { GPCT_RESET };  
	    insn.insn= INSN_CONFIG;   
	    insn.n= 1;                
	    insn.data= params;        
	    insn.subdev= subdev;     
	    insn.chanspec= CH(channel); 
	    return comedi_do_insn(dev, &insn);
	}  

	int ComediCounterSetZero(comedi_t *dev, int subdev, int channel){
		comedi_insn insn;
		lsampl_t params[]= {(long)pow(2.0,23.0)};    
	        insn.insn = INSN_WRITE;
	        insn.n = 1;
	        insn.data = params;
	        insn.subdev = subdev;
	        insn.chanspec = CR_PACK (channel, 0, 0 );
	        return comedi_do_insn (dev,&insn);
        }


	int ComediCounterSetSource(comedi_t *dev, int subdev, int channel, int SrcType){
	    comedi_insn insn;
	    lsampl_t params[]= { GPCT_SET_SOURCE, SrcType };
		insn.insn= INSN_CONFIG;   
	    insn.n= 2;                
	    insn.data= params;        
	    insn.subdev= subdev;      
	    insn.chanspec= CH(channel);  
	    return comedi_do_insn(dev, &insn);
	}  

	int ComediCounterSetGate(comedi_t *dev, int subdev, int channel, int GateType){
	    comedi_insn insn;
	    lsampl_t params[]= { GPCT_SET_GATE, GateType };
	    insn.insn= INSN_CONFIG;  
	    insn.n= 2;                
	    insn.data= params;       
	    insn.subdev= subdev;      
	    insn.chanspec= CH(channel);   
	    return comedi_do_insn(dev, &insn);
	} 

	int ComediCounterSetDirection(comedi_t *dev, int subdev, int channel, int Direction){
	    comedi_insn insn;
	    lsampl_t params[]= { GPCT_SET_DIRECTION, Direction };
	    insn.insn= INSN_CONFIG;  
	    insn.n= 2;                
	    insn.data= params;       
	    insn.subdev= subdev;      
	    insn.chanspec= CH(channel);   
	    return comedi_do_insn(dev, &insn);
	} 

	int ComediCounterSetOperation(comedi_t *dev, int subdev, int channel, int Operation, int OptParam){
	    comedi_insn insn;
	    lsampl_t params[]= { GPCT_SET_OPERATION, Operation, OptParam };
	    insn.insn= INSN_CONFIG;   
	    insn.n= OptParam == -1 ? 2 : 3; 
	    insn.data= params;       
	    insn.subdev= subdev;      
	    insn.chanspec= CH(channel);   
	    return comedi_do_insn(dev, &insn);
	} 

	int ComediCounterArm(comedi_t *dev, int subdev, int channel){
	    comedi_insn insn;
	    lsampl_t params[]= { GPCT_ARM };  
	    insn.insn= INSN_CONFIG;  
	    insn.n= 1;                
	    insn.data= params;       
	    insn.subdev= subdev;     
	    insn.chanspec= CH(channel); 
	    return comedi_do_insn(dev, &insn);
	} 

	int ComediCounterDisarm(comedi_t *dev, int subdev, int channel){
	    comedi_insn insn;
	    lsampl_t params[]= { GPCT_DISARM };  
	    insn.insn= INSN_CONFIG;   
	    insn.n= 1;                
	    insn.data= params;       
	    insn.subdev= subdev;      
	    insn.chanspec= CH(channel); 

	    return comedi_do_insn(dev, &insn);
	} 

	 lsampl_t ComediCounterRead(comedi_t *dev, int subdev, int channel)
	  {
		comedi_insn insn;
		lsampl_t value= 0;
		insn.insn= INSN_READ;    
		insn.n= 1;             
		insn.data= &value;      
		insn.subdev= subdev;    
		insn.chanspec= CH(channel);   
		if (comedi_do_insn(dev, &insn) < 0)
		printf("[Attention!] comedi_do_insn failed.\n ComediCounterRead: returned value is not valid.\n");
		return value;
	} 
	
	long getCount(){

		int read_value;
		int subdevice= SUBDEV_COUNTER;
		read_value = ComediCounterRead(comediDev,subdevice,channel);
		return (long)read_value - COUNT_OFFSET;

	} 
};

#endif
