/*
 * DataClient.java
 * \brief Serveix per demanar data, el grafcet i notificacions d'events
 * \brief al DataServer.
 */

package RT_App_Files;

import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;

/* class Client Data
 * Aquesta classe serveix per accedir al server de data de l'equip que controla
 * l'systemPlatform.
 * A traves del client es pot demanar l'systemPlatform, dels data o que notifiqui els
 * fiferents events que es poden donar en la execucio de l'systemPlatform. 
 * La classe implementa Runnable per rebre les notificacions en segon pla.
 */
public class RemoteDataClient implements Runnable{
    
    protected String server = null; /**<Nom del server al qual es connect*/
    protected int port = 0; /**<Port del server al qual es connect*/
    int portNotifications = 0; /**< es el port pel que es reben les notificacions*/
    
    boolean connected = false;/**<Flag per saber si s'esta connected al server de peticions*/
    boolean notifications_at_receive= true; /**< Flag per saber si s'esta rebent notificacions*/
    
    Socket socket = null;/**<Socket cap al server de peticions*/
    ObjectInputStream input = null; /**< canal d'input de data*/
    ObjectOutputStream output = null; /**< canal de output de data*/
    
    Socket socketNotification = null;   /**<socket per a les notificacions*/
    DataInputStream entnot = null; /**< canal d'input de les notificacions*/
    
    Event event = null; /**< event exterior que tracta les notificacions*/
    SystemPlatform systemPlatform = null; /**< systemPlatform sobre el cual actuen les notificacions*/
    Thread t = null; /**<thread per rebre notificacions*/
    
    /** Contstructor. No realitza res.*/
    public RemoteDataClient(){
    }

    /**
     * Constructor del client en que s'inicialitza la cadena del host server
     * i el numero de port
     */
    public RemoteDataClient(String s, int p, int pnot){
        this.server= s;
        this.port= p;
        this.portNotifications= pnot;
    }
    
    /**Fixa el nom del host on hi ha el DataServer*/
    public void setServer(String host){
        this.server= host;
    }
    
    /**Retorna el nom del host del server que s'ha fixat*/
    public String getServer(){
        return this.server;
    }
    
    /**Fixa el port per on se serveixen les peticions*/
    public void setServerPort(int port){
        this.port= port;
    }
    
    /**Retonra el value actual del port de peticions*/
    public int getPort(){
        return this.port;
    }
    
    /**Fixa el numero de port per a les notificacions del events*/
    public void setPortNotificacions(int portNotificacions){
        this.portNotifications= portNotificacions;
    }
    
    /**Retorna el value actual del port de les notificacions*/
    public int getPortNotificacions(){
        return this.portNotifications;
    }
    
    /**Metode per connectar-se a l'objecte DataServer. Abans s'han d'haver
     * fixat el nom del host i el port del server de peticions.
     */
    public void connect()
    throws UnknownHostException, IOException{
        try{
              // Obrim un socket connected al server i al número de port
              socket = new Socket( server,port );
              // Aconseguim el canal de output
              output =  new ObjectOutputStream( socket.getOutputStream() );
              // Aconseguim el canal d'input     
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
    
    /** Avisa al server de peticions de la desconnexio*/
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
    
    /**Am aquest metode s'aconsegueix del DataServer l'objecte Grafcet
     * que te referenciat.
     */
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
    
    /**Amb aquest metode s'aconsegueix remotament l'objecte Data que el DataServer
     * te referenciades.
     */
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
            // Obrim un socket connected al server i al número de port
        this.socketNotification = new Socket( server, this.portNotifications );
        this.entnot = new DataInputStream( socketNotification.getInputStream() );
        this.notifications_at_receive= true;
        start();
    }
    
    /**Amb aquest metode es fixa l'objecte Event que es cridara cada cop que l'objecte
     * remot DataServer notifiqui un event que s'hagi produit en la execucio de l'systemPlatform.
     */
    public void initNotifications(Event e)
    throws UnknownHostException, IOException {
        this.event= e;
        this.initNotifications();
    }
    
    /** Amb aquest metode es para el tractament a les notificacions de l'ojbecte remot
     * DataServer.
    */
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
    
    /**Metode per fixar l'objecte Event que rebra les notificacions remotes.
    */
    public void setEvent(Event e){
        this.event = e;
    }
    
    /**Metode que retorna la referencia a l'ojbecte Event actualment referenciat en l'objecte*/
    public Event getEvent(){
        return this.event;
    }
    
    /** Metode per iniciar el thrd que rep els events*/
    protected void start(){
        t= new Thread(this);
        t.setDaemon(true);
        t.start();
    }
    
    /**Metode que s'executa en segon pla i que va rebent notificacions.
    */
    public void run() {
        int ne; // numero d'event
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

    /** class Code
    * Conté els codis per a les operacions
    */
    public class Code{
        public final static int GET_GRAFCET=0;
        public final static int GET_DATA=1;
        public final static int NOTIFY_EVENTS=2;
        public final static int END_NOTIFY_EVENTS=3;
        public final static int END_CONNECTION=4;
    }

}