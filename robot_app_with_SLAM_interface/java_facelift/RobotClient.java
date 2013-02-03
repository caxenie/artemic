/*
 * RobotClient.java
 *
 */
import java.lang.*;
import java.net.*;
import java.io.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.filechooser.*;
import RT_App_Files.*;

public class RobotClient extends javax.swing.JFrame {

     
    class ExecutionEvent extends RT_App_Files.Event{
        public ExecutionEvent(){
        }
        public void signal(int signal) {
            if(signal == SysPlatform.EventCode.ADVANCE){
                txtEvent.setText("Running");
                textSystemPlatform1.setText( sysPlatform.grafcet.write().toString() ); 
            }else if(signal == SysPlatform.EventCode.ERROR){
                txtEvent.setText("Error");
            }else if(signal == SysPlatform.EventCode.PAUSE){
                txtEvent.setText("Pause");
            }else if(signal == SysPlatform.EventCode.START){
                txtEvent.setText("Start");
            }else if(signal == SysPlatform.EventCode.STOP){
                txtEvent.setText("Stop");
            }else if(signal == SysPlatform.EventCode.END){
                txtEvent.setText("END");
            }
        }
    }
    
   
    SysPlatform sysPlatform= null; 
    Control control= null; 
    Control data= null; 
    
    Grafic graf= null;
    
    public RobotClient() {
        initComponents();
        sysPlatform= new SysPlatform();
        this.setBounds(0,0,750,450);
    }
    
    
    private void initComponents() {//GEN-BEGIN:initComponents
        jTabbedPane1 = new javax.swing.JTabbedPane();
        jPanel1 = new javax.swing.JPanel();
        jButton5 = new javax.swing.JButton();
        jButton4 = new javax.swing.JButton();
        jButton3 = new javax.swing.JButton();
        jButton2 = new javax.swing.JButton();
        textSystemPlatform1 = new java.awt.TextArea();
        txtEvent = new javax.swing.JTextField();
        jButton7 = new javax.swing.JButton();
        jPanel2 = new javax.swing.JPanel();
        jLabel2 = new javax.swing.JLabel();
        jLabel3 = new javax.swing.JLabel();
        jLabel4 = new javax.swing.JLabel();
        jLabel5 = new javax.swing.JLabel();
        jLabel6 = new javax.swing.JLabel();
        jLabel7 = new javax.swing.JLabel();
        jLabel8 = new javax.swing.JLabel();
        jLabel9 = new javax.swing.JLabel();
        jLabel10 = new javax.swing.JLabel();
        jLabel11 = new javax.swing.JLabel();
        jSeparator1 = new javax.swing.JSeparator();
        jButton6 = new javax.swing.JButton();
        jButton8 = new javax.swing.JButton();
        jComboFases = new javax.swing.JComboBox();
        jLabel15 = new javax.swing.JLabel();
        txtT11 = new javax.swing.JTextField();
        txtT12 = new javax.swing.JTextField();
        jLabel16 = new javax.swing.JLabel();
        txtT13 = new javax.swing.JTextField();
        jLabel17 = new javax.swing.JLabel();
        txtT14 = new javax.swing.JTextField();
        jLabel18 = new javax.swing.JLabel();
        jLabel19 = new javax.swing.JLabel();
        txtX11 = new javax.swing.JTextField();
        txtX12 = new javax.swing.JTextField();
        jLabel20 = new javax.swing.JLabel();
        txtX21 = new javax.swing.JTextField();
        jLabel21 = new javax.swing.JLabel();
        txtX22 = new javax.swing.JTextField();
        jLabel22 = new javax.swing.JLabel();
        jLabel23 = new javax.swing.JLabel();
        jLabel24 = new javax.swing.JLabel();
        jLabel25 = new javax.swing.JLabel();
        jLabel26 = new javax.swing.JLabel();
        jLabel27 = new javax.swing.JLabel();
        jLabel28 = new javax.swing.JLabel();
        jLabel29 = new javax.swing.JLabel();
        jLabel30 = new javax.swing.JLabel();
        txtT21 = new javax.swing.JTextField();
        txtT22 = new javax.swing.JTextField();
        txtT23 = new javax.swing.JTextField();
        txtT24 = new javax.swing.JTextField();
        jLabel31 = new javax.swing.JLabel();
        jLabel32 = new javax.swing.JLabel();
        jLabel33 = new javax.swing.JLabel();
        jLabel34 = new javax.swing.JLabel();
        jLabel35 = new javax.swing.JLabel();
        jLabel36 = new javax.swing.JLabel();
        jLabel37 = new javax.swing.JLabel();
        jLabel38 = new javax.swing.JLabel();
        jLabel39 = new javax.swing.JLabel();
        jLabel40 = new javax.swing.JLabel();
        jButton9 = new javax.swing.JButton();
        jButton10 = new javax.swing.JButton();
        jPanel3 = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        jButton1 = new javax.swing.JButton();
        jTextField1 = new javax.swing.JTextField();
        textSysPlatform = new java.awt.TextArea();
        jSeparator2 = new javax.swing.JSeparator();
        jLabel12 = new javax.swing.JLabel();
        jLabel13 = new javax.swing.JLabel();
        jLabel14 = new javax.swing.JLabel();
        jtxtAdrecaHost = new javax.swing.JTextField();
        jtxtPortHost = new javax.swing.JTextField();
        buttonConnection = new javax.swing.JToggleButton();
        jButton70 = new javax.swing.JButton();
        jButton90 = new javax.swing.JButton();
		jButton100 = new javax.swing.JButton();
		jButton200 = new javax.swing.JButton();
		jButton111 = new javax.swing.JButton();
		jButton112 = new javax.swing.JButton(); 
		jButton113 = new javax.swing.JButton();
		jButton114 = new javax.swing.JButton();
		jButton115 = new javax.swing.JButton();
		textReconfState = new javax.swing.JTextField();
			
        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Distributed robot client for monitoring and supervision");
        setName("frameMain");
        
        setResizable(false);
        getAccessibleContext().setAccessibleName("frameMain");
        getAccessibleContext().setAccessibleDescription("frameMain");
        jPanel1.setLayout(null);

        jPanel1.addComponentListener(new java.awt.event.ComponentAdapter() {
            public void componentShown(java.awt.event.ComponentEvent evt) {
                jPanel1ComponentShown(evt);
            }
        });

        jButton5.setText("Reset");
        jButton5.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton5ActionPerformed(evt);
            }
        });

        jPanel1.add(jButton5);
        jButton5.setBounds(220, 10, 68, 25);

        jButton4.setText("Stop");
        jButton4.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton4ActionPerformed(evt);
            }
        });

        jPanel1.add(jButton4);
        jButton4.setBounds(160, 10, 60, 25);

        jButton3.setText("Pause");
        jButton3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton3ActionPerformed(evt);
            }
        });

        jPanel1.add(jButton3);
        jButton3.setBounds(90, 10, 70, 25);

        jButton2.setText("Engage");
        jButton2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton2ActionPerformed(evt);
            }
        });

        jPanel1.add(jButton2);
        jButton2.setBounds(10, 10, 79, 25);

        textSystemPlatform1.setEditable(false);
        jPanel1.add(textSystemPlatform1);
        textSystemPlatform1.setBounds(10, 50, 490, 320);

        jPanel1.add(txtEvent);
        txtEvent.setBounds(360, 10, 110, 19);

        jButton7.setText("Motor 1 Current");
        jButton7.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton7ActionPerformed(evt);
            }
        });

        jPanel1.add(jButton7);
        jButton7.setBounds(550, 70, 170, 25);


		 jButton70.setText("Motor 2 Current");
        jButton70.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton70ActionPerformed(evt);
            }
        });

        jPanel1.add(jButton70);
        jButton70.setBounds(550, 100, 170, 25);

		 jButton100.setText("Robot trajectory");
        jButton100.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton100ActionPerformed(evt);
            }
        });

        jPanel1.add(jButton100);
        jButton100.setBounds(550, 130, 170, 25);
        
        
        
        jTabbedPane1.addTab("System Execution", jPanel1);

        jPanel2.setLayout(null);

        jButton6.setText("Engage");
        jButton6.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton6ActionPerformed(evt);
            }
        });

        jPanel2.add(jButton6);
        jButton6.setBounds(20, 10, 79, 25);

        jButton8.setText("Stop");
        jButton8.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton8ActionPerformed(evt);
            }
        });

        jPanel2.add(jButton8);
        jButton8.setBounds(100, 10, 79, 25);

        jComboFases.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Serial Phase", "Parallel Phase" }));
        jPanel2.add(jComboFases);
        jComboFases.setBounds(10, 50, 200, 24);

        jButton9.setText("Motor 1 Current");
        jButton9.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton9ActionPerformed(evt);
            }
        });

		
        jPanel2.add(jButton9);
                
        jButton9.setBounds(10, 100, 170, 25);
        
        jButton90.setText("Motor 2 Current");
        jButton90.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton90ActionPerformed(evt);
            }
        });

		
        jPanel2.add(jButton90);
                
        jButton90.setBounds(10,130, 170, 25);
        
         jButton200.setText("Robot trajectory");
        jButton200.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton200ActionPerformed(evt);
            }
        });

		
        jPanel2.add(jButton200);
                
        jButton200.setBounds(10,160, 170, 25);
        
        //------------------------------------------------------------------
        
        jButton111.setText("Inject fault 1");
        jButton111.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton111ActionPerformed(evt);
            }
        });

        jPanel2.add(jButton111);
        jButton111.setBounds(300, 70, 170, 25);


		 jButton112.setText("Inject fault 2");
        jButton112.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton112ActionPerformed(evt);
            }
        });

        jPanel2.add(jButton112);
        jButton112.setBounds(300, 100, 170, 25);

		 jButton113.setText("Inject fault 3");
        jButton113.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton113ActionPerformed(evt);
            }
        });

        jPanel2.add(jButton113);
        jButton113.setBounds(300,130, 170, 25);
        
          jButton114.setText("Inject fault 4");
        jButton114.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton114ActionPerformed(evt);
            }
        });

        jPanel2.add(jButton114);
        jButton114.setBounds(300, 160, 170, 25);


		 jButton115.setText("Get reconf state");
        jButton115.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton115ActionPerformed(evt);
            }
        });

        jPanel2.add(jButton115);
        jButton115.setBounds(300, 190, 170, 25);
        
        jPanel2.add(textReconfState);
        textReconfState.setBounds(300, 240, 110, 19);
        
        //------------------------------------------------------------------
        
        
        
      jTabbedPane1.addTab("Manual Execution", jPanel2);

        jPanel3.setLayout(null);

        jLabel1.setText("System File");
        jPanel3.add(jLabel1);
        jLabel1.setBounds(50, 50, 100, 20);

        jButton1.setIcon(new javax.swing.ImageIcon("E:/"));
        jButton1.setText("Browse");
        jButton1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton1ActionPerformed(evt);
            }
        });

        jPanel3.add(jButton1);
        jButton1.setBounds(50, 70, 89, 25);

        jTextField1.setText(" [ Adress Archive ]");
        jTextField1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jTextField1ActionPerformed(evt);
            }
        });

        jPanel3.add(jTextField1);
        jTextField1.setBounds(160, 70, 390, 30);

        textSysPlatform.setEditable(false);
        jPanel3.add(textSysPlatform);
        textSysPlatform.setBounds(110, 110, 370, 80);

        jPanel3.add(jSeparator2);
        jSeparator2.setBounds(50, 202, 510, 2);

        jLabel12.setText("Connection with the C++/RTAI server");
        jPanel3.add(jLabel12);
        jLabel12.setBounds(50, 210, 210, 20);

        jLabel13.setText("Adress");
        jPanel3.add(jLabel13);
        jLabel13.setBounds(50, 230, 50, 20);

        jLabel14.setText("Port");
        jPanel3.add(jLabel14);
        jLabel14.setBounds(470, 230, 30, 20);

        jtxtAdrecaHost.setText("192.168.0.100");
        jPanel3.add(jtxtAdrecaHost);
        jtxtAdrecaHost.setBounds(50, 250, 400, 19);

        jtxtPortHost.setText("1500");
        jPanel3.add(jtxtPortHost);
        jtxtPortHost.setBounds(470, 250, 50, 20);

        buttonConnection.setText("Connect");
        buttonConnection.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                buttonConnectionActionPerformed(evt);
            }
        });

        jPanel3.add(buttonConnection);
        buttonConnection.setBounds(240, 270, 97, 25);

        jTabbedPane1.addTab("Aplication Configuration", jPanel3);

        jTabbedPane1.setSelectedIndex(2);

        getContentPane().add(jTabbedPane1, java.awt.BorderLayout.CENTER);

        pack();
    }//GEN-END:initComponents

  

    private void jButton9ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton9ActionPerformed
        // TODO add your handling code here:
      if( control!= null){
           Grafic g = new Grafic( this.control );
        
            g.start();
      }else
         JOptionPane.showMessageDialog(null, "No connection established.", "Error", JOptionPane.ERROR_MESSAGE);
    }//GEN-LAST:event_jButton9ActionPerformed

    private void jButton7ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton7ActionPerformed
        // TODO add your handling code here:
      if( control!= null){
           Grafic g = new Grafic( this.control );
        
            g.start();
        }else
         JOptionPane.showMessageDialog(null, "No connection established.", "Error", JOptionPane.ERROR_MESSAGE);
    }//GEN-LAST:event_jButton7ActionPerformed

	    private void jButton90ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton9ActionPerformed
        // TODO add your handling code here:
     if( control!= null){
           Grafic g = new Grafic( this.control );
      
            g.start();
      }else
         JOptionPane.showMessageDialog(null, "No connection established.", "Error", JOptionPane.ERROR_MESSAGE);
    }//GEN-LAST:event_jButton9ActionPerformed

    private void jButton70ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton7ActionPerformed
        // TODO add your handling code here:
       if( control!= null){
           Grafic g = new Grafic( this.control );
     
            g.start();
       }else
           JOptionPane.showMessageDialog(null, "No connection established.", "Error", JOptionPane.ERROR_MESSAGE);
    }//GEN-LAST:event_jButton7ActionPerformed
    
        private void jButton100ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton7ActionPerformed
        // TODO add your handling code here:
       if( control!= null){
        // add the specific code for robot trajectory generation
       }else
           JOptionPane.showMessageDialog(null, "No connection established.", "Error", JOptionPane.ERROR_MESSAGE);
    }//GEN-LAST:event_jButton7ActionPerformed
    
    //-----------------------------------------------------------------------------------
    
    private void jButton111ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton7ActionPerformed
        // TODO add your handling code here:
       try{
 				control.set(P.INJECT,(double)1.0);
        }catch(Throwable e){}   
    }//GEN-LAST:event_jButton7ActionPerformed
    
     private void jButton112ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton7ActionPerformed
        // TODO add your handling code here:
       try{
				control.set(P.INJECT,(double)2.0);
        }catch(Throwable e){}   
    }//GEN-LAST:event_jButton7ActionPerformed
    
     private void jButton113ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton7ActionPerformed
        // TODO add your handling code here:
       try{
				control.set(P.INJECT,(double)3.0);
        }catch(Throwable e){}   
    }//GEN-LAST:event_jButton7ActionPerformed
    
     private void jButton114ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton7ActionPerformed
        // TODO add your handling code here:
       try{
				control.set(P.INJECT,(double)4.0);
        }catch(Throwable e){}   
    }//GEN-LAST:event_jButton7ActionPerformed
    
     private void jButton115ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton7ActionPerformed
        // TODO add your handling code here:
       try{
            textReconfState.setText(String.valueOf(control.get(P.GET_RECONF_STATE)));
        }catch(Throwable e){}   
    }//GEN-LAST:event_jButton7ActionPerformed
    
    
    //-----------------------------------------------------------------------------------
    
        private void jButton200ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton7ActionPerformed
        // TODO add your handling code here:
       if( control!= null){
           Grafic g = new Grafic( this.control );
     
            g.start();
       }else
           JOptionPane.showMessageDialog(null, "No connection established.", "Error", JOptionPane.ERROR_MESSAGE);
    }//GEN-LAST:event_jButton7ActionPerformed
    
    private void jButton2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton2ActionPerformed
        // TODO add your handling code here:
        sysPlatform.start();
    }//GEN-LAST:event_jButton2ActionPerformed

    private void jButton3ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton3ActionPerformed
        // TODO add your handling code here:
        sysPlatform.pause();
    }//GEN-LAST:event_jButton3ActionPerformed

    private void jButton4ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton4ActionPerformed
        // TODO add your handling code here:
        try{
            sysPlatform.stop();
        }catch(Throwable e){
            JOptionPane.showMessageDialog(null, "Error Stopping the System: \n" + e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        }
    }//GEN-LAST:event_jButton4ActionPerformed

    private void jButton5ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton5ActionPerformed
        // TODO add your handling code here:
        sysPlatform.grafcet.reset();
        textSystemPlatform1.setText(sysPlatform.grafcet.write().toString());
    }//GEN-LAST:event_jButton5ActionPerformed

    private void jPanel1ComponentShown(java.awt.event.ComponentEvent evt) {//GEN-FIRST:event_jPanel1ComponentShown
        // TODO add your handling code here:
        ExecutionEvent ev = new RobotClient.ExecutionEvent();
        sysPlatform.setEvent(ev);
        textSystemPlatform1.setText( sysPlatform.grafcet.write().toString() );        
    }//GEN-LAST:event_jPanel1ComponentShown


    private void jButton8ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton8ActionPerformed
        // TODO add your handling code here:
        try{
            data.stop();
        }catch(Throwable e){}
    }//GEN-LAST:event_jButton8ActionPerformed

    /**Classe auxiliar per execute una phase en segon pla */
    class ExePhase implements Runnable{
        Thread t;
        int phase=0;
        public void exe_phase(int phase){
                this.phase= phase;
                t=new Thread(this);
                t.setDaemon(true);
		t.start();
        }
        public void run(){
            try{
                control.exe_phase(phase);
            }catch(Throwable ioe){
                JOptionPane.showMessageDialog(null, "No connection established with C++RTAI: \n" + ioe.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
            }
        }
    }
    private void jButton6ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton6ActionPerformed
        // TODO add your handling code here:
        try{
            ExePhase ef = new ExePhase();
            ef.exe_phase(jComboFases.getSelectedIndex());
        }catch(Throwable e){}
    }//GEN-LAST:event_jButton6ActionPerformed

    private void buttonConnectionActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_botoConnexioActionPerformed
        // TODO add your handling code here:
        if(buttonConnection.isSelected()){
            try{
                control = new Control(jtxtAdrecaHost.getText(), Integer.parseInt(jtxtPortHost.getText()));
                data = new Control( control.getHost(), control.getPort());
                sysPlatform.setControl(control);
                buttonConnection.setText("Disconnect");
                jTabbedPane1.setEnabled(true);
            }catch(UnknownHostException uhe){
                buttonConnection.setSelected(false);
                JOptionPane.showMessageDialog(null, "Error. No connection established with C++RTAI: \n" + uhe.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
            }catch(IOException ioe){
                buttonConnection.setSelected(false);                
                JOptionPane.showMessageDialog(null, "Error. Comunication Error: \n" + ioe.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
            }
        }else{
            try{
                control.disconnect();
                data.disconnect();
                sysPlatform.disconnect();
            }catch(IOException ioe){
                JOptionPane.showMessageDialog(null, "Error. Connection Error Trying to Disconnect: \n" + ioe.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
            }
            buttonConnection.setText("Connecting");
            buttonConnection.setSelected(false);
        }
    }//GEN-LAST:event_botoConnexioActionPerformed


    private void jButton1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton1ActionPerformed
        // TODO add your handling code here:
        JFileChooser fc = new JFileChooser();
        File directori = new File("./");
        fc.setCurrentDirectory(directori);
        int returnVal = fc.showOpenDialog(RobotClient.this);

        if (returnVal == JFileChooser.APPROVE_OPTION) {
            File file = fc.getSelectedFile();
            //This is where a real application would open the file.
            jTextField1.setText( file.getAbsolutePath() + "\n");
            SystemPlatform pa = new SystemPlatform(fc.getSelectedFile());
            pa.platform();
            sysPlatform = new SysPlatform();
            sysPlatform.setGrafcet(pa.getGrafcet());
            sysPlatform.grafcet.reset();
            textSysPlatform.setText( sysPlatform.grafcet.write().toString() );
            textSystemPlatform1.setText(textSysPlatform.getText());
            // finalment hi fixem el control
            sysPlatform.setControl(control);
            //activem el panell d'execucio de l'sysPlatform
        }
    }//GEN-LAST:event_jButton1ActionPerformed

    private void jTextField1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jTextField1ActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_jTextField1ActionPerformed
        
    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        new RobotClient().show();
    }
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JToggleButton buttonConnection;
    private javax.swing.JButton jButton1;
    private javax.swing.JButton jButton10;
    private javax.swing.JButton jButton2;
    private javax.swing.JButton jButton3;
    private javax.swing.JButton jButton4;
    private javax.swing.JButton jButton5;
    private javax.swing.JButton jButton6;
    private javax.swing.JButton jButton7;
    private javax.swing.JButton jButton8;
    private javax.swing.JButton jButton9;
    private javax.swing.JComboBox jComboFases;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel10;
    private javax.swing.JLabel jLabel11;
    private javax.swing.JLabel jLabel12;
    private javax.swing.JLabel jLabel13;
    private javax.swing.JLabel jLabel14;
    private javax.swing.JLabel jLabel15;
    private javax.swing.JLabel jLabel16;
    private javax.swing.JLabel jLabel17;
    private javax.swing.JLabel jLabel18;
    private javax.swing.JLabel jLabel19;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel20;
    private javax.swing.JLabel jLabel21;
    private javax.swing.JLabel jLabel22;
    private javax.swing.JLabel jLabel23;
    private javax.swing.JLabel jLabel24;
    private javax.swing.JLabel jLabel25;
    private javax.swing.JLabel jLabel26;
    private javax.swing.JLabel jLabel27;
    private javax.swing.JLabel jLabel28;
    private javax.swing.JLabel jLabel29;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel30;
    private javax.swing.JLabel jLabel31;
    private javax.swing.JLabel jLabel32;
    private javax.swing.JLabel jLabel33;
    private javax.swing.JLabel jLabel34;
    private javax.swing.JLabel jLabel35;
    private javax.swing.JLabel jLabel36;
    private javax.swing.JLabel jLabel37;
    private javax.swing.JLabel jLabel38;
    private javax.swing.JLabel jLabel39;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel40;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JLabel jLabel6;
    private javax.swing.JLabel jLabel7;
    private javax.swing.JLabel jLabel8;
    private javax.swing.JLabel jLabel9;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JPanel jPanel3;
    private javax.swing.JSeparator jSeparator1;
    private javax.swing.JSeparator jSeparator2;
    private javax.swing.JTabbedPane jTabbedPane1;
    private javax.swing.JTextField jTextField1;
    private javax.swing.JTextField jtxtAdrecaHost;
    private javax.swing.JTextField jtxtPortHost;
    private java.awt.TextArea textSysPlatform;
    private java.awt.TextArea textSystemPlatform1;
    private javax.swing.JTextField txtEvent;
    private javax.swing.JTextField txtT11;
    private javax.swing.JTextField txtT12;
    private javax.swing.JTextField txtT13;
    private javax.swing.JTextField txtT14;
    private javax.swing.JTextField txtT21;
    private javax.swing.JTextField txtT22;
    private javax.swing.JTextField txtT23;
    private javax.swing.JTextField txtT24;
    private javax.swing.JTextField txtX11;
    private javax.swing.JTextField txtX12;
    private javax.swing.JTextField txtX21;
    private javax.swing.JTextField txtX22;
    private javax.swing.JButton jButton70;
    private javax.swing.JButton jButton90;
 	private javax.swing.JButton jButton100;
 	private javax.swing.JButton jButton111;
 	private javax.swing.JButton jButton112;
 	private javax.swing.JButton jButton113;
 	private javax.swing.JButton jButton114;
 	private javax.swing.JButton jButton115;
 	private javax.swing.JButton jButton200;
 	private javax.swing.JTextField textReconfState;
    // End of variables declaration//GEN-END:variables
    

/**Constants dels parameters*/
    public class P{
            public final static int START=0;
            public final static int INJECT = 1;
            public final static int GET_RECONF_STATE = 2;
            public final static int ERROR=3;
    }
    /**Constants de les fases*/
    public class F{
            public final static int FASE_SERIE=0;
            public final static int FASE_PARALLEL=1;
    }

    /**Constants dels actuadors*/
    public class A{
            public final static int ACM1=0;
            public final static int ACM2=1;
    }

    /**sensor values on the robot*/
    public class S{
            public final static int SM1=0;
            public final static int SM2=1;
    }

}
