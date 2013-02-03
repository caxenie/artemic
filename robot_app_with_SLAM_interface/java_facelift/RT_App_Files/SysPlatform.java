/*
 * SysPlatform.java
 * \brief Permet execute en segon pla un SysPlatform, save-lo i restore-lo
 * \brief a m�s d'informar dels events produ�ts.
 */

package RT_App_Files;

import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;

/** Class SysPlatform
 * Aquesta classe serveix per a controlar l'systemPlatform. Conte un objecte Grafcet format
 * per Accions que defineix l'systemPlatform. Aquest objecte Grafcet es pot gravar a disc
 * o restore-lo.
 * La classe SysPlatform implementa Runnable per poder llencar la execucio de l'systemPlatform
 * en un thrd d'execucio en que se li pot fer start, stop i pause.
 * A mes a mes, es pot assignar un objecte Event al qual es cridarà cada cop que es
 * produeixi un event d'engegada, parada, avanc o error en l'systemPlatform. Aquest objecte
 * Event permetrà actualitzar data, notificar events, llegir dels sensors, ...
 */
public class SysPlatform implements Runnable{
    public Grafcet grafcet; /**<Referencia al grafcet de l'systemPlatform*/
    public Event event; /**<Referencia a l'objecte al que se li notificaran els events*/

    protected Thread t; /**<Objecte Thread pel maneig del thrd d'execucio*/
    protected boolean executing=false; /**<Flag per saber si s'esta executing*/
    protected Control control=null; /**<Serveix per tenir control per parar l'systemPlatform fent stop()*/

    /** Constructor. Inicialitza el grafcet per evitar que sigui nul.*/
    public SysPlatform(){
        grafcet = new Grafcet();
    }

    /** Constructor que inicialitza el grafcet i assigna l'objecte control per a totes les Accions.*/
    public SysPlatform(Control c)
    throws UnknownHostException, IOException{
	grafcet = new Grafcet(c);
        this.control = new Control(c.getHost(), c.getPort());
    }
    
    /** Amb aquest metode fixa el control al grafcet i es guarda un control per poder fer un stop asincron*/
    public void setControl(Control c){
        grafcet.setControl(c);
        if(c!=null)
            if(c.connected)
                try{
                    this.control = new Control(c.getHost(), c.getPort());
                }catch(Throwable e){}
            else
                this.control = c;
    }
    
    /** Aquest metode retorna la referencia actual a l'objecte control de l'systemPlatform*/
    public Control getControl(){
        return this.control;
    }
    
    /** Aquest metode serveix per desonnectar el control de l'systemPlatform*/
    public void disconnect(){
        if(this.control.connected())
            try{ this.control.disconnect(); }catch(Throwable ignored){}
    }
    /**Aquest metode s'executa en un altre thrd quan es crida start(). Va executing i avancant el grafcet
     * de l'systemPlatform.
     */
    public void run() {
        executing= true;
        try{
            while(!grafcet.end() && executing){
                grafcet.execute();
                grafcet.advance();
                if( event!=null)
                    event.signal(EventCode.ADVANCE);
            }            
            if(event != null && executing)
                event.signal(EventCode.END);
        }catch(IOException ioe){
            if(executing){
                System.out.println("SysPlatform: Execution error...closing socket " + ioe.getMessage());
                if(event!=null)
                    event.signal(SysPlatform.EventCode.ERROR);
            }
        }catch(NullPointerException npe){
            System.out.println("SysPlatform: Error. null pointer.");
            if(event!=null)
                event.signal(SysPlatform.EventCode.ERROR);
        }
        executing= false;
    }

    /** Fixa la referencia al grafcet g*/
    public void setGrafcet(Grafcet g){
        grafcet= g;
    }

    /** Retorna el grafcet referenciat en l'systemPlatform*/
    public Grafcet getGrafcet(){
        return grafcet;
    }
    
    /** Desa l'objecte Grafcet en el seu estat actual en el file passat com a parametre*/
    public void save(String file){
        //guardem l'objecte grafcet en el file:
        try{
            FileOutputStream fos= new FileOutputStream(file);
            ObjectOutputStream oos=new ObjectOutputStream(fos);
            oos.writeObject(grafcet);
            oos.flush();
            oos.close();
        }catch(Exception e){ System.out.println(e.getMessage()); }        
    }
    
    /** Recupera l'objecte Grafcet guardat en el file passat com a parametre d'entada*/
    public void restore(String file){
        //recuperem el grafcet del file
        try{
            FileInputStream fis= new FileInputStream(file);
            ObjectInputStream ois= new ObjectInputStream(fis);
            grafcet= (Grafcet) ois.readObject();
            ois.close();
        }catch(Exception e){ System.out.println("SysPlatform: Error fetching the grafcet: "+e.getMessage()); }                
    }
    
    /** Fixa l'objecte Event al qual es notificaran els events d'start, stop, avanca o error*/
    public void setEvent(Event e){
        this.event= e;
    }
    
    /** Retorna la referencia a l'objecte Event*/
    public Event getEvent(){
        return this.event;
    }
    
    /** Inicia el thread que executa el grafcet*/
    public void start(){
        t = new Thread( this );
        if( event!=null)
            event.signal(EventCode.START);
        t.start();
    }
    
    /** Para de forma immediata l'systemPlatform. Fa servir un altre control diferent
     * al de la referencia. El motiu es que necessitem un altre canal de peticions
     * diferent.
     **/
    public void stop()
    throws IOException{
        if( t!=null){
            t.stop();
            t= null;
        }
	executing= false;
        if( event!=null)
            event.signal(EventCode.STOP);
        control.stop();          
    }
    
    /** Para el thread que executa l'systemPlatform pero la phase actual acaba.*/
    public void pause(){
        if(t!=null)// si hi ha un thrd el parem
            t.stop();
        this.executing= false; // posem el flag d'executing-se a fals
        if( event!=null) // enviem el signal de pause
            event.signal(EventCode.PAUSE);
    }
    
    /** Serveix per fer una pause de ms milisegons.*/
    public void sleep(int ms){
        try {
            Thread.sleep( ms );
        }catch( InterruptedException e ) { System.out.println(e.getMessage()); };
    }
    
    /** class EventCode
     * Aquesta classe serveix nomes per tenir les constants dels codis dels diferents
     * esdeveniments.
     */
    public class EventCode{
        public final static int START=0;
        public final static int STOP=1;
        public final static int ADVANCE=2;
        public final static int PAUSE=3;
        public final static int END=4;
        public final static int ERROR=-1;
    }
}

