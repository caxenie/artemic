/* event driven comm support*/

package RT_App_Files;

public abstract class Event {
    
    int signal;

   
    public Event(){
    }
 
    abstract public void signal(int signal);

}
