/*
 * Data.java
 * \brief Serveix per consultar i save les data de l'systemPlatform.
 */

package RT_App_Files;

import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;

/** class Data
 * Aquesta classe serveix per portar les data de l'systemPlatform. Esta pensada per
 * sobreescriure els metodes de "fillData()" i "write()" que serveixen
 * per emplenar les data i mostrar-les per pantalla respectivament.
 * Aixi doncs, una classe que hereti pot omplir les data consultant-les a traves
 * d'un objecte Control i aquestes es podrien consultar remotament pels DataClient
 * a traves del DataServer.
 * A més ofereix metodes per gravar les data a disc en fomrat XML.
 */
public class RemoteData {
    public File file= null; /**<Referencia a l'objecte FILE que es on es guarden les data*/
    RandomAccessFile raf= null;

    public double data[]=null; /**<Referencia a la taula de data*/
    public String fields[]=null; /**<Nom dels campd de la taula de data per al file XML*/

    /** Constructor que no fa res*/
    public RemoteData(){
    }

    /**Constructor que fixa la taula de data */
    public RemoteData(double[] data){
        this.data= data;
    }
    
    /**Metode que emplena les data. Esta pensat per a sobreescriure'l*/
    public void fillData(){
    }
    
    /**Metode per fixar el vector de data*/
    public void setData(double [] data){
        this.data = data;
    }
    
    /**Retorna el vector de data*/
    public double[] getData(){
        return this.data;
    }
    
    /**Retorna l'string que mostra el vector de data*/
    public String write(){
        StringBuffer ret = new StringBuffer("");
        if(data.length>0){
            ret.insert(0,data[0]);
            for(int i=1; i< data.length; i++)
                ret.append(", "+data[i]);
        }
        return ret.substring(0);
    }
    
    /**Obre un nou file i li effectuate la capcalera de XML.
     */
    public void newXMLFile(String file_name)
    throws Throwable{
        file = new File(file_name);
        if(file.createNewFile()){
            raf = new RandomAccessFile(file, "rwd");
            this.writeXMLHeader();
        }else
            throw new Throwable("Data: Error. Cannot create the file.");
    }
    
    /**Prepara el file que ja conte data XML per a continuar-lo.
     */
    public void continueXMLFile(String file_name)
    throws IOException, Throwable {
        file = new File(file_name);
        if(file.length()>40){ // si el file ja esta comencat
            raf = new RandomAccessFile(file, "rwd");
            raf.setLength(raf.length()-10);
            raf.seek(raf.length());
            Date d= new Date();            
            raf.writeBytes("<!-- " + file.getName() + " " + d + " -->\n");
        }else
            this.newXMLFile(file_name);
    }
    
    /**Tanca el file XML posant la finalitzacio correcta.
     */
    public void closeXMLFile()
    throws IOException{
        raf.seek(raf.length());
        raf.writeBytes("</systemPlatform>\n");
        raf.close();
    }
    
    /**Escriu les data al file XML segons els noms dels fields de data i del vector de data
     */
    public void writeDataInXMLFile()
    throws IOException{
        raf.writeBytes("\t<dada ");
        for(int i=0; i< data.length; i++)
            raf.writeBytes( fields[i]+ "='" + data[i] + "' ");
        raf.writeBytes("/>\n");
    }
    
    /**Fixa la referencia al vector amb les descripcions dels fields de data.
     */
    public void setDescriptionFieldsXML( String [] fields){
        this.fields= fields;
    }
    
    /**Escriu la capcalera del file XML posant en nom del file i la data.
     */
    protected void writeXMLHeader()
    throws IOException{
        raf.writeBytes("<?xml version=\"1.0\" standalone='yes' ?>\n");
        Date d = new Date();
        raf.writeBytes("<!-- " + file.getName() + " " + d + " -->\n");
        raf.writeBytes("<systemPlatform>\n");
    }
} 
