/*
 * Phase.java
 * \brief Action que executa la una phase i n cops.
 */

package RT_App_Files;

import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;

/** class Phase
 * Exten la classe Action per execute fases. Recordem que la classe base Action conte una referencia
 * a un objecte de la classe Control que servira per execute remotament la classe.
 */
public class Phase extends Action {
        int phase=-1; /**<Numero de phase per a execute*/
        int n=0;/**<Nobre total de cops a execute la phase*/
        int i=0;/**<Nombre d'execucions que s'han fet fins al moment de la phase*/

        /**Constructor que fixa la phase que s'executara i els cops que s'executa.*/
        public Phase(int nr_phase, int nr_data){
            phase= nr_phase;
            n= nr_data;
        }

        /**En el metode execute es crida la execucio de la phase que s'hi fixat*/
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
        /**Posa en numero de cops que s'ha executat la phase a zero*/
        public void reset() {
            i=0;
        }
	
        /** Serveix per advance el l'systemPlatform. Si no s'ha executat el nombre de cops demanat
         * es retornara aquest mateix objecte per a seguir executing la phase.
         */
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
        
        /** La Action actual es l'objecte mateix*/
        public Action actual(){
            return this;
        }
        
        /**Retorna l'String on es veu la phase que s'executa i el nombre de cops total i fins al moment*/
        public StringBuffer write(int depth, Action actual){
            StringBuffer ret = new StringBuffer("phase " + phase + " " + i + "/" + n);
            if( this.equals(actual))
                ret.append("  <--\n");
            else
                ret.append("\n");
            return ret.insert(0, space(depth));
        }
        
}
