/* parameter handling class that implements specific methids to proper
set the parameters values in the parameter table */

package RT_App_Files;

import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;


public class Param  extends Action implements Serializable{
        int parameters[] = null; 
        double values[] = null;

        public Param(int p[], double v[]){
            parameters= p;
            values= v;
        }
	
        public void execute()
        throws IOException, NullPointerException {
            if( parameters != null && values != null)
                if(control!=null)
                    for(int i=0; i< parameters.length; i++)
                        control.set(parameters[i], values[i]);
                     
                else{
                    NullPointerException e = new NullPointerException("Param Error. Null Control pointer!");
                    throw e;
                }
	}
        
        public void reset() {
        }
        
        public Action forward(){
            if(anterior!=null)
                return anterior.forward();
            else 
                return null;
	}
        
        public Action actual(){
            return this;
        }
        
        public StringBuffer write(int depth, Action actual){
            StringBuffer ret = new StringBuffer("Param ");
            for(int i=0; i< parameters.length; i++)
                ret.append("(" + parameters[i] + ", " + values[i] + ") ");
            if( this.equals(actual))
                ret.append("  <--\n");
            else
                ret.append("\n");
            return ret.insert(0, space(depth));
        }
        
}
