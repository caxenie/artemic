/* acces remote data using a specific function interface */

package RT_App_Files;

import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;


public class RemoteData {
    public File file= null; 
    RandomAccessFile raf= null;

    public double data[]=null; 
    public String fields[]=null; 

    public RemoteData(){
    }

    public RemoteData(double[] data){
        this.data= data;
    }
    
    public void fillData(){
    }
    
    public void setData(double [] data){
        this.data = data;
    }
    
    public double[] getData(){
        return this.data;
    }
    
    public String write(){
        StringBuffer ret = new StringBuffer("");
        if(data.length>0){
            ret.insert(0,data[0]);
            for(int i=1; i< data.length; i++)
                ret.append(", "+data[i]);
        }
        return ret.substring(0);
    }
    
    
    public void newXMLFile(String file_name)
    throws Throwable{
        file = new File(file_name);
        if(file.createNewFile()){
            raf = new RandomAccessFile(file, "rwd");
            this.writeXMLHeader();
        }else
            throw new Throwable("Data: Error. Cannot create the file.");
    }
    
    
    public void continueXMLFile(String file_name)
    throws IOException, Throwable {
        file = new File(file_name);
        if(file.length()>40){ 
            raf = new RandomAccessFile(file, "rwd");
            raf.setLength(raf.length()-10);
            raf.seek(raf.length());
            Date d= new Date();            
            raf.writeBytes("<!-- " + file.getName() + " " + d + " -->\n");
        }else
            this.newXMLFile(file_name);
    }
    
    
    public void closeXMLFile()
    throws IOException{
        raf.seek(raf.length());
        raf.writeBytes("</systemPlatform>\n");
        raf.close();
    }
    
    
    public void writeDataInXMLFile()
    throws IOException{
        raf.writeBytes("\t<data ");
        for(int i=0; i< data.length; i++)
            raf.writeBytes( fields[i]+ "='" + data[i] + "' ");
        raf.writeBytes("/>\n");
    }
    
   
    public void setDescriptionFieldsXML( String [] fields){
        this.fields= fields;
    }
    
    protected void writeXMLHeader()
    throws IOException{
        raf.writeBytes("<?xml version=\"1.0\" standalone='yes' ?>\n");
        Date d = new Date();
        raf.writeBytes("<!-- " + file.getName() + " " + d + " -->\n");
        raf.writeBytes("<systemPlatform>\n");
    }
} 
