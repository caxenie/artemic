/* class that implements specific Grafcet control elements */

package RT_App_Files;

import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;


public class Grafcet implements Serializable{
	DoIt list;
        Action anterior;
	Action actual;

        private void ini_Grafcet(){
            list=new DoIt(1);
            actual= null;
            anterior = null;
        }
        
        public Grafcet(){
            ini_Grafcet();
        }
      
        public Grafcet(Control c){
            ini_Grafcet();            
            list.setControl(c);
        }
        
        public void setControl(Control c){
            list.setControl(c);
        }
        
        public Control getControl(){
            return list.getControl();
        }
	
        public int effectuate(Action a){
                if(a!=null){
                    list.effectuate(a);
                    a.set_anterior(list);
                    if(list.list.size()==1){
                        Action aux = (Action) list.list.elementAt(0);
                        actual=aux.actual();
                    }
                }else System.out.println("SystemPlatform: Error. Trying to execute a null action!");
		return list.list.size();
	}

        public void execute()
        throws IOException {
		if(actual!= null)
			actual.execute();
	}
        
        public void reset(){
            this.list.reset();
            this.anterior= null;
            this.actual= list.actual();
        }
        
        public Action advance(){
            Action ret;
            if(actual!=null){
                actual= actual.forward();
                ret= actual;
            }else ret=null;
            return ret;
        }
	
        public boolean end(){
		return actual==null;
	}
        
        public Action actual() {
            return list.actual();
        }
        
        public StringBuffer write(){
            StringBuffer ret = new StringBuffer();
            Action a;
            for(int i=0; i< list.list.size(); i++){
                a= (Action) list.list.elementAt(i);
                ret.append(a.write(0, this.actual()));
            }                
            return ret;
        }        
}
