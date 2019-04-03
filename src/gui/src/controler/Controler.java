
/*
** chybové stavy:
** 1 - chyba spojení s databází!
** 2 - neznámé ID objednávky!
** 3 - Neznámá pozice objednávky!
** 4 - Nelze se připojit k tiskárně!
** 5 - Neúspěšné odpojení tiskárny!
*/



package controler;

import controler.scanner.Scanner;
import controler.eet.EET;
import controler.printer.Printer;
import controler.database.Database;
import java.util.ArrayList;

/**
 *
 * @author petr
 */
public class Controler 
{
    /* modules objects*/
    private final EET eet_ref;
    private final Printer printer_ref;
    private final Scanner scanner_ref;
    private final Database database_ref;
    
    /* local atributs */
    private final ArrayList<OrderItem> order_list = new ArrayList();
    private String error_message;
    double order_prise;
    
    public Controler()
    {
        this.eet_ref = new EET();
        this.printer_ref = new Printer();
        this.scanner_ref = new Scanner();
        this.database_ref = new Database();
        
        this.error_message = new String();
        

        if(database_ref.connect_db() == false)
            this.error_message = "#1 Chyba spojení s databází!";
    }
    
    
    /* public function - class interface */
    public String get_error_meesage()
    {
        return this.error_message;
    }
    
    /* return list of order items */
    public ArrayList get_order_list()
    {
        return this.order_list;
    }
    
   
    
    /*
    ** function add item to item list or increment quantity of existing
    */
    public boolean add_order_item(int ID)
    {
        if(database_ref.is_connected() == true)
        {
            String item_name = get_order_item_name_by_code(ID);
            
            if(item_name != null)
            {
                OrderItem new_item = new OrderItem(ID, item_name,  this.get_oder_item_price_by_code(ID));
                boolean item_found = false;
                
                for(int i=0; i<this.order_list.size(); i++)
                {
                    OrderItem item = this.order_list.get(i);
                    
                    if(item.get_id() == ID)
                    {
                        item_found = true;
                        item.increment_quantity();
                        break;
                    } 
                }
                
                if(item_found == false)
                {
                    order_list.add(new_item);
                }
                
                return true;
            }
            else
            {
                this.error_message = "#2 Neznámý ID kód objednávky!";
            }
        }
        
        return false;
    }
    
    /*
    ** function is cyclic called from gui and if the database is not connected, then is set an error string and displayed in gui interface
    */
    public void check_db_connection()
    {
        if(database_ref.is_connected() == false)
        {
             this.error_message = "#1 Chyba spojení s databází!";
        }
        else
        {
            if(this.error_message.equals("#1 Chyba spojení s databází!"))
                this.error_message = "";
        }
    }
    
    
    public void generate_bill_data()
    {
        String sum_string = "Celkem Včetně DPH:";
                
        this.printer_ref.add_blank_line(3);
        this.printer_ref.add_order_item("Zboží", "Ks", "Cena" ,"S DPH");
        this.printer_ref.add_blank_line(1);
        
        for(int i=0; i<this.order_list.size(); i++)
        {
            OrderItem item = this.order_list.get(i);
            this.printer_ref.add_order_item(item.get_order_name(), 
                                        Integer.toString(item.get_quantity())+"Ks", 
                                        Double.toString(item.get_total_price())+"Kč",
                                        Double.toString(Math.round(item.get_total_price()*this.get_dph_value()))+"Kč");
        }
        
        this.printer_ref.line_feed('-', 42);
        this.printer_ref.add_string(sum_string);
        
        String price_str = this.get_order_price_with_dph()+"Kč";
        this.printer_ref.line_feed(' ', 42-sum_string.length()-price_str.length());
        this.printer_ref.add_string(price_str);
         
        this.printer_ref.add_blank_line(3);
        this.printer_ref.cut_paper();
    }
    
    public void clear_bill_data()
    {
        this.printer_ref.clear_print_buffer();
    }
    
    public double get_dph_value()
    {
        return 1.21;
    }
    
    /*
    ** this function return state from scanner module, which holds information about input from scanner 
    */
    public boolean update_order_list_by_scanner()
    {
        return this.scanner_ref.scanner_in_event_state();
    }
    
    /* generates data for print of the bill and sent this data to printer */
    public void print_bill()
    {
        if(this.printer_ref.connect_printer_lin() == true)
        {
            this.printer_ref.print();
            
            if(this.printer_ref.close_printer_connection_lin() == false)
            {
                this.error_message = "#5 Neúspěšné odpojení tiskárny!";
            }
        }
        else
        {
            this.error_message = "#4 Nelze se připojit k tiskárně!";
        }
    }
    
    /* decrements quantity of order item in array list, or remove the record from array list if the quantitiy is zero */
    public void decrement_item(int index)
    {
        if((index >= 0) && (index < this.order_list.size()))
        {
            this.order_list.get(index).decrement_quantity();
            if(this.order_list.get(index).get_quantity() <= 0)
            {
                this.order_list.remove(index);
            }
        }
        else
        {
            this.error_message = "#3 Neznámá pozice objednávky!";
        }
    }
    
    
    /* increments quantity of order item in array list */
    public void increment_item(int index)
    {
        if(index >= 0 && index < this.order_list.size())
        {
            this.order_list.get(index).increment_quantity();
        }
        else
        {
            this.error_message = "#3 Neznámá pozice objednávky!";
        }
    }
    
    public double get_order_price_with_dph()
    {
        return Math.round(this.get_order_price() * this.get_dph_value());
    }
    
    public double get_order_price()
    {
        double total_prise = 0.0;
        
        for(int i=0; i<this.order_list.size(); i++)
        {
            OrderItem item = order_list.get(i);
            total_prise += item.get_total_price();
        }
        
        return total_prise;
    }
    
    /* clear order list */
    public void clear_order()
    {
        this.order_list.clear();
        clear_bill_data(); 
        reset_error();
    }
    
    public void print_bill_if_not_printed()
    {
        if(this.printer_ref.get_print_counter() == 0)
        {
            this.print_bill();
        }
    }
    
    /* reset the error state */
    public void reset_error()
    {
        this.error_message = "";
    }
    
    /* private functions */
    
    
    private double get_oder_item_price_by_code(int ID)
    {
        if(ID == 0)
        {
            return 20.0;
        }
        else if(ID == 1)
        {
            return 35.0;
        }
        else if(ID == 2)
        {
            return 50.0;
        }
        else if(ID == 3)
        {
            return 50.0;
        }
        else if(ID == 4)
        {
            return 80.0;
        }
        else if(ID == 5)
        {
            return 25.0;
        }
        else if(ID == 6)
        {
            return 80.0;
        }
        else if(ID == 7)
        {
            return 120.0;
        }
        else if(ID == 8)
        {
            return 200.0;
        }
        else if(ID == 9)
        {
            return 370.0;
        }
        else
        {
            return 0.0;
        }
    }
    
    /* get name of the order name by given ID scanned from bar code or manual inserted via graphic interface */
    private String get_order_item_name_by_code(int ID)
    {
        if(ID == 0)
        {
            return "Žitná mouka 5Kg";
        }
        else if(ID == 1)
        {
            return "Žitná mouka 10Kg";
        }
        else if(ID == 2)
        {
            return "Žitná mouka 15Kg";
        }
        else if(ID == 3)
        {
            return "Žitná mouka 25Kg";
        }
        else if(ID == 4)
        {
            return "Žitná mouka 50Kg";
        }
        else if(ID == 5)
        {
            return "Špaldová mouka 5Kg";
        }
        else if(ID == 6)
        {
            return "Špaldová mouka 10Kg";
        }
        else if(ID == 7)
        {
            return "Špaldová mouka 15Kg";
        }
        else if(ID == 8)
        {
            return "Špaldová mouka 25Kg";
        }
        else if(ID == 9)
        {
            return "Špaldová mouka 50Kg";
        }
        else
        {
            return null;
        }
    }
}
