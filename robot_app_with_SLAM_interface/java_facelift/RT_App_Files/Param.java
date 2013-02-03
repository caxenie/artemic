/*
 * Param.java
 * \brief Es una acció de l'systemPlatform que permet parametritzar-lo amb una list de
 * \brief paràmetres i de values.
*/

package RT_App_Files;

import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;

/* Class Param
 * Serveix per parametritzar l'systemPlatform en un moment donat. Hereta de la classe Action
 * i es part del Grafcet.
 * Implementa Serialitzable per la qual cosa es pot save a disc.
 */
public class Param  extends Action implements Serializable{
        int parameters[] = null; /**<Llista de numeros de parameters*/
        double values[] = null;/**<Llista dels values dels parameters*/
        

        /**Constructor que fixa la referencia al vector de parameters i al de values.
         * La llargada dels dos vectors ha de ser la mateixa i el parametre "i" es 
         * fixara amb el value "i"
         */
        public Param(int p[], double v[]){
            parameters= p;
            values= v;
        }
	
        /**En la seva execucio fa servir l'objecte Control per a parametritzar remotament
         * els parameters en la execucio de l'systemPlatform*/
        public void execute()
        throws IOException, NullPointerException {
            if( parameters != null && values != null)
                if(control!=null)
                    for(int i=0; i< parameters.length; i++)
                        control.set(parameters[i], values[i]);
                        control.set_diagnosis(parameters[i], values[i]);
                else{
                    NullPointerException e = new NullPointerException("Param Error. Null Control pointer!");
                    throw e;
                }
	}
        
        /** No realitza cap accio*/
        public void reset() {
        }
        
        /**Avanca en el grafcet*/
        public Action forward(){
            if(anterior!=null)
                return anterior.forward();
            else 
                return null;
	}
        
        /**Retorna el mateix objecte*/
        public Action actual(){
            return this;
        }
        
        /**Retorna un String on es pot veure les parelles de parametre-value*/
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
