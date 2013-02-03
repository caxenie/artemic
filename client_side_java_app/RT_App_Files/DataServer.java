/* 
class that implements the data server giving specific
functionality to transfer data between the 2 apps 
similar structure to data client 
implemented separately to ensure bidirectional transfers
*/

package RT_App_Files;

import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;
public class DataServer implements Runnable {
    
    public Data data= null; 
    int port= 0; 
    int portev= 0; 
    Thread t=null; 
    public SystemPlatform systemPlatform = null; 
    
    boolean serving = false; 
    ConnectEvent notev= null; 
   
    public DataServer(int serving_port, int portNotEv){
        this.port= serving_port;
        this.portev= portNotEv;
    }

    protected void initDataServer(){
    }
    
    public DataServer(){
        initDataServer();
    }
        
    public void setSystemPlatform(SystemPlatform a){
        this.systemPlatform = a;
    }
    
    public SystemPlatform getSystemPlatform(){
        return systemPlatform;
    }
    
    public void setPort(int serving_port){
        this.port= serving_port;
    }
    
    public int getPort(){
        return this.port;
    }
    
    public void setPortEvent(int portNotEv){
        this.portev= portNotEv;
    }
    
    public int getPortEvent(){
        return this.portev;
    }
    
    public void setData(Data d){
        this.data= d;
    }
    
    public Data getData(){
        return this.data;
    }
    
    public void serveConnections(){
        t= new Thread(this);
        serving = true;
        t.setDaemon(true);
        t.start();
    }
    
    public void endConnections(){
        serving = false;
        if(t!=null) 
            t.stop();
        t=null;
    }
    
    public void serveNotifications()
    throws Throwable {
        this.notev= new DataServer.ConnectEvent(this);        
    }
    
    public void run() {
        try {
        
          ServerSocket socket = new ServerSocket( this.port );
          System.out.println( "The Server wakes up the port " + this.port );
      
          while( this.serving )
            
            new DataConnection( socket.accept() , this);
        } catch( IOException e ) { 
            System.out.println("DataServer: "+e.getMessage());
            System.out.println("DataServer: Stopping serving requests.");
            this.serving= false;
        }
    }
    
    public void notifyEvent(int event){
        this.notev.notifyEvent(event);
    }
    
    public void endNotifyEvent(){
        this.notev.endNotifyEvent();
    }

    private class DataConnection extends Thread {

      DataServer sdata=null;  
      Socket socketclient;
   
      DataConnection( Socket s , DataServer sdata) {
          this.sdata= sdata;
          System.out.println( "Send a request to the port... " + s.getLocalPort()
                                + " of the client " + s.getInetAddress());
          this.socketclient = s;
      
          setPriority( NORM_PRIORITY-1 );
      
          start();
      }

      
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
    }    
  
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

    private class ConnectEvent implements Runnable{
        protected Thread t= null;
        protected Vector handlers = new Vector ();
        
        DataServer sd= null;
        ServerSocket socketevents= null;
        boolean notificant = false; 
        
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
    }
    
 
    public class Code{
        public final static int GET_GRAFCET=0;
        public final static int GET_DATA=1;
        public final static int NOTIFY_EVENTS=2;
        public final static int END_NOTIFY_EVENTS=3;
        public final static int END_CONNECTION=4;
    }
}
