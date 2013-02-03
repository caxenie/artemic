/*
 * DataClient.java
 * \brief Serveix per rebre data asincronament de l'systemPlatform sense peticio
 * \brief directa sino que es l'equip C++RTAI que decideix quan enviar data.
 */

package RT_App_Files;

import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;

/* class Client Data
 * Aquesta classe serveix per connectar-se al server de data de l'equip C++RTAI
 * que envia data sense necessitat de petició del client. Quan el server envia
 * data es genera un event i dins de l'objecte event es pot decidir que fer amb les
 * data, si rebre-les o rebutjar-les. Per rebre-les es necessita un objecte data.
 * La classe implementa Runnable per rebre les notificacions en segon pla.
 */
public class DataClient implements Runnable{
    
    protected String server = null; /**<Nom del server al qual es connect*/
    protected int port = 0; /**<Port del server al qual es connect*/
    
    boolean connected = false;/**<Flag per saber si s'esta connected al server de data*/
    boolean receive = false;/**<Flag per saber si s'esta receive data del server de data*/
    
    Socket socket = null;/**<Socket cap al server de data*/
    ObjectInputStream input = null; /**< canal d'input de data*/
    ObjectOutputStream output = null; /**< canal de output de data*/
        
    Event event = null; /**< event exterior que tracta les data*/
    Thread t = null; /**<thread per rebre notificacions*/
    
    /** Contstructor. No realitza res.*/
    public DataClient(){
    }

    /**
     * Constructor del client en que s'inicialitza la cadena del host server
     * i el numero de port
     */
    public DataClient(String s, int p){
        this.server= s;
        this.port= p;
    }
    
    /**Fixa el nom del host on hi ha el DataServer*/
    public void setServer(String host){
        this.server= host;
    }
    
    /**Retorna el nom del host del server que s'ha fixat*/
    public String getServer(){
        return this.server;
    }
    
    /**Fixa el port per on se serveixen les data*/
    public void setServerPort(int port){
        this.port= port;
    }
    
    /**Retonra el value actual del port de data*/
    public int getPort(){
        return this.port;
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
                System.out.println("DataClient: Error while trying to disconnect...");
            }
        }
    }
        
    public void initReceive()
    throws UnknownHostException, IOException{
        // Obrim un socket connected al server i al número de port
        this.receive= true;
        start();
    }
    
    /**Amb aquest metode es fixa l'objecte Event que es cridara cada cop que l'objecte
     * remot DataServer notifiqui un event que s'hagi produit en la execucio de l'systemPlatform.
     */
    public void initNotifications(Event e)
    throws UnknownHostException, IOException {
        this.event= e;
        this.initReceive();
    }
    
    /** Amb aquest metode es para el tractament a les notificacions de l'ojbecte remot
     * DataServer.
    */
    public void endReceive(){
        this.receive= false;
        if(t!=null)
            this.t.stop();
        this.t= null;
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
    
    /**Metode que s'executa en segon pla i que va receive data
    */
    public void run() {
        int ne; // numero d'event
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