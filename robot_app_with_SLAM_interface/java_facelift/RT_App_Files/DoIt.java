/*
 * DoIt.java
 * \brief Es un bucle d'objectes Action del Grafcet de l'SystemPlatform.
 */

package RT_App_Files;

import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;

/** class DoIt
 * Exten la classe Action per fer iteraccions sobre accions. D'aquesta forma
 * es permet fer bucles de parts de l'systemPlatform.
 */
public class DoIt extends Action{
	int i; /**<Numero d'iteracio actual*/
	int N; /**<Nombre totat d'iteracions*/
	public Vector list; /**<Llista d'Accions que es realitzen en cada iteracio*/
        int j; /**<Action actual de la list de la iteracio*/

        /** Constructor */
        public DoIt(){
		i=0; N=0; j=0;
        	list = new Vector();
        }

        /** Constructor que fixa en nombre d'iteracions total*/
        public DoIt(int n){
            if(n>0) N=n;
            else N=0;
            i=0; j=0;
            list = new Vector();
        }
	
        /**La execucio d'un DoIt no produeix cap resultat*/
        public void execute() throws IOException{
	}
        
        /**Inicialitza l'objecte DoIt amb les iteracions a zero*/
        public void reset(){
            Action aux= null;
            for(int i=0; i<list.size(); i++){
                aux=(Action) list.elementAt(i);
                aux.reset();
            }
            i=0;
            j=0;
        }
	
        /**Avanca en la list d'accions o en el nombre d'iteracions. Si ja esta
         * tot realitzat llavors crida al metode forward() de la accio anterior.*/
        public Action forward(){
            Action ret;
            j++;
            if( j<list.size()){ // si ens queden accions dins del fer
                Action a = (Action) list.elementAt(j);
                ret = a.actual();
            }else{ // si totes les accions del fer estan fetes
                j=0;
                i++;
                if(i<N){ // si queden iteracions
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
        
        /**Retorna la referencia a l'objecte Action que cal execute*/
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
	
        /**Afegeix una accio a la list del DoIt*/
        public int effectuate(Action a){
                if(a!=null){
                    list.add(a);
                    a.set_anterior(this);
                }else System.out.println("DoIt: Error. Trying to make a null action...");
		return list.size();
	}
	
        /**Afegeix una accio a la list en una determinada posicio*/
        public int effectuate(Action a, int index){
		list.add(index, a);
		return list.size();
	}
	
        /**Fixa en numero d'iteracions total*/
        public int set_n( int n){
		int ret;
		ret= N;
        	N= n;
		return ret;
	}
	
        /**Retorna el numero d'iteracions total*/
        public int get_n(){
		return N;
	}
	
        /**Fixa el numer d'iteracio actual*/
        public int set_i(int nou_i){
		int ret=i;
		i=nou_i;
		return i;
	}
	
        /**Retorna el numero d'iteracio actual*/
        public int get_i(){
		return i;
	}
	
        /*Fixa el numero d'accio de la list a execute*/
        public int set_j(int nou_j){
		int ret=j;
		j=nou_j;
		return j;
	}
	
        /**Retorna el numero de la list que s'ha d'execute*/
        public int get_j(){
		return j;
	}
        
        /**Retorna l'String on es pot veure l'estat del DoIt i el cos del bucle*/
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
