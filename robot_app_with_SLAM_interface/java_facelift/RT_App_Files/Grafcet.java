/*
 * Grafcet.java
 * \brief Cont� la estructura de l'systemPlatform en forma de bucles, execucions de phase
 * \brief i parametritzacions.
 */


package RT_App_Files;

import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;

/**
 * class Grafcet
 * Aquesta classe conte la estructura de l'systemPlatform. Implementa Serializable per
 * a poder save l'estat del grafcet en un file o passar-lo per la xarxa.
 */
public class Grafcet implements Serializable{
	DoIt list;/**<Llista d'accions inicial del grafcet*/
        Action anterior;/**<Refereccia a la accio anterior*/
	Action actual;/**<Referencia a la Action actual que s'ha d'execute*/
        
        /**Inicialitza els fields i la list inicial d'accions*/
        private void ini_Grafcet(){
            list=new DoIt(1);
            actual= null;
            anterior = null;
        }
        
        /**Constructor que inicialitza els fields*/
        public Grafcet(){
            ini_Grafcet();
        }
        
        /**Constructor que fixa la referencia a l'objecte Control per a tots
         * els objectes Action*/
        public Grafcet(Control c){
            ini_Grafcet();            
            list.setControl(c);
        }
        
        /** Fixa la referencia a l'objecte control en la list d'accions*/
        public void setControl(Control c){
            list.setControl(c);
        }
        
        /** Retorna la referencia al control de la list d'accions*/
        public Control getControl(){
            return list.getControl();
        }
	
        /**Afegeix un objecte Action a la list inicial d'accions del grafcet*/
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
	
        /**Executa l'accio actual del Grafcet*/
        public void execute()
        throws IOException {
		if(actual!= null)
			actual.execute();
	}
        
        /**Inicialitza tots els objectes Action*/
        public void reset(){
            this.list.reset();
            this.anterior= null;
            this.actual= list.actual();
        }
        
        /**Avanca en les accions a realitzar. Se sol cridar advance() despres d'execute()*/
        public Action advance(){
            Action ret;
            if(actual!=null){
                actual= actual.forward();
                ret= actual;
            }else ret=null;
            return ret;
        }
	
        /**Retorna CERT si ja no queden accions a realitzar i per tant no es pot advance mes*/
        public boolean end(){
		return actual==null;
	}
        
        /**Retorna l'objecte Action actual de la list*/
        public Action actual() {
            return list.actual();
        }
        
        /**Retorna l'String on es pot veure l'estat del grafcet*/
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
