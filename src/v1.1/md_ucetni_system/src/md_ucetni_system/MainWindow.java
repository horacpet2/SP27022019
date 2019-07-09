/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package md_ucetni_system;


import java.awt.Color;
import java.awt.Cursor;
import java.awt.Font;
import java.awt.Point;
import java.awt.Toolkit;
import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;
import java.util.TreeMap;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;


/**
 *
 * @author petr
 */
public class MainWindow extends javax.swing.JFrame 
{
    private int click_to_finish;
    private final Timer exit_null_timer;
    private final Timer error_blink;
    private Controler controler_ref;
    private boolean error_blink_bool;
    private int man_input_btn_offset;

    public MainWindow() 
    {
        initComponents();
        
        /* setup window */
        this.order_table_view.getTableHeader().setFont(new Font("Dialog", Font.BOLD, 30));
        setExtendedState(JFrame.MAXIMIZED_BOTH); 

        /* initialize local variables */
        this.click_to_finish = 0;
        this.controler_ref = new Controler();
        this.exit_null_timer = new Timer();
        this.error_blink = new Timer();
        
        this.error_blink_bool = false;
        this.btn_go_to_pay.setEnabled(false);
        this.man_input_btn_offset = 0;

        exit_null_timer.scheduleAtFixedRate(new TimerTask() 
        {
            @Override
            public void run() 
            {
                click_to_finish = 0;
            }
        }, 5*1000, 5*1000);
        
        error_blink.scheduleAtFixedRate(new TimerTask() 
        {
            @Override
            public void run() 
            {
                error_blink_bool = !error_blink_bool;
                
                error_line_control(error_line);
                error_line_control(error_line1);
                
                   
                
                controler_ref.update_order_list_by_scanner();
            }
        }, 0, 1000);
     
        DefaultTableCellRenderer centerRenderer = new DefaultTableCellRenderer();
        centerRenderer.setHorizontalAlignment(JLabel.CENTER );
        
        order_table_view.getColumnModel().getColumn(0).setCellRenderer( centerRenderer );
        order_table_view.getColumnModel().getColumn(1).setCellRenderer( centerRenderer );
        order_table_view.getColumnModel().getColumn(2).setCellRenderer( centerRenderer );
        order_table_view.getColumnModel().getColumn(3).setCellRenderer( centerRenderer );
        
        /* initial hide all other panels exeptionaly order panel */
        initialize_manual_input(this.controler_ref.get_available_item_quantity());
        show_order_panel();
        
        
        //hide_cursor();
    }

   
    
    private void error_line_control(JLabel error_line)
    {
        if(controler_ref.get_error_meesage() != null && !controler_ref.get_error_meesage().equals(""))
        {
            error_line.setVisible(true);
            error_line.setText(controler_ref.get_error_meesage());

            if(error_blink_bool == true)
                   error_line.setBackground(Color.red);
            else
                   error_line.setBackground(Color.orange);
        }
        else
        {
            error_line.setVisible(false);
            error_line.setText("");
        } 
    }
    
    private void initialize_manual_input(int max)
    {
        /* povolit tlačítko pro pohyb v manuálním zadávání zpět */
        if(this.man_input_btn_offset <= 0)
            this.btn_manual_previous.setEnabled(false);
        else
            this.btn_manual_previous.setEnabled(true);
        
        /* povolit tlačítko pro pohyb v manuálním zadávání dopředu */
        if(((this.man_input_btn_offset+1)*15) >= max)
            this.btn_manual_next.setEnabled(false);
        else
            this.btn_manual_next.setEnabled(true);
        
        
        /* zapsat hodnoty tlačítkům */
        for(int i = 0; i < 15; i++)
        {
            JButton btn_man_input = get_btn_manual_input(i);
            
            if(btn_man_input != null)
            {
                if(((this.man_input_btn_offset*15)+i) <= max-1)
                {
                    btn_man_input.setEnabled(true);
                    btn_man_input.setText(this.controler_ref.get_item_name_by_ID((this.man_input_btn_offset*15)+i));
                }
                else
                {
                     btn_man_input.setEnabled(false);
                     btn_man_input.setText("");
                }
            }
        }
    }
    
    private JButton get_btn_manual_input(int index)
    {
        switch(index)
        {
            case 0:
                return this.btn_man_input_1;
            case 1:
                return this.btn_man_input_2;
            case 2:
                return this.btn_man_input_3;
            case 3:
                    return this.btn_man_input_4;
            case 4:
                    return this.btn_man_input_5;
            case 5:
                    return this.btn_man_input_6;
            case 6:
                    return this.btn_man_input_7;
            case 7:
                    return this.btn_man_input_8;
            case 8:
                    return this.btn_man_input_9;      
            case 9:
                    return this.btn_man_input_10;    
            case 10:
                    return this.btn_man_input_11; 
            case 11:
                    return this.btn_man_input_12;        
            case 12:
                    return this.btn_man_input_13;
            case 13:
                    return this.btn_man_input_14; 
            case 14:
                    return this.btn_man_input_15;        
            default:
                return null;
        }
    }
    
    private void hide_cursor()
    {
         BufferedImage cursorImg = new BufferedImage(16, 16, BufferedImage.TYPE_INT_ARGB);

        // Create a new blank cursor.
        Cursor blankCursor = Toolkit.getDefaultToolkit().createCustomCursor(cursorImg, new Point(0, 0), "blank cursor");

        // Set the blank cursor to the JFrame.
        this.getContentPane().setCursor(blankCursor);
    }
    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jRadioButtonMenuItem1 = new javax.swing.JRadioButtonMenuItem();
        jLayeredPane1 = new javax.swing.JLayeredPane();
        order_panel = new javax.swing.JPanel();
        jLabel4 = new javax.swing.JLabel();
        btn_go_to_pay = new javax.swing.JButton();
        jScrollPane2 = new javax.swing.JScrollPane();
        order_table_view = new javax.swing.JTable();
        jLabel2 = new javax.swing.JLabel();
        overview_total_prise_lbl = new javax.swing.JLabel();
        clear_and_new_order_btn = new javax.swing.JButton();
        decrease_order_size = new javax.swing.JButton();
        increase_order_size = new javax.swing.JButton();
        jButton14 = new javax.swing.JButton();
        error_line = new javax.swing.JLabel();
        manual_input_panel = new javax.swing.JPanel();
        btn_man_input_1 = new javax.swing.JButton();
        jButton3 = new javax.swing.JButton();
        btn_man_input_2 = new javax.swing.JButton();
        btn_man_input_4 = new javax.swing.JButton();
        btn_man_input_5 = new javax.swing.JButton();
        btn_man_input_6 = new javax.swing.JButton();
        btn_man_input_7 = new javax.swing.JButton();
        btn_man_input_9 = new javax.swing.JButton();
        btn_man_input_10 = new javax.swing.JButton();
        btn_man_input_3 = new javax.swing.JButton();
        btn_man_input_8 = new javax.swing.JButton();
        btn_man_input_11 = new javax.swing.JButton();
        btn_man_input_12 = new javax.swing.JButton();
        btn_man_input_13 = new javax.swing.JButton();
        btn_man_input_14 = new javax.swing.JButton();
        btn_man_input_15 = new javax.swing.JButton();
        btn_manual_next = new javax.swing.JButton();
        btn_manual_previous = new javax.swing.JButton();
        finish_order_panel = new javax.swing.JPanel();
        final_total_price = new javax.swing.JLabel();
        jLabel5 = new javax.swing.JLabel();
        jLabel6 = new javax.swing.JLabel();
        given_money_input = new javax.swing.JTextField();
        jLabel7 = new javax.swing.JLabel();
        return_money_lbl = new javax.swing.JLabel();
        btn_print_bill = new javax.swing.JButton();
        btn_back_to_order = new javax.swing.JButton();
        btn_one = new javax.swing.JButton();
        btn_two = new javax.swing.JButton();
        btn_three = new javax.swing.JButton();
        btn_four = new javax.swing.JButton();
        btn_five = new javax.swing.JButton();
        btn_six = new javax.swing.JButton();
        btn_seven = new javax.swing.JButton();
        btn_eight = new javax.swing.JButton();
        btn_nine = new javax.swing.JButton();
        btn_remove_char = new javax.swing.JButton();
        btn_clear = new javax.swing.JButton();
        btn_zero = new javax.swing.JButton();
        btn_finish_order = new javax.swing.JButton();
        error_line1 = new javax.swing.JLabel();
        bill_browser = new javax.swing.JPanel();

        jRadioButtonMenuItem1.setSelected(true);
        jRadioButtonMenuItem1.setText("jRadioButtonMenuItem1");

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Pokladní systém");
        setAlwaysOnTop(true);
        setBackground(new java.awt.Color(204, 204, 255));
        setUndecorated(true);
        setResizable(false);

        jLayeredPane1.setBackground(new java.awt.Color(204, 204, 255));

        jLabel4.setIcon(new javax.swing.ImageIcon(getClass().getResource("/md_ucetni_system/logo-mlyn-dubecko.png"))); // NOI18N
        jLabel4.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jLabel4MouseClicked(evt);
            }
        });

        btn_go_to_pay.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        btn_go_to_pay.setText("Zaplatit");
        btn_go_to_pay.setActionCommand("jButton2");
        btn_go_to_pay.setFocusPainted(false);
        btn_go_to_pay.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_go_to_payActionPerformed(evt);
            }
        });

        order_table_view.setFont(new java.awt.Font("Dialog", 1, 24)); // NOI18N
        order_table_view.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {

            },
            new String [] {
                "Zboží", "Množství", "Cena bez DPH", "Cena s DPH"
            }
        ) {
            boolean[] canEdit = new boolean [] {
                false, false, false, false
            };

            public boolean isCellEditable(int rowIndex, int columnIndex) {
                return canEdit [columnIndex];
            }
        });
        order_table_view.getTableHeader().setReorderingAllowed(false);
        jScrollPane2.setViewportView(order_table_view);
        if (order_table_view.getColumnModel().getColumnCount() > 0) {
            order_table_view.getColumnModel().getColumn(0).setResizable(false);
            order_table_view.getColumnModel().getColumn(1).setResizable(false);
            order_table_view.getColumnModel().getColumn(2).setResizable(false);
            order_table_view.getColumnModel().getColumn(3).setResizable(false);
        }

        jLabel2.setFont(new java.awt.Font("Dialog", 1, 36)); // NOI18N
        jLabel2.setText("Celkem:");

        overview_total_prise_lbl.setFont(new java.awt.Font("Dialog", 1, 36)); // NOI18N
        overview_total_prise_lbl.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        overview_total_prise_lbl.setText("0.0 Kč");

        clear_and_new_order_btn.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        clear_and_new_order_btn.setText("Nová platba");
        clear_and_new_order_btn.setFocusPainted(false);
        clear_and_new_order_btn.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                clear_and_new_order_btnActionPerformed(evt);
            }
        });

        decrease_order_size.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        decrease_order_size.setText("-1");
        decrease_order_size.setFocusPainted(false);
        decrease_order_size.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                decrease_order_sizeActionPerformed(evt);
            }
        });

        increase_order_size.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        increase_order_size.setText("+1");
        increase_order_size.setFocusPainted(false);
        increase_order_size.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                increase_order_sizeActionPerformed(evt);
            }
        });

        jButton14.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        jButton14.setText("Zadat ručně");
        jButton14.setFocusPainted(false);
        jButton14.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton14ActionPerformed(evt);
            }
        });

        error_line.setBackground(new java.awt.Color(255, 0, 0));
        error_line.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        error_line.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        error_line.setOpaque(true);
        error_line.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                error_lineMouseClicked(evt);
            }
        });

        javax.swing.GroupLayout order_panelLayout = new javax.swing.GroupLayout(order_panel);
        order_panel.setLayout(order_panelLayout);
        order_panelLayout.setHorizontalGroup(
            order_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, order_panelLayout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(jLabel4)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, order_panelLayout.createSequentialGroup()
                .addGap(50, 50, 50)
                .addGroup(order_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(error_line, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addGroup(order_panelLayout.createSequentialGroup()
                        .addComponent(jLabel2)
                        .addGap(353, 353, 353)
                        .addComponent(overview_total_prise_lbl, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                    .addComponent(jScrollPane2)
                    .addGroup(order_panelLayout.createSequentialGroup()
                        .addComponent(decrease_order_size, javax.swing.GroupLayout.PREFERRED_SIZE, 71, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(100, 100, 100)
                        .addComponent(clear_and_new_order_btn, javax.swing.GroupLayout.PREFERRED_SIZE, 181, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 135, Short.MAX_VALUE)
                        .addComponent(jButton14)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 135, Short.MAX_VALUE)
                        .addComponent(btn_go_to_pay, javax.swing.GroupLayout.PREFERRED_SIZE, 181, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(100, 100, 100)
                        .addComponent(increase_order_size, javax.swing.GroupLayout.PREFERRED_SIZE, 71, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addGap(50, 50, 50))
        );
        order_panelLayout.setVerticalGroup(
            order_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(order_panelLayout.createSequentialGroup()
                .addGap(51, 51, 51)
                .addComponent(jLabel4)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(error_line, javax.swing.GroupLayout.PREFERRED_SIZE, 23, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(order_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(overview_total_prise_lbl, javax.swing.GroupLayout.PREFERRED_SIZE, 71, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jLabel2))
                .addGap(18, 18, 18)
                .addComponent(jScrollPane2, javax.swing.GroupLayout.DEFAULT_SIZE, 444, Short.MAX_VALUE)
                .addGap(36, 36, 36)
                .addGroup(order_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(decrease_order_size, javax.swing.GroupLayout.PREFERRED_SIZE, 71, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(clear_and_new_order_btn, javax.swing.GroupLayout.PREFERRED_SIZE, 51, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btn_go_to_pay, javax.swing.GroupLayout.PREFERRED_SIZE, 51, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(increase_order_size, javax.swing.GroupLayout.PREFERRED_SIZE, 71, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jButton14))
                .addGap(90, 90, 90))
        );

        order_panelLayout.linkSize(javax.swing.SwingConstants.VERTICAL, new java.awt.Component[] {jLabel2, overview_total_prise_lbl});

        order_panelLayout.linkSize(javax.swing.SwingConstants.VERTICAL, new java.awt.Component[] {btn_go_to_pay, clear_and_new_order_btn, decrease_order_size, jButton14});

        btn_man_input_1.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        btn_man_input_1.setText("Žitná mouka 5Kg");
        btn_man_input_1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_man_input_1ActionPerformed(evt);
            }
        });

        jButton3.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        jButton3.setText("Zpět");
        jButton3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton3ActionPerformed(evt);
            }
        });

        btn_man_input_2.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        btn_man_input_2.setText("Žitná mouka 10Kg");
        btn_man_input_2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_man_input_2ActionPerformed(evt);
            }
        });

        btn_man_input_4.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        btn_man_input_4.setText("Žitná mouka 25Kg");
        btn_man_input_4.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_man_input_4ActionPerformed(evt);
            }
        });

        btn_man_input_5.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        btn_man_input_5.setText("Žitná mouka 50Kg");
        btn_man_input_5.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_man_input_5ActionPerformed(evt);
            }
        });

        btn_man_input_6.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        btn_man_input_6.setText("Špaldová mouka 5Kg");
        btn_man_input_6.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_man_input_6ActionPerformed(evt);
            }
        });

        btn_man_input_7.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        btn_man_input_7.setText("Špaldová mouka 10Kg");
        btn_man_input_7.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_man_input_7ActionPerformed(evt);
            }
        });

        btn_man_input_9.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        btn_man_input_9.setText("Špaldová mouka 25Kg");
        btn_man_input_9.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_man_input_9ActionPerformed(evt);
            }
        });

        btn_man_input_10.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        btn_man_input_10.setText("Špaldová mouka 50Kg");
        btn_man_input_10.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_man_input_10ActionPerformed(evt);
            }
        });

        btn_man_input_3.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        btn_man_input_3.setText("Špaldová mouka 15Kg");
        btn_man_input_3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_man_input_3ActionPerformed(evt);
            }
        });

        btn_man_input_8.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        btn_man_input_8.setText("Špaldová mouka 15Kg");
        btn_man_input_8.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_man_input_8ActionPerformed(evt);
            }
        });

        btn_man_input_11.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        btn_man_input_11.setText("Špaldová mouka 5Kg");
        btn_man_input_11.setFocusable(false);
        btn_man_input_11.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_man_input_11ActionPerformed(evt);
            }
        });

        btn_man_input_12.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        btn_man_input_12.setText("Špaldová mouka 10Kg");
        btn_man_input_12.setFocusable(false);
        btn_man_input_12.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_man_input_12ActionPerformed(evt);
            }
        });

        btn_man_input_13.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        btn_man_input_13.setText("Špaldová mouka 15Kg");
        btn_man_input_13.setFocusable(false);
        btn_man_input_13.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_man_input_13ActionPerformed(evt);
            }
        });

        btn_man_input_14.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        btn_man_input_14.setText("Špaldová mouka 25Kg");
        btn_man_input_14.setFocusable(false);
        btn_man_input_14.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_man_input_14ActionPerformed(evt);
            }
        });

        btn_man_input_15.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        btn_man_input_15.setText("Špaldová mouka 50Kg");
        btn_man_input_15.setFocusable(false);
        btn_man_input_15.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_man_input_15ActionPerformed(evt);
            }
        });

        btn_manual_next.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        btn_manual_next.setText("Další");
        btn_manual_next.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_manual_nextActionPerformed(evt);
            }
        });

        btn_manual_previous.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        btn_manual_previous.setText("Předchozí");
        btn_manual_previous.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_manual_previousActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout manual_input_panelLayout = new javax.swing.GroupLayout(manual_input_panel);
        manual_input_panel.setLayout(manual_input_panelLayout);
        manual_input_panelLayout.setHorizontalGroup(
            manual_input_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(manual_input_panelLayout.createSequentialGroup()
                .addContainerGap(79, Short.MAX_VALUE)
                .addGroup(manual_input_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(btn_manual_previous, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(btn_man_input_1, javax.swing.GroupLayout.DEFAULT_SIZE, 228, Short.MAX_VALUE)
                    .addComponent(btn_man_input_2, javax.swing.GroupLayout.DEFAULT_SIZE, 228, Short.MAX_VALUE)
                    .addComponent(btn_man_input_4, javax.swing.GroupLayout.DEFAULT_SIZE, 228, Short.MAX_VALUE)
                    .addComponent(btn_man_input_3, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(btn_man_input_5, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addGap(50, 50, 50)
                .addGroup(manual_input_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jButton3, javax.swing.GroupLayout.PREFERRED_SIZE, 263, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btn_man_input_6, javax.swing.GroupLayout.PREFERRED_SIZE, 263, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btn_man_input_7, javax.swing.GroupLayout.PREFERRED_SIZE, 263, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btn_man_input_9, javax.swing.GroupLayout.PREFERRED_SIZE, 263, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btn_man_input_10, javax.swing.GroupLayout.PREFERRED_SIZE, 263, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btn_man_input_8, javax.swing.GroupLayout.PREFERRED_SIZE, 263, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(50, 50, 50)
                .addGroup(manual_input_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(btn_man_input_11, javax.swing.GroupLayout.DEFAULT_SIZE, 263, Short.MAX_VALUE)
                    .addComponent(btn_man_input_12, javax.swing.GroupLayout.DEFAULT_SIZE, 263, Short.MAX_VALUE)
                    .addComponent(btn_man_input_13, javax.swing.GroupLayout.DEFAULT_SIZE, 263, Short.MAX_VALUE)
                    .addComponent(btn_man_input_14, javax.swing.GroupLayout.DEFAULT_SIZE, 263, Short.MAX_VALUE)
                    .addComponent(btn_man_input_15, javax.swing.GroupLayout.DEFAULT_SIZE, 263, Short.MAX_VALUE)
                    .addComponent(btn_manual_next, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap(140, Short.MAX_VALUE))
        );

        manual_input_panelLayout.linkSize(javax.swing.SwingConstants.HORIZONTAL, new java.awt.Component[] {btn_man_input_1, btn_man_input_2, btn_man_input_4, btn_man_input_6});

        manual_input_panelLayout.setVerticalGroup(
            manual_input_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(manual_input_panelLayout.createSequentialGroup()
                .addGap(67, 67, 67)
                .addGroup(manual_input_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(manual_input_panelLayout.createSequentialGroup()
                        .addComponent(btn_man_input_11, javax.swing.GroupLayout.PREFERRED_SIZE, 77, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(31, 31, 31)
                        .addComponent(btn_man_input_12, javax.swing.GroupLayout.PREFERRED_SIZE, 77, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(31, 31, 31)
                        .addGroup(manual_input_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(btn_man_input_13, javax.swing.GroupLayout.PREFERRED_SIZE, 77, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addGroup(manual_input_panelLayout.createSequentialGroup()
                                .addGap(110, 110, 110)
                                .addGroup(manual_input_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(btn_man_input_14, javax.swing.GroupLayout.PREFERRED_SIZE, 77, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addGroup(manual_input_panelLayout.createSequentialGroup()
                                        .addGap(110, 110, 110)
                                        .addComponent(btn_man_input_15, javax.swing.GroupLayout.PREFERRED_SIZE, 77, javax.swing.GroupLayout.PREFERRED_SIZE))))))
                    .addGroup(manual_input_panelLayout.createSequentialGroup()
                        .addGroup(manual_input_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(btn_man_input_1, javax.swing.GroupLayout.PREFERRED_SIZE, 77, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(btn_man_input_6, javax.swing.GroupLayout.PREFERRED_SIZE, 77, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(31, 31, 31)
                        .addGroup(manual_input_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(btn_man_input_2, javax.swing.GroupLayout.PREFERRED_SIZE, 77, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(btn_man_input_7, javax.swing.GroupLayout.PREFERRED_SIZE, 77, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(31, 31, 31)
                        .addGroup(manual_input_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(manual_input_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                .addComponent(btn_man_input_3, javax.swing.GroupLayout.PREFERRED_SIZE, 77, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addComponent(btn_man_input_8, javax.swing.GroupLayout.PREFERRED_SIZE, 77, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addGroup(manual_input_panelLayout.createSequentialGroup()
                                .addGap(110, 110, 110)
                                .addGroup(manual_input_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(btn_man_input_9, javax.swing.GroupLayout.PREFERRED_SIZE, 77, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addGroup(manual_input_panelLayout.createSequentialGroup()
                                        .addComponent(btn_man_input_4, javax.swing.GroupLayout.PREFERRED_SIZE, 77, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addGap(33, 33, 33)
                                        .addGroup(manual_input_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                            .addComponent(btn_man_input_5, javax.swing.GroupLayout.PREFERRED_SIZE, 77, javax.swing.GroupLayout.PREFERRED_SIZE)
                                            .addComponent(btn_man_input_10, javax.swing.GroupLayout.PREFERRED_SIZE, 77, javax.swing.GroupLayout.PREFERRED_SIZE))))))))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 100, Short.MAX_VALUE)
                .addGroup(manual_input_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(btn_manual_next)
                    .addComponent(jButton3, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btn_manual_previous))
                .addContainerGap(79, Short.MAX_VALUE))
        );

        manual_input_panelLayout.linkSize(javax.swing.SwingConstants.VERTICAL, new java.awt.Component[] {btn_manual_next, btn_manual_previous, jButton3});

        final_total_price.setFont(new java.awt.Font("Dialog", 1, 28)); // NOI18N
        final_total_price.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        final_total_price.setText("1500 Kč");

        jLabel5.setFont(new java.awt.Font("Dialog", 1, 28)); // NOI18N
        jLabel5.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel5.setText("Celkem k zaplacení:");

        jLabel6.setFont(new java.awt.Font("Dialog", 1, 28)); // NOI18N
        jLabel6.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel6.setText("Zaplaceno:");

        given_money_input.setFont(new java.awt.Font("Dialog", 1, 28)); // NOI18N
        given_money_input.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        given_money_input.setText("0");
        given_money_input.setFocusable(false);

        jLabel7.setFont(new java.awt.Font("Dialog", 1, 28)); // NOI18N
        jLabel7.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        jLabel7.setText("Na zpět:");

        return_money_lbl.setFont(new java.awt.Font("Dialog", 1, 28)); // NOI18N
        return_money_lbl.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        return_money_lbl.setText("1500 Kč");

        btn_print_bill.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        btn_print_bill.setText("<html><center>Vytisknout<br>účtenku</center></html>");
        btn_print_bill.setFocusable(false);
        btn_print_bill.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_print_billActionPerformed(evt);
            }
        });

        btn_back_to_order.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        btn_back_to_order.setText("Zpět");
        btn_back_to_order.setFocusable(false);
        btn_back_to_order.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_back_to_orderActionPerformed(evt);
            }
        });

        btn_one.setFont(new java.awt.Font("Dialog", 1, 24)); // NOI18N
        btn_one.setText("1");
        btn_one.setToolTipText("");
        btn_one.setFocusable(false);
        btn_one.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_oneActionPerformed(evt);
            }
        });

        btn_two.setFont(new java.awt.Font("Dialog", 1, 24)); // NOI18N
        btn_two.setText("2");
        btn_two.setToolTipText("");
        btn_two.setFocusable(false);
        btn_two.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_twoActionPerformed(evt);
            }
        });

        btn_three.setFont(new java.awt.Font("Dialog", 1, 24)); // NOI18N
        btn_three.setText("3");
        btn_three.setToolTipText("");
        btn_three.setFocusable(false);
        btn_three.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_threeActionPerformed(evt);
            }
        });

        btn_four.setFont(new java.awt.Font("Dialog", 1, 24)); // NOI18N
        btn_four.setText("4");
        btn_four.setToolTipText("");
        btn_four.setFocusable(false);
        btn_four.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_fourActionPerformed(evt);
            }
        });

        btn_five.setFont(new java.awt.Font("Dialog", 1, 24)); // NOI18N
        btn_five.setText("5");
        btn_five.setToolTipText("");
        btn_five.setFocusable(false);
        btn_five.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_fiveActionPerformed(evt);
            }
        });

        btn_six.setFont(new java.awt.Font("Dialog", 1, 24)); // NOI18N
        btn_six.setText("6");
        btn_six.setToolTipText("");
        btn_six.setFocusable(false);
        btn_six.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_sixActionPerformed(evt);
            }
        });

        btn_seven.setFont(new java.awt.Font("Dialog", 1, 24)); // NOI18N
        btn_seven.setText("7");
        btn_seven.setToolTipText("");
        btn_seven.setFocusable(false);
        btn_seven.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_sevenActionPerformed(evt);
            }
        });

        btn_eight.setFont(new java.awt.Font("Dialog", 1, 24)); // NOI18N
        btn_eight.setText("8");
        btn_eight.setToolTipText("");
        btn_eight.setFocusable(false);
        btn_eight.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_eightActionPerformed(evt);
            }
        });

        btn_nine.setFont(new java.awt.Font("Dialog", 1, 24)); // NOI18N
        btn_nine.setText("9");
        btn_nine.setToolTipText("");
        btn_nine.setFocusable(false);
        btn_nine.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_nineActionPerformed(evt);
            }
        });

        btn_remove_char.setFont(new java.awt.Font("Dialog", 1, 24)); // NOI18N
        btn_remove_char.setText("C");
        btn_remove_char.setToolTipText("");
        btn_remove_char.setFocusable(false);
        btn_remove_char.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_remove_charActionPerformed(evt);
            }
        });

        btn_clear.setFont(new java.awt.Font("Dialog", 1, 24)); // NOI18N
        btn_clear.setText("CE");
        btn_clear.setToolTipText("");
        btn_clear.setFocusable(false);
        btn_clear.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_clearActionPerformed(evt);
            }
        });

        btn_zero.setFont(new java.awt.Font("Dialog", 1, 24)); // NOI18N
        btn_zero.setText("0");
        btn_zero.setToolTipText("");
        btn_zero.setFocusable(false);
        btn_zero.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_zeroActionPerformed(evt);
            }
        });

        btn_finish_order.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        btn_finish_order.setText("<html><center>Dokončit<br>objednávku</center></html>");
        btn_finish_order.setFocusable(false);
        btn_finish_order.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_finish_orderActionPerformed(evt);
            }
        });

        error_line1.setBackground(new java.awt.Color(255, 0, 0));
        error_line1.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        error_line1.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        error_line1.setOpaque(true);
        error_line1.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                error_line1MouseClicked(evt);
            }
        });

        javax.swing.GroupLayout finish_order_panelLayout = new javax.swing.GroupLayout(finish_order_panel);
        finish_order_panel.setLayout(finish_order_panelLayout);
        finish_order_panelLayout.setHorizontalGroup(
            finish_order_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, finish_order_panelLayout.createSequentialGroup()
                .addGroup(finish_order_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(finish_order_panelLayout.createSequentialGroup()
                        .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addGroup(finish_order_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(btn_remove_char, javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(btn_clear, javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(btn_zero, javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(18, 18, 18)
                        .addGroup(finish_order_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(finish_order_panelLayout.createSequentialGroup()
                                .addComponent(btn_one, javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(18, 18, 18)
                                .addComponent(btn_two, javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(18, 18, 18)
                                .addComponent(btn_three, javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addGroup(finish_order_panelLayout.createSequentialGroup()
                                .addComponent(btn_four, javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(18, 18, 18)
                                .addComponent(btn_five, javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(18, 18, 18)
                                .addComponent(btn_six, javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addGroup(finish_order_panelLayout.createSequentialGroup()
                                .addComponent(btn_seven, javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(18, 18, 18)
                                .addComponent(btn_eight, javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(18, 18, 18)
                                .addComponent(btn_nine, javax.swing.GroupLayout.PREFERRED_SIZE, 91, javax.swing.GroupLayout.PREFERRED_SIZE))))
                    .addGroup(finish_order_panelLayout.createSequentialGroup()
                        .addGap(100, 100, 100)
                        .addGroup(finish_order_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(btn_print_bill, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(jLabel5)
                            .addComponent(jLabel6, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 267, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(jLabel7, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 267, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 302, Short.MAX_VALUE)
                        .addGroup(finish_order_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, finish_order_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                                .addComponent(final_total_price, javax.swing.GroupLayout.DEFAULT_SIZE, 418, Short.MAX_VALUE)
                                .addComponent(given_money_input, javax.swing.GroupLayout.Alignment.LEADING))
                            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, finish_order_panelLayout.createSequentialGroup()
                                .addComponent(btn_back_to_order, javax.swing.GroupLayout.PREFERRED_SIZE, 200, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(18, 18, 18)
                                .addComponent(btn_finish_order, javax.swing.GroupLayout.PREFERRED_SIZE, 200, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addComponent(return_money_lbl, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 418, javax.swing.GroupLayout.PREFERRED_SIZE))))
                .addGap(94, 94, 94))
            .addGroup(finish_order_panelLayout.createSequentialGroup()
                .addGap(50, 50, 50)
                .addComponent(error_line1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addGap(50, 50, 50))
        );

        finish_order_panelLayout.linkSize(javax.swing.SwingConstants.HORIZONTAL, new java.awt.Component[] {jLabel6, jLabel7});

        finish_order_panelLayout.linkSize(javax.swing.SwingConstants.HORIZONTAL, new java.awt.Component[] {btn_back_to_order, btn_print_bill});

        finish_order_panelLayout.setVerticalGroup(
            finish_order_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(finish_order_panelLayout.createSequentialGroup()
                .addGap(75, 75, 75)
                .addComponent(error_line1, javax.swing.GroupLayout.PREFERRED_SIZE, 23, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(30, 30, 30)
                .addGroup(finish_order_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel5, javax.swing.GroupLayout.PREFERRED_SIZE, 61, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(final_total_price, javax.swing.GroupLayout.PREFERRED_SIZE, 61, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(20, 20, 20)
                .addGroup(finish_order_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel6, javax.swing.GroupLayout.PREFERRED_SIZE, 61, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(given_money_input, javax.swing.GroupLayout.PREFERRED_SIZE, 61, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(20, 20, 20)
                .addGroup(finish_order_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel7, javax.swing.GroupLayout.PREFERRED_SIZE, 61, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(return_money_lbl, javax.swing.GroupLayout.PREFERRED_SIZE, 61, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(19, 19, 19)
                .addGroup(finish_order_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(finish_order_panelLayout.createSequentialGroup()
                        .addGroup(finish_order_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(btn_one, javax.swing.GroupLayout.PREFERRED_SIZE, 85, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(btn_two, javax.swing.GroupLayout.PREFERRED_SIZE, 85, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(btn_three, javax.swing.GroupLayout.PREFERRED_SIZE, 85, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(18, 18, 18)
                        .addGroup(finish_order_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(btn_four, javax.swing.GroupLayout.PREFERRED_SIZE, 85, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(btn_five, javax.swing.GroupLayout.PREFERRED_SIZE, 85, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(btn_six, javax.swing.GroupLayout.PREFERRED_SIZE, 85, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(18, 18, 18)
                        .addGroup(finish_order_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(btn_seven, javax.swing.GroupLayout.PREFERRED_SIZE, 85, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(btn_eight, javax.swing.GroupLayout.PREFERRED_SIZE, 85, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(btn_nine, javax.swing.GroupLayout.PREFERRED_SIZE, 85, javax.swing.GroupLayout.PREFERRED_SIZE)))
                    .addGroup(finish_order_panelLayout.createSequentialGroup()
                        .addComponent(btn_remove_char, javax.swing.GroupLayout.PREFERRED_SIZE, 85, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addComponent(btn_clear, javax.swing.GroupLayout.PREFERRED_SIZE, 85, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addComponent(btn_zero, javax.swing.GroupLayout.PREFERRED_SIZE, 85, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 40, Short.MAX_VALUE)
                .addGroup(finish_order_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(btn_finish_order, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGroup(finish_order_panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addComponent(btn_print_bill, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(btn_back_to_order, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap(131, Short.MAX_VALUE))
        );

        finish_order_panelLayout.linkSize(javax.swing.SwingConstants.VERTICAL, new java.awt.Component[] {btn_back_to_order, btn_print_bill});

        javax.swing.GroupLayout bill_browserLayout = new javax.swing.GroupLayout(bill_browser);
        bill_browser.setLayout(bill_browserLayout);
        bill_browserLayout.setHorizontalGroup(
            bill_browserLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 1113, Short.MAX_VALUE)
        );
        bill_browserLayout.setVerticalGroup(
            bill_browserLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 710, Short.MAX_VALUE)
        );

        javax.swing.GroupLayout jLayeredPane1Layout = new javax.swing.GroupLayout(jLayeredPane1);
        jLayeredPane1.setLayout(jLayeredPane1Layout);
        jLayeredPane1Layout.setHorizontalGroup(
            jLayeredPane1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(order_panel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addGroup(jLayeredPane1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addComponent(manual_input_panel, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
            .addGroup(jLayeredPane1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addComponent(finish_order_panel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
            .addGroup(jLayeredPane1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(jLayeredPane1Layout.createSequentialGroup()
                    .addGap(0, 0, Short.MAX_VALUE)
                    .addComponent(bill_browser, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGap(0, 0, Short.MAX_VALUE)))
        );
        jLayeredPane1Layout.setVerticalGroup(
            jLayeredPane1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(order_panel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addGroup(jLayeredPane1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addComponent(manual_input_panel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
            .addGroup(jLayeredPane1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addComponent(finish_order_panel, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
            .addGroup(jLayeredPane1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(jLayeredPane1Layout.createSequentialGroup()
                    .addGap(0, 0, Short.MAX_VALUE)
                    .addComponent(bill_browser, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGap(0, 0, Short.MAX_VALUE)))
        );
        jLayeredPane1.setLayer(order_panel, javax.swing.JLayeredPane.DEFAULT_LAYER);
        jLayeredPane1.setLayer(manual_input_panel, javax.swing.JLayeredPane.DEFAULT_LAYER);
        jLayeredPane1.setLayer(finish_order_panel, javax.swing.JLayeredPane.DEFAULT_LAYER);
        jLayeredPane1.setLayer(bill_browser, javax.swing.JLayeredPane.DEFAULT_LAYER);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jLayeredPane1)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jLayeredPane1)
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void btn_go_to_payActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_go_to_payActionPerformed
        if(this.controler_ref.get_order_list().size() > 0)
        {
            show_order_finish_panel();
            this.final_total_price.setText(Double.toString(this.controler_ref.get_order_price_with_dph()) + " Kč");
            this.given_money_input.setText("0");
            this.return_money_lbl.setText("0.0 Kč");
            this.controler_ref.generate_bill_data();
        }  
    }//GEN-LAST:event_btn_go_to_payActionPerformed

    private void decrease_order_sizeActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_decrease_order_sizeActionPerformed
        int table_size = this.controler_ref.get_order_list().size();
        
        if(table_size > 0)
        {
            int selected_row = this.order_table_view.getSelectedRow();
            
            if(selected_row >= 0)
            {
                this.controler_ref.decrement_item_in_order_list(selected_row);

                update_order_table_list();

                if(table_size == this.controler_ref.get_order_list().size())
                    this.order_table_view.setRowSelectionInterval(selected_row,selected_row);

                if(this.controler_ref.get_order_list().isEmpty())
                    this.btn_go_to_pay.setEnabled(false);
            }
        }
    }//GEN-LAST:event_decrease_order_sizeActionPerformed

    private void increase_order_sizeActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_increase_order_sizeActionPerformed
        if(controler_ref.get_order_list().size() > 0)
        {
            int selected_row = this.order_table_view.getSelectedRow();
            if(selected_row >= 0)
            {
                this.controler_ref.increment_item_in_order_list(selected_row);

                update_order_table_list();

                this.order_table_view.setRowSelectionInterval(selected_row,selected_row);
            }
        }
    }//GEN-LAST:event_increase_order_sizeActionPerformed

    private void jButton14ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton14ActionPerformed
        show_manual_input_panel();
    }//GEN-LAST:event_jButton14ActionPerformed

    private void jButton3ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton3ActionPerformed
        show_order_panel();
    }//GEN-LAST:event_jButton3ActionPerformed

    private void jLabel4MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jLabel4MouseClicked
        this.click_to_finish++;
        
        if(this.click_to_finish >=2)
        {
            System.exit(0);
        }
    }//GEN-LAST:event_jLabel4MouseClicked

    private void btn_man_input_1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_man_input_1ActionPerformed
        manual_add_item(0+(man_input_btn_offset*15));
    }//GEN-LAST:event_btn_man_input_1ActionPerformed

    private void btn_man_input_2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_man_input_2ActionPerformed
        manual_add_item(1+(man_input_btn_offset*15));
    }//GEN-LAST:event_btn_man_input_2ActionPerformed

    private void btn_man_input_4ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_man_input_4ActionPerformed
        manual_add_item(3+(man_input_btn_offset*15));
    }//GEN-LAST:event_btn_man_input_4ActionPerformed

    private void btn_man_input_5ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_man_input_5ActionPerformed
        manual_add_item(4+(man_input_btn_offset*15));
    }//GEN-LAST:event_btn_man_input_5ActionPerformed

    private void btn_man_input_6ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_man_input_6ActionPerformed
        manual_add_item(5+(man_input_btn_offset*15));
    }//GEN-LAST:event_btn_man_input_6ActionPerformed

    private void btn_man_input_7ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_man_input_7ActionPerformed
        manual_add_item(6+(man_input_btn_offset*15));
    }//GEN-LAST:event_btn_man_input_7ActionPerformed

    private void btn_man_input_9ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_man_input_9ActionPerformed
        manual_add_item(8+(man_input_btn_offset*15));
    }//GEN-LAST:event_btn_man_input_9ActionPerformed

    private void btn_man_input_10ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_man_input_10ActionPerformed
        manual_add_item(9+(man_input_btn_offset*15));
    }//GEN-LAST:event_btn_man_input_10ActionPerformed

    private void error_lineMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_error_lineMouseClicked
        controler_ref.reset_internal_error();   
    }//GEN-LAST:event_error_lineMouseClicked

    private void clear_and_new_order_btnActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_clear_and_new_order_btnActionPerformed
        this.controler_ref.clear_order();
        this.btn_go_to_pay.setEnabled(false);
        update_order_table_list();
    }//GEN-LAST:event_clear_and_new_order_btnActionPerformed

    private void btn_finish_orderActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_finish_orderActionPerformed
        this.controler_ref.print_bill_if_not_printed_in_order();
        this.controler_ref.save_bill_data_for_printing_to_database();
        this.controler_ref.update_item_quantity();
        this.controler_ref.clear_order();
        update_order_table_list();
        this.btn_back_to_order.setEnabled(true);
        this.btn_go_to_pay.setEnabled(false);
        show_order_panel();
    }//GEN-LAST:event_btn_finish_orderActionPerformed

    private void btn_zeroActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_zeroActionPerformed
        set_btn_number_string("0");
    }//GEN-LAST:event_btn_zeroActionPerformed

    private void btn_clearActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_clearActionPerformed
        this.given_money_input.setText("0");
        update_order_table_list();
        count_rest_money();
    }//GEN-LAST:event_btn_clearActionPerformed

    private void btn_remove_charActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_remove_charActionPerformed
        if(this.given_money_input.getText().length() <= 1)
            this.given_money_input.setText("0");
        else
            this.given_money_input.setText(this.given_money_input.getText().substring(0, this.given_money_input.getText().length()-1));
        
        count_rest_money();
    }//GEN-LAST:event_btn_remove_charActionPerformed

    private void btn_nineActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_nineActionPerformed
        set_btn_number_string("9");
    }//GEN-LAST:event_btn_nineActionPerformed

    private void btn_eightActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_eightActionPerformed
        set_btn_number_string("8");
    }//GEN-LAST:event_btn_eightActionPerformed

    private void btn_sevenActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_sevenActionPerformed
        set_btn_number_string("7");
    }//GEN-LAST:event_btn_sevenActionPerformed

    private void btn_sixActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_sixActionPerformed
        set_btn_number_string("6");
    }//GEN-LAST:event_btn_sixActionPerformed

    private void btn_fiveActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_fiveActionPerformed
        set_btn_number_string("5");
    }//GEN-LAST:event_btn_fiveActionPerformed

    private void btn_fourActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_fourActionPerformed
        set_btn_number_string("4");
    }//GEN-LAST:event_btn_fourActionPerformed

    private void btn_threeActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_threeActionPerformed
        set_btn_number_string("3");
    }//GEN-LAST:event_btn_threeActionPerformed

    private void btn_twoActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_twoActionPerformed
        set_btn_number_string("2");
    }//GEN-LAST:event_btn_twoActionPerformed

    private void btn_oneActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_oneActionPerformed
        set_btn_number_string("1");
    }//GEN-LAST:event_btn_oneActionPerformed

    private void btn_back_to_orderActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_back_to_orderActionPerformed
        show_order_panel();
        this.controler_ref.clear_print_buffer();
    }//GEN-LAST:event_btn_back_to_orderActionPerformed

    private void btn_print_billActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_print_billActionPerformed
      // pokud se již vytiskne účtenka nelze se vrátit zpět do objednávkového okna, tlačítko zpět se musí tratit
        //this.btn_back_to_order.setEnabled(false);
        controler_ref.print_bill();
    }//GEN-LAST:event_btn_print_billActionPerformed

    private void error_line1MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_error_line1MouseClicked
        controler_ref.reset_internal_error(); 
    }//GEN-LAST:event_error_line1MouseClicked

    private void btn_man_input_3ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_man_input_3ActionPerformed
        manual_add_item(2+(man_input_btn_offset*15));
    }//GEN-LAST:event_btn_man_input_3ActionPerformed

    private void btn_man_input_8ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_man_input_8ActionPerformed
        manual_add_item(7+(man_input_btn_offset*15));
    }//GEN-LAST:event_btn_man_input_8ActionPerformed

    private void btn_man_input_11ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_man_input_11ActionPerformed
        manual_add_item(10+(man_input_btn_offset*15));
    }//GEN-LAST:event_btn_man_input_11ActionPerformed

    private void btn_man_input_12ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_man_input_12ActionPerformed
       manual_add_item(11+(man_input_btn_offset*15));
    }//GEN-LAST:event_btn_man_input_12ActionPerformed

    private void btn_man_input_13ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_man_input_13ActionPerformed
        manual_add_item(12+(man_input_btn_offset*15));
    }//GEN-LAST:event_btn_man_input_13ActionPerformed

    private void btn_man_input_14ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_man_input_14ActionPerformed
        manual_add_item(13+(man_input_btn_offset*15));
    }//GEN-LAST:event_btn_man_input_14ActionPerformed

    private void btn_man_input_15ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_man_input_15ActionPerformed
        manual_add_item(14+(man_input_btn_offset*15));
    }//GEN-LAST:event_btn_man_input_15ActionPerformed

    private void btn_manual_previousActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_manual_previousActionPerformed
        if(this.man_input_btn_offset > 0)
        {
            this.man_input_btn_offset --;
            initialize_manual_input(this.controler_ref.get_available_item_quantity());
        }
    }//GEN-LAST:event_btn_manual_previousActionPerformed

    private void btn_manual_nextActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_manual_nextActionPerformed
        int max = this.controler_ref.get_available_item_quantity();
        
        if(((this.man_input_btn_offset)*15) < max-1)
        {
            this.man_input_btn_offset ++;
            
            initialize_manual_input(max);
        }
    }//GEN-LAST:event_btn_manual_nextActionPerformed

    
    private void manual_add_item(int ID)
    {
        this.controler_ref.add_order_item(ID);
        this.btn_go_to_pay.setEnabled(true);
        update_order_table_list();
        show_order_panel();
    }
    
    /* local functions */
    
    /*
    ** function manipulating with layert layout, this function displayes layer with order overview
    */
    private void show_order_panel()
    {
        this.order_panel.setVisible(true);
        this.finish_order_panel.setVisible(false);
        this.manual_input_panel.setVisible(false);
    }
    
    /*
    ** function manipulating with layert layout, this function displayes layer with order finalizing
    */
    private void show_order_finish_panel()
    {
        this.order_panel.setVisible(false);
        this.finish_order_panel.setVisible(true);
        this.manual_input_panel.setVisible(false);        
    }
    
    /*
    ** function manipulating with layert layout, this function displayes layer with manual input of order data
    */
    private void show_manual_input_panel()
    {
        this.order_panel.setVisible(false);
        this.finish_order_panel.setVisible(false);
        this.manual_input_panel.setVisible(true);
    }
    
    private void count_rest_money()
    {
        double given_money = Double.parseDouble(this.given_money_input.getText());
        double rest = 0.0;
        double price = this.controler_ref.get_order_price_with_dph();
       
        
        if(given_money > price)
            rest = given_money - price;
        
        this.return_money_lbl.setText(Double.toString(rest) + " Kč");   
    }
    
    /*
    ** utility function which set string number to button label in key board in layer with order finalizing
    */
    private void set_btn_number_string(String num_str)
    {
        if(this.given_money_input.getText().equals("0") || this.given_money_input.getText().equals("") || (this.given_money_input.getText() == null))
            this.given_money_input.setText(num_str);
        else
            this.given_money_input.setText(this.given_money_input.getText()+num_str);
        
        count_rest_money();
    }
    
    /*
    ** function for update order view in table in layer with order overview
    */
    private void update_order_table_list()
    {
        /* clear table first */
        DefaultTableModel dm = (DefaultTableModel) this.order_table_view.getModel();
        dm.getDataVector().removeAllElements();
        dm.fireTableDataChanged(); // notifies the JTable that the model has changed
        
        /* load new records */
        ArrayList<OrderItem> order_list = controler_ref.get_order_list();

        for(int i=0; i<order_list.size(); i++)
        {
            OrderItem item = order_list.get(i);
            
            Object[] row = {item.getItemName(), 
                            Integer.toString(item.getQuantity())+" ks", 
                            Double.toString(item.getTotalPrice())+" Kč", 
                            Double.toString(Math.round(item.getTotalPrice()*this.controler_ref.get_dph_value()))+" Kč"};

            DefaultTableModel model = (DefaultTableModel) order_table_view.getModel();

            model.addRow(row);
            order_table_view.setRowHeight(i, 40);
        }
       
        this.overview_total_prise_lbl.setText(Double.toString(this.controler_ref.get_order_price_with_dph()) + " Kč");
    }
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JPanel bill_browser;
    private javax.swing.JButton btn_back_to_order;
    private javax.swing.JButton btn_clear;
    private javax.swing.JButton btn_eight;
    private javax.swing.JButton btn_finish_order;
    private javax.swing.JButton btn_five;
    private javax.swing.JButton btn_four;
    private javax.swing.JButton btn_go_to_pay;
    private javax.swing.JButton btn_man_input_1;
    private javax.swing.JButton btn_man_input_10;
    private javax.swing.JButton btn_man_input_11;
    private javax.swing.JButton btn_man_input_12;
    private javax.swing.JButton btn_man_input_13;
    private javax.swing.JButton btn_man_input_14;
    private javax.swing.JButton btn_man_input_15;
    private javax.swing.JButton btn_man_input_2;
    private javax.swing.JButton btn_man_input_3;
    private javax.swing.JButton btn_man_input_4;
    private javax.swing.JButton btn_man_input_5;
    private javax.swing.JButton btn_man_input_6;
    private javax.swing.JButton btn_man_input_7;
    private javax.swing.JButton btn_man_input_8;
    private javax.swing.JButton btn_man_input_9;
    private javax.swing.JButton btn_manual_next;
    private javax.swing.JButton btn_manual_previous;
    private javax.swing.JButton btn_nine;
    private javax.swing.JButton btn_one;
    private javax.swing.JButton btn_print_bill;
    private javax.swing.JButton btn_remove_char;
    private javax.swing.JButton btn_seven;
    private javax.swing.JButton btn_six;
    private javax.swing.JButton btn_three;
    private javax.swing.JButton btn_two;
    private javax.swing.JButton btn_zero;
    private javax.swing.JButton clear_and_new_order_btn;
    private javax.swing.JButton decrease_order_size;
    private javax.swing.JLabel error_line;
    private javax.swing.JLabel error_line1;
    private javax.swing.JLabel final_total_price;
    private javax.swing.JPanel finish_order_panel;
    private javax.swing.JTextField given_money_input;
    private javax.swing.JButton increase_order_size;
    private javax.swing.JButton jButton14;
    private javax.swing.JButton jButton3;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JLabel jLabel6;
    private javax.swing.JLabel jLabel7;
    private javax.swing.JLayeredPane jLayeredPane1;
    private javax.swing.JRadioButtonMenuItem jRadioButtonMenuItem1;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JPanel manual_input_panel;
    private javax.swing.JPanel order_panel;
    private javax.swing.JTable order_table_view;
    private javax.swing.JLabel overview_total_prise_lbl;
    private javax.swing.JLabel return_money_lbl;
    // End of variables declaration//GEN-END:variables
}
