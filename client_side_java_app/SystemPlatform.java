
import java.util.StringTokenizer;
import java.io.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.filechooser.*;
import RT_App_Files.*;
import java.lang.String.*;

public class SystemPlatform {
    File file=null;
    DataInputStream dis=null;
    boolean fi=false;
    
    Grafcet g=null;
    String s=null;
 
    public SystemPlatform(File f) {
        file = f;
        g= new Grafcet();
    }
    public Grafcet getGrafcet(){
        return g;
    }
    public void platform(){
        try{
            FileInputStream fis = new FileInputStream(file);
            dis = new DataInputStream(fis);
            fi= false;
            int i=0;
         
            String [] p= null;
            int n_tokens=0;
            while(!fi){
                p= new String[100];
                n_tokens= readTheLine(p);
                if(n_tokens>0){
                    if(p[0].compareTo("//")==0){
                        ;
                    }else if(p[0].compareTo("param")==0){
                        int param[]= new int [n_tokens-1];
                        double val[]= new double [n_tokens-1];
                        for(i=0; i<n_tokens-1; i++){
                            param[i]=i;
                            val[i]=Double.parseDouble(p[i+1]);
                        }
                        this.g.effectuate(new Param(param, val));
                    }else if(p[0].compareTo("phase")==0){
                        g.effectuate(new Phase( Integer.parseInt(p[1]), Integer.parseInt(p[2]) ));
                    }
                }
                if(dis.available()==0)
                    fi= true;
            }            
        }catch(EOFException eof){ 
            fi=true;
        }catch(FileNotFoundException fne){
        }catch(IOException ioe){
        }
    }
    public String returnContent(){
        return s;
    }
    protected int readTheLine(String [] retorn)
    throws EOFException{
        boolean fil;
        int ret=0;       
        int i=0;
        try{
            StringTokenizer tokens = new StringTokenizer(dis.readLine());
            ret= tokens.countTokens();
            for( i=0; i< ret; i++){
                retorn[i]= tokens.nextToken();
            }
        }catch(IOException ioe){
        }
        return ret;
    }
}
