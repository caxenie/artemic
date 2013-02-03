/*acces specific data using a specific interface / client specific functions */

package RT_App_Files;

import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;

public class RemoteDataClient implements Runnable{
    
    protected String server = null;
    protected int port = 0; 
    int portNotifications = 0; 
    
    boolean connected = false;
    boolean notifications_at_receive= true; 
    
    Socket socket = null;
    ObjectInputStream input = null; 
    ObjectOutputStream output = null; 
    
    Socket socketNotification = null;   
    DataInputStream entnot = null; 
    Event event = null; 
    SystemPlatform systemPlatform = null; 
    Thread t = null; 
    
    public RemoteDataClient(){
    }

    public RemoteDataClient(String s, int p, int pnot){
        this.server= s;
        this.port= p;
        this.portNotifications= pnot;
    }
    
    public void setServer(String host){
        this.server= host;
    }
    
    public String getServer(){
        return this.server;
    }
    
   
    public void setServerPort(int port){
        this.port= port;
    }
    
    public int getPort(){
        return this.port;
    }
    
  
    public void setPortNotificacions(int portNotificacions){
        this.portNotifications= portNotificacions;
    }
    
    
    public int getPortNotificacions(){
        return this.portNotifications;
    }
    
   
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
    
    public void disconnect(){
        if( connected ){
            try{ 
                Operation o = new Operation(Code.END_CONNECTION, null);
                output.writeObject(o);
                output.flush();
                connected= false;
                socket.close(); 
            }catch(Throwable e){ 
                System.out.println("DataClient: Error in trying to disconnect...");
            }
        }
    }
    
    
    public Grafcet getGrafcet()
     throws UnknownHostException, IOException, ClassNotFoundException{
       Grafcet returnGraf = null;
        if(connected){
                Operation o = new Operation(Code.GET_GRAFCET, null);
                output.writeObject(o);
                output.flush();
                returnGraf= (Grafcet) input.readObject();
        }else 
            System.out.println("DataClient: Error. Not connected.");
        return returnGraf;
    } 
    
    
    public double[] getData()
    throws IOException, ClassNotFoundException{
        double [] returnData = null;
        if(connected){
                Operation o = new Operation(Code.GET_DATA, null);
                output.writeObject(o);
                output.flush();
                returnData= (double []) input.readObject();
        }else System.out.println("DataClient: Error. Not connected.");
        return returnData;
    }
    
    public void initNotifications()
    throws UnknownHostException, IOException{
       
        this.socketNotification = new Socket( server, this.portNotifications );
        this.entnot = new DataInputStream( socketNotification.getInputStream() );
        this.notifications_at_receive= true;
        start();
    }
    
   
    public void initNotifications(Event e)
    throws UnknownHostException, IOException {
        this.event= e;
        this.initNotifications();
    }
    
    
    public void endNotifications(){
        this.notifications_at_receive= false;
        if(t!=null)
            this.t.stop();
        this.t= null;
        try{ 
            this.socketNotification.close(); 
        }
        catch (Throwable e){
        }
        this.notifications_at_receive= false;
    }
    
  
    public void setEvent(Event e){
        this.event = e;
    }
    
   
    public Event getEvent(){
        return this.event;
    }
    
    
    protected void start(){
        t= new Thread(this);
        t.setDaemon(true);
        t.start();
    }
    
   
    public void run() {
        int ne; 
        while( this.notifications_at_receive){
            try{ 
                ne= this.entnot.readInt();
                this.event.signal(ne);
            }catch(Throwable e){ 
                if(this.notifications_at_receive)
                    System.out.println("DataClient: Error in notifications."+e.getMessage());
                this.notifications_at_receive= false;
            }
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
