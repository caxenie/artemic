// template file to implement the control and 
// monitoring tasks in real time setting all
// the specific GRAFCET elements
#ifndef OPEN_GRAFCET_H
#define OPEN_GRAFCET_H

#include <iostream.h>
#include <stdio.h>
#include <fstream.h>
#include "grafcet.h"
#include "sensor_actuator.h"
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#include "matrix_ops.c"// used in matrix computations
#include "trajectory_planner_options.h"// set the desired trajectory 

#include "eta_buffer_nominal.h"// nominal behaviour of the robot

#define TO_NS 1000000000  // 1s
#define MAX_PARAMETERS 100 
#define MAX_PHASES 5 
#define MAX_SENSORS 5
#define MAX_DIGITAL_SENSORS 5
#define MAX_ANALOG_SENSORS 5
#define MAX_ACTUATORS 5
#define MAX_ANALOG_ACTUATORS 5
#define MAX_DIGITAL_ACTUATORS 5
#define MAX_COUNTERS 5
#define CYCLE11_PERIOD 50000000  // control cycle execution time 50ms
#define CYCLE12_PERIOD 50000000  // monitoring cycle execution time 50ms
#define PULSES_ENC 500
#define WHEEL_BASE 0.37 //m
#define RADS 57.2958 // for the degreees to rads conversion
#define TWOPI 2*PI
#define TS 0.05 // sampling time for the PI controllers
#define TS1 0.20 // sampling time the Sliding Mode control
#define WHEEL_RADIUS 0.08 
#define WHEEL_RADIUS_LEFT_FF 0.08
#define WHEEL_RADIUS_RIGHT_FF 0.08
#define WHEEL_RADIUS_LEFT_F1 0.08
#define WHEEL_RADIUS_RIGHT_F1 0.04
#define WHEEL_RADIUS_LEFT_F2 0.04
#define WHEEL_RADIUS_RIGHT_F2 0.08
#define WHEEL_RADIUS_LEFT_F3 0.08
#define WHEEL_RADIUS_RIGHT_F3 0.12
#define WHEEL_RADIUS_LEFT_F4 0.10
#define WHEEL_RADIUS_RIGHT_F4 0.08
#define sign(x) ((x)>=0?1:-1)
#define CH(a) (a)
#define SUBDEV_COUNTER 4

double tp[MAX_PARAMETERS];	

enum { START = 0,INJECT,GET_RECONF_STATE, F1, F2, F3, F4, TR, ERROR };

class Phase * tf[MAX_PHASES];	

enum { SERIAL_PHASE = 0, PARALLEL_PHASE };

class Actuator * ta[MAX_ACTUATORS];	

enum { ACA_1=0 , ACA_2 , ACD_1, ACD_2, ACD_3 };

class Sensor * ts[MAX_SENSORS];	

enum { SCA_1 = 0, SCA_2, SCD_1 , SCD_2, SCA_3};

class Counter * tc[MAX_COUNTERS];	

enum { CNT_1 = 0, CNT_2 };

////////////////////////////////////////////////////////////////						
//           DAQ BOARD, SENSORS & ACTUATORS
////////////////////////////////////////////////////////////////

Comedi *daq;

AnalogActuator *pwm_mot1; // PWM motor 1 (motor right) [Ao0-->22]
AnalogActuator *pwm_mot2; // PWM motor 2 (motor left)[Ao1-->21]

DigitalActuator *rel_pow ; // power relay [PO1-->17]
DigitalActuator *rel_sens_mot1 ; // sense relay motor 1 [PO2-->49]
DigitalActuator *rel_sens_mot2; // sense relay motor 2[PO5-->51]

AnalogSensor *current_mot1; // current feedback motor 1 [AI6-->25]
AnalogSensor *current_mot2; // current feedback motor 2 [AI13-->26]
AnalogSensor *battery_voltage; 

DigitalSensor *front_bumper ; // [PO4-->19]
DigitalSensor *rear_bumper; //[P00-->52]

Counter *encoder_mot1;// [CTR0-->37]
Counter *encoder_mot2;//[CTR1-->42]

comedi_t *Device= comedi_open("/dev/comedi0");

FILE *f,*f1,*f2,*f3,*f4; // for various logs

int reconf_ctrl;// set if reconf is activated

int finalize;// finalization condition for the diagnosis task

double *pEta = eta_buffer;// faster access to nominal values buffer

// multiplication factor choosed according the sampling period to convert
// seconds to samples
#define MULT_FACTOR 20 
// set the fault injection moment
// arbitrary choose the moment of the fault injection in the Java client 
#define INJECT_F1 20*(int)tp[F1]
#define INJECT_F2 20*(int)tp[F2] 
#define INJECT_F3 20*(int)tp[F3] 
#define INJECT_F4 20*(int)tp[F4] 

int chooser;// switch to select a certain trajectory
int activate_params;
double len;
double ref_profile[286][4];
////////////////////////////////////////////////////////////////
//                         ACTIONS
////////////////////////////////////////////////////////////////
class Aempty:public Action{
public:
	void debug(){
	
		cout << name << endl;
	}
	void run(){
		
	}
};

class Aerror11:public Action{
public:
	void debug(){
		cout << name << endl;
	}
	void run(){
		printf("An ERROR occured in cycle 11...\n");
		tp[ERROR] = 0; 
	}
};
	
class Aerror12:public Action{
public:
	void debug(){
		cout << name << endl;
	}
	void run(){
		printf("An ERROR occured in cycle 12...\n");
		tp[ERROR] = 0;
	}
};
////////////////////////////////////////////////////////////////
//                         CYCLES
////////////////////////////////////////////////////////////////

class Cycle11:public Cycle{
private:
	
	int i, cnt;
	float d;
	float t;
	int sleep_time ;
	long execute;
	long timer;

	// odometry specific variables 
	float sens;	
	long L_ticks, R_ticks;
	long lsamp, rsamp,u;
	long last_left, last_right;
	int inject_fault;
	int freeze_reconf_request;

	double omegal, omegar, v_current, w_current;

	double teta, teta_ant;
	double X_pos , Y_pos, X_pos_ant, Y_pos_ant;

	// sliding mode control specific variables

	double Q1, Q2, P1, P2; // sliding mode specific constants
	double k1, k2 ,k0 ; // sliding surfaces specific constants
	double x_e, y_e, teta_e, x_e_der, y_e_der, teta_e_der; //errors
	double x_des, y_des, teta_des, teta_des_ant, x_des_ant, y_des_ant; // desired values
	double v, w, v_der, w_der; // speed refereces and derivatives
	double w_l, w_r;
	float pwm_l, pwm_r; // voltage for pwm 
	double s1,s2; //sliding surfaces
	double num1, num2; // temps
	double v_c_der, w_c, v_c, v_c_ant;// control signal components

	// specific motor PI controller variables

	double err_left, err_left_ant, err_right, err_right_ant;
	double Kp_left, Ki_left, Kp_right, Ki_right;
	double cmd_left, cmd_left_ant, cmd_right, cmd_right_ant;
	double w_l_des, w_r_des; 



public:
		Cycle11(){
		set_name("C11");
		set_period(CYCLE11_PERIOD);
		
	}
	void initialize(){	
		// interactive trajectory choosing code
		chooser = (int)tp[TR];
		if(chooser==1){
		activate_params = activate_params1;
		len = len1;
		for(int ix = 1;ix<len;ix++){
				ref_profile[ix][1] = ref_profile1[ix][1];
				ref_profile[ix][2] = ref_profile1[ix][2];
				ref_profile[ix][3] = ref_profile1[ix][3];
				ref_profile[ix][4] = ref_profile1[ix][4];
		    }
		}
		if(chooser==2){
		activate_params = activate_params2;
		len = len2;
		for(int ix = 1;ix < len; ix++){
				ref_profile[ix][1] = ref_profile2[ix][1];
				ref_profile[ix][2] = ref_profile2[ix][2];
				ref_profile[ix][3] = ref_profile2[ix][3];
				ref_profile[ix][4] = ref_profile2[ix][4];
		    }
		}
		if(chooser==3){
		activate_params = activate_params3;
		len = len3;
		for(int ix = 1;ix<len;ix++){
				ref_profile[ix][1] = ref_profile3[ix][1];
				ref_profile[ix][2] = ref_profile3[ix][2];
				ref_profile[ix][3] = ref_profile3[ix][3];
				ref_profile[ix][4] = ref_profile3[ix][4];
		    }
		}
		if(chooser==4){
		activate_params = activate_params4;
		len = len4;
		for(int ix = 1;ix<len;ix++){
				ref_profile[ix][1] = ref_profile4[ix][1];
				ref_profile[ix][2] = ref_profile4[ix][2];
				ref_profile[ix][3] = ref_profile4[ix][3];
				ref_profile[ix][4] = ref_profile4[ix][4];
		    }
		}
	// odometry specific variables initialization
		u = 1;
		t = 0.0;
		i = 0;
		d = 0.1;
		cnt =0;
		execute = 0;
		timer = 0;
		inject_fault = (int)tp[INJECT];
		freeze_reconf_request = 0;
		reconf_ctrl = 0;
		sens = 0.0; // 0 forward and 1 for backward
		encoder_mot1->reset();
		encoder_mot2->reset();
		rel_pow->set(0.0);
		teta_des_ant = 0.0;
		x_des_ant = 0.0;
		y_des_ant = 0.0;
		L_ticks = 0;
		R_ticks = 0;
		lsamp = 0;
		rsamp = 0;
		last_left = 0;
		last_right = 0;
		teta_ant = 0.0;
		teta = 0.0;		
			
		X_pos = 0.0;
		Y_pos = 0.0;
		X_pos_ant = 0.0;
		Y_pos_ant = 0.0;

		omegal = 0.0;
		omegar = 0.0;

		w_current = 0.0;
		v_current = 0.0;

		//f = fopen("real_robot.txt","a+"); 
		
		if(activate_params==1){
		// sliding mode control specific variables initialization	
		// initialization values
		
		// values for Q, P, k...;
		Q1 = 0.05; // Q big ==> big oscilations on X 
		Q2 = 2.5; // for Y and teta
		P1 = 0.075; //0.075// P is forcing the error to converge to 0 on X 
		P2 = 0.075;// for Y and teta
		
		k1 = 0.75;// surface : error weight on X 
		k2 = 60; // surface : error weight on Y 
		k0 = (k2/(PI/3)); //surface weight on Theta
		}
		
		if(activate_params==2){
		// alternate sliding mode parameters 	
		// just for the simple line demo
		// values for Q, P, k...;
		Q1 = 0.05; 
		Q2 = 5.5;  
		P1 = 0.075;
		P2 = 5.75;
		
		k1 = 0.75; 
		k2 = 0.075;
		k0 = (k2/(PI/3)); 
		}
	
		if(activate_params==3){
		// just for simple circle demo
		// values for Q, P, k...;
		Q1 = 0.05; 
		Q2 = 1.5; 
		P1 = 0.075; 
		P2 = 0.75;
		k1 = 0.75; 
		k2 = 0.15;  
		k0 = (k2/(PI/2))/100; 
		}
		
		// specific motor PI controller init var

		cmd_left_ant = 0.0;
		cmd_right_ant = 0.0;
		err_left_ant = 0.0;
		err_right_ant = 0.0;

		// from MATLAB + experimental tuning
	
		Kp_left = 0.1309;
		Ki_left = 0.5142;

		Kp_right = 0.4572;
		Ki_right = 0.4628;
		
	}

	int final_cond(){

		if(i == len || tp[ERROR] == 1){
	
			finalize = 1;
			return 1;
		}
		
		return 0;	
	}
inline double saturation(double val){
	
	if(val < -1.0)
		return -1.0;
	else if(val > 1.0)
		return 1.0;
	else 
		return val;
}

inline void reset_parameters(){

		// add more variables if needed 
		// reset needed when entering new trajectory profile	
		encoder_mot1->reset();
		encoder_mot2->reset();

		teta_des = 0.0;
		x_des_ant = 0.0;
		y_des_ant = 0.0;
		
		L_ticks = 0;
		R_ticks = 0;
		lsamp = 0;
		rsamp = 0;
		last_left = 0;
		last_right = 0;

		teta_ant = 0.0;
		teta = 0.0;		
			
		X_pos = 0.0;
		Y_pos = 0.0;
		X_pos_ant = 0.0;
		Y_pos_ant = 0.0;

		omegal = 0.0;
		omegar = 0.0;

		w_current = 0.0;
		v_current = 0.0;

		cmd_left_ant = 0.0;
		cmd_right_ant = 0.0;
		err_left_ant = 0.0;
		err_right_ant = 0.0;

		teta_des_ant = 0.0;
		x_des_ant = 0.0;
		y_des_ant = 0.0;
		v_c_ant = 0.0;

		w_l_des = 0.0;
		w_r_des = 0.0;	

		// testing 

		y_e = 0.0;
		x_e = 0.0;
		teta_e = 0.0;
		cnt = 0;

}

void control(){

	// odometry system
	lsamp = encoder_mot2->getCount()/20; // divide by 20 for filtering max impulses
	rsamp = encoder_mot1->getCount();	
		
	L_ticks = lsamp - last_left;	
	R_ticks = rsamp - last_right;

	omegal = (L_ticks*TWOPI)/(PULSES_ENC*TS); // rad/s	
	omegar = (R_ticks*TWOPI)/(PULSES_ENC*TS); // rad/s

	// current values for speeds ( measured )

	switch(inject_fault){

		case 1:		printf("SM : fault 1 selected \n");
		           if(cnt>=INJECT_F1){
				printf("SM : fault 1 INJECTED \n");
				v_current = omegal*WHEEL_RADIUS_LEFT_F1/2 + omegar*WHEEL_RADIUS_RIGHT_F1/2; // linear speed m/s
				w_current = omegar*WHEEL_RADIUS_RIGHT_F1/WHEEL_BASE - omegal*WHEEL_RADIUS_LEFT_F1/WHEEL_BASE; // angular speed rad/s
				}
				// if not injected
				v_current = (omegal+omegar)*WHEEL_RADIUS/2; // linear speed m/s
				w_current = (omegar-omegal)*WHEEL_RADIUS/WHEEL_BASE; // angular speed rad/s
				break;
				
		case 2:		printf("SM : fault 2 selected \n");
			   if(cnt>=INJECT_F2){
				printf("SM : fault 2 INJECTED \n");
				v_current = omegal*WHEEL_RADIUS_LEFT_F2/2 + omegar*WHEEL_RADIUS_RIGHT_F2/2; // linear speed m/s
				w_current = omegar*WHEEL_RADIUS_RIGHT_F2/WHEEL_BASE - omegal*WHEEL_RADIUS_LEFT_F2/WHEEL_BASE; // angular speed rad/s
				}
				// if not injected
				v_current = (omegal+omegar)*WHEEL_RADIUS/2; // linear speed m/s
				w_current = (omegar-omegal)*WHEEL_RADIUS/WHEEL_BASE; // angular speed rad/s
				break;

		case 3:		printf("SM : fault 3 selected \n");
			    if(cnt>=INJECT_F3){
				
				if(u%2==0) {
				    printf("SM:fault 3 INJECTED \n");
			v_current = omegal*WHEEL_RADIUS_LEFT_F3/2 + omegar*WHEEL_RADIUS_RIGHT_F3/2; // linear speed m/s
				
			w_current = omegar*WHEEL_RADIUS_RIGHT_F3/WHEEL_BASE - omegal*WHEEL_RADIUS_LEFT_F3/WHEEL_BASE; // angular speed rad/s
				}
			}
				// if not injected
				v_current = (omegal+omegar)*WHEEL_RADIUS/2; // linear speed m/s
				w_current = (omegar-omegal)*WHEEL_RADIUS/WHEEL_BASE; // angular speed rad/s
				break;
				
		case 4:		printf("SM : fault 4 selected \n");	
			
		            if(cnt>=INJECT_F4){	
			
			       if(u%3==0){
				printf("SM:fault 4 INJECTED \n");
			v_current = omegal*WHEEL_RADIUS_LEFT_F4/2 + omegar*WHEEL_RADIUS_RIGHT_F4/2; // linear speed m/s

			w_current = omegar*WHEEL_RADIUS_RIGHT_F4/WHEEL_BASE - omegal*WHEEL_RADIUS_LEFT_F4/WHEEL_BASE; // angular speed rad/s
				}
			}
				// if not injected
				v_current = (omegal+omegar)*WHEEL_RADIUS/2; // linear speed m/s
				w_current = (omegar-omegal)*WHEEL_RADIUS/WHEEL_BASE; // angular speed rad/s
				break;

		default: 
				printf("SM : no fault injected \n");
				v_current = (omegal+omegar)*WHEEL_RADIUS/2; // linear speed m/s
				w_current = (omegar-omegal)*WHEEL_RADIUS/WHEEL_BASE; // angular speed rad/s
				

	}// end switch

	teta = teta_ant + TS*w_current;// heading in rad

	// heading angle limitation

	if(teta < -PI){

		teta += TWOPI;
	   }
	else if (teta > PI)
	   {
		teta -= TWOPI;
	    }
	else {
		teta = teta;
	      }	

	X_pos = X_pos_ant + TS*(v_current*cos(teta) - d*w_current*sin(teta)); //m

	Y_pos = Y_pos_ant + TS*(v_current*sin(teta) + d*w_current*cos(teta)); //m
		
	//fprintf(f,"%f %f\n",X_pos,Y_pos); 
	
	// The SLIDING MODE CONTROLLER

	// we have the reference given by a multidimensional array that contains the trajeectory given by a profile of
        // linear speed, linear acceleration, angular speed and acceleration

	// references
	v = ref_profile[i][0]; 		// linear speed profile
	v_der = ref_profile[i][1]; 	// linear acc profile
	w = ref_profile[i][2]; 		// angular speed profile
	w_der = ref_profile[i][3]; 	// angular acc profile

if(execute%4==0){
	
	// from the kinematic model of the robot we can extract the following 
	// current values of interest, in fact the desired values

	teta_des = (teta_des_ant + TS1*w);

	// heading angle limitation

	if(teta_des < -PI){

		teta_des += TWOPI;
	   }
	else if (teta_des > PI)
	   {
		teta_des -= TWOPI;
	    }
	else {
		teta_des = teta_des;
	      }	


	x_des = x_des_ant + TS1*(v*cos(teta_des_ant));

	y_des = y_des_ant + TS1*(v*sin(teta_des_ant));
	
	// error calculations from the setpoint to the actual robot

	x_e = (X_pos - x_des_ant)*cos(teta_des_ant) + (Y_pos - y_des_ant)*sin(teta_des_ant);
	y_e = -(X_pos - x_des_ant)*sin(teta_des_ant) + (Y_pos - y_des_ant)*cos(teta_des_ant);
	teta_e = teta - teta_des_ant;
	
	// heading angle limitation

	if(teta_e < -PI){

		teta_e += TWOPI;
	   }
	else if (teta_e > PI)
	   {
		teta_e -= TWOPI;
	    }
	else {
		teta_e = teta_e;
	      }	

	// error derivatives

	x_e_der = -v + v_current * cos(teta_e) + y_e*w;
	y_e_der = v_current * sin(teta_e) - x_e*w; 	
	teta_e_der =  w_current - w;

	if(y_e < 0)
		  {
		   k2 = -abs(k2);
		  }
	else if(y_e > 0)
		   {
		     k2 = abs(k2);
		    }

	// sliding surfaces

	s1 = x_e_der + k1*x_e;
	s2 = y_e_der + k2*y_e + k0*sign(y_e)*teta_e;

	// control signal components

	num1 = -Q1*s1 - P1*saturation(s1/0.5) - k1*x_e_der - w_der*y_e - w*y_e_der + v_der; // s1/0.15 for faster response
	num2 = -Q2*s2 - P2*saturation(s2/0.5) - k2*y_e_der + w_der*x_e + w*x_e_der;// s2/0.15 for faster response

	v_c_der = (num1 + v_current * teta_e_der*sin(teta_e))/cos(teta_e);
	
	v_c = v_c_ant + (TS1*v_c_der);

	if(v_c < 0)
		{
		v_c = 0.0;
		}

	w_c = (num2 - v_c_der*sin(teta_e))/(v_current * cos(teta_e) + k0*sign(y_e)) + w;

	
		// TEST FOR CONTROL RECONFIGURATION FLAG AND START RECONFIGURATION SPECIFIC ACTIONS

	switch(reconf_ctrl){

		case 1: 	if(freeze_reconf_request<=4){// to filter spurious and invalid reconf requests 
				printf("SM RECONF : a CLASS 1 FAULT OCCURED...start reconfiguring control...! \n ");
				//TODO IMPLEMENTATION adjust control signal to ensure further operation safely
				
				freeze_reconf_request++;
				}
				printf("...RECONFIGURING CONTROL...\n");
				break;
		case 2: 	if(freeze_reconf_request<=4){// filter spurious/invalid reconf requests
				printf("SM RECONF : a CLASS 2 FAULT OCCURED...start reconfiguring control...! \n");				
				//TODO IMPLEMENTATION adjust control signal to ensure further operation safely
				
				freeze_reconf_request++;
				}
				printf("...RECONFIGURING CONTROL...\n");
				break;
		default:	printf("SM RECONF : system is running properly...\n");
				printf("SM RECONF : no faults detected...\n");
				break;
	}

	// variables update

	teta_des_ant = teta_des;
	x_des_ant = x_des;
	y_des_ant = y_des;
	v_c_ant = v_c;	
	i++; // next point

} // END SM LOOP CONTROL SIGNAL GENERATION


	// PI controllers for the DC motors	

	// desired values for the PI loops obtained from the sliding mode output values

	w_l_des = (v_c - WHEEL_BASE*w_c/2)/WHEEL_RADIUS;
	w_r_des = (v_c + WHEEL_BASE*w_c/2)/WHEEL_RADIUS;

/*
	// left motor PI controller with Zero Order Hold discretization (ZOH)

	// error calculation
	
	err_left =  w_l_des - omegal ;	
	
	// control signal
	cmd_left = cmd_left_ant + Kp_left*err_left + (TS*Ki_left - Kp_left)*err_left_ant;
	
	// right motor PI controller with Zero Order Hold discretization
	
	// error 

	err_right = w_r_des - omegar;	

	// control signal
	cmd_right = cmd_right_ant + Kp_right*err_right + (TS*Ki_right - Kp_right)*err_right_ant;

	w_l = cmd_left;
	w_r = cmd_right;
*/

	// left motor PI controller with First Order Hold dicretization (FOH)

	// error calculation
	
	err_left =  w_l_des - omegal ;	
	
	// control signal
	cmd_left = cmd_left_ant + (Kp_left + Ki_left*TS)*err_left + (TS*Ki_left - Kp_left)*err_left_ant;
	
	// right motor PI controller with First Order Hold discretization
	
	// error 

	err_right = w_r_des - omegar;	

	// control signal
	cmd_right = cmd_right_ant + (Kp_right + Ki_right*TS)*err_right + (TS*Ki_right - Kp_right)*err_right_ant;

	w_l = cmd_left;
	w_r = cmd_right;

	// set the correspondence between the angular velocity and U_PWM
	// liniarized dependency U_PWM = f(omega)
	// U_pwm_l = f(wl);
	// U_pwm_r = f(wr);
	// from the experiments
	

	//left motor 
	
	if(w_l < 0.77){

		pwm_l = 1.75;
	   }
	else if (w_l > 0.77 & w_l < 1.18){
	
		pwm_l = 1.27 + 0.6*w_l;
	   }
	else if (w_l > 1.18 & w_l < 1.54){
	   
		pwm_l = 1.16 + 0.7*w_l;
	   }
	else if (w_l > 1.54 & w_l < 1.80){
	
		pwm_l = 0.79 + 0.94*w_l;
    	   }
	else if (w_l > 1.80 & w_l < 2.12){
	
		pwm_l = 1.07 + 0.78*w_l;
	  }
	else if (w_l > 2.12 & w_l < 2.45){

		pwm_l = 1.16 + 0.74*w_l;
	  }
	else if (w_l > 2.45 & w_l < 2.79){

		pwm_l = 1.18 + 0.73*w_l;
	  }
	else if (w_l > 2.79 & w_l < 3.18){

		pwm_l = 1.44 + 0.64*w_l;
	  }
	else if (w_l > 3.18 & w_l < 3.39){
	
		pwm_l = -0.319 + 1.199*w_l;
	  }
	else if (w_l > 3.39 & w_l < 3.60){

		pwm_l = -0.312 + 1.197*w_l;
	  }
	else if (w_l > 3.60 & w_l < 3.90){

		pwm_l = 1 + 0.83*w_l;
	  }
	else if (w_l > 3.90 & w_l < 4.15){

		pwm_l = 0.33 + 1*w_l;
	  }
	else if (w_l > 4.15 & w_l < 4.63){

		pwm_l = 2.34 + 0.52*w_l;
	  }
	else if (w_l > 4.63 & w_l < 4.8){

		pwm_l = -2.13 + 1.48*w_l;
	  }	
	else if (w_l > 4.8){

		pwm_l = 5.0;
	}

	// right motor 

	if(w_r < 0.65){

		pwm_r = 1.75;
	   }
	else if (w_r > 0.65 & w_r < 1.08){
	
		pwm_r = 1.37 + 0.57*w_r;
	   }
	else if (w_r > 1.08 & w_r < 1.50){
	   
		pwm_r = 1.34 + 0.59*w_r;
	   }
	else if (w_r > 1.50 & w_r < 1.81){
	
		pwm_r = 1.62 + 0.81*w_r;
    	   }
	else if (w_r > 1.81 & w_r < 2.25){
	
		pwm_r = 1.47 + 0.56*w_r;
	  }
	else if (w_r > 2.25 & w_r < 2.66){

		pwm_r = 1.37 + 0.6*w_r;
	  }
	else if (w_r > 2.66 & w_r < 2.99){

		pwm_r = 0.96 + 0.76*w_r;
	  }
	else if (w_r > 2.99 & w_r < 3.38){

		pwm_r = 1.34 + 0.63*w_r;
	  }
	else if (w_r > 3.38 & w_r < 3.71){

		pwm_r = 0.87 + 0.77*w_r;
	  }
	else if (w_r > 3.71 & w_r < 4.09){

		pwm_r = 1.35 + 0.64*w_r;
	  }
	else if (w_r > 4.09 & w_r < 4.42){

		pwm_r = 0.89 + 0.75*w_r;
	  }
	else if (w_r > 4.42 & w_r < 4.71){

		pwm_r = 0.35 + 0.87*w_r;
	  }
	else if (w_r > 4.71 & w_r < 5.22){

		pwm_r = 2.19 + 0.48*w_r;
	  }
	else if (w_r > 5.22 & w_r < 5.4){

		pwm_r = -2.61 + 1.4*w_r;
	  }
	else if (w_r > 5.4){

		pwm_r = 5.0;
	}

	// limitations for safety reasons

	if(pwm_r < 0.0)
	   {
		pwm_r = 0.0;
	   }
	if(pwm_r > 5.0)
	   {
		pwm_r = 5.0;
	   }
	if(pwm_l < 0.0 )
	   {
		pwm_l = 0.0;
	   }	
	if(pwm_l > 5.0)
	   {
		pwm_l = 5.0;
	
   }

// CONTROL TASK DEBUGGING printfs
//	printf("i =[%d] X_pos [%f]m , Y_pos [%f]m , teta [%f]rad \n",i,X_pos, Y_pos, teta);
//	printf("%f, %f, %f \n",x_des,y_des, teta_des);
//	printf("w_l_des[%f], w_l_mas[%f] \n",w_l_des,omegal);
//	printf("cmd_left [%f] \n",pwm_l);
//	printf("w_r_des[%f], w_r_mas[%f] \n",w_r_des,omegar);
//	printf("cmd_right [%f] \n",pwm_r);	
//	printf("x_e[%f],y_e[%f],teta_e[%f]\n",x_e,y_e,teta_e);
//	printf("y_des[%f],x_e[%f],y_e[%f]\n",y_des,x_e,y_e);	
		
/*
	fprintf(f,"i =[%d] X_pos [%f]m , Y_pos [%f]m , teta [%f]rad \n",i,X_pos, Y_pos, teta);
	fprintf(f,"i =[%d] x_des[%f], y_des[%f], teta_des[%f] \n",i,x_des,y_des, teta_des);
	fprintf(f,"w_l_des[%f], w_l_mas[%f] \n",w_l_des,omegal);
	fprintf(f,"cmd_left [%f] \n",pwm_l);
	fprintf(f,"w_r_des[%f], w_r_mas[%f] \n",w_r_des,omegar);
	fprintf(f,"cmd_right [%f] \n",pwm_r);	
	fprintf(f,"x_e[%f],y_e[%f],teta_e[%f]\n",x_e,y_e,teta_e);
*/

	
//	printf("%f %f\n",v_c,w_c);
	
	// set wheels direction

	rel_sens_mot1->set(sens);// 0 forward and 1 for backward
	rel_sens_mot2->set(sens);
		
	// set the actuator command

	pwm_mot1->set(pwm_r);
	pwm_mot2->set(pwm_l);

	// variables update

	X_pos_ant = X_pos;
	Y_pos_ant = Y_pos;	
	teta_ant = teta;
	last_left = lsamp;
	last_right = rsamp;
	err_right_ant = err_right;
	cmd_right_ant = cmd_right; 
	err_left_ant = err_left;
	cmd_left_ant = cmd_left;

   if((int)front_bumper->get() == 0 | (int)rear_bumper->get() == 0){

	// here is the emergency stop specific action
	end_ctrl();

	}
	cnt++;
	execute++;
	u++;
}  // end control function

void end_ctrl(){

		pwm_mot1->set(0.0);
		pwm_mot2->set(0.0);

		rel_pow->set(1.0);
		cnt = 0;
		i = 0;
		execute = 0;
		sens = 0.0; // 0 forward and 1 for backward
		reset_parameters();
	
		}

	void debug(){
		cout << name << endl;
	}
};


class Cycle12:public Cycle{
private:
	// odometry specific
	long L_ticks, R_ticks,u;
	int i;
	int num_states;
	double battery_status,d;
	long lsamp, rsamp;
	long last_left, last_right;
	double omegal, omegar, v_current, w_current;
	double teta, teta_ant, teta_des, x_des_ant, y_des_ant, teta_des_ant;
	double X_pos , Y_pos, X_pos_ant, Y_pos_ant;
	int inject_fault;
	// EKF specific
	int fault_type;
	int fault_flag;
	m_elem *Xk_prev0, *Xk_prev1, *Xk_prev2, *Xk_prev3, *Xk_prev4;
	double sigma_model0, sigma_model1, sigma_model2, sigma_model3, sigma_model4;
	m_elem *sum_eta0, *sum_eta1, *sum_eta2, *sum_eta3, *sum_eta4;
	int N ; // samples
	int k;//index
	int l;//second index for 3/3 counting
	int increment;
	int freeze_reconf_update;
	double sigma_meas;
	double sigma_x, sigma_y, sigma_teta;
	m_elem *Z;
        m_elem **Q0, **Q1, **Q2, **Q3, **Q4, **R0, **R1, **R2, **R3, **R4;
	m_elem **Phi0, **Phi1, **Phi2, **Phi3, **Phi4;
	m_elem **P10, **P11, **P12, **P13, **P14;
	m_elem **H0, **H1, **H2, **H3, **H4;
	m_elem **S0, **S1, **S2, **S3, **S4;
	m_elem **K0,**K1, **K2, **K3, **K4;
	m_elem **P0, **P1, **P2, **P3, **P4;
	m_elem *r0, *r1, *r2, *r3, *r4;
	m_elem *Xk0, *Xk1, *Xk2, *Xk3, *Xk4;
	m_elem *etaS0, *etaS1, *etaS2, *etaS3, *etaS4;
	m_elem *etaS_hat0, *etaS_hat1, *etaS_hat2, *etaS_hat3, *etaS_hat4;
	//temps
	m_elem **T1, **T2, **T3, **T4, **T5,**T6,**T7,**T8, **T10, *T14, **T15;
	m_elem *T11,  *T12, *T13, **T16, **T17, **T18, **T19;
	// for the moment if a single fault is detected the specific flags for detection
	// identification and reconfiguration should remain set 
	// TODO queueing mechanism and appearance time profile detection for multiple faults
	int freeze_diagnosis;
	long idx1, idx2;
	// offsets to implement thresholding based FDI
	double offsetx_min, offsetx_max;
   	double offsety_min, offsety_max;
   	double offsetteta_min, offsetteta_max;


public:
	Cycle12(){
		set_name("C12");
		set_period(CYCLE12_PERIOD);
		
	}
	void initialize(){	
		
		increment = 0;
		num_states = 3;
		inject_fault = (int)tp[INJECT];
		reconf_ctrl = 0;
		battery_status = 0;
		encoder_mot1->reset();
		encoder_mot2->reset();
		rel_pow->set(0.0);
		teta_des_ant = 0.0;
		teta_des  = 0.0;
		x_des_ant = 0.0;
		y_des_ant = 0.0;
		L_ticks = 0;
		R_ticks = 0;
		lsamp = 0;
		rsamp = 0;
		last_left = 0;
		last_right = 0;
		teta_ant = 0.0;
		teta = 0.0;	
		d = 0.1;	
		u = 1;
		i = 0;
		X_pos = 0.0;
		Y_pos = 0.0;
		X_pos_ant = 0.0;
		Y_pos_ant = 0.0;
		/*
		f = fopen("eta_buffer_nominal.h","a+");		
		f1= fopen("eta_buffer_EKF1.h","a+");
		f2= fopen("eta_buffer_EKF2.h","a+");
		f3= fopen("eta_buffer_EKF3.h","a+");
		f4= fopen("eta_buffer_EKF4.h","a+");
		*/
		idx1 = 0;
		idx2 = 0;
		omegal = 0.0;
		omegar = 0.0;

		w_current = 0.0;
		v_current = 0.0;
		
		// useful values for thresholding based fault detection

		 offsetx_min = -36.5;
		 offsetx_max = 36.5;
		 offsety_min = -36.5;
		 offsety_max = 36.5;
		 offsetteta_min = -36.5;
		 offsetteta_max = 36.5;

		fault_flag = 0;
		fault_type = 0;
		freeze_reconf_update = 0;
		l = 0;
		freeze_diagnosis = 0;
		Xk_prev0 = vect(1,num_states);
		Xk_prev1 = vect(1,num_states);
		Xk_prev2 = vect(1,num_states);
		Xk_prev3 = vect(1,num_states);
		Xk_prev4 = vect(1,num_states);

		sigma_model0 = 0.01;
		sigma_model1 = 0.01;
		sigma_model2 = 0.01;
		sigma_model3 = 0.01;
		sigma_model4 = 0.01;

		sum_eta0 = vect(1,num_states);
		sum_eta0[1] = 0;
		sum_eta0[2] = 0;
		sum_eta0[3] = 0;

		sum_eta1 = vect(1,num_states);
		sum_eta1[1] = 0;
		sum_eta1[2] = 0;
		sum_eta1[3] = 0;

		sum_eta2 = vect(1,num_states);
		sum_eta2[1] = 0;
		sum_eta2[2] = 0;
		sum_eta2[3] = 0;

		sum_eta3 = vect(1,num_states);
		sum_eta3[1] = 0;
		sum_eta3[2] = 0;
		sum_eta3[3] = 0;

		sum_eta4 = vect(1,num_states);
		sum_eta4[1] = 0;
		sum_eta4[2] = 0;
		sum_eta4[3] = 0;

		N = 323;
		k = 1;

		sigma_meas = 0.01;

		Z = vect(1,num_states);

		P0 = matrix(1,num_states,1,num_states);
		P0[1][1] = sigma_model0;
		P0[1][2] = 0;
		P0[1][3] = 0;
		P0[2][1] = 0;
		P0[2][2] = P0[1][1];
		P0[2][3] = 0;
		P0[3][1] = 0;
		P0[3][2] = 0;
		P0[3][3]  = P0[1][1];

		P1 = matrix(1,num_states,1,num_states);
		P1[1][1] = sigma_model1;
		P1[1][2] = 0;
		P1[1][3] = 0;
		P1[2][1] = 0;
		P1[2][2] = P1[1][1];
		P1[2][3] = 0;
		P1[3][1] = 0;
		P1[3][2] = 0;
		P1[3][3]  = P1[1][1];

		P2 = matrix(1,num_states,1,num_states);
		P2[1][1] = sigma_model2;
		P2[1][2] = 0;
		P2[1][3] = 0;
		P2[2][1] = 0;
		P2[2][2] = P2[1][1];
		P2[2][3] = 0; 
		P2[3][1] = 0;
		P2[3][2] = 0;
		P2[3][3]  = P2[1][1];

		P3 = matrix(1,num_states,1,num_states);
		P3[1][1] = sigma_model3;
		P3[1][2] = 0;
		P3[1][3] = 0;
		P3[2][1] = 0;
		P3[2][2] = P3[1][1];
		P3[2][3] = 0;
		P3[3][1] = 0;
		P3[3][2] = 0;
		P3[3][3]  = P3[1][1];

		P4 = matrix(1,num_states,1,num_states);
		P4[1][1] = sigma_model4;
		P4[1][2] = 0;
		P4[1][3] = 0;
		P4[2][1] = 0;
		P4[2][2] = P4[1][1];
		P4[2][3] = 0;
		P4[3][1] = 0;
		P4[3][2] = 0;
		P4[3][3]  = P4[1][1];

		Q0 = matrix(1,num_states,1,num_states);
		Q0[1][1] = sigma_x*sigma_x;
		Q0[1][2] = 0;
		Q0[1][3] = 0;
		Q0[2][1] = 0;
		Q0[2][2] = sigma_y*sigma_y;
		Q0[2][3] = 0;
		Q0[3][1] = 0;
		Q0[3][2] = 0;
		Q0[3][3] = sigma_teta*sigma_teta;

		Q1 = matrix(1,num_states,1,num_states);
		Q1[1][1] = sigma_x*sigma_x;
		Q1[1][2] = 0;
		Q1[1][3] = 0;
		Q1[2][1] = 0;
		Q1[2][2] = sigma_y*sigma_y;
		Q1[2][3] = 0;
		Q1[3][1] = 0;
		Q1[3][2] = 0;
		Q1[3][3] = sigma_teta*sigma_teta;

		Q2 = matrix(1,num_states,1,num_states);
		Q2[1][1] = sigma_x*sigma_x;
		Q2[1][2] = 0;
		Q2[1][3] = 0;
		Q2[2][1] = 0;
		Q2[2][2] = sigma_y*sigma_y;
		Q2[2][3] = 0;
		Q2[3][1] = 0;
		Q2[3][2] = 0;
		Q2[3][3] = sigma_teta*sigma_teta;


		Q3 = matrix(1,num_states,1,num_states);
		Q3[1][1] = sigma_x*sigma_x;
		Q3[1][2] = 0;
		Q3[1][3] = 0;
		Q3[2][1] = 0;
		Q3[2][2] = sigma_y*sigma_y;
		Q3[2][3] = 0;
		Q3[3][1] = 0;
		Q3[3][2] = 0;
		Q3[3][3] = sigma_teta*sigma_teta;

		Q4 = matrix(1,num_states,1,num_states);
		Q4[1][1] = sigma_x*sigma_x;
		Q4[1][2] = 0;
		Q4[1][3] = 0;
		Q4[2][1] = 0;
		Q4[2][2] = sigma_y*sigma_y;
		Q4[2][3] = 0;
		Q4[3][1] = 0;
		Q4[3][2] = 0;
		Q4[3][3] = sigma_teta*sigma_teta;

		R0 = matrix(1,num_states,1,num_states);
		R0[1][1] = sigma_meas;
		R0[1][2] = 0;
		R0[1][3] = 0;
		R0[2][1] = 0;
		R0[2][2] = sigma_meas;
		R0[2][3] = 0;
		R0[1][3] = 0;
		R0[2][3] = 0;
		R0[3][3] = sigma_meas;

		R1 = matrix(1,num_states,1,num_states);
		R2 = matrix(1,num_states,1,num_states);
		R3 = matrix(1,num_states,1,num_states);
		R4 = matrix(1,num_states,1,num_states);

		mat_copy(R0,R1,num_states,num_states);
		mat_copy(R0,R2,num_states,num_states);
		mat_copy(R0,R3,num_states,num_states);
		mat_copy(R0,R4,num_states,num_states);

		Phi0 = matrix(1,num_states,1,num_states);
		Phi1 = matrix(1,num_states,1,num_states);
		Phi2 = matrix(1,num_states,1,num_states);
		Phi3 = matrix(1,num_states,1,num_states);
		Phi4 = matrix(1,num_states,1,num_states);

		P10 = matrix(1,num_states,1,num_states);
		P11 = matrix(1,num_states,1,num_states);
		P12 = matrix(1,num_states,1,num_states);
		P13 = matrix(1,num_states,1,num_states);
		P14 = matrix(1,num_states,1,num_states);

		H0 = matrix(1,num_states,1,num_states);
		H0[1][1] = 1;
		H0[1][2] = 0;
		H0[1][3] = 0;
		H0[2][1] = 0;
		H0[2][2] = 1;
		H0[2][3] = 0;
		H0[3][1] = 0;
		H0[3][2] = 0;
		H0[3][3] = 1;

		H1 = matrix(1,num_states,1,num_states);
		H2 = matrix(1,num_states,1,num_states);
		H3 = matrix(1,num_states,1,num_states);
		H4 = matrix(1,num_states,1,num_states);

		mat_copy(H0,H1,num_states,num_states);
		mat_copy(H0,H2,num_states,num_states);
		mat_copy(H0,H3,num_states,num_states);
		mat_copy(H0,H4,num_states,num_states);

		S0 = matrix(1,num_states,1,num_states);
		S1 = matrix(1,num_states,1,num_states);
		S2 = matrix(1,num_states,1,num_states);
		S3 = matrix(1,num_states,1,num_states);
		S4 = matrix(1,num_states,1,num_states);
	
		K0 = matrix(1,num_states,1,num_states);
		K1 = matrix(1,num_states,1,num_states);
		K2 = matrix(1,num_states,1,num_states);
		K3 = matrix(1,num_states,1,num_states);
		K4 = matrix(1,num_states,1,num_states);

		r0 = vect(1,num_states);
		r1 = vect(1,num_states);
		r2 = vect(1,num_states);
		r3 = vect(1,num_states);
		r4 = vect(1,num_states);

		Xk0 = vect(1,num_states);
		Xk1 = vect(1,num_states);
		Xk2 = vect(1,num_states);
		Xk3 = vect(1,num_states);
		Xk4 = vect(1,num_states);

		etaS0 = vect(1,num_states);
		etaS1 = vect(1,num_states);
		etaS2 = vect(1,num_states);
		etaS3 = vect(1,num_states);
		etaS4 = vect(1,num_states);

		etaS_hat0 = vect(1,num_states);
		etaS_hat1 = vect(1,num_states);
		etaS_hat2 = vect(1,num_states);
		etaS_hat3 = vect(1,num_states);
		etaS_hat4 = vect(1,num_states);

		// temps

			T1 = matrix(1,num_states,1,num_states);
			T2 = matrix(1,num_states,1,num_states);
			T3 = matrix(1,num_states,1,num_states);
			T4 = matrix(1,num_states,1,num_states);
			T5 = matrix(1,num_states,1,num_states);
			T6 = matrix(1,num_states,1,num_states);
			T7 = matrix(1,num_states,1,num_states);
			T8 = matrix(1,num_states,1,num_states);
			T10 = matrix(1,num_states,1,num_states);
			T14 = vect(1,num_states);
			T11 = vect(1,num_states);
			T12 = vect(1,num_states);
			T13 = vect(1,num_states);
			T15 = matrix(1,num_states,1,num_states);
			T16 = matrix(1,num_states,1,num_states);
			T17 = matrix(1,num_states,1,num_states);
			T18 = matrix(1,num_states,1,num_states);
			T19 = matrix(1,num_states,1,num_states);
	
	}
	
int final_cond(){
		
		return (finalize==1 || (int)front_bumper->get() == 0 || (int)rear_bumper->get() == 0);
	}
	
	inline void reset_parameters(){


		encoder_mot1->reset();
		encoder_mot2->reset();

		teta_des = 0.0;
		x_des_ant = 0.0;
		y_des_ant = 0.0;

		L_ticks = 0;
		R_ticks = 0;
		lsamp = 0;
		rsamp = 0;
		last_left = 0;
		last_right = 0;

		teta_ant = 0.0;
		teta = 0.0;		
			
		X_pos = 0.0;
		Y_pos = 0.0;
		X_pos_ant = 0.0;
		Y_pos_ant = 0.0;

		omegal = 0.0;
		omegar = 0.0;

		w_current = 0.0;
		v_current = 0.0;
		increment = 0;
		sigma_x = 0.1;
		sigma_y = 0.1;
		sigma_teta = 0.1;
		
	}
	
// false alarm filtering used in fault detection module
		
inline int filter_false_alarms()
		{
		
					
	if((inject_fault==1.0 && increment>=INJECT_F1) || (inject_fault==2.0 && increment>=INJECT_F2) || (inject_fault==3.0 &&  increment>=INJECT_F3) || (inject_fault==4.0 && increment>=INJECT_F4)) 
		return 1;
	
		return 0;
	}

void control(){

	// ODOMETRY COMPUTATION USED AS INPUT FOR THE EKF BANC USED FOR FDI

	lsamp = encoder_mot2->getCount()/20; // divide by 20 for filtering max impulses
	rsamp = encoder_mot1->getCount();	
		
	L_ticks = lsamp - last_left;	
	R_ticks = rsamp - last_right;

	omegal = (L_ticks*TWOPI)/(PULSES_ENC*TS); // rad/s	
	omegar = (R_ticks*TWOPI)/(PULSES_ENC*TS); // rad/s

	// current values for speeds ( measured )
  
	
	switch(inject_fault){

		case 1:	printf("DIAG : fault 1 selected \n");
			if(increment>=INJECT_F1){
			printf("DIAG : fault 1 INJECTED \n");
	v_current = omegal*WHEEL_RADIUS_LEFT_F1/2 + omegar*WHEEL_RADIUS_RIGHT_F1/2; // linear speed m/s
	w_current = omegar*WHEEL_RADIUS_RIGHT_F1/WHEEL_BASE - omegal*WHEEL_RADIUS_LEFT_F1/WHEEL_BASE; // angular speed rad/s
				}
				// until injection use default values (normal behaviour)
				v_current = (omegal+omegar)*WHEEL_RADIUS/2; // linear speed m/s
				w_current = (omegar-omegal)*WHEEL_RADIUS/WHEEL_BASE; // angular speed rad/s
				break;

				
		case 2:	printf("DIAG : fault 2 selected \n");
			if(increment>=INJECT_F2){
			printf("DIAG : fault 2 INJECTED \n");
	v_current = omegal*WHEEL_RADIUS_LEFT_F2/2 + omegar*WHEEL_RADIUS_RIGHT_F2/2; // linear speed m/s
	w_current = omegar*WHEEL_RADIUS_RIGHT_F2/WHEEL_BASE - omegal*WHEEL_RADIUS_LEFT_F2/WHEEL_BASE; // angular speed rad/s
				}
				// until injection use default values (normal behaviour)
				v_current = (omegal+omegar)*WHEEL_RADIUS/2; // linear speed m/s
				w_current = (omegar-omegal)*WHEEL_RADIUS/WHEEL_BASE; // angular speed rad/s
				break;

		case 3: printf("DIAG : fault 3 selected \n");
			if(increment>=INJECT_F3){			
			  if(u%2==0){	
				printf("DIAG : fault 3 INJECTED \n");
v_current = omegal*WHEEL_RADIUS_LEFT_F3/2 + omegar*WHEEL_RADIUS_RIGHT_F3/2; // linear speed m/s

w_current = omegar*WHEEL_RADIUS_RIGHT_F3/WHEEL_BASE - omegal*WHEEL_RADIUS_LEFT_F3/WHEEL_BASE; // angular speed rad/s
				}
			}	
				// until injection use default values (normal behaviour)
				v_current = (omegal+omegar)*WHEEL_RADIUS/2; // linear speed m/s
				w_current = (omegar-omegal)*WHEEL_RADIUS/WHEEL_BASE; // angular speed rad/s
				break;
				
		case 4:	printf("DIAG : fault 4 selected \n");
			if(increment>=INJECT_F4){
				if(u%3==0){
			printf("DIAG : fault 4 INJECTED \n");		
v_current = omegal*WHEEL_RADIUS_LEFT_F4/2 + omegar*WHEEL_RADIUS_RIGHT_F4/2; // linear speed m/s
				
w_current = omegar*WHEEL_RADIUS_RIGHT_F4/WHEEL_BASE - omegal*WHEEL_RADIUS_LEFT_F4/WHEEL_BASE; // angular speed rad/s
				}
			}
				// until injection use default values (normal behaviour)
				v_current = (omegal+omegar)*WHEEL_RADIUS/2; // linear speed m/s
				w_current = (omegar-omegal)*WHEEL_RADIUS/WHEEL_BASE; // angular speed rad/s
				break;

		default: 
				printf("DIAG : no faults injected \n");
				// normal behaviour
				v_current = (omegal+omegar)*WHEEL_RADIUS/2; // linear speed m/s
				w_current = (omegar-omegal)*WHEEL_RADIUS/WHEEL_BASE; // angular speed rad/s
				

	}

	teta = teta_ant + TS*w_current;// heading in rads

	// heading angle limitation

	if(teta < -PI){

		teta += TWOPI;
	   }
	else if (teta > PI)
	   {
		teta -= TWOPI;
	    }
	else {
		teta = teta;
	      }	

	X_pos = X_pos_ant + TS*(v_current*cos(teta) - d*w_current*sin(teta)); //m

	Y_pos = Y_pos_ant + TS*(v_current*sin(teta) + d*w_current*cos(teta)); //m


	// EKF FDI IMPLEMENTATION
	
	// masurement vect based on odometry system output
	Z[1] = X_pos + sigma_meas * rand();
	Z[2] = Y_pos + sigma_meas * rand();
	Z[3] = teta + sigma_meas * rand();


	// NOMINAL EKF FILTER IMPLEMENTATION [EKF0]
	
	// prediction
	
	Phi0[1][1] = 1;
	Phi0[1][2] = 0;
	Phi0[1][3] = -0.002*PI*(0.5*WHEEL_RADIUS_RIGHT_FF+0.5*WHEEL_RADIUS_LEFT_FF)*(rsamp+lsamp)*sin(teta+0.00333*PI*(0.5*WHEEL_RADIUS_RIGHT_FF+0.5*WHEEL_RADIUS_LEFT_FF)*(rsamp-lsamp));
	Phi0[2][1] = 0;
	Phi0[2][2] = 1;
	Phi0[2][3] = 0.002*PI*(0.5*WHEEL_RADIUS_RIGHT_FF+0.5*WHEEL_RADIUS_LEFT_FF)*(rsamp+lsamp)*cos(teta+0.00333*PI*(0.5*WHEEL_RADIUS_RIGHT_FF+0.5*WHEEL_RADIUS_LEFT_FF)*(rsamp-lsamp));
	Phi0[3][1] = 0;
	Phi0[3][2] = 0;
	Phi0[3][3] = 1;
	
	//P10 = Phi0*P0*Phi0' + Q0;
	
	 mat_mult(Phi0,P0,T1,num_states,num_states,num_states);
         mat_mult_transpose(T1,Phi0,T2,num_states,num_states,num_states);
	 mat_add(T2,Q0,P10,num_states,num_states);
	
	// correction
	 //S0 = H0*P10*H0' + R0;

	 mat_mult(H0,P10,T3,num_states,num_states,num_states);
     	 mat_mult_transpose(T3,H0,T4,num_states,num_states,num_states);
	 mat_add(T4,R0,S0,num_states,num_states);

	//K0 = P10*H0'*inv(S0);

	mat_mult_transpose(P10,H0,T5,num_states,num_states,num_states);
	take_inverse(S0,T6,num_states);
	mat_mult(T5,T6,K0,num_states,num_states,num_states);
	
	//P0 = P10 - K0*H0*P10;
	
	mat_mult(K0,H0,T7,num_states,num_states,num_states);
	mat_mult(T7,P10,T8,num_states,num_states,num_states);
	mat_sub(P10,T8,P0,num_states,num_states);

	//r0 = Z - H0*Phi0*Xk_prev0;

	mat_mult(H0,Phi0,T10,num_states,num_states,num_states);
	mat_mult_vect(T10,Xk_prev0,T11,num_states,num_states);
	vec_sub(Z,T11,r0,num_states);

	//Xk0 = Phi0*Xk_prev0 + K0*r0;

	mat_mult_vect(Phi0,Xk_prev0,T12,num_states,num_states);
	mat_mult_vect(K0,r0,T13,num_states,num_states);
	vec_add(T12,T13,Xk0,num_states);

	//etaS0 = inv(sqrt(S0))*r0;

	for(int i = 1;i<=num_states;i++)
		{
			for(int j = 1;j<=num_states;j++){

				S0[i][j] = pow(S0[i][j],0.5);
				
				if(isnan(S0[i][j])){
					
					S0[i][j] = 0.0;
				}
				
			}
		}

	
	take_inverse(S0,T15,num_states);
	
	mat_mult_vect(T15,r0,etaS0,num_states,num_states);

	// sum_eta0 = sum_eta0 + etaS0;

	vec_add(sum_eta0,etaS0,sum_eta0,num_states);

	// etaS_hat0  = 1/N*sum_eta0;

	for(int i = 1;i<=num_states;i++)
		{
			sum_eta0[i] = 0.003*sum_eta0[i];// 1/N = 1/323 = 0.003
		}
	
	vec_copy(sum_eta0,etaS_hat0,num_states);

	//fprintf(f,"%f,%f,%f,",etaS_hat0[1],etaS_hat0[2],etaS_hat0[3]);
	

	// RIGHT TIRE FLAT FAULT EKF FILTER IMPLEMENTATION [EKF1]
	
	// prediction
	
	Phi1[1][1] = 1;
	Phi1[1][2] = 0;
	Phi1[1][3] = -0.002*PI*(0.5*WHEEL_RADIUS_RIGHT_F1+0.5*WHEEL_RADIUS_LEFT_F1)*(rsamp+lsamp)*sin(teta+0.00333*PI*(0.5*WHEEL_RADIUS_RIGHT_F1+0.5*WHEEL_RADIUS_LEFT_F1)*(rsamp-lsamp));
	Phi1[2][1] = 0;
	Phi1[2][2] = 1;
	Phi1[2][3] = 0.002*PI*(0.5*WHEEL_RADIUS_RIGHT_F1+0.5*WHEEL_RADIUS_LEFT_F1)*(rsamp+lsamp)*cos(teta+0.00333*PI*(0.5*WHEEL_RADIUS_RIGHT_F1+0.5*WHEEL_RADIUS_LEFT_F1)*(rsamp-lsamp));
	Phi1[3][1] = 0;
	Phi1[3][2] = 0;
	Phi1[3][3] = 1;
	
	//P11 = Phi1*P1*Phi1' + Q1;

	 mat_mult(Phi1,P0,T1,num_states,num_states,num_states);
     	 mat_mult_transpose(T1,Phi1,T2,num_states,num_states,num_states);
	 mat_add(T2,Q1,P11,num_states,num_states);

 	// correction
	 //S1 = H1*P11*H1' + R1;

	 mat_mult(H1,P11,T3,num_states,num_states,num_states);
     mat_mult_transpose(T3,H1,T4,num_states,num_states,num_states);
	 mat_add(T4,R1,S1,num_states,num_states);

	//K1 = P11*H1'*inv(S1);

	mat_mult_transpose(P11,H1,T5,num_states,num_states,num_states);
	take_inverse(S1,T6,num_states);
	mat_mult(T5,T6,K1,num_states,num_states,num_states);

	//P1 = P11 - K1*H1*P11;
	
	mat_mult(K1,H1,T7,num_states,num_states,num_states);
	mat_mult(T7,P11,T8,num_states,num_states,num_states);
	mat_sub(P11,T8,P1,num_states,num_states);

	//r1 = Z - H1*Phi1*Xk_prev1;

	mat_mult(H1,Phi1,T10,num_states,num_states,num_states);
	mat_mult_vect(T10,Xk_prev1,T11,num_states,num_states);
	vec_sub(Z,T11,r1,num_states);

	//Xk1 = Phi1*Xk_prev1 + K1*r1;

	mat_mult_vect(Phi1,Xk_prev1,T12,num_states,num_states);
	mat_mult_vect(K1,r1,T13,num_states,num_states);
	vec_add(T12,T13,Xk1,num_states);

	//etaS1 = inv(sqrt(S1))*r1;

	for(int i = 1;i<=num_states;i++)
		{
			for(int j = 1;j<num_states;j++){
			
				S1[i][j] = pow(S1[i][j],0.5);
				
				if(isnan(S1[i][j])){
					
					S1[i][j] = 0.0;
				}
	
			}
		}
	take_inverse(S1,T16,num_states);
	mat_mult_vect(T16,r1,etaS1,num_states,num_states);


	// sum_eta1 = sum_eta1 + etaS1;

	vec_add(sum_eta1,etaS1,sum_eta1,num_states);

	// etaS_hat1  = 1/N*sum_eta1;

	for(int i = 1;i<=num_states;i++)
		{
			sum_eta1[i] = 0.003*sum_eta1[i];
		}

	vec_copy(sum_eta1,etaS_hat1,num_states);

	//fprintf(f1,"%f,%f,%f,",etaS_hat1[1],etaS_hat1[2],etaS_hat1[3]);

	// LEFT TIRE FLAT EKF FILTER IMPLEMENTATION [EKF2]
	
	// prediction
	
	Phi2[1][1] = 1;
	Phi2[1][2] = 0;
	Phi2[1][3] = -0.002*PI*(0.5*WHEEL_RADIUS_RIGHT_F2+0.5*WHEEL_RADIUS_LEFT_F2)*(rsamp+lsamp)*sin(teta+0.00333*PI*(0.5*WHEEL_RADIUS_RIGHT_F2+0.5*WHEEL_RADIUS_LEFT_F2)*(rsamp-lsamp));
	Phi2[2][1] = 0;
	Phi2[2][2] = 1;
	Phi2[2][3] = 0.002*PI*(0.5*WHEEL_RADIUS_RIGHT_F2+0.5*WHEEL_RADIUS_LEFT_F2)*(rsamp+lsamp)*cos(teta+0.00333*PI*(0.5*WHEEL_RADIUS_RIGHT_F2+0.5*WHEEL_RADIUS_LEFT_F2)*(rsamp-lsamp));
	Phi2[3][1] = 0;
	Phi2[3][2] = 0;
	Phi2[3][3] = 1;
	
	//P12 = Phi2*P2*Phi2' + Q2;

	 mat_mult(Phi2,P2,T1,num_states,num_states,num_states);
     mat_mult_transpose(T1,Phi2,T2,num_states,num_states,num_states);
	 mat_add(T2,Q2,P12,num_states,num_states);

	// correction
	 //S2 = H2*P12*H2' + R2;

	 mat_mult(H2,P12,T3,num_states,num_states,num_states);
     mat_mult_transpose(T3,H2,T4,num_states,num_states,num_states);
	 mat_add(T4,R2,S2,num_states,num_states);

	//K2 = P12*H2'*inv(S2);

	mat_mult_transpose(P12,H2,T5,num_states,num_states,num_states);
	take_inverse(S2,T6,num_states);
	mat_mult(T5,T6,K2,num_states,num_states,num_states);

	//P2= P12 - K2*H2*P12;
	
	mat_mult(K2,H2,T7,num_states,num_states,num_states);
	mat_mult(T7,P12,T8,num_states,num_states,num_states);
	mat_sub(P12,T8,P2,num_states,num_states);

	//r2 = Z - H2*Phi2*Xk_prev2;

	mat_mult(H2,Phi2,T10,num_states,num_states,num_states);
	mat_mult_vect(T10,Xk_prev2,T11,num_states,num_states);
	vec_sub(Z,T11,r2,num_states);

	//Xk2 = Phi2*Xk_prev2 + K2*r2;

	mat_mult_vect(Phi2,Xk_prev2,T12,num_states,num_states);
	mat_mult_vect(K2,r2,T13,num_states,num_states);
	vec_add(T12,T13,Xk2,num_states);

	//etaS2 = inv(sqrt(S2))*r2;

	for(int i = 1;i<=num_states;i++)
		{
			for(int j = 1;j<num_states;j++){

				S2[i][j] = pow(S2[i][j],0.5);
				
				if(isnan(S2[i][j])){
					
					S2[i][j] = 0.0;
				}
	
			}
		}
	take_inverse(S2,T17,num_states);
	mat_mult_vect(T17,r2,etaS2,num_states,num_states);


	// sum_eta2 = sum_eta2 + etaS2;

	vec_add(sum_eta2,etaS2,sum_eta2,num_states);

	// etaS_hat2  = 1/N*sum_eta2;

	for(int i = 1;i<=num_states;i++)
		{
			sum_eta2[i] = 0.003*sum_eta2[i];
		}

	vec_copy(sum_eta2,etaS_hat2,num_states);

	//fprintf(f2,"%f,%f,%f,",etaS_hat2[1],etaS_hat2[2],etaS_hat2[3]);

	// RIGHT TIRE BUMP EKF FILTER IMPLEMENTATION [EKF3]
	
	// prediction
	
	if(k%2==0){

	Phi3[1][1] = 1;
	Phi3[1][2] = 0;
	Phi3[1][3] = -0.002*PI*(0.5*WHEEL_RADIUS_RIGHT_F3+0.5*WHEEL_RADIUS_LEFT_F3)*(rsamp+lsamp)*sin(teta+0.00333*PI*(0.5*WHEEL_RADIUS_RIGHT_F3+0.5*WHEEL_RADIUS_LEFT_F3)*(rsamp-lsamp));
	Phi3[2][1] = 0;
	Phi3[2][2] = 1;
	Phi3[2][3] = 0.002*PI*(0.5*WHEEL_RADIUS_RIGHT_F3+0.5*WHEEL_RADIUS_LEFT_F3)*(rsamp+lsamp)*cos(teta+0.00333*PI*(0.5*WHEEL_RADIUS_RIGHT_F3+0.5*WHEEL_RADIUS_LEFT_F3)*(rsamp-lsamp));
	Phi3[3][1] = 0;
	Phi3[3][2] = 0;
	Phi3[3][3] = 1;

	}
	else{

	Phi3[1][1] = 1;
	Phi3[1][2] = 0;
	Phi3[1][3] = -0.002*PI*(0.5*WHEEL_RADIUS_RIGHT_FF+0.5*WHEEL_RADIUS_LEFT_FF)*(rsamp+lsamp)*sin(teta+0.00333*PI*(0.5*WHEEL_RADIUS_RIGHT_FF+0.5*WHEEL_RADIUS_LEFT_FF)*(rsamp-lsamp));
	Phi3[2][1] = 0;
	Phi3[2][2] = 1;
	Phi3[2][3] = 0.002*PI*(0.5*WHEEL_RADIUS_RIGHT_FF+0.5*WHEEL_RADIUS_LEFT_FF)*(rsamp+lsamp)*cos(teta+0.00333*PI*(0.5*WHEEL_RADIUS_RIGHT_FF+0.5*WHEEL_RADIUS_LEFT_FF)*(rsamp-lsamp));
	Phi3[3][1] = 0;
	Phi3[3][2] = 0;
	Phi3[3][3] = 1;
	}
	//P13 = Phi3*P3*Phi3' + Q3;

	 mat_mult(Phi3,P3,T1,num_states,num_states,num_states);
     mat_mult_transpose(T1,Phi3,T2,num_states,num_states,num_states);
	 mat_add(T2,Q3,P13,num_states,num_states);

	// correction
	 //S3 = H3*P13*H3' + R3;

	 mat_mult(H3,P13,T3,num_states,num_states,num_states);
     mat_mult_transpose(T3,H3,T4,num_states,num_states,num_states);
	 mat_add(T4,R3,S3,num_states,num_states);

	//K3 = P13*H3'*inv(S3);

	mat_mult_transpose(P13,H3,T5,num_states,num_states,num_states);
	take_inverse(S3,T6,num_states);
	mat_mult(T5,T6,K3,num_states,num_states,num_states);

	//P3 = P13 - K3*H3*P13;
	
	mat_mult(K3,H3,T7,num_states,num_states,num_states);
	mat_mult(T7,P13,T8,num_states,num_states,num_states);
	mat_sub(P13,T8,P3,num_states,num_states);

	//r3 = Z - H3*Phi3*Xk_prev3;

	mat_mult(H3,Phi3,T10,num_states,num_states,num_states);
	mat_mult_vect(T10,Xk_prev3,T11,num_states,num_states);
	vec_sub(Z,T11,r3,num_states);

	//Xk3 = Phi3*Xk_prev3 + K3*r3;

	mat_mult_vect(Phi3,Xk_prev3,T12,num_states,num_states);
	mat_mult_vect(K3,r3,T13,num_states,num_states);
	vec_add(T12,T13,Xk3,num_states);

	//etaS3 = inv(sqrt(S3))*r3;

	for(int i = 1;i<=num_states;i++)
		{
			for(int j = 1;j<num_states;j++){

				S3[i][j] = pow(S3[i][j],0.5);
				
				if(isnan(S3[i][j])){
					
					S3[i][j] = 0.0;
				}
	
			}
		}
	take_inverse(S3,T18,num_states);
	mat_mult_vect(T18,r3,etaS3,num_states,num_states);


	// sum_eta3 = sum_eta3+ etaS3;

	vec_add(sum_eta3,etaS3,sum_eta3,num_states);

	// etaS_hat3  = 1/N*sum_eta3;

	for(int i = 1;i<=num_states;i++)
		{
			sum_eta3[i] = 0.003*sum_eta3[i];
		}

	vec_copy(sum_eta3,etaS_hat3,num_states);

	//fprintf(f3,"%f,%f,%f,",etaS_hat3[1],etaS_hat3[2],etaS_hat3[3]);

	// LEFT TIRE BUMP EKF FILTER IMPLEMENTATION [EKF4]
	
	// prediction
	
	if(k%3==0){

	Phi4[1][1] = 1;
	Phi4[1][2] = 0;
	Phi4[1][3] = -0.002*PI*(0.5*WHEEL_RADIUS_RIGHT_F4+0.5*WHEEL_RADIUS_LEFT_F4)*(rsamp+lsamp)*sin(teta+0.00333*PI*(0.5*WHEEL_RADIUS_RIGHT_F4+0.5*WHEEL_RADIUS_LEFT_F4)*(rsamp-lsamp));
	Phi4[2][1] = 0;
	Phi4[2][2] = 1;
	Phi4[2][3] = 0.002*PI*(0.5*WHEEL_RADIUS_RIGHT_F4+0.5*WHEEL_RADIUS_LEFT_F4)*(rsamp+lsamp)*cos(teta+0.00333*PI*(0.5*WHEEL_RADIUS_RIGHT_F4+0.5*WHEEL_RADIUS_LEFT_F4)*(rsamp-lsamp));
	Phi4[3][1] = 0;
	Phi4[3][2] = 0;
	Phi4[3][3] = 1;

	}
	else{

	Phi4[1][1] = 1;
	Phi4[1][2] = 0;
	Phi4[1][3] = -0.002*PI*(0.5*WHEEL_RADIUS_RIGHT_FF+0.5*WHEEL_RADIUS_LEFT_FF)*(rsamp+lsamp)*sin(teta+0.00333*PI*(0.5*WHEEL_RADIUS_RIGHT_FF+0.5*WHEEL_RADIUS_LEFT_FF)*(rsamp-lsamp));
	Phi4[2][1] = 0;
	Phi4[2][2] = 1;
	Phi4[2][3] = 0.002*PI*(0.5*WHEEL_RADIUS_RIGHT_FF+0.5*WHEEL_RADIUS_LEFT_FF)*(rsamp+lsamp)*cos(teta+0.00333*PI*(0.5*WHEEL_RADIUS_RIGHT_FF+0.5*WHEEL_RADIUS_LEFT_FF)*(rsamp-lsamp));
	Phi4[3][1] = 0;
	Phi4[3][2] = 0;
	Phi4[3][3] = 1;
	}
	//P14 = Phi4*P3*Phi4' + Q4;

	 mat_mult(Phi4,P4,T1,num_states,num_states,num_states);
     mat_mult_transpose(T1,Phi4,T2,num_states,num_states,num_states);
	 mat_add(T2,Q4,P14,num_states,num_states);

	// correction
	 //S4 = H4*P14*H4' + R4;

	 mat_mult(H4,P14,T3,num_states,num_states,num_states);
     mat_mult_transpose(T3,H4,T4,num_states,num_states,num_states);
	 mat_add(T4,R4,S4,num_states,num_states);

	//K4 = P14*H4'*inv(S4);

	mat_mult_transpose(P14,H4,T5,num_states,num_states,num_states);
	take_inverse(S4,T6,num_states);
	mat_mult(T5,T6,K4,num_states,num_states,num_states);

	//P4 = P14 - K4*H4*P14;
	
	mat_mult(K4,H4,T7,num_states,num_states,num_states);
	mat_mult(T7,P14,T8,num_states,num_states,num_states);
	mat_sub(P14,T8,P4,num_states,num_states);

	//r4 = Z - H4*Phi4*Xk_prev4;

	mat_mult(H4,Phi4,T10,num_states,num_states,num_states);
	mat_mult_vect(T10,Xk_prev4,T11,num_states,num_states);
	vec_sub(Z,T11,r4,num_states);

	//Xk4 = Phi4*Xk_prev4 + K4*r4;

	mat_mult_vect(Phi4,Xk_prev4,T12,num_states,num_states);
	mat_mult_vect(K4,r4,T14,num_states,num_states);
	vec_add(T12,T14,Xk4,num_states);

	//etaS4 = inv(sqrt(S4))*r4;

	for(int i = 1;i<=num_states;i++)
		{
			for(int j = 1;j<num_states;j++){

				S4[i][j] = pow(S4[i][j],0.5);
				
				if(isnan(S4[i][j])){
					
					S4[i][j] = 0.0;
				}
	
			}
		}
	take_inverse(S4,T19,num_states);
	mat_mult_vect(T19,r4,etaS4,num_states,num_states);


	// sum_eta4 = sum_eta4+ etaS4;

	vec_add(sum_eta4,etaS4,sum_eta4,num_states);

	// etaS_hat4  = 1/N*sum_eta4;

	for(int i = 1;i<=num_states;i++)
		{
			sum_eta4[i] = 0.003*sum_eta4[i];
		}

	vec_copy(sum_eta4,etaS_hat4,num_states);

	//fprintf(f4,"%f,%f,%f,",etaS_hat4[1],etaS_hat4[2],etaS_hat4[3]);
	
	// UPDATE VARS
	
	vec_copy(Xk0,Xk_prev0, num_states);
	vec_copy(Xk1,Xk_prev1, num_states);
	vec_copy(Xk2,Xk_prev2, num_states);
	vec_copy(Xk3,Xk_prev3, num_states);
	vec_copy(Xk4,Xk_prev4, num_states);
	
	
	// FAULT DETECTION SUB-MODULE
	
	if(l<3387){
	  if(etaS_hat0[1] <= *(pEta+l) + offsetx_min || etaS_hat0[1] >= *(pEta+l) + offsetx_max || etaS_hat0[2] <= *(pEta+(l+1)) + offsety_min || etaS_hat0[2] >= *(pEta+(l+1)) + offsety_max || etaS_hat0[3] <= *(pEta+(l+2)) + offsetteta_min || etaS_hat0[3] >= *(pEta+(l+2)) + offsetteta_max)
		{	 
			if(filter_false_alarms() && freeze_diagnosis==0){// filter false alarms
			printf("FDI : A FAULT WAS DETECTED...START IDENTIFICATION...\n");
				    fault_flag = 1;
	            		    freeze_diagnosis = 1;
			
		           	}
		}
		else{	
			 if(freeze_diagnosis==0){
				fault_flag = 0;// no fault detected yet
				printf("FDI : no faults detected...\n");
				}
				else{// multiple faults management not implemented yet, so freeze FDI module after first fault detected	
					printf("FDI : ...IDENTIFYING THE FAULT...\n");
				}
		    }	

	}

		
	// FAULT IDENTIFICATION SUB-MODULE
	
	if(fault_flag==1){
	
	double temp[4][4];
	temp[0][0] = r1[1];
	temp[0][1] = r1[2];
	temp[0][2] = r1[3];
	temp[1][0] = r2[1];
	temp[1][1] = r2[2];
	temp[1][2] = r2[3];
	temp[2][0] = r3[1];
	temp[2][1] = r3[2];
	temp[2][2] = r3[3];
	temp[3][0] = r4[1];
	temp[3][1] = r4[2];
	temp[3][2] = r4[3];
	
	double min1 = temp[0][0];
	double min2 = temp[0][1];
	double min3 = temp[0][2];

		for(int i = 0;i<4;i++){

			
			   if(temp[i][0]<min1){

				   min1 = temp[i][0];
			   }

			   if(temp[i][1]<min2){

				   min3 = temp[i][1];
			   }

			   if(temp[i][2]<min3){

				   min3 = temp[i][2];
			   }

			   if((min1==r1[1] && min2 ==r1[2] || min2==r1[2] && min3 ==r1[3] || min1==r1[1] && min3 ==r1[3])|| (min1==r2[1] && min2 ==r2[2] || min2==r2[2] && min3 ==r2[3] || min1==r2[1] && min3 ==r2[3])){
			
				fault_type = 1;// first class fault
				 
			   }
			   else
			   {

				fault_type = 2;//second class fault
				
			   }

	  }//end for i


		switch(fault_type){
	
			case 1:     
					reconf_ctrl = 1;
					tp[GET_RECONF_STATE]=(double)reconf_ctrl;
					break;

			case 2:     
					reconf_ctrl = 2;
					tp[GET_RECONF_STATE]=(double)reconf_ctrl;
					break;
			default : 
					reconf_ctrl = 0;
					tp[GET_RECONF_STATE] = (double)reconf_ctrl;
					break;

		}
	// multiple faults management not implemented yet, so freeze FDI module after first fault detected
		
	}// end if fault_flag
	
	// BACKGROUND MONITORING TASKS (Robot STATE INFO)

	// test values of motor currents 
	
	if(current_mot1->get() >= 15.5 || current_mot2->get() >= 15.5){

		printf("M1 current value : [ %f]A , M2 current value :[ %f ]A \n",current_mot1->get(),current_mot2->get());
		// stop robot
		pwm_mot1->set(0.0);
		pwm_mot2->set(0.0);

		rel_pow->set(1.0);
	}
	// battery monitoring

	battery_status = battery_voltage->get();
	if(battery_status < 10){
	printf("BAT [%f]V ... CONSIDER STOPPING THE ROBOT, LOW BATTERY...\n",battery_status);
	}
	else if(battery_status < 9.8){
	printf("BAT [%f]V ... EMERGENCY STOP ! \n",battery_status);
	}
	
	// vars update
	X_pos_ant = X_pos;
	Y_pos_ant = Y_pos;	
	teta_ant = teta;
	last_left = lsamp;
	last_right = rsamp;
	k++;
	l = l+3;
	u++;
	increment++;
	

}// end rt diag and monitor task

    void end_ctrl(){
	
	free_vect(Xk_prev0,1,num_states);
	free_vect(Xk_prev1,1,num_states);
	free_vect(Xk_prev2,1,num_states);
	free_vect(Xk_prev3,1,num_states);
	free_vect(Xk_prev4,1,num_states);
	free_vect(Xk0,1,num_states);
	free_vect(Xk1,1,num_states);
	free_vect(Xk2,1,num_states);
	free_vect(Xk3,1,num_states);
	free_vect(Xk4,1,num_states);
	free_vect(r0,1,num_states);
	free_vect(r1,1,num_states);
	free_vect(r2,1,num_states);
	free_vect(r3,1,num_states);
	free_vect(r4,1,num_states);
	free_vect(Z,1,num_states);
	free_vect(sum_eta0,1,num_states);
	free_vect(sum_eta1,1,num_states);
	free_vect(sum_eta2,1,num_states);
	free_vect(sum_eta3,1,num_states);
	free_vect(sum_eta4,1,num_states);
	free_vect(etaS0,1,num_states);
	free_vect(etaS1,1,num_states);
	free_vect(etaS2,1,num_states);
	free_vect(etaS3,1,num_states);
	free_vect(etaS4,1,num_states);
	free_vect(etaS_hat0,1,num_states);
	free_vect(etaS_hat1,1,num_states);
	free_vect(etaS_hat2,1,num_states);
	free_vect(etaS_hat3,1,num_states);
	free_vect(etaS_hat4,1,num_states);
	free_vect(T11,1,num_states);
	free_vect(T12,1,num_states);
	free_vect(T13,1,num_states);
	free_vect(T14,1,num_states);
	// matrix deallocation
	free_matrix(Q0,1,num_states,1,num_states);
	free_matrix(Q1,1,num_states,1,num_states);
	free_matrix(Q2,1,num_states,1,num_states);
	free_matrix(Q3,1,num_states,1,num_states);
	free_matrix(Q4,1,num_states,1,num_states);
	free_matrix(Phi0,1,num_states,1,num_states);
	free_matrix(Phi1,1,num_states,1,num_states);
	free_matrix(Phi2,1,num_states,1,num_states);
	free_matrix(Phi3,1,num_states,1,num_states);
	free_matrix(Phi4,1,num_states,1,num_states);
	free_matrix(P10,1,num_states,1,num_states);
	free_matrix(P11,1,num_states,1,num_states);
	free_matrix(P12,1,num_states,1,num_states);
	free_matrix(P13,1,num_states,1,num_states);
	free_matrix(P14,1,num_states,1,num_states);
	free_matrix(H0,1,num_states,1,num_states);
	free_matrix(H1,1,num_states,1,num_states);
	free_matrix(H2,1,num_states,1,num_states);
	free_matrix(H3,1,num_states,1,num_states);
	free_matrix(H4,1,num_states,1,num_states);
	free_matrix(S0,1,num_states,1,num_states);
	free_matrix(S1,1,num_states,1,num_states);
	free_matrix(S2,1,num_states,1,num_states);
	free_matrix(S3,1,num_states,1,num_states);
	free_matrix(S4,1,num_states,1,num_states);
	free_matrix(P0,1,num_states,1,num_states);
	free_matrix(P1,1,num_states,1,num_states);
	free_matrix(P2,1,num_states,1,num_states);
	free_matrix(P3,1,num_states,1,num_states);
	free_matrix(P4,1,num_states,1,num_states);
	free_matrix(K0,1,num_states,1,num_states);
	free_matrix(K1,1,num_states,1,num_states);
	free_matrix(K2,1,num_states,1,num_states);
	free_matrix(K3,1,num_states,1,num_states);
	free_matrix(K4,1,num_states,1,num_states);
	free_matrix(T1,1,num_states,1,num_states);
	free_matrix(T2,1,num_states,1,num_states);
	free_matrix(T3,1,num_states,1,num_states);
	free_matrix(T4,1,num_states,1,num_states);
	free_matrix(T5,1,num_states,1,num_states);
	free_matrix(T6,1,num_states,1,num_states);
	free_matrix(T7,1,num_states,1,num_states);
	free_matrix(T8,1,num_states,1,num_states);
	free_matrix(T10,1,num_states,1,num_states);
	free_matrix(T15,1,num_states,1,num_states);
	free_matrix(T16,1,num_states,1,num_states);
	free_matrix(T17,1,num_states,1,num_states);
	free_matrix(T18,1,num_states,1,num_states);
	free_matrix(T19,1,num_states,1,num_states);
	}
	
    void debug(){
		cout << name << endl;
	}
};

////////////////////////////////////////////////////////////////
//                         TRANSITIONS
////////////////////////////////////////////////////////////////

class Tempty:public Transition{
public:
	void debug(){
		
		cout << name << endl;
	}
	int eval(){

		return 1;
	}
};

class TError11:public Transition{
public:
	void debug(){
		
		cout << name << endl;
	}
	int eval(){
		
		return tp[ERROR] == 1;
	}
};

class TError21:public Transition{
public:
	void debug(){
		
		cout << name << endl;
	}
	int eval(){
		
		return tp[ERROR] == 1;
	} 
};


////////////////////////////////////////////////////////////////
//                         PHASES
////////////////////////////////////////////////////////////////

class SerialPhase:public Phase{
private:
	
	Stage *A10, *C11, *A12, *C12, *AE11, *AE12, *A15;
	
	Transition *T10, *T11, *T12, *TE11, *T13, *TE12, *T14;
	
public:
	SerialPhase(): Phase(){
		set_name("Phase1");
		
		cout << "Generating Serial Phase instance ..." << endl;

		// PWM 
		pwm_mot1 = new AnalogActuator(0,daq);
		pwm_mot2 = new AnalogActuator(1,daq);

		// Switching
		rel_pow = new DigitalActuator(1,daq);
		rel_sens_mot1 = new DigitalActuator(2,daq);
		rel_sens_mot2 = new DigitalActuator(5,daq);
	
		//current feedback
		current_mot1 = new AnalogSensor(6,daq);
		current_mot2 = new AnalogSensor(13,daq);
		
		// bumpers
		front_bumper = new DigitalSensor(4,daq);
		rear_bumper = new DigitalSensor(0,daq);

		// encoders
		encoder_mot1 = new Counter(0,daq);
		encoder_mot2 = new Counter(1,daq);
		
 		// battery voltage
		battery_voltage = new AnalogSensor(1,daq);
		
		// Grafcet defs

        	A10 = new Aempty(); A10->set_name("A10");
		C11 = new Cycle11(); C11->set_name("C11");
		C12 = new Cycle12(); C12->set_name("C12");
		
		A12 = new Aempty(); A12->set_name("A12");
		
		T10 = new Tempty(); T10->set_name("T10");
		T11 = new Tempty(); T11->set_name("T11");
		T12 = new Tempty(); T11->set_name("T12");
		
		TE11 = new TError11(); TE11->set_name("TE11");
		AE11 = new Aerror11; TE11->set_name("AE11");
		T13 = new Tempty(); T13->set_name("T13");
		
		TE12 = new TError11(); TE12->set_name("TE12");
		AE12 = new Aerror12; TE12->set_name("AE12");
		T14 = new Tempty(); T14->set_name("T14");
		
		A15 = new Aempty(); A15->set_name("A15");


		cout << "Building the Serial Phase ..." << endl;

		A10->add(T10); T10->add(C11);
		C11->add(T11); T11->add(C12); 
		C11->add(TE11); TE11->add(AE11); 
		AE11->add(T13); T13->add(A15);
		
		C12->add(T12); T12->add(A15);
		C12->add(TE12); TE12->add(AE12); 
		AE12->add(T14); T14->add(A15);
					
		first_stage(A10);
		last_stage(A15);
	}

	~SerialPhase(){
		cout << "Finishing the Serial Phase ..." << endl;
		delete A10;
		delete A12;
		delete A15;
		delete C11;
		delete C12;
		delete T10;
		delete T11;
		delete T12;
		delete T13;
		delete T14;
		delete TE11;
		delete TE12;
		delete AE11;
		delete AE12;
	}
};

class ParallelPhase:public Phase{
private:

	Stage *A20, *C21, *C22,*A23, *AE21, *AE22, *A25;

	Transition *T20, *T21, *TE21, *TE22, *T23, *T24;

public:

	ParallelPhase(): Phase(){
		set_name("Phase2");
		
		cout << "Generating Parallel Phase instance..." << endl;

		A20 = new Aempty(); A20->set_name("A20");
		C21 = new Cycle11(); C21->set_name("C21");
		C22 = new Cycle12(); C22->set_name("C22");
		A23 = new Aempty(); A23->set_name("A23");
		
		T20 = new Tempty(); T20->set_name("T20");
		T21 = new Tempty(); T21->set_name("T21");

		TE21 = new TError21(); TE21->set_name("TE21");		
		TE22 = new TError21(); TE22->set_name("TE22");
		AE21 = new Aerror11; TE21->set_name("AE21");
		AE22 = new Aerror12; TE22->set_name("AE22");
		T23 = new Tempty(); T23->set_name("T23");
		T24 = new Tempty(); T24->set_name("T24");
		A25 = new Aempty(); A25->set_name("A25");


		cout << "Building the Parallel Phase ..." << endl;

		A20->add(T20); T20->add(C21); T20->add(C22);
		C21->add(T21); C22->add(T21); T21->add(A25);
		C21->add(TE21); TE21->add(AE21); AE21->add(T23); T23->add(A25);
		C22->add(TE22); TE22->add(AE22); AE22->add(T24); T24->add(A25);				
		first_stage(A20);
		last_stage(A25);
	}
	~ParallelPhase(){
		cout << "Finishing the Parallel Phase ..." << endl;
		delete A20;
		delete C21;
		delete C22;
		delete A23;
		delete T20;
		delete T21;
		delete TE21;		
		delete TE22;
		delete AE21;
		delete AE22;
		delete T23;
		delete T24;
		delete A25;
	}
};


////////////////////////////////////////////////////////////////
//                         CONTROL
////////////////////////////////////////////////////////////////
class TotalControl: public Control{
public:
	TotalControl(){

		tf[ SERIAL_PHASE ]= new SerialPhase();
		tf[ PARALLEL_PHASE ]= new ParallelPhase();
		set_phases(tf,2);

		
		//analogic actuator instances
        	ta[ACA_1]= pwm_mot1;
		ta[ACA_2]= pwm_mot2;
		//digital actuator instances
		ta[ACD_1] = rel_pow;
		ta[ACD_2] = rel_sens_mot1;
		ta[ACD_3] = rel_sens_mot2;
		set_actuators(ta);
		
		// analogic sensor instances
		ts[SCA_1] = current_mot1;
		ts[SCA_2] = current_mot2;
		ts[SCA_3] = battery_voltage;
		// digital sensor table
		ts[SCD_1] = front_bumper;
		ts[SCD_2] = rear_bumper;
		set_sensors(ts);
        
         	//counter table
		tc[CNT_1]= encoder_mot1;
		tc[CNT_2]= encoder_mot2;
        	set_counters(tc);
		// set the parameter table
		set_parameters(tp);	
			
				
	}
	~TotalControl(){
		delete tf[ SERIAL_PHASE ];
		delete tf[ PARALLEL_PHASE ];
	}
};

TotalControl * control;

////////////////////////////////////////////////////////////////
//                    CONTROL SERVER
////////////////////////////////////////////////////////////////
class RemoteControlServer: public ControlServer{
public:
	RemoteControlServer(int p, Control * c) : ControlServer(p, c) { }
	int serve_special_request(int operation, int fd){
		return 0;
	}
};

RemoteControlServer *scontrol;

#endif
