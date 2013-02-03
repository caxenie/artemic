/*define specific system Grafcet structure */

package RT_App_Files;

import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;

public class SysPlatform implements Runnable{
    public Grafcet grafcet; 
    public Event event; 

    protected Thread t; 
    protected boolean executing=false; 
    protected Control control=null; 

    public SysPlatform(){
        grafcet = new Grafcet();
    }

   
    public SysPlatform(Control c)
    throws UnknownHostException, IOException{
	grafcet = new Grafcet(c);
        this.control = new Control(c.getHost(), c.getPort());
    }
   
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
    
    public Control getControl(){
        return this.control;
    }
    
    public void disconnect(){
        if(this.control.connected())
            try{ this.control.disconnect(); }catch(Throwable ignored){}
    }
  
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

    public void setGrafcet(Grafcet g){
        grafcet= g;
    }

    public Grafcet getGrafcet(){
        return grafcet;
    }
    
    public void save(String file){
  
        try{
            FileOutputStream fos= new FileOutputStream(file);
            ObjectOutputStream oos=new ObjectOutputStream(fos);
            oos.writeObject(grafcet);
            oos.flush();
            oos.close();
        }catch(Exception e){ System.out.println(e.getMessage()); }        
    }
    
    public void restore(String file){
       
        try{
            FileInputStream fis= new FileInputStream(file);
            ObjectInputStream ois= new ObjectInputStream(fis);
            grafcet= (Grafcet) ois.readObject();
            ois.close();
        }catch(Exception e){ System.out.println("SysPlatform: Error fetching the grafcet: "+e.getMessage()); }                
    }
    
    public void setEvent(Event e){
        this.event= e;
    }
    
    public Event getEvent(){
        return this.event;
    }
    
    public void start(){
        t = new Thread( this );
        if( event!=null)
            event.signal(EventCode.START);
        t.start();
    }
    
  
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
    
    public void pause(){
        if(t!=null)
            t.stop();
        this.executing= false; 
        if( event!=null) 
            event.signal(EventCode.PAUSE);
    }
    
    public void sleep(int ms){
        try {
            Thread.sleep( ms );
        }catch( InterruptedException e ) { System.out.println(e.getMessage()); };
    }
  
    public class EventCode{
        public final static int START=0;
        public final static int STOP=1;
        public final static int ADVANCE=2;
        public final static int PAUSE=3;
        public final static int END=4;
        public final static int ERROR=-1;
    }
}

