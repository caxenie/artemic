/* specific class that implements the Control functions
 used to issue specific commands to the similar class
 running on the C++ embedded server application */
 
package RT_App_Files;

import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;


public class Control { 

    class Operations {
        double GET = 0;
        double SET = 1;
        double EXE_PHASE = 2;
        double STOP = 3;
        double ACT = 4;
        double SEN = 5;
        double END = -1;
        int nop=2;
    }
    protected Operations o;
    
    protected Socket s= null;
    protected DataInputStream sIn= null; 
    protected DataOutputStream sOut= null;

    protected boolean connected= false; 
    String hostRTAI; 
    int portRTAI;
    
   // ctor
    public Control(){
        o = new Control.Operations();
        actuator = new Control.Actuator();
        sensor = new Control.Sensor();
        
        s = null;
        sIn = null;
        sOut = null;
        
    }
   // ctor 
    public Control(String host, int port) 
    throws UnknownHostException , IOException{
    
        o = new Control.Operations();
        actuator = new Control.Actuator();
        sensor = new Control.Sensor();
        
        s = null;
        sIn = null;
        sOut = null;
        
        hostRTAI = host;
        portRTAI = port;
        this.connect();
    }
    
   // connect to receive requests / send commands
    public void connect()
    throws UnknownHostException, IOException{
        
        s = new Socket( hostRTAI, portRTAI );
        sIn = new DataInputStream( s.getInputStream() );
        sOut = new DataOutputStream( s.getOutputStream() ) ;
        connected= true;
    }
   // disconnect
    public void disconnect() throws IOException{
        connected= false;
        sOut.writeDouble(o.END);
        sOut.close();
        sIn.close();
        s.close();  
    }
    // status checking functions
    public boolean connected(){
        return connected;
    }

    public String getHost(){
        return hostRTAI;
    }
    // set the host
    public void setHost(String host){
       hostRTAI = host;
    }
    
    public int getPort(){
        return portRTAI;
    }
    
    public void setPort(int port){
        portRTAI = port;
    }
    // set the value for a specific parameter from the parameter table
    synchronized public double set(int param, double value)
    throws IOException{ 
        double ret=-1;

        sOut.writeDouble(o.SET);
        sOut.writeDouble((double) param);
        sOut.writeDouble((double) value);
        ret = sIn.readDouble();
        return ret;
    }   // get the value of a specific parameter from the table
    public double get(int param)
    throws IOException{ 
        double ret=-1;
        
        sOut.writeDouble(o.GET);
        sOut.writeDouble((double) param);
        ret = sIn.readDouble();
 	return ret;
    }
    // execute a specific phase in the Grafcet structure
    synchronized public double exe_phase(int phase)
    throws IOException{ 
        double ret=-1;
        
        sOut.writeDouble(o.EXE_PHASE);
        sOut.writeDouble((double) phase);
        ret = sIn.readDouble();
 	return ret;
    }
    // stop execution
    synchronized public double stop()
    throws IOException{         
        double ret;
        
        sOut.writeDouble(o.STOP);
        ret = sIn.readDouble();
        return ret;
    }

   // specific actuator class functions / client side 
    public class Actuator{
            public synchronized double set(int actuator, double value)
            throws IOException{ 
                double ret=0;
                
                sOut.writeDouble(o.ACT);
                sOut.writeDouble((double) actuator);
                sOut.writeDouble(value);
                ret = sIn.readDouble();
                return ret;
            }
    }
    public Actuator actuator; 
   // specific sensor class functions / client side 
    public class Sensor{
            public synchronized double get(int sensor)
            throws IOException{ 
                double ret=0;
                
                sOut.writeDouble(o.SEN);
                sOut.writeDouble((double) sensor);
                ret = sIn.readDouble();
                return ret;
            }
    }
    public Sensor sensor; 
}
