/* to separate specific operations during execution */

package RT_App_Files;

import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;

 
public class Operation implements Serializable {
    protected int operation;
    protected double parameters[];

    public Operation(int operation, double [] ent){
        this.operation= operation;
        this.parameters= ent;
    }
}
