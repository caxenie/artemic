/* plot specifc signals from the robot
currently just the currents from the motors 
TODO 
-implement all parameter monitorization
-real time visualisation system
*/
import java.awt.Canvas;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics2D;
import java.awt.image.BufferStrategy;

import javax.swing.*;
import java.awt.*;

import java.awt.event.*;

import RT_App_Files.Control; 

public class Grafic extends Canvas implements Runnable{
    Control control = null;
    
    Thread thrd = null;
    private BufferStrategy strategy;
    public static final int WIDTH = 550;
    public static final int HEIGHT = 450;
    
    
    private int factorH = 50;
    private  int factorV = 28;
    private double factor;
    double value;
    private int xGraph, yGraph= 0;
    
    private int xValue;
    //private int xAnterior, yAnterior;
    private int grafic1X[] = new  int[WIDTH/2];
    private int grafic1Y[] = new  int[WIDTH/2];
    private int grafic2X[] = new  int[WIDTH/2];
    private int grafic2Y[] = new  int[WIDTH/2];
    private int counter;
    
    public Grafic(Control c){
        
        control = c;
        
        xValue = 0;
       
        counter = 0;
        factor = (double)HEIGHT / 18000.0;
         
        final Grafic auxg = this;
        JFrame thewindow = new JFrame("Signal Viewer");
      
               
        thewindow.addWindowListener(new WindowAdapter(){
            public void windowClosing(WindowEvent e){
                System.out.println("closing window");
                auxg.stop();
            }
        }
        );

        JPanel panel = (JPanel)thewindow.getContentPane();
        setBounds(0,0,WIDTH,HEIGHT);
        panel.setLayout(null);
        panel.add(this);
  
        thewindow.setBounds(0,0,WIDTH,HEIGHT);
        thewindow.setVisible(true);
        thewindow.setResizable(false);
       
        createBufferStrategy(2); 
        strategy = getBufferStrategy(); 
        gameLoop();
    }
    
    
    public void gameLoop() {
        Graphics2D g2 = (Graphics2D) strategy.getDrawGraphics();    
        g2.setRenderingHint(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_SPEED);
        
        g2.setColor(Color.GRAY);
        g2.fillRect(0,0,getWidth(),getHeight());

        g2.setColor(Color.LIGHT_GRAY);
        g2.drawLine(0, 0, 0, getHeight() - 1);
        g2.drawLine(1, 0, 1, getHeight() - 1);
        g2.drawLine(2, 0, 2, getHeight() - 1);
        for(int i = factorH; i < getWidth(); i += factorH)
            g2.drawLine(i - 1, 0, i - 1, getHeight() - 1);
        for(int i = factorV; i < getHeight(); i += factorV)
            g2.drawLine(0, i - 1, getWidth() - 1, i - 1);
        g2.drawLine(0, 250, getWidth() - 1, 250);
        g2.drawLine(0, 252, getWidth() - 1, 252);
         
        xValue += 2;
            
       try{
        if(xValue < getWidth() ){
            value = control.sensor.get( RobotClient.S.SCA_1 );// graphical output values
            
           
            if(value >= 0)
                yGraph = (int)-(value * factor - (double)HEIGHT / 2.0); 
            else
                yGraph = (int)(-value * factor + (double)HEIGHT / 2.0); 
            
            grafic1X[counter] = xValue;
            grafic1Y[counter] = yGraph;
            
            value = control.sensor.get( RobotClient.S.SCA_2 );
            
            if(value >= 0)
                yGraph = (int)-(value * factor - (double)HEIGHT / 2.0);             
            else
                yGraph = (int)(-value * factor + (double)HEIGHT / 2.0); 
                        
            grafic2X[counter] = xValue;
            grafic2Y[counter] = yGraph;
            counter++;

            g2.setColor(Color.red);
            g2.drawPolyline(grafic1X, grafic1Y, counter);
            g2.setColor(Color.yellow);
            g2.drawPolyline(grafic2X, grafic2Y, counter);
        }
        else{
            counter = 0;
            xValue = 0;
        }
        //g2.dispose();
        strategy.show();
       }catch(Throwable e){
           JOptionPane.showMessageDialog(null, "Grafic: Communication closed.", "Error", JOptionPane.ERROR_MESSAGE);
           this.stop();
       }
    
    }
    
     public void start() {
       if (thrd==null) {
        thrd = new Thread(this);
        thrd.start();
       }
    } 
 
    public void stop() {
        thrd = null;
    }
    
    public void run() {
        while (thrd!=null && thrd.isAlive()) {
          gameLoop();
          try {
             
             thrd.sleep(40);
          }catch (InterruptedException e) {} 
        }
    }
}


