/**
 * Operation.java
 * \brief Serveix per demanar operacions des de la classe DataClient a la classe
 * \brief DataServer.
 */

package RT_App_Files;

import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;

 /** class Operation
  * Serveix per a realitzar peticions d'operation remotament. Conte un camp per
  * al codi de la operation i un vector de parameters d'input de tipud double.
  * Aquesta classe la fa servir la classe DataClient per demanar accions a la 
  * classe DataServer. 
 */
public class Operation implements Serializable {
    protected int operation;/**<Code de la operation*/
    protected double parameters[];/**<Vector de parameters d'input*/
    
    /**
     * Constructor que fixa el numero d'operation i els parameters d'input.
     */
    public Operation(int operation, double [] ent){
        this.operation= operation;
        this.parameters= ent;
    }
}
