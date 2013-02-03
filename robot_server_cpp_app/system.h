/* Real Time and Comedi specific modules management
 here the program loads the necessary modules 
 for real-time and data aquisition */
 
#ifndef LOAD_UNLOAD
#define LOAD_UNLOAD

#include <iostream>

using namespace std;
class System{
	
public:
	System(){
	};
	int load(){
		cout << "Loading RTAI modules: ..." << endl;
		cout << "	rtai_hal, rtai_ksched, rtai_lxrt, rtai_sem, rtai_shm" << endl;
		
		if(system("insmod /usr/realtime/modules/rtai_hal.o") == -1) return -1;
		if(system("insmod /usr/realtime/modules/rtai_ksched.o") == -1) return -1;
		if(system("insmod /usr/realtime/modules/rtai_lxrt.o") == -1) return -1;
		if(system("insmod /usr/realtime/modules/rtai_sem.o") == -1) return -1;
		if(system("insmod /usr/realtime/modules/rtai_shm.o") == -1) return -1;

		cout << "Loading the COMEDI modules: ..." << endl;
		cout << "	ni_pcimio, kcomedilib" <<endl;

		if(system("modprobe ni_pcimio") == -1) return -1;
		if(system("modprobe kcomedilib") == -1) return -1;
		if(system("comedi_config /dev/comedi0 ni_pcimio") == -1) return -1;
		return 0;
	}
	int unload(){
		cout << "Unloading modules: ..." << endl;
		cout << "	kcomedilib, ni_pcimio, 8255, comedi_fc, comedi," << endl;
		cout << "	rtai_comedi, rtai_lxrt, rtai_kscked, rtai_hal," << endl;
		cout << "	rtai_sem" << endl;

		if(system("rmmod kcomedilib") == -1) return -1;
		if(system("rmmod ni_pcimio") == -1) return -1;
		if(system("rmmod 8255") == -1) return -1;
		if(system("rmmod mite") == -1) return -1;	
		if(system("rmmod comedi_fc") == -1) return -1;
		if(system("rmmod comedi") == -1) return -1;

		if(system("rmmod rtai_shm") == -1) return -1;
		if(system("rmmod rtai_sem") == -1) return -1;

		if(system("rmmod rtai_lxrt") == -1) return -1;
		if(system("rmmod rtai_ksched") == -1) return -1;
		if(system("rmmod rtai_hal") == -1) return -1;
		return 0;
	}
};
#endif
