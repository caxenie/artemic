//specific Grafcet functionality implementation
#include "grafcet.h"

using namespace std;


	template <class T>
	void ReverseByteOrder(T val, char * buf, int bufLen)
	{
		assert(bufLen >= (int) sizeof(T));
		memset(buf, 0x00, bufLen);	
		for (int i = 0; i < (int) sizeof(T); i++){
			buf[i] = *(((char*)&val)+(sizeof(T)-i-1));
		}
	}	
	template <class T>
	void ReverseByteOrder(T* pVal)
	{
		ReverseByteOrder(*pVal, (char*)pVal, sizeof(T));
	}


	

Thread::Thread(){
	pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER; 
	mutex = m;
}
	
Thread::Thread( char * nname){ 
	set_name(nname); 
	pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER; 
	mutex = m;
}
	
Thread::~Thread(){ 	
	pthread_mutex_destroy(&mutex); 
}

void Thread::debug(){

}	

char * Thread::set_name(char * nname){

	char * ret;
	if(strlen(nname) < NAME){
		strcpy(name, nname);
		ret=name;
	}else{	cout << "Thread: Error. The name  " << NAME << " cannot contain characters and \"" << nname;
		cout << "\" a number of " << strlen(nname) << " characters." << endl;
		ret=NULL;  
	}
	return ret;
}
	
char * Thread::get_name(){	
	return name;
}


//------------------------------------------------------------------------------------------------
//  STAGE CLASS
//------------------------------------------------------------------------------------------------
Stage::Stage(){
	active= true; 
}
	
Stage::Stage(char * name): Thread(name){
} // ctor that initializaes the thread name
	
Stage::~Stage(){
}

#define TIME_EXPECTED_BEFORE_CHANGING_STAGE 200000

void Stage::transition(){ 
	int last_stage=0;
	int change_stage=0;
	Transition * t;
	
	for(unsigned int i=0; i<transitions.size(); i++)
		last_stage+=transitions[i]->end();
	
		cout << name << " Last Stage " << last_stage << " transitions.size  " << transitions.size() << endl;
	if( last_stage==0 && transitions.size()>0){ //if it is the last stage we can iterate on the transition
			while(!change_stage){ // test if we need stage change
				for(unsigned int i=0; i<transitions.size(); i++){
					t=transitions[i];
					if(t->evaluate()){
						t->go();
						change_stage=1;
					}
			}
			if(change_stage==0){
				usleep(TIME_EXPECTED_BEFORE_CHANGING_STAGE);
			}
		}
		// reset transitions
		for(unsigned int i=0; i<transitions.size(); i++){
			transitions[i]->reset();
		}
	}
}

void * Stage::thread(void * p){

	class Stage * e = static_cast< Stage * >(p);
	// ensure that no stage is exectuing at the moment
	if( pthread_mutex_trylock( & e->mutex ) != EBUSY){ // test if mutex locked
		pthread_detach( pthread_self() ); // detach thread
		e->run();	// call Stage::run()
		pthread_mutex_unlock( & e->mutex );// free mutex
		e->transition();	// stage transition
	}else{ 
		cout << "Stage " << e->name << ": Error. Trying to execute a running Stage." << endl;
		e->transition(); // stage transition to overcome deadlock
	}
	pthread_exit(NULL);
	return 0;
}
		
void Stage::execute(){
	if( active ){
		debug();
		pthread_create(& tid, NULL, thread, this);
	}else cout << "The stage is not active and cannot be executed..." << endl;
}
	
void Stage::add(class Transition *t) {
// test if executing null transition
	if( t!=NULL){
		transitions.push_back(t);
		t->pred();
	}else cout << "Stage " << name << ": Error. Trying to execute a null Transition." << endl;
}
void Stage::stop(){
	if( active ){
		active=false;
		for(unsigned int i=0; i<transitions.size(); i++)
			transitions[i]->stop();
		pthread_mutex_unlock( &mutex ); 
		pthread_cancel( tid );
	}
}
void Stage::start(){
	if( !active ){
		active=true;
		for(unsigned int i=0; i<transitions.size(); i++){
			transitions[i]->start();
			transitions[i]->reset();
		}
	}
}


//------------------------------------------------------------------------------------------------
//  TRANSITION CLASS
//------------------------------------------------------------------------------------------------

Transition::Transition(){ // default ctor
	predecessors=0;	// stage number
	pred_ended=0;
}

Transition::Transition(char * nname): Thread(nname) { //object name ctor
	predecessors=0;
	pred_ended=0;
}

Transition::~Transition(){
}

void * Transition::thread(void * p){
//function that creates new thread
	class Transition * t = static_cast< Transition * >(p);
	
	if( pthread_mutex_trylock( & t->mutex ) != EBUSY){ // test mutex 
		pthread_detach( pthread_self() ); // detach
		t->th_go();
		pthread_mutex_unlock( & t->mutex );// unlock mutex
		pthread_exit(NULL);
	}else 
		cout << "Transition " << t->name << ": Error. Trying to execute a transition already launched..." << endl;
	return 0;
}
	
void Transition::th_go(){
//call if eval returns ok
	for(unsigned int i=0;i<follows.size();i++) // executes all stages that the transitin points at
		follows[i]->execute(); // launch new stage execution
}
	
int Transition::evaluate(){
	int ret;
	if( predecessors == pred_ended){ // if all past stages called eval, begin evaluation
		ret=eval();	// context evaluation
	}else ret=0;
	return ret;
}
	
void Transition::go(){
		debug();
		pthread_create(& tid, NULL, thread, this);
}
	
void Transition::add(Stage *e){
// adds a new stage; used also for creating new phases
	if( e!=NULL )
		follows.push_back(e);
	else cout << "Transition " << name << ": Error. Trying to referenciate a null Stage"<<endl;
}
	
void Transition::pred(){
	predecessors++;
}
	
int Transition::end(){
// signals to a transition that the last stage finished 
	pthread_mutex_lock( &mutex );//lock
	int ret=0;
	pred_ended++;
	ret= predecessors-pred_ended;
	pthread_mutex_unlock( &mutex );//free
	return ret;
}
	
void Transition::reset(){
// stage number reset
	pthread_mutex_lock( &mutex );//lock
	pred_ended=0;
	pthread_mutex_unlock( &mutex );//free
}

void Transition::stop(){
// stops all stages that following the transition
	for(unsigned int i=0;i<follows.size();i++)
		follows[i]->stop();
}
	
void Transition::start(){
// activate al stages follwinging the transition
	for(unsigned int i=0;i<follows.size();i++)
		follows[i]->start();
}

//------------------------------------------------------------------------------------------------
//  ACTION CLASS
//------------------------------------------------------------------------------------------------

Action::Action(){
}

Action::Action(char * name): Stage(name) {
} //ctor

Action::~Action(){
}// dtor

//------------------------------------------------------------------------------------------------
//  CYCLE CLASS
//------------------------------------------------------------------------------------------------


static int num_cycle = 0;

Cycle::Cycle(){
	sprintf(name, "C%i", num_cycle++); 
	period=1000000000; // default 1s
	task=NULL;
}

Cycle::Cycle(char * name): Stage(name){	
	period=1000000000;
	task=NULL;
}
	
Cycle::~Cycle(){
}
	
void Cycle::run(){
//real time computation
	if( strcmp(name, "") != 0 ){ 
		task = rt_task_init( nam2num(name), 0, 0, 0); // init real time task
		rt_task_make_periodic (task, rt_get_time(), nano2count(period)); // make the RT task periodic
		rt_make_hard_real_time(); // pass in hard real time mode
		// cycle template
		initialize(); // init
		while(!final_cond() && active){ // evaluate the finalization condition
			control(); // control task
			rt_task_wait_period(); // the task wait a period
		}
		end_ctrl(); // exit hard real time mode
		rt_make_soft_real_time(); // switch to soft real time
		rt_task_delete(task); // delete the RT task
	}else cout << "Cycle: Error. The Cycle doesn't have an identifier." << endl;
}
	
void Cycle::set_period(unsigned long long int nperiod){
	period= nperiod;// excution period
}
	
unsigned long long int Cycle::get_period(){
	return period;
}
	
void Cycle::stop(){
	Stage::stop();
}

//------------------------------------------------------------------------------------------------
//  FinalTransition CLASS
//------------------------------------------------------------------------------------------------

void FinalTransition::th_go(){ 
	pthread_mutex_lock( mutex );
	pthread_cond_signal( var_cond );
	pthread_mutex_unlock( mutex );
}
	
FinalTransition::FinalTransition(){ 
	strcpy(name, "Final Transition"); 
}
	
FinalTransition::~FinalTransition(){
}
	
int FinalTransition::eval(){ 
	return 1;
}
	
void FinalTransition::unblock(pthread_mutex_t & m, pthread_cond_t & v){
// unlock final transition in the phase
	mutex= & m;
	var_cond= & v;
}
	
void FinalTransition::stop(){
	pthread_mutex_lock( mutex );
	pthread_cond_signal( var_cond );
	pthread_mutex_unlock( mutex );
}		


//------------------------------------------------------------------------------------------------
//  Phase CLASS
//------------------------------------------------------------------------------------------------
Phase::Phase(){// ctor
	// init
	first= NULL;
	last= NULL;
	tfinal= NULL;
	task_main= NULL;
	activ= false;
	pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER; 
	mutex = m;
	pthread_cond_t v = PTHREAD_COND_INITIALIZER; 
	var_cond = v;
}

Phase::~Phase(){ // dtor
	pthread_mutex_destroy( & mutex );	
	pthread_cond_destroy( & var_cond );	
}
	
void Phase::first_stage(Stage * e){
// set first stage 
	if( e!=NULL ) first= e;
	else cout << "Phase " << name <<" : Error. Trying to set a null reference to first Stage..." << endl;
}
	
void Phase::last_stage(Stage * e){
	if( e!=NULL ){
		last= e;
		tfinal = new FinalTransition(); // the final transition unlocks the phase
		last->add(tfinal); // add the transition 
		tfinal->unblock(mutex, var_cond); // signal the last transition
	}else cout << "Phase:  Error. Trying to set a null reference to last Stage...." << endl;
}
void Phase::run(){
	if( first!=NULL) first->execute();
	else cout << "Phase" << name << ": Error. No first Stage to execute..." << endl;	
}
	
void Phase::execute(){
	if( ! activ){
		if( first!=NULL ){
			activ= true;
			first->start();	// all stages are now active
			run();		// launch first stage
			if( last ){ 
				pthread_mutex_lock( & mutex );		// lock
				pthread_cond_wait( & var_cond, & mutex );	// wait for final transition
				activ= false;
				pthread_mutex_unlock( & mutex );		// free
				stop();						// all stages are inactive
			}else cout << "Phase " << name << " : Error. Trying to establish an illegal last Stage..." << endl;
		}else cout << "Phase " << name << " : Error. Trying to establish an illegal last Stage..." << endl;
	}else cout << "Phase " << name << " : Error. The Phase cannot be launched because it's already in execution..." << endl;
}

void Phase::start(){
	if( first ) first->start();
	else cout << "Phase " << name << ": Error. No first Stage to start." << endl;
}
	
void Phase::stop(){
	if( activ ){ // check if stage is active
		first->stop();	// lock other stages
		activ=false;	// inactivate phase
		if( last){ // if a final transition is defined
			pthread_mutex_lock( & mutex ); 
			pthread_cond_signal( & var_cond ); 
			pthread_mutex_unlock( & mutex );
		}
	}                                            
}

//------------------------------------------------------------------------------------------------
//  Control CLASS
//------------------------------------------------------------------------------------------------
Control::Control(){
	parameters= NULL;
	phases = NULL;
	n_phases= 0;
	sensors = NULL;
	counters = NULL;
	actuators = NULL;

	// main task specific data
	int priority=0;  
	int stack_size=512; 
	int msg_size=256;   

	struct sched_param mysched;
	mysched.sched_priority = sched_get_priority_max(SCHED_FIFO) - 1;
	if( sched_setscheduler( 0, SCHED_FIFO, &mysched ) == -1 ) {
		puts("ERROR SETTING THE SCHEDULER");
		perror("errno");
		exit(1);
	}
	// memory space
	mlockall(MCL_CURRENT | MCL_FUTURE);
	// create the RT task
	task_main = rt_task_init( nam2num("main"), priority, stack_size, msg_size);
	if( task_main != NULL){
		// timer mode
		rt_set_oneshot_mode();
		// init timer
		start_rt_timer(nano2count(1000000000));
	}else cout << "Control: Error. The main RTAI task cannot be created, another one is already in execution..." << endl;		
}
	
Control::~Control(){
	if(task_main!=NULL)
		rt_task_delete(task_main);	// kill main task
}
	
double Control::get(int param){
// return the parameter table if set
	double ret;
	if( parameters!= NULL){
		ret= parameters[ param ];
	}else{
		cout << "Control: Error. The parameter table was not set." << endl;
		ret= 0;
	}
	return ret;
}
	
double Control::set(int param, double value){
// put the specific value in the parameter table
	double ret;
	if( parameters!= NULL){
		ret= parameters[ param ];
		parameters[ param ] = value;
	}else{
		cout << "Control: Error. The parameter table was not set." << endl;
		ret= 0;
	}
	return ret;
}

double Control::exe_phase(int phase){
	// execute the specified phase
	double ret;
	if( phases != NULL){
		if(phases[ phase ] != NULL){
			phases[phase]->execute();
			ret= 0;
		}else{
			cout << "Control: Error. the reference " << phase << " to the phases table is null"<< endl;
			ret= -1;
		}
	}else{
		cout << "Control: Error. The parameter table was not set..." << endl;
		ret= -1;
	}
	return ret;
}
	
double Control::stop(){
// stop all phases
	double ret = 0;
	if( phases != NULL){
		for( int i=0; i< n_phases; i++)
			if(phases[ i ] != NULL){
				phases[i]->stop();
				ret= 0;
			}else{
				cout << "Control: Error.the reference " << i << " to the phases table is null." << endl;
				ret= -1;
			}
	}else{
		cout << "Control: Error. The perimeter table was not set..." << endl;
		ret= -1;
	}
	return ret;
}

double Control::actuator(int actuator, double value){
// return the actuator table if set
	double ret;
	if( actuators!= NULL){
		ret= 1;
		actuators[ actuator ]->set(value);
	}else{
		cout << "Control: Error. The actuator table was not set." << endl;
		ret= 0;
	}
	return ret;
}

double Control::sensor(int sensor){
// get the sensor value from the sensor table
	double ret;
	if( sensors!= NULL){
		ret= sensors[ sensor ]->get();
	}else{
		cout << "Control: Error. The sensor table was not set." << endl;
		ret= 0;
	}
	return ret;
}


int Control::counter(int counter){
// get the counter value from the sensor table
	int ret;
	if( counters!= NULL){
		ret= counters[ counter ]->getCount();
	}else{
		cout << "Control: Error. The sensor table was not set." << endl;
		ret= 0;
	}
	return ret;
}	
void Control::set_parameters(double p[]){
	parameters= p;
}

double * Control::get_parameters(){
	return parameters;
}

void Control::set_phases(Phase * f[], int n){ 
	phases= f;
	n_phases= n;
}
	
Phase ** Control::get_phases(){
	return phases;
}
	
void Control::set_sensors(Sensor * s[]){
	sensors= s;
}

Sensor ** Control::get_sensors(){
	return sensors;
}

void Control::set_counters(Counter * c[]){
	counters= c;
}

Counter ** Control::get_counters(){
	return counters;
}
	
void Control::set_actuators(Actuator * a[]){
	actuators= a;
}

Actuator ** Control::get_actuators(){
	return actuators;
}



void Control::shutDown(){
	system("echo \"finish\" > /root/fifo");
}


//------------------------------------------------------------------------------------------------
//  ControlServer CLASS
//------------------------------------------------------------------------------------------------

//  Constants
#define CONTROL_SERVER_PORT	1500  	// control server default port
#define QUEUE_DIM	10	// max client queue length


ControlServer::ControlServer(){
	port= CONTROL_SERVER_PORT; 
	serving= false;		
	control=NULL;
	strcpy(ip_control, "127.0.0.1"); // default localhost
}
	
ControlServer::ControlServer(int p, Control * c){ // set port and control pointer
	port= p; 
	serving= false;		
	if( c!= NULL) 
		control=c;
	else cout << "ControlServer : Error. The Control object reference is null." << endl;
	strcpy(ip_control, "127.0.0.1");
}
	
ControlServer::~ControlServer() {
	if( serving) stop_serving(); 
	close(fd_s);
}
	
int ControlServer::connect(){
// create a socket and return file descriptor
	int       fd_s;                		
	struct    sockaddr_in servaddr;  	

	if ( (fd_s = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
		fprintf(stderr, "ControlServer : ERROR the socket cannot be created...\n");
		exit(EXIT_FAILURE);
	}
	// init socket
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(port);
	// bind to address
	if ( bind(fd_s, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0 ){
		fprintf(stderr, "ControlServer Cannot call the function \"bind\"\n");
	}
	return fd_s;
}	
	
int ControlServer::serve_client(int fd, char * ip){
// serve clients requests
	int ret = solve_request(fd, ip);
	thr_map.erase( thr_map.find(pthread_self()));
	return ret;
}
	
int ControlServer::get_fd_c(){
	return fd_c; 
}	
	
void * ControlServer::pthread_serve_requests(void * p){

	pthread_detach(pthread_self());
	//class ControlServer *c = (class ControlServer *)p;
	class ControlServer * c = static_cast< class ControlServer * >(p);
	
	struct sockaddr_in client;	   	// client addr
	socklen_t a;	
	pthread_t taux;
	if( c->get_control() != NULL ){
		c->fd_s=c->connect(); 
		if ( listen(c->fd_s, QUEUE_DIM) < 0 ){ 
			fprintf(stderr, "ERROR: Cannot call the function \"listen\"\n");
			exit(EXIT_FAILURE);
		}else ; 
		// enter serve request loop
		c->serve= true;
		c->serving= true; 
		while ( c->serve ){
			// wait for client to connect
			if ( (c->fd_c = accept(c->fd_s,(struct sockaddr *)&client,&a) ) < 0 ){
				fprintf(stderr, "ERROR with the function \"accept\"\n");
				exit(EXIT_FAILURE);
			}else {
				cout << endl << "Server : A Client is connected... " << inet_ntoa(client.sin_addr) << "with the file descriptor fd = " << c->fd_c << endl;
				strcpy(c->ip, inet_ntoa(client.sin_addr));
				pthread_create(& taux, NULL, pth_serve_client, c);
				c->thr_map.insert(std::map<pthread_t,int>::value_type(taux,c->fd_c)); 
			}
		}
		close(c->fd_s); 
		close(c->fd_c);
		c->serving= false; 
	}else{
		cout << "ControlServer:ServingRequests : Error. Cannot serve the requests because";
		cout << " the reference to the object is null" << endl;
	}
	pthread_exit(NULL);
}
	
void * ControlServer::pth_serve_client(void * p){

	pthread_detach(pthread_self());
	
	ControlServer * sc= static_cast< ControlServer * >(p);
	int fdc = sc->get_fd_c();
	sc->serve_client( fdc , sc->ip); 
	close(fdc); 
	pthread_exit( NULL );
}
	
// supported ops
#define GET 		0
#define SET 		1
#define EXE_PHASE	2
#define STOP		3
#define ACT			4
#define SEN			5
#define SHUTDOWN	6
#define CNT			7
#define END			-1

int ControlServer::serve_special_request(int operation, int fd){ 
	return 0; 
}
	
int ControlServer::solve_request(int fd, char * ip){ 

	int cont;
	double operation, param, sensor, actuator, value, phase, return_val;
	int counter;
	int val_count;
	bool be, end = false;
	cout << "ControlServer: Serving the requests for the client with the IP " << ip << endl;

	while( (cont= read(fd, & operation, sizeof(double))) && serve && !end){		
		if(cont<0){
			fprintf(stderr, "ControlServer: Cannot read...\n");
		}else{
			be = true;
			ReverseByteOrder(& operation);
			switch((int) operation){ 
				case GET:
					be = be && (read(fd,& param,sizeof(double))>=0); ReverseByteOrder(& param);
					if(be){
						value= (double)control->get((int) param);
						cout << "control->get(" << (int)param << ") = " << value << ";" << endl;
						ReverseByteOrder(& value); be = be && (write(fd,& value,sizeof(double))>=0);
					}
					if(!be)
						 cout << "ControlServer : parameter error." << endl;
					break;
				case SEN:
					be = be && (read(fd,& sensor,sizeof(double))>=0); ReverseByteOrder(& sensor);
					if(be){
						value= (double)control->sensor((int) sensor);
						cout << "control->sensor(" << (int)sensor << ") = " << value << ";" << endl;
						ReverseByteOrder(& value); be = be && (write(fd,& value,sizeof(double))>=0);
					}
					if(!be)
						 cout << "ControlServer : parameter error." << endl;
					break;

				case CNT:
					be = be && (read(fd,& counter,sizeof(double))>=0); ReverseByteOrder(& counter);
					if(be){
						val_count= (int)control->counter((int) counter);
						cout << "control->counter(" << (int)counter << ") = " << val_count << ";" << endl;
						ReverseByteOrder(& val_count); 
						be = be && (write(fd,& val_count,sizeof(double))>=0);
					}
					if(!be)
						 cout << "ControlServer : parameter error." << endl;
					break;

				case END:
					end=true;
					cout << "end();"  << endl;
					break;
				default:if( strcmp(ip, ip_control) == 0 || true ) 
						switch((int) operation){
							case SET :
								be = be && (read(fd,& param,sizeof(double))>=0); ReverseByteOrder(& param);
								be = be && (read(fd,& value,sizeof(double))>=0); ReverseByteOrder(& value);
								return_val= control->set((int) param, value);
								cout << "control->set(" << (int) param << ", " << value << ") = " << return_val << endl;
								ReverseByteOrder(& return_val);write(fd,& return_val,sizeof(double));
								break;
							case ACT :
								be = be && (read(fd,& actuator,sizeof(double))>=0); ReverseByteOrder(& actuator);
								be = be && (read(fd,& value,sizeof(double))>=0); ReverseByteOrder(& value);
								return_val= control->actuator((int) actuator, value);
								cout << "control->actuator(" << (int) actuator << ", " << value << ") = " << return_val << endl;
								ReverseByteOrder(& return_val);write(fd,& return_val,sizeof(double));
								break;
							case EXE_PHASE :
								be = be && (read(fd,& phase,sizeof(double))>=0); ReverseByteOrder(& phase);
								return_val= control->exe_phase((int) phase);
								cout << "control->exe_phase(" << (int) phase << ") = " << return_val << endl;
								ReverseByteOrder(& return_val);
								cout<<"WRITE "<<write(fd,& return_val,sizeof(double))<<endl;
								break;
							case STOP :
								return_val= control->stop();
								cout << "control->stop() = " << return_val << endl;
								ReverseByteOrder(& return_val);
								write(fd,& return_val,sizeof(double));
								break;
							case SHUTDOWN :
								control->shutDown();
								cout << "control->shutDown() = " << endl;
								break;
							default: if(serve_special_request((int) operation - 5, fd));
								else cout << "ControlServer : Error unrecognized " << (int) operation << " request\n";
						}
					else cout << "RemoteControlServer: Error,unrecognized" << (int) operation << "operation or a unauthorized client connected\n";
			}			
		}
	}
	close(fd);
	return 0;
}
	
void ControlServer::setPort(int p){ 
	port= p;
}

int ControlServer::getPort(){ 
	return port;
}

void ControlServer::set_control(Control * c){ 
	if( c!= NULL) 
		control=c;
	else cout << "ControlServer : Error. The reference to the Control object is null." << endl;
}
	
inline Control * ControlServer::get_control(){ 
	return control;
}
	
int ControlServer::serving_requests(){

	if( ! serving) 
		pthread_create(& tid, NULL,pthread_serve_requests,this);
	else
		cout << "ControlServer: Error. Already serving requests..." << endl;
	return tid;
}

void ControlServer::stop_serving(){ 
	this->serve=false; 
	close(fd_s); 

	map< pthread_t, int>::iterator iter;
	for( iter = thr_map.begin(); iter != thr_map.end(); iter++){
		cout << "ControlServer: cancelling tread \"" << (*iter).first << "\"" ;
		cout << " closing it's file descriptor "<< (*iter).second << endl;
		pthread_cancel( (*iter).first );
		close( (*iter).second);
	}
	close(fd_c); 
	serving=false;
	pthread_cancel( tid ); 
}

void ControlServer::set_ip_control(char * nip_control){
	if( strlen(nip_control)<15)
		strcpy(ip_control, nip_control);
	else cout << "ControlServer: Error. IP address format is not recognized..." << endl;
}
	
char * ControlServer::get_ip_control(){
	return ip_control;
}

//------------------------------------------------------------------------------------------------
//  DataServer CLASS
//------------------------------------------------------------------------------------------------
// constants
#define INIT_RECEPTION 0
#define END_RECEPTION 1
#define DISCONNECT -1


int DataServer::connect(){
	
	int       fd_s;                		
	struct    sockaddr_in servaddr;  	
	
	if ( (fd_s = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
		fprintf(stderr, "DataServer: Error, the socket cannot be created\n");
		return 0;
	}else{
		servaddr.sin_family      = AF_INET;
		servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		servaddr.sin_port        = htons(port);

		if ( bind(fd_s, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0 ){
			fprintf(stderr, "DataServer: Error, cannot call the function: \bind \n");
			return 0;
		}
	}
	return fd_s;
}	

void * DataServer::pthread_servingData(void * p){

	pthread_detach(pthread_self());
	class DataServer * sd = static_cast< class DataServer * >(p);
	
	struct sockaddr_in client;	  
	socklen_t a;	

	sd->fd_s=sd->connect(); 
	if ( listen(sd->fd_s, 10) < 0 ){ 
		fprintf(stderr, "ERROR: Cannot call the function: \"listen\"\n");
	}else{
		
		sd->serving= true; 
		while ( sd->serving ){
			
			if ( (sd->fd_input = accept(sd->fd_s,(struct sockaddr *)&client,&a) ) >= 0 ){ 
				if ( (sd->fd_output = accept(sd->fd_s,(struct sockaddr *)&client,&a) ) >= 0 ){ 
					sd->client_connected= true;
					strcpy(sd->ip, inet_ntoa(client.sin_addr)); 
					cout << endl << "DataServer: A client is connected " << sd->ip << " with the input = " << sd->fd_input << " and the output= " << sd->fd_output << endl;
					
					sd->serve_requests();
				}else 
					fprintf(stderr, "ERROR in function \"accept\"\n");
			}else 
				fprintf(stderr, "ERROR in function \"accept\"\n");
		}
	}
	close(sd->fd_s);
	close(sd->fd_input);
	close(sd->fd_output);
	sd->serving= false; 

	pthread_exit(NULL);
}	

void * DataServer::pthread_sendData(void * p){
	
	pthread_detach(pthread_self());
	double value;
	class DataServer * sd = static_cast< class DataServer * >(p);
	sd->sending = true; 

	
	while (sd->sending && sd->beginning != sd->end){ 
		value = sd->buffer[sd->beginning]; 
		ReverseByteOrder(& value); 
		sd->sending = sd->sending && (write(sd->fd_output, & value, sizeof(double))>=0); 
		sd->beginning = (sd->beginning+1)%TBUFFER; 
	} 
	sd->sending = false;
	pthread_exit(NULL);
}

void DataServer::initialize(){
	fd_input= -1;
	fd_output= -1;
	fd_s= -1;
	port= 1502;
	transmitting = false;
	serving= false;
	client_connected= false;
	
	beginning = 0;
	end = 0;
	sending = false;
}

void DataServer::serve_requests(){
	
	int cont;
	double operation;
	bool be, end=false;
	cout << "DataServer: Serving requests from the client with the ip " << ip << endl;
	
	while( (cont= read(fd_input, & operation, sizeof(double))) && serving && !end){		
		if(cont<0){
			fprintf(stderr, "DataSerever: Cannot read...\n");
		}else{
			be = true;
			ReverseByteOrder(& operation);
			switch((int) operation){ 
				case INIT_RECEPTION:
					transmitting = true;
					break;
				case END_RECEPTION:
					transmitting = false;
					break;
				case DISCONNECT:
					end=true;
					break;
				default:
					cout << "DataServer: Error. Request " << operation << " not recognized" << endl;
			}
		}
	}
}

DataServer::DataServer(){
	initialize();		
}

DataServer::DataServer(int port){
	initialize();
	this->port= port;
}

DataServer::~DataServer(){				
}

bool DataServer::servingData(){
	return serving;
}

bool DataServer::clientConnected(){ 
	return client_connected;
}

void DataServer::setPort(int p){
	port= p;
}

int DataServer::getPort(){ 
	return port;
}

int DataServer::serveData(){
	
	if( ! serving) 
		pthread_create(& tid, NULL,pthread_servingData,this);
	else{
		cout << "DataServer: Error. Already serving requests." << endl;
		return 0;
	}
	return tid;
}

void DataServer::stop_serving(){
	
	if(serving){
		close(fd_s); 
		close(fd_input); 
		close(fd_output); 
		serving= false;
	}
}

void DataServer::send(double v){
	
	buffer[ end++ ] = v;
	end %= TBUFFER;
	
	if( end == beginning)
		beginning = (beginning+1) % TBUFFER;
	
	if( ! sending && transmitting ) 
		pthread_create(& tid_data, NULL,pthread_sendData,this);
}


void DataServer::send(double v[], int n){
	
	int i=end, j=0;
	while( j < n && (i+1)%TBUFFER != beginning ){ 
		buffer[i] = v[j];
		j++;
		i= (i+1)% TBUFFER;
	}
	if( j < n){ 
		while( j < n){ 
			buffer[i] = v[j];
			j++;
			i= (i+1)% TBUFFER;
			beginning= (i+1)% TBUFFER; 
		}
	}
	end = (end+n) % TBUFFER; 
	
	if( ! sending && transmitting ) 
		pthread_create(& tid_data, NULL,pthread_sendData,this);
}

bool DataServer::bufferFull(){
	
	return (end+1)%TBUFFER == beginning;
}

bool DataServer::bufferEmpty(){
	
	return beginning == end;
}
