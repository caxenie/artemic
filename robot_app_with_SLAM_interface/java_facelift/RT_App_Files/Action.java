/*
 * Action.java
 * \brief Classe base per a les diferents accions de que es composa un Grafcet
 * \brief com són Phase, Param i DoIt.
 */

package RT_App_Files;

import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;

/** class Action
 * Aquesta es una classe base per a les diferents accions de que es composa un
 * systemPlatform. Aixi doncs un objecte Grafcet tindra una estructura d'accions.
 * Les accions podran ser execute fases (Phase), parametritzar l'systemPlatform (Param)
 * i fer iteracions sobre les accions anteriors (DoIt).
 * Aquesta classe implementa la interficie Serialitzable per a poder passar
 * l'systemPlatform a traves d'un stream per save-lo a disc o passar-lo per xarxa.
 */
public abstract class Action implements Serializable{
	protected Action anterior=null; /**< Referencia a la accio que conte aquesta instancia*/
        static Control control; /**< El cotrol sera comu per a totes les accions*/

        /** Contructor. Simplement posa la referencia a la Action anterior a nul*/
        public Action(){
            anterior=null;
        }
        
        /** Amb aquest constructor s'assigna un control per a totes les accions ja que
         *aquest camp es estatic i per tant compartit entre tots els objectes que heretin
         *d' Action.*/
        public Action(Control c){
            anterior=null;
            control=c;
        }
	
        /**Cada tipus d'Action ha de tenir el seu tipus d'execucio. D'aquesta forma
         *es podran execute les fases o parametritzar l'systemPlatform.*/
        public abstract void execute() throws IOException;
        
        /**Serveix per inicialitzar l'accio.*/
        public abstract void reset();
	
        /** Pot ser que una Action realitzi mes d'una accio en la seva execucio i per
         *tant hi ha diferents formes d'advance.*/
        public Action forward(){
            if(anterior!=null) return anterior.forward();
            else return null;
        }

        /** Per defecte l'actual serva l'objecte Action mateix pero aquesta varia per als
         * objectes de DoIt*/
        public Action actual(){
            return this;
        }
        
        /** Fixa la referencia a l'accio anterior.*/
        public void set_anterior(Action a){
            if(a != null ){
                anterior=a;
            }else System.out.println("Action: Error. The reference to the last stage is null.");
        }
        
        /** Fixa la referencia a un objecte Control. El control sera comu per a tots els
         * objectes d'Action i serveix per execute fases i parametritzar l'systemPlatform remotament.*/
        public void setControl(Control c){
            control=c;
        }
        
        /** Retorna la referencia a l'objecte Control de la Action.*/
        public Control getControl(){
            return control;
        }
        
        /** Serveix per write la descripcio de la Action per pantalla. La depth
         *marca en quin bucle es troba i serveix simplement per tabular la output per pantalla.*/
        abstract public StringBuffer write(int depth, Action actual);
        
        /** Afegeix l'space per tabular la output per pantalla de la descripcio de la Action.*/
        protected StringBuffer space(int depth){
            StringBuffer ret = new StringBuffer(depth);
            for(int i=0; i<depth; i++)
                ret.append(" ");
            return ret;
        }

}
