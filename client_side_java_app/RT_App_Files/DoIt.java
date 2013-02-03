/* class that ensures that proper actions are executed on time 
multiple checks on comm parameters and execution flow*/

package RT_App_Files;

import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;


public class DoIt extends Action{
	int i; 
	int N; 
	public Vector list; 
        int j; 

        public DoIt(){
		i=0; N=0; j=0;
        	list = new Vector();
        }

    public DoIt(int n){
            if(n>0) N=n;
            else N=0;
            i=0; j=0;
            list = new Vector();
        }
	
        public void execute() throws IOException{
	}
        
        public void reset(){
            Action aux= null;
            for(int i=0; i<list.size(); i++){
                aux=(Action) list.elementAt(i);
                aux.reset();
            }
            i=0;
            j=0;
        }
	
        public Action forward(){
            Action ret;
            j++;
            if( j<list.size()){ 
                Action a = (Action) list.elementAt(j);
                ret = a.actual();
            }else{ 
                j=0;
                i++;
                if(i<N){ 
                    this.reset();
                    if(list.size()>0){
                        Action a= (Action) list.elementAt(0);
                        ret= a.actual();
                    }else ret= null;
                }else{
                    if(anterior!=null){
                        ret= anterior.forward();
                    }else ret= null;
                }
            }
            return ret;
	}
        
	public Action actual(){
            Action ret;
            if(i<N && j<list.size()){
                    Action a= (Action) list.elementAt(j);
                    ret= a.actual();
            }else{
                    if( anterior!=null)
                        ret= anterior.forward();
                    else ret= null;
            }
            return ret;
        }
	
        public int effectuate(Action a){
                if(a!=null){
                    list.add(a);
                    a.set_anterior(this);
                }else System.out.println("DoIt: Error. Trying to make a null action...");
		return list.size();
	}
	
        public int effectuate(Action a, int index){
		list.add(index, a);
		return list.size();
	}
	
        public int set_n( int n){
		int ret;
		ret= N;
        	N= n;
		return ret;
	}
	
        public int get_n(){
		return N;
	}
	
        public int set_i(int nou_i){
		int ret=i;
		i=nou_i;
		return i;
	}
	
        public int get_i(){
		return i;
	}
	
        public int set_j(int nou_j){
		int ret=j;
		j=nou_j;
		return j;
	}
	
        public int get_j(){
		return j;
	}
        
        public StringBuffer write(int depth, Action actual){
            StringBuffer ret = new StringBuffer("do "+i+" "+N+"\n");
            ret.insert(0, space(depth));
            Action aux;
            for(int i=0; i<list.size(); i++){
                aux=(Action) list.elementAt(i);
                ret.append(aux.write(depth+2, actual));
            }
            ret.append(space(depth)+" do \n");
            return ret;
        }
}
