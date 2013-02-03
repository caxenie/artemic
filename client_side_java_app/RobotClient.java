/*
 * RobotClient.java
 * robot interface software that supports start/stop, parameter set/get
 * and implements the fault injection framework
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
        JButton5 = new javax.swing.JButton();
        JButton4 = new javax.swing.JButton();
        JButton3 = new javax.swing.JButton();
        JButton2 = new javax.swing.JButton();
        textSystemPlatform1 = new java.awt.TextArea();
        txtEvent = new javax.swing.JTextField();
        JButton7 = new javax.swing.JButton();
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
        JButton6 = new javax.swing.JButton();
        JButton8 = new javax.swing.JButton();
        jComboFases = new javax.swing.JComboBox();
        jLabel15 = new javax.swing.JLabel();
        txtFault1 = new javax.swing.JTextField();
        txtFault2 = new javax.swing.JTextField();
        jLabel16 = new javax.swing.JLabel();
        txtFault3 = new javax.swing.JTextField();
        jLabel17 = new javax.swing.JLabel();
        txtFault4 = new javax.swing.JTextField();
	robotImage = new javax.swing.ImageIcon("RT_App_Files/robot/robot.jpg"); 		 
	robotImage2 = new javax.swing.ImageIcon("RT_App_Files/robot/robot2.jpg");	
	trajImage = new javax.swing.ImageIcon("RT_App_Files/robot/trajectory.jpg");
        jLabel18 = new javax.swing.JLabel();
        jLabel19 = new javax.swing.JLabel();
        txtX11 = new javax.swing.JTextField();
        txtX12 = new javax.swing.JTextField();
        jLabel20 = new javax.swing.JLabel();
        txtX21 = new javax.swing.JTextField();
        jLabel21 = new javax.swing.JLabel();
        txtX22 = new javax.swing.JTextField();
        jLabelFaultFramework = new javax.swing.JLabel();
        jButtonReconf = new javax.swing.JButton();
        jLabel24 = new javax.swing.JLabel();
        jLabel25 = new javax.swing.JLabel();
        jLabel26 = new javax.swing.JLabel();
        jLabel27 = new javax.swing.JLabel();
        jLabel28 = new javax.swing.JLabel();
        jLabelImage = new javax.swing.JLabel(robotImage);
        jLabelImage2 = new javax.swing.JLabel(trajImage);
	jLabelImage3 = new javax.swing.JLabel(robotImage2);
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
        JButton9 = new javax.swing.JButton();
        JButton10 = new javax.swing.JButton();
        jPanel3 = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        JButton1 = new javax.swing.JButton();
        jTextField1 = new javax.swing.JTextField();
        textSysPlatform = new java.awt.TextArea();
        jSeparator2 = new javax.swing.JSeparator();
        jLabel12 = new javax.swing.JLabel();
        jLabel13 = new javax.swing.JLabel();
        jLabel14 = new javax.swing.JLabel();
        jtxtAdrecaHost = new javax.swing.JTextField();
        jtxtPortHost = new javax.swing.JTextField();
        buttonConnection = new javax.swing.JToggleButton();
        JButton70 = new javax.swing.JButton();
        JButton90 = new javax.swing.JButton();
		
		JButton200 = new javax.swing.JButton();
		JButton111 = new javax.swing.JButton();
		JButton112 = new javax.swing.JButton(); 
		JButton113 = new javax.swing.JButton();
		JButton114 = new javax.swing.JButton();
		JButtonTR1 = new javax.swing.JButton();
		JButtonTR2 = new javax.swing.JButton();
		JButtonTR3 = new javax.swing.JButton();
		JButtonTR4 = new javax.swing.JButton();
		jLabelTRAJ = new javax.swing.JLabel("Trajectory chooser");
		
		
		textReconfState = new javax.swing.JTextArea();
			
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

        JButton5.setText("Reset");
        JButton5.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                JButton5ActionPerformed(evt);
            }
        });

        jPanel1.add(JButton5);
        JButton5.setBounds(220, 10, 68, 25);

        JButton4.setText("Stop");
        JButton4.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                JButton4ActionPerformed(evt);
            }
        });

        jPanel1.add(JButton4);
        JButton4.setBounds(160, 10, 68, 25);

	jPanel1.add(jLabelImage);
	jLabelImage.setBounds(450,200,220,190);

        JButton3.setText("Pause");
        JButton3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                JButton3ActionPerformed(evt);
            }
        });

        jPanel1.add(JButton3);
        JButton3.setBounds(85, 10, 70, 25);

        JButton2.setText("Engage");
        JButton2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                JButton2ActionPerformed(evt);
            }
        });

        jPanel1.add(JButton2);
        JButton2.setBounds(10, 10, 79, 25);

        textSystemPlatform1.setEditable(false);
        jPanel1.add(textSystemPlatform1);
        textSystemPlatform1.setBounds(10, 50, 490, 320);

        jPanel1.add(txtEvent);
        txtEvent.setBounds(360, 10, 110, 19);

        JButton7.setText("Motor 1 Current");
        JButton7.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                JButton7ActionPerformed(evt);
            }
        });

        jPanel1.add(JButton7);
        JButton7.setBounds(550, 70, 170, 25);


		 JButton70.setText("Motor 2 Current");
        JButton70.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                JButton70ActionPerformed(evt);
            }
        });

        jPanel1.add(JButton70);
        JButton70.setBounds(550, 100, 170, 25);

	jPanel1.add(jLabelImage3);
	
	jLabelImage3.setBounds(502,160,230,190);

        jTabbedPane1.addTab("System Execution", jPanel1);

        jPanel2.setLayout(null);
	
        JButton6.setText("Engage");
        JButton6.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                JButton6ActionPerformed(evt);
            }
        });

        jPanel2.add(JButton6);
        JButton6.setBounds(20, 10, 79, 25);

        JButton8.setText("Stop");
        JButton8.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                JButton8ActionPerformed(evt);
            }
        });

        jPanel2.add(JButton8);
        JButton8.setBounds(100, 10, 79, 25);

        jComboFases.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Serial Phase", "Parallel Phase" }));
        jPanel2.add(jComboFases);
        jComboFases.setBounds(10, 50, 200, 24);

        JButton9.setText("Motor 1 Current");
        JButton9.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                JButton9ActionPerformed(evt);
            }
        });

		
        jPanel2.add(JButton9);
                
        JButton9.setBounds(10, 100, 170, 25);
        
        JButton90.setText("Motor 2 Current");
        JButton90.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                JButton90ActionPerformed(evt);
            }
        });

			
        jPanel2.add(JButton90);
                
        JButton90.setBounds(10,130, 170, 25);
        
	jPanel2.add(jLabelTRAJ);
	jLabelTRAJ.setBounds(10,150,190,25);
 
	// trajectory chooser
	 jPanel2.add(JButtonTR1);
                
        JButtonTR1.setBounds(10,170, 100, 20);
        
	JButtonTR1.setText("Line");
        JButtonTR1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                JButtonTR1ActionPerformed(evt);
            }
        });

		 jPanel2.add(JButtonTR2);
                
        JButtonTR2.setBounds(10,190, 100, 20);
        
	JButtonTR2.setText("Circle");
        JButtonTR2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                JButtonTR2ActionPerformed(evt);
            }
        });

		 jPanel2.add(JButtonTR3);
                
        JButtonTR3.setBounds(110,170, 100, 20);
        
	JButtonTR3.setText("Simple");
        JButtonTR3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                JButtonTR3ActionPerformed(evt);
            }
        });

		 jPanel2.add(JButtonTR4);
                
        JButtonTR4.setBounds(110,190, 100, 20);
        
	JButtonTR4.setText("Complex");
        JButtonTR4.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                JButtonTR4ActionPerformed(evt);
            }
        });

	jPanel2.add(jLabelImage);
	jPanel2.add(jLabelImage2);
	
	jLabelImage2.setBounds(2,140,290,300);
	jLabelImage.setBounds(450,200,220,190);

        //------------------------------------------------------------------
	jLabelFaultFramework.setText("Fault Injection Framework");
	jPanel2.add(jLabelFaultFramework);
	jLabelFaultFramework.setBounds(350,40,170,25);
        
        JButton111.setText("Inject fault 1");
        JButton111.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                JButton111ActionPerformed(evt);
            }
        });

        jPanel2.add(JButton111);
        JButton111.setBounds(300, 70, 170, 25);

	txtFault1.setText("t inject F1");
        txtFault1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtFault1ActionPerformed(evt);
            }
        });

        jPanel2.add(txtFault1);
        txtFault1.setBounds(500, 70, 70, 25);

		 JButton112.setText("Inject fault 2");
        JButton112.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                JButton112ActionPerformed(evt);
            }
        });

        jPanel2.add(JButton112);
        JButton112.setBounds(300, 100, 170, 25);

	txtFault2.setText("t inject F2");
        txtFault2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtFault2ActionPerformed(evt);
            }
        });

        jPanel2.add(txtFault2);
        txtFault2.setBounds(500, 100, 70, 25);


		 JButton113.setText("Inject fault 3");
        JButton113.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                JButton113ActionPerformed(evt);
            }
        });

        jPanel2.add(JButton113);
        JButton113.setBounds(300,130, 170, 25);

	txtFault3.setText("t inject F3");
        txtFault3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtFault3ActionPerformed(evt);
            }
        });

        jPanel2.add(txtFault3);
        txtFault3.setBounds(500, 130, 70, 25);

        
          JButton114.setText("Inject fault 4");
        JButton114.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                JButton114ActionPerformed(evt);
            }
        });

        jPanel2.add(JButton114);
        JButton114.setBounds(300, 160, 170, 25);

	txtFault4.setText("t inject F4");
        txtFault4.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txtFault4ActionPerformed(evt);
            }
        });

        jPanel2.add(txtFault4);
        txtFault4.setBounds(500, 160, 70, 25);

        
        jPanel2.add(textReconfState);
	textReconfState.setEditable(true);
        textReconfState.setBounds(295, 240, 150, 100);

		
	
	jButtonReconf.setText("Reconf status");
	jPanel2.add(jButtonReconf);
	jButtonReconf.setBounds(300,215,140,20);

	jButtonReconf.addActionListener(new java.awt.event.ActionListener(){
		public void actionPerformed(java.awt.event.ActionEvent evt){
			jButtonReconfActionPerformed(evt);
		}
	});       
	
        //------------------------------------------------------------------
        
        
          jTabbedPane1.addTab("Manual Execution", jPanel2);

        jPanel3.setLayout(null);

        jLabel1.setText("System File");
        jPanel3.add(jLabel1);
        jLabel1.setBounds(50, 50, 100, 20);

        JButton1.setIcon(new javax.swing.ImageIcon(""));
        JButton1.setText("Browse");
        JButton1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                JButton1ActionPerformed(evt);
            }
        });

        jPanel3.add(JButton1);
        JButton1.setBounds(50, 70, 89, 25);

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
        jLabel12.setBounds(50, 210, 260, 20);

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
    }

  

    private void JButton9ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_JButton9ActionPerformed

      if( control!= null){
           Grafic g = new Grafic( this.control );
        
            g.start();
      }else
         JOptionPane.showMessageDialog(null, "No connection established.", "Error", JOptionPane.ERROR_MESSAGE);
    }

    private void JButton7ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_JButton7ActionPerformed
       
      if( control!= null){
           Grafic g = new Grafic( this.control );
        
            g.start();
        }else
         JOptionPane.showMessageDialog(null, "No connection established.", "Error", JOptionPane.ERROR_MESSAGE);
    }

	    private void JButton90ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_JButton9ActionPerformed
       
     if( control!= null){
           Grafic g = new Grafic( this.control );
      
            g.start();
      }else
         JOptionPane.showMessageDialog(null, "No connection established.", "Error", JOptionPane.ERROR_MESSAGE);
    }

    private void JButton70ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_JButton7ActionPerformed
       
       if( control!= null){
           Grafic g = new Grafic( this.control );
     
            g.start();
       }else
           JOptionPane.showMessageDialog(null, "No connection established.", "Error", JOptionPane.ERROR_MESSAGE);
    }
    

    //-----------------------------------------------------------------------------------
	  private void JButtonTR1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_JButton7ActionPerformed
       
       try{			
 				control.set(P.TR,(double)1.0);
				jLabelImage2.setIcon(new javax.swing.ImageIcon("/home/haustiq/Desktop/jdk1.6.0_11/bin/RT_App_Files/robot/line.jpg"));
				
        }catch(Throwable e){}   
    }

	  private void JButtonTR2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_JButton7ActionPerformed
       
       try{			
 				control.set(P.TR,(double)2.0);
				jLabelImage2.setIcon(new javax.swing.ImageIcon("/home/haustiq/Desktop/jdk1.6.0_11/bin/RT_App_Files/robot/circle.jpg"));
				
        }catch(Throwable e){}   
    }

      private void JButtonTR3ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_JButton7ActionPerformed
       
       try{			
 				control.set(P.TR,(double)3.0);
				jLabelImage2.setIcon(new javax.swing.ImageIcon("/home/haustiq/Desktop/jdk1.6.0_11/bin/RT_App_Files/robot/simple.jpg"));
				
        }catch(Throwable e){}   
    }


	  private void JButtonTR4ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_JButton7ActionPerformed
       
       try{			
 				control.set(P.TR,(double)4.0);
				jLabelImage2.setIcon(new javax.swing.ImageIcon("/home/haustiq/Desktop/jdk1.6.0_11/bin/RT_App_Files/robot/trajectory.jpg"));
				
        }catch(Throwable e){}   
    }

    private void JButton111ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_JButton7ActionPerformed
       
       try{			
 				control.set(P.INJECT,(double)1.0);
				control.set(P.F1, Double.parseDouble(txtFault1.getText()) );
				
        }catch(Throwable e){}   
    }
    
     private void JButton112ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_JButton7ActionPerformed
       
       try{			
				control.set(P.INJECT,(double)2.0);
				control.set(P.F2, Double.parseDouble(txtFault2.getText()) );
				
        }catch(Throwable e){}   
    }
    
     private void JButton113ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_JButton7ActionPerformed
       
       try{		
				control.set(P.INJECT,(double)3.0);
				control.set(P.F3, Double.parseDouble(txtFault3.getText()) );
				
        }catch(Throwable e){}   
    }
    
     private void JButton114ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_JButton7ActionPerformed
       
       try{
				
				control.set(P.INJECT,(double)4.0);
				control.set(P.F4, Double.parseDouble(txtFault4.getText()) );
        }catch(Throwable e){}   
    }
    
 	private void txtFault1ActionPerformed(java.awt.event.ActionEvent evt) {
       
        try{
            control.set(P.F1, Double.parseDouble(txtFault1.getText()) );
        }catch(Throwable e){}        
    	}
	
	private void txtFault2ActionPerformed(java.awt.event.ActionEvent evt) {
       
        try{
            control.set(P.F2, Double.parseDouble(txtFault2.getText()) );
        }catch(Throwable e){}        
    	}

  	private void txtFault3ActionPerformed(java.awt.event.ActionEvent evt) {
       
        try{
            control.set(P.F3, Double.parseDouble(txtFault3.getText()) );
        }catch(Throwable e){}        
    	}

	private void txtFault4ActionPerformed(java.awt.event.ActionEvent evt) {
       
        try{
            control.set(P.F4, Double.parseDouble(txtFault4.getText()) );
        }catch(Throwable e){}        
    	} 

	private void jButtonReconfActionPerformed(java.awt.event.ActionEvent evt){
		
	try{
            if(control.get(P.GET_RECONF_STATE)==1.0){
		textReconfState.setText("");
		textReconfState.append("during operation a 1st\n");
		textReconfState.append("class fault occurred and\n ");
		textReconfState.append("specific reconfiguration\n");
		textReconfState.append("actions were issued...\n");		
		}
	if(control.get(P.GET_RECONF_STATE)==2.0){
		textReconfState.setText("");
		textReconfState.append("during operation a 2nd\n");
		textReconfState.append("class fault occurred and\n ");
		textReconfState.append("specific reconfiguration\n");
		textReconfState.append("actions were issued...\n");		
		}
		  
        }catch(Throwable e)
		{
		textReconfState.setText("");
			textReconfState.append("during operation no \n");
		textReconfState.append("fault occurred and no \n ");
		textReconfState.append("reconfiguration actions \n");
		textReconfState.append("were issued...\n");		
	   }

	}
    //-----------------------------------------------------------------------------------
    
        private void JButton200ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_JButton7ActionPerformed
       
       if( control!= null){
           Grafic g = new Grafic( this.control );
     
            g.start();
       }else
           JOptionPane.showMessageDialog(null, "No connection established.", "Error", JOptionPane.ERROR_MESSAGE);
    }
    
    private void JButton2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_JButton2ActionPerformed
       
        sysPlatform.start();
    }

    private void JButton3ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_JButton3ActionPerformed
       
        sysPlatform.pause();
    }

    private void JButton4ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_JButton4ActionPerformed
       
        try{
            sysPlatform.stop();
        }catch(Throwable e){
            JOptionPane.showMessageDialog(null, "Error Stopping the System: \n" + e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void JButton5ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_JButton5ActionPerformed
       
        sysPlatform.grafcet.reset();
        textSystemPlatform1.setText(sysPlatform.grafcet.write().toString());
    }

    private void jPanel1ComponentShown(java.awt.event.ComponentEvent evt) {//GEN-FIRST:event_jPanel1ComponentShown
       
        ExecutionEvent ev = new RobotClient.ExecutionEvent();
        sysPlatform.setEvent(ev);
        textSystemPlatform1.setText( sysPlatform.grafcet.write().toString() );        
    }


    private void JButton8ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_JButton8ActionPerformed
       
        try{
            data.stop();
        }catch(Throwable e){}
    }
    
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
    private void JButton6ActionPerformed(java.awt.event.ActionEvent evt) {
       
        try{
            ExePhase ef = new ExePhase();
            ef.exe_phase(jComboFases.getSelectedIndex());
        }catch(Throwable e){}
    }

    private void buttonConnectionActionPerformed(java.awt.event.ActionEvent evt) {
       
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
    }


    private void JButton1ActionPerformed(java.awt.event.ActionEvent evt) {
       
        JFileChooser fc = new JFileChooser();
        File directori = new File("./");
        fc.setCurrentDirectory(directori);
        int returnVal = fc.showOpenDialog(RobotClient.this);

        if (returnVal == JFileChooser.APPROVE_OPTION) {
            File file = fc.getSelectedFile();
 
            jTextField1.setText( file.getAbsolutePath() + "\n");
            SystemPlatform pa = new SystemPlatform(fc.getSelectedFile());
            pa.platform();
            sysPlatform = new SysPlatform();
            sysPlatform.setGrafcet(pa.getGrafcet());
            sysPlatform.grafcet.reset();
            textSysPlatform.setText( sysPlatform.grafcet.write().toString() );
            textSystemPlatform1.setText(textSysPlatform.getText());
    
            sysPlatform.setControl(control);
          
        }
    }

    private void jTextField1ActionPerformed(java.awt.event.ActionEvent evt) {
       
    }
        

    public static void main(String args[]) {
        new RobotClient().show();
    }
    
 
    private javax.swing.JToggleButton buttonConnection;
    private javax.swing.JButton JButton1;
    private javax.swing.JButton JButton10;
    private javax.swing.JButton JButton2;
    private javax.swing.JButton JButton3;
    private javax.swing.JButton JButton4;
    private javax.swing.JButton JButton5;
    private javax.swing.JButton JButton6;
    private javax.swing.JButton JButton7;
    private javax.swing.JButton JButton8;
    private javax.swing.JButton JButton9;
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
    private javax.swing.JLabel jLabelFaultFramework;
    private javax.swing.JButton jButtonReconf;
    private javax.swing.JLabel jLabel24;
    private javax.swing.JLabel jLabel25;
    private javax.swing.JLabel jLabel26;
    private javax.swing.JLabel jLabel27;
    private javax.swing.JLabel jLabel28;
    private javax.swing.JLabel jLabelImage;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabelImage2;
    private javax.swing.JLabel jLabelImage3;
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
    private javax.swing.JTextField txtFault1;
    private javax.swing.JTextField txtFault2;
    private javax.swing.JTextField txtFault3;
    private javax.swing.JTextField txtFault4;
    private javax.swing.JTextField txtT22;
    private javax.swing.JTextField txtT23;
    private javax.swing.JTextField txtT24;
    private javax.swing.JTextField txtX11;
    private javax.swing.JTextField txtX12;
    private javax.swing.JTextField txtX21;
    private javax.swing.JTextField txtX22;
    private javax.swing.JButton JButton70;
    private javax.swing.JButton JButton90;
    private javax.swing.ImageIcon robotImage;
    private javax.swing.ImageIcon robotImage2;    
    private javax.swing.ImageIcon trajImage;
 
 	private javax.swing.JButton JButton111;
 	private javax.swing.JButton JButton112;
 	private javax.swing.JButton JButton113;
 	private javax.swing.JButton JButton114;
 	private javax.swing.JButton JButton200;
 	private javax.swing.JTextArea textReconfState;
	private javax.swing.JButton JButtonTR1;
	private javax.swing.JButton JButtonTR2;
	private javax.swing.JButton JButtonTR3;
	private javax.swing.JButton JButtonTR4;
	private javax.swing.JLabel jLabelTRAJ;
 
    

/**parameters constants*/
    public class P{
            public final static int START=0;
            public final static int INJECT = 1;
            public final static int GET_RECONF_STATE = 2;
	    public final static int F1 = 3;	 
            public final static int F2 = 4;
	    public final static int F3 = 5;
	    public final static int F4 = 6;
	    public final static int TR = 7;
	    public final static int ERROR = 8;
    }
    /**phases constants*/
    public class F{
            public final static int FASE_SERIE=0;
            public final static int FASE_PARALLEL=1;
    }

    /**actuators constants*/
    public class A{
            public final static int ACM1=0;
            public final static int ACM2=1;
    }

    /**sensor values on the robot*/
    public class S{
            public final static int SCA_1=0;
            public final static int SCA_2=1;
    }

}
