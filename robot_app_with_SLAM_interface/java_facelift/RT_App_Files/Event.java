/*
 * Event.java
 * \brief Els objectes derivats s'encarreguen de realitzar accions quan es
 * \brief produeix un event en l'systemPlatform (start, stop, pause, error).
 */

package RT_App_Files;

/** class Event
 *  Aquesta classe abstracta serveix execute una classe filla en moments
 * assincrons en la execucio de l'systemPlatform. Nomes cal implementar el metode
 * void signal(int) que s'encarrega de tractar el tipus d'event.
 */
public abstract class Event {
    
    int signal;

    /** Constructor  */
    public Event(){
    }
 
    abstract public void signal(int signal);

}
