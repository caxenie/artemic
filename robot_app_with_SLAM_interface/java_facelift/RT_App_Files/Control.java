/*
 * Control.java
 * \brief Permet controlar remotament actuadors, sensors i execucions de fases
 * \brief en l'aplicaci� C++RTAI.
 */

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
    protected DataInputStream sIn= null; /**<Canal d'input*/
    protected DataOutputStream sOut= null;/**<Canal de output*/

    protected boolean connected= false; 
    String hostRTAI; 
    int portRTAI;
    
   
    public Control(){
        o = new Control.Operations();
        actuator = new Control.Actuator();
        sensor = new Control.Sensor();
        
        s = null;
        sIn = null;
        sOut = null;
        
    }

    public Control(String host, int port) 
    throws UnknownHostException , IOException{
       // actuator = new Control.Actuator();
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
    
    /**Aquest metode serveix per a connectar-se al server. Abans s'han d'haver fixat
     * el nom del host i el port del servei.
    */
    public void connect()
    throws UnknownHostException, IOException{
        // Obrim una conexión amb el localhost en el prot 1500
        // que es el mateix que obrim amb el server en c
        // obrir els streams d' input i output
        s = new Socket( hostRTAI, portRTAI );
        sIn = new DataInputStream( s.getInputStream() );
        sOut = new DataOutputStream( s.getOutputStream() ) ;
        connected= true;
    }

    /**Aquest metode indica al server que ja pot tancar les connexions i es tanquen
     * tots els canals.
    */
    public void disconnect() throws IOException{
        connected= false;
        sOut.writeDouble(o.END);
        sOut.close();
        sIn.close();
        s.close();  
    }
    
    /**Retorna CERT si l'objecte esta connected al server i FALS en cas contrari*/
    public boolean connected(){
        return connected;
    }

    /**Retorna el nom del host*/
    public String getHost(){
        return hostRTAI;
    }
    
    /**Fixa el nom del host*/
    public void setHost(String host){
       hostRTAI = host;
    }
    
    /**Retorna el numero del port del server*/
    public int getPort(){
        return portRTAI;
    }
    
    /**Fixa el numero de port del server*/
    public void setPort(int port){
        portRTAI = port;
    }
    
    /**Amb aquest metode es fixa remotament el value del parametre.
     * Un cop connected a l'objecte ServidorControl de l'equip C++RTAI
     * es pot demanar que s'efectui aquesta ordre per fixar un parametre.*/
    synchronized public double set(int param, double value)
    throws IOException{ 
        double ret=-1;

        sOut.writeDouble(o.SET);
        sOut.writeDouble((double) param);
        sOut.writeDouble((double) value);
        ret = sIn.readDouble();
        return ret;
    }

    /**Amb aquest metode es consulta remotament el value del parametre.
     * Un cop connected a l'objecte ServidorControl de l'equip C++RTAI
     * es pot demanar que s'efectui aquesta ordre per consultar un parametre.*/
    public double get(int param)
    throws IOException{ 
        double ret=-1;
        
        sOut.writeDouble(o.GET);
        sOut.writeDouble((double) param);
        ret = sIn.readDouble();
 	return ret;
    }
    
     /**Amb aquest metode s'executa remotament una phase.
     * Un cop connected a l'objecte ServidorControl de l'equip C++RTAI
     * es pot demanar que s'efectui aquesta ordre per execute una phase.*/
    synchronized public double exe_phase(int phase)
    throws IOException{ 
        double ret=-1;
        
        sOut.writeDouble(o.EXE_PHASE);
        sOut.writeDouble((double) phase);
        ret = sIn.readDouble();
 	return ret;
    }

    /**Amb aquest metode es demana que s'executi en l'equip C++RTAI l'ordre
     *de stop que para totes les fases en execucio de forma immediata.
     *No cal dir que hi ha d'haver connexio.*/
    synchronized public double stop()
    throws IOException{         
        double ret;
        
        sOut.writeDouble(o.STOP);
        ret = sIn.readDouble();
        return ret;
    }

    /**class Actuator
     * Amb aquesta classe es pot demanar que s'actui directament sobre un actuator.
     */
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
    public Actuator actuator; /**<A traves d'aquest camp es pot actuar remotament sobre els actuadors*/
 
    /**class Sensor
     * Amb aquesta classe es pot demanar que es consulti directament un sensor.
     */
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
    public Sensor sensor; /**<A traves d'aquest camp es poden consultar remotament els sensors*/

}
