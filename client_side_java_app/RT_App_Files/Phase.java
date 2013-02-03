/* implements specific phase elements during Grafcet execution */

package RT_App_Files;

import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;


public class Phase extends Action {
        int phase=-1; 
        int n=0;
        int i=0;

        public Phase(int nr_phase, int nr_data){
            phase= nr_phase;
            n= nr_data;
        }
	// execute phase
        public void execute()
        throws IOException, NullPointerException {
            if(i<n)
                if(control!= null)
                    control.exe_phase(phase);
                else{
                    NullPointerException e = new NullPointerException("Phase Error. Null Control pointer!");
                    throw e;
                }
	}

        public void reset() {
            i=0;
        }
	
   	// next action 
        public Action forward(){
		Action ret;
                i++;
                if(i<n) ret=this;
                else{
                    if(anterior==null) ret=null;
                    else ret= anterior.forward();
                }
		return ret;
	}
        
        public Action actual(){
            return this;
        }
        
   
        public StringBuffer write(int depth, Action actual){
            StringBuffer ret = new StringBuffer("phase " + phase + " " + i + "/" + n);
            if( this.equals(actual))
                ret.append("  <--\n");
            else
                ret.append("\n");
            return ret.insert(0, space(depth));
        }
        
}
