//TEST FILE
// the robot appplication starts waiting for commands 
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "system.h"
#include "system_phases.h"

int main(){

	System *system =  new System();
	char c;
	
	system->load();
		
	cout << "Entering the Main() function ..." << endl;
	
	daq = new Comedi();
	daq->open();
	
	control = new TotalControl();
	
	scontrol = new RemoteControlServer(1500, control);
	
	scontrol->serving_requests();

	c=getchar();

	control->stop();
	
	scontrol->stop_serving();
	
	cout << "Ending the Main() function ..." << endl;
	
	daq->close();
	
		
	delete scontrol;
	delete control;
	delete daq;
	
	system->unload();
	
	delete system;
		
	return 0;}
