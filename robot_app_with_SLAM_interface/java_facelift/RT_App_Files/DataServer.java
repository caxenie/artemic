/**
 * DataServer.java
 * \brief Classe per passar data, estructures d'systemPlatform i notificar events als objectes
 * \brief de la classe DataClient.
 */

package RT_App_Files;

import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;

/** class DataServer
 * Amb un objecte d'aquesta classe es pot servir les data d'un objecte Data,
 * es poden notificar events de la execucio d'un objecte SystemPlatform aixi com servir
 * la estructura del grafcet.
 */
public class DataServer implements Runnable {
    
    public Data data= null; /**< referencia a l'objecte que consulta les data*/
    int port= 0; /**< port per servir les peticions de servei*/
    int portev= 0; /**< port per a les notificacions d'events*/
    
    Thread t=null; /**< thread per quedar escoltant peticions*/
    public SystemPlatform systemPlatform = null; /**< systemPlatform del qual es serveixen data*/
    
    boolean serving = false; /**< flag per saber si s'està serving o no*/
        
    ConnectEvent notev= null; /**< objecte per notificar els events*/
    
    /** Constructor del DataServer passant el número del port de servei 
     */
    public DataServer(int serving_port, int portNotEv){
        this.port= serving_port;
        this.portev= portNotEv;
    }

    protected void initDataServer(){
    }
    
    public DataServer(){
        initDataServer();
    }
        
    /**Fixa la referencia a l'SystemPlatform*/
    public void setSystemPlatform(SystemPlatform a){
        this.systemPlatform = a;
    }
    
    /**Retorna la referencia a l'SystemPlatform*/
    public SystemPlatform getSystemPlatform(){
        return systemPlatform;
    }
    
    /**Fixa el port al servei de peticions*/
    public void setPort(int serving_port){
        this.port= serving_port;
    }
    
    /**Retorna el numero del servei de peticons*/
    public int getPort(){
        return this.port;
    }
    
    /**Fixa el numero de port per a la notificacio d'events*/
    public void setPortEvent(int portNotEv){
        this.portev= portNotEv;
    }
    
    /**Retorna el numero de port per a la notificacio d'events*/
    public int getPortEvent(){
        return this.portev;
    }
    
    /**Fixa la referencia a Data que se serviran sota demanda*/
    public void setData(Data d){
        this.data= d;
    }
    
    /**Retorna la referencia a Data que se serveixen sota demanda*/
    public Data getData(){
        return this.data;
    }
    
    /**Inicia el servei d'atencio a les peticions*/
    public void serveConnections(){
        t= new Thread(this);
        serving = true;
        t.setDaemon(true);
        t.start();
    }
    
    /**Finalitza el servei a les peticions*/
    public void endConnections(){
        serving = false;
        if(t!=null) 
            t.stop();
        t=null;
    }
    
    /**Inicia el servei de peticions de notificacions*/
    public void serveNotifications()
    throws Throwable {
        this.notev= new DataServer.ConnectEvent(this);        
    }
    
    /**Metode que s'executa en segon pla per servir les peticions*/
    public void run() {
        try {
          // S' instancia un objecte sobre el port de servei a les peticons
          ServerSocket socket = new ServerSocket( this.port );
          System.out.println( "The Server wakes up the port " + this.port );
          // Entrem en un bucle escontant el port. Quan es produeix 
          // una crida, es llenca un thrd d'execucio d'atancio
          // DataConnection per a servir les peticions
          while( this.serving )
            // Nos quedamos parados en el accept(), y devolvemos un socket
            // cuando se recibe la llamada. Este socket es el que se pasa
            // como par�metro al nuevo hilo de ejecuci�n que se crea
            new DataConnection( socket.accept() , this);
        } catch( IOException e ) { 
            System.out.println("DataServer: "+e.getMessage());
            System.out.println("DataServer: Stopping serving requests.");
            this.serving= false;
        }
    }
    
    /**Crida la notificacio d'events que avisara a tots els clients*/
    public void notifyEvent(int event){
        this.notev.notifyEvent(event);
    }
    
    /**Acaba la notificacio d'events*/
    public void endNotifyEvent(){
        this.notev.endNotifyEvent();
    }
    
    /** class DataConnection
     * Aquesta classe permet llencar un nou thrd d'execucio cada cop que es fa una connexió
     * amb el server de data per part d'un client. D'aquesta manera s'atén més d'un client
     * alhora.
     */
    private class DataConnection extends Thread {

      DataServer sdata=null;  
      Socket socketclient;
      // Constructor
      DataConnection( Socket s , DataServer sdata) {
          this.sdata= sdata;
          System.out.println( "Send a request to the port... " + s.getLocalPort()
                                + " of the client " + s.getInetAddress());
          this.socketclient = s;
          // Treballem amb prioritat menor als altres ports
          setPriority( NORM_PRIORITY-1 );
          // S'arrenca el nou thrd i ja esta treballant el run()
          start();
      }

      /**Fil d'execucio que es queda serving les peticion de notificacions d'events*/
      public void run() {
        System.out.println( "Launch the port scanning thread... "+ socketclient.getLocalPort() );
        ObjectInputStream input = null;
        ObjectOutputStream output = null;

        boolean end= false;
        try {
                input= new ObjectInputStream( this.socketclient.getInputStream());
                output= new ObjectOutputStream( this.socketclient.getOutputStream());
                Operation oent=null;
                while( serving && ! end){
                    oent = (Operation) input.readObject();
                    if(oent.operation != Code.END_CONNECTION){
			this.sdata.serve_request(oent, input, output);
                    }else end=true;                        
                }
                socketclient.close();
                System.out.println( "DataServer: Socket from server to client closed." );
        } catch( Throwable e ) { System.out.println("DataServer: Error. "+ e.getMessage()); }
      }
    } // end class DataConnection
    
    /**Amb aquest metode es tracta cada possible peticio com son get_grafcet o get_dades.
     */
    protected void serve_request(Operation oent, ObjectInputStream input, ObjectOutputStream output){
        try {
          System.out.println("DataServer: serve_request "+ oent.operation);
          switch(oent.operation){
              case Code.GET_GRAFCET: 
                  Grafcet aux = systemPlatform.getGrafcet();
                  System.out.println("DataServer: request GET_GRAFCET "+aux.write());
                  output.writeObject(aux);
                  break;
              case Code.GET_DATA:
                  output.writeObject(this.data.getData());
                  break;
              case Code.NOTIFY_EVENTS:
                  break;
          }    
        } catch( Throwable e ) { System.out.println("DataServer: Error. "+ e.getMessage()); }
    }
    
    /** class ConnectEvent
     * Aquest objecte es queda a la espera de noves connexions i les effectuate en 
     * un conjunt per a notificar. Es un canal nomes de output per la qual cosa
     * no es reben ordres per aquest canal per part dels clients.
     */
    private class ConnectEvent implements Runnable{
        protected Thread t= null;
        protected Vector handlers = new Vector ();
        
        DataServer sd= null;
        ServerSocket socketevents= null;
        boolean notificant = false; /** flag per saber si cal notificar events */
        
        public ConnectEvent (DataServer sd) throws IOException {
            this.sd= sd;
            this.socketevents= new ServerSocket (this.sd.portev);
            t= new Thread(this);
            t.setDaemon(true);
            this.notificant= true;
            this.t.start();
        }

        public void run() {
            DataOutputStream dos=null;
            while (this.notificant) {
                System.out.println("Serving notification requests...");
                try{
                    
                    Socket client = this.socketevents.accept ();
                    System.out.println("A new notification client is connected...");
                    dos = new DataOutputStream(client.getOutputStream());
                    synchronized(handlers){
                        handlers.add(dos);
                    }
                }catch( Throwable e){
                    if(this.notificant)
                        System.out.println("DataServer: Error in the notification socket...");
                    if( this.socketevents!= null)
                        try{
                            this.socketevents.close();
                        }catch( IOException ioe){}
                    this.notificant= false;
                }
            }
        }
        
        public void notifyEvent(int nevent){
            synchronized (handlers) {
                Enumeration e = handlers.elements ();
                //System.out.println("Notificant event "+nevent+" a "+handlers.size());
                while (e.hasMoreElements ()) {
                    DataOutputStream c = (DataOutputStream) e.nextElement ();
                    try {
                            synchronized (c) {
                                c.writeInt(nevent);
                            }
                            c.flush ();
                        } catch (IOException ex) {
                            handlers.removeElement(e);
                        }
                    }
                }
        }
        public void endNotifyEvent(){
            this.notificant= false;
            if(this.t != null){
                this.t.stop();
                this.t= null;
            }
            try{
                this.socketevents.close();
            }catch(Throwable e){}
        }
    }//end class ConnectEvent
    
    /** class Code
    * Conté els codis per a les operacions demanades
    */
    public class Code{
        public final static int GET_GRAFCET=0;
        public final static int GET_DATA=1;
        public final static int NOTIFY_EVENTS=2;
        public final static int END_NOTIFY_EVENTS=3;
        public final static int END_CONNECTION=4;
    }
}
