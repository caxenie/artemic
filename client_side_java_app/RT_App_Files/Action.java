// class that abtracts and implements specific Action Grafcet element
package RT_App_Files;

import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;

public abstract class Action implements Serializable{
	protected Action anterior=null; 
        static Control control; 

        // ctor
        public Action(){
            anterior=null;
        }
        
       // ctor
        public Action(Control c){
            anterior=null;
            control=c;
        }
	// execute action
        public abstract void execute() throws IOException;
        
       // reset action
        public abstract void reset();
	
       // iterate
        public Action forward(){
            if(anterior!=null) return anterior.forward();
            else return null;
        }
	// get current 
        public Action actual(){
            return this;
        }
        // go back to set past action
        public void set_anterior(Action a){
            if(a != null ){
                anterior=a;
            }else System.out.println("Action: Error. The reference to the last stage is null.");
        }
        // communicate with control 
        public void setControl(Control c){
            control=c;
        }
        // get control instance
        public Control getControl(){
            return control;
        }
        // write action
        abstract public StringBuffer write(int depth, Action actual);
        
        protected StringBuffer space(int depth){
            StringBuffer ret = new StringBuffer(depth);
            for(int i=0; i<depth; i++)
                ret.append(" ");
            return ret;
        }

}
