
/*
** Jádro systému, které propojuje jednotlivé dílčí moduly: Printer, Database, Scanner, EET
** 
**
**
**
**
** chybové stavy:
** 1 - chyba spojení s databází!
** 2 - neznámé ID objednávky!
** 3 - Neznámá pozice objednávky!
** 4 - Tisk účtenky nebyl úspěšný!
** 5 - Chyba načítání dat, něco se stalo s databází!
** 6 - Nedostatek skladových zásob
** 7 - Chyba při aktualizaci skladových zásob
*/



package controler;

import controler.scanner.Scanner;
import controler.eet.EET;
import controler.printer.Printer;
import controler.database.Database;
import java.util.ArrayList;
import java.util.Date;
import java.util.TreeMap;

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
    private final TreeMap <Integer, OrderItem> order_list;
    private String error_message;
    private final int platform;
    
    public Controler()
    {
        this.eet_ref = new EET();
        this.printer_ref = new Printer();
        this.scanner_ref = new Scanner();
        this.database_ref = new Database();
        
        this.error_message = new String();        
        this.platform = get_running_platform(System.getProperty("os.name"));
        this.order_list = new TreeMap<>();
        
        if(database_ref.connect_db() == false)
        {
            this.error_message = "#1 Chyba spojení s databází!";
        }
        else
        {
            save_bills_from_file_to_database();
        }    
    }
    
    
    /************************* public function - class interface **********************/
    
    
    public String get_error_meesage()
    {
        return this.error_message;
    }
    
    public TreeMap get_order_list()
    {
        return this.order_list;
    } 
    
    public boolean add_order_item(int ID)
    {        
        if(database_ref.is_connected() == true)
        {
            int item_quantity = this.database_ref.get_available_item_quantity_by_ID(ID);
            
            if (item_quantity >= 0)
            {
                if(this.order_list.get(ID) != null)
                { 
                    if(item_quantity+1 >= this.order_list.get(ID).quantity)
                    {

                    }
                }
                else
                {
                    if(this.database_ref.get_available_item_quantity_by_ID(ID) >= 1)
                    {
                        String item_name = get_order_item_name_by_id(ID);
                        String item_shortcut_name = get_order_item_shortcut_name_by_id(ID);
                        double item_price = get_order_item_price_by_ID(ID);

                        OrderItem new_item = new OrderItem(ID, item_name, item_shortcut_name, item_price);
                    }
                }

            }
            else
            {
                error_message = "#2 neznámé ID objednávky!";
            }
        }
        
        return false;
    }
    
    public void check_db_connection()
    {
        if(database_ref.is_connected() == false)
        {
            // this.error_message = "#1 Chyba spojení s databází!";
        }
        else
        {
            if(this.error_message.equals("#1 Chyba spojení s databází!"))
                this.error_message = "";
        }
    }
    
    /*
    ** generování dat pro tisk účtenky z pole obsahující objednávku
    ** tato data jsou generována pouze jednou a poté je možné účtenku podle
    ** stejné předlohy tisknout opakovaně
    ** při návratu do objednávky pro její úpravu jsou vygenerované instrukce vymazány a
    ** poté opět vygenerovány z aktualizovaných dat
    */
    public void generate_bill_data()
    {
        String sum_string = "Celkem Včetně DPH:";
                
        this.printer_ref.add_blank_line(3);
        
        /* hlavička */
        this.printer_ref.add_string("Michal Zuna");
        this.printer_ref.add_blank_line(1);
        this.printer_ref.add_string("Pod Zelenou cestou 1768");
        this.printer_ref.add_blank_line(1);
        this.printer_ref.add_string("511 01 Turnov");
        this.printer_ref.add_blank_line(1);
        
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
    

    public void clear_printer_output_buffer()
    {
        this.printer_ref.clear_print_buffer();
    }

    public double get_dph_value()
    {
        return 1.15;
    }

    public boolean save_bill_data_for_printing_to_database()
    {
        long date_in_millisec = new Date().getTime();
        return this.database_ref.save_bill_data(this.printer_ref.get_print_buffer(), date_in_millisec);
    }
    
    /*
    ** this function return state from scanner module, which holds information about input from scanner 
    */
    public boolean update_order_list_by_scanner()
    {
        return this.scanner_ref.scanner_in_event_state();
    }
    
    public void print_bill()
    {
        if(this.printer_ref.print(this.platform) == false)
        {
            this.error_message = "#4 Tisk účtenky nebyl úspěšný!";
        }
    }
    

    public void decrement_item_in_order_list(int index)
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
    
    
    public void increment_item_in_order_list(int index)
    {
        if(index >= 0 && index < this.order_list.size())
        {
            int quantity = this.database_ref.get_available_item_quantity_by_ID(this.order_list.get(index).get_id());
            
            if(this.order_list.get(index).get_quantity() < quantity)
                this.order_list.get(index).increment_quantity();
            else
                this.error_message = "#6 Nedostatek skladových zásob";
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

    public void clear_order()
    {
        this.order_list.clear();
        clear_printer_output_buffer(); 
        //reset_error();
    }
    
    public boolean update_item_quantity()
    {
        for(int i=0; i < this.order_list.size(); i++)
        {
            OrderItem item = this.order_list.get(i);
            int quantity = this.database_ref.get_available_item_quantity_by_ID(item.get_id());
            
            if(this.database_ref.update_item_quantity_by_ID(item.get_id(), quantity-item.get_quantity()) == false)
            {
                this.error_message = "#7 Chyba při aktualizaci skladových zásob";
                return false;
            }
        }
        
        return true;
    }
    
    public void print_bill_if_not_printed_in_order()
    {
        if(this.printer_ref.get_print_counter() == 0)
        {
            this.print_bill();
        }
    }
    

    public void reset_internal_error()
    {
        this.error_message = "";
    }
    
    public int get_available_item_num()
    {
        return this.database_ref.get_available_item_quantity();
    }    
    
    public String get_order_item_shortcut_name_by_id(int ID)
    {
        
        return null;
    }

    public String get_order_item_name_by_id(int ID)
    {
         return this.database_ref.get_item_name_by_ID(ID);
         
        /*
        switch (ID) {
            case 0:
                return "Žitná chlebová 5Kg";
            case 1:
                return "Žitná chlebová 10Kg";
            case 2:
                return "Žitná chlebová 15Kg";
            case 3:
                return "Žitná chlebová 25Kg";
            case 4:
                return "Žitná chlebová 50Kg";
            case 5:
                return "Žitná celozrnná 5Kg";
            case 6:
                return "Žitná celozrnná 10Kg";
            case 7:
                return "Žitná celozrnná 15Kg";
            case 8:
                return "Žitná celozrnná 25Kg";
            case 9:
                return "Žitná celozrnná 50Kg";
            case 10:
                return "Žitná trhanka 5Kg";
            case 11:
                return "Žitná trhanka 10Kg";
            case 12:
                return "Žitná trhanka 15Kg";    
            case 13:
                return "Žitná trhanka 25Kg";  
            case 14:
                return "Žitná trhanka 50Kg";    
            case 15:
                return "Špaldová mouka 50Kg"; 
            default:
                return "defalult";
        }
        */
    }
    
    /*********************** private functions ***************************/
    
    private void save_bill_data_to_file(String bill_cmd, String key)
    {
        
    }
    
    private ArrayList check_nonsaved_bills_in_directory()
    {
        ArrayList<String> bill_list = new ArrayList<>();
        return bill_list;
    }
    
    private void save_bills_from_file_to_database()
    {
        ArrayList bill_list = check_nonsaved_bills_in_directory();
        
        if(bill_list.size() > 0)
        {
            
        }
    }

    private double get_order_item_price_by_ID(int ID)
    {
            return this.database_ref.get_item_price_by_ID(ID);
    }
    
    private int get_running_platform(String platform_name)
    {
        if(platform_name.startsWith("Windows"))
        {
            return 0;
        }
        else if(platform_name.startsWith("Linux"))
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
}
