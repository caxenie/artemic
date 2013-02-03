/* 
   Application entry - point
   the robot appplication starts waiting for commands from the client 
   */
   
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "system.h"
#include "system_phases.h"

void force_unload(int sig);// used to catch Ctrl+C when running out of control :)

int main(){

	(void)signal(SIGINT,force_unload);
	
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
		
	return 0;

}

void force_unload(int sig){

		pwm1->set(0.0);
		pwm2->set(0.0);
		rel_pow->set(1.0);
		system("rmmod kcomedilib");
		system("rmmod ni_pcimio");
		system("rmmod 8255");
		system("rmmod comedi_fc");
		system("rmmod comedi");
		system("rmmod rtai_shm");
		system("rmmod rtai_sem");
		system("rmmod rtai_lxrt");
		system("rmmod rtai_ksched");
		system("rmmod rtai_hal");
		(void)signal(SIGINT,SIG_DFL);
		cout<<" modules forced to unload ! \n";

}
