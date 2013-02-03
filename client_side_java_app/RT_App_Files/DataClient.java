/* class that implements specific functionality to
communicate with the robot server application / it manages
data transfers (data fetching from sensors) */

package RT_App_Files;

import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;

public class DataClient implements Runnable{
    
    protected String server = null; 
    protected int port = 0; 
    
    boolean connected = false;
    boolean receive = false;
    
    Socket socket = null;
    ObjectInputStream input = null; 
    ObjectOutputStream output = null; 
        
    Event event = null; 
    Thread t = null; 
   //ctors
    public DataClient(){
    }

    public DataClient(String s, int p){
        this.server= s;
        this.port= p;
    }
    
   // choose a server to connect to 
    public void setServer(String host){
        this.server= host;
    }
    // get status 
    public String getServer(){
        return this.server;
    }
    // port set / get accesors
    public void setServerPort(int port){
        this.port= port;
    }
    
    public int getPort(){
        return this.port;
    }
    
    // connect to the robot
    public void connect()
    throws UnknownHostException, IOException{
        try{
              socket = new Socket( server,port );
             
              output =  new ObjectOutputStream( socket.getOutputStream() );
                  
              input = new ObjectInputStream( socket.getInputStream() );             
              connected= true;
        }catch( UnknownHostException uh){
            throw uh;
        }catch( IOException io){
            if(socket!= null)
                socket.close();
            throw io;
        }
    }
    // disconnect from the robot
    public void disconnect(){
        if( connected ){
            try{ 
                Operation o = new Operation(Code.END_CONNECTION, null);
                output.writeObject(o);
                output.flush();
                connected= false;
                socket.close(); 
            }catch(Throwable e){ 
                System.out.println("DataClient: Error while trying to disconnect...");
            }
        }
    }
    // initialise data transfer    
    public void initReceive()
    throws UnknownHostException, IOException{
     
        this.receive= true;
        start();
    }
    
    // initialise data request notifications
    public void initNotifications(Event e)
    throws UnknownHostException, IOException {
        this.event= e;
        this.initReceive();
    }
    
    // close transfer
    public void endReceive(){
        this.receive= false;
        if(t!=null)
            this.t.stop();
        this.t= null;
    }
    // event driven communication level
    public void setEvent(Event e){
        this.event = e;
    }
    
    public Event getEvent(){
        return this.event;
    }
    // start comm
    protected void start(){
        t= new Thread(this);
        t.setDaemon(true);
        t.start();
    }
   
    public void run() {
        int ne;
        while( this.receive){
            try{ 
                ne= this.input.readInt();
                this.event.signal(ne);
            }catch(Throwable e){ 
                if(this.receive)
                    System.out.println("DataClient: Error in fetching data..."+e.getMessage());
                this.receive= false;
            }
        }
    }    

    // specific  codes 
    public class Code{
        public final static int GET_GRAFCET=0;
        public final static int GET_DATA=1;
        public final static int NOTIFY_EVENTS=2;
        public final static int END_NOTIFY_EVENTS=3;
        public final static int END_CONNECTION=4;
    }

}
