
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

package md_ucetni_system;

import java.util.ArrayList;
import java.util.Date;

/**
 *
 * @author petr
 */
public class Controler extends Database
{
    private String error_message;
    private final int platform;
    private final OrderService orderService; 
    
    public Controler()
    {
        super();
        
        this.orderService = new OrderService();
        this.error_message = new String();        
        this.platform = get_running_platform(System.getProperty("os.name"));
        
        if(this.connect_db() == false)
        {
            this.error_message = "#1 Chyba spojení s databází!";
        }
        else
        {
            save_bills_from_file_to_database();
        }    
    }
    
    public boolean add_order_item(int ID)
    {
        if(is_connected() == true)
        {
            int item_quantity = this.get_available_item_quantity_by_ID(ID);
            
            if(item_quantity < 0)
            {
                error_message = "#2 neznámé ID objednávky!";
            }
            else if(item_quantity == 0)
            {
                error_message = "#6 Nedostatek skladových zásob";
            }
            else
            {
                update_order_list(ID, item_quantity);
                
                return true;
            }
        }

        return false;
    }
    
    private void update_order_list(int ID, int item_quantity)
    {
        if(this.orderService.containItemWithID(ID))
                { 
                    if(item_quantity+1 >= this.orderService.findOrderItemByID(ID).getQuantity())
                    {
                        this.orderService.findOrderItemByID(ID).incrementQuantity();
                    }                    
                }
                else
                {
                    if(this.get_available_item_quantity_by_ID(ID) >= 1)
                    {
                        String item_name = get_order_item_name_by_id(ID);
                        String item_shortcut_name = get_item_shortcut_name_by_ID(ID);
                        double item_price = get_item_price_by_ID(ID);
                        
                        this.orderService.addNewItem(ID, item_name, item_shortcut_name, item_price);
                    }
                    
                }
    }
    
    public void check_db_connection()
    {
        if(is_connected() == false)
        {
            if(this.connect_db() == false)
                this.error_message = "#1 Chyba spojení s databází!";
        }
        else
        {
            if(this.error_message.equals("#1 Chyba spojení s databází!"))
                this.error_message = "";
        }
    }
    
    private void bill_header()
    {
        this.add_string("Michal Zuna");
        this.add_blank_line(1);
        this.add_string("Pod Zelenou cestou 1768");
        this.add_blank_line(1);
        this.add_string("511 01 Turnov");
        this.add_blank_line(1);
    }
    
    void bill_content()
    {
         for(int i=0; i < this.orderService.getListSize(); i++)
        {
            OrderItem item = this.orderService.getOderList().get(i);
            this.add_order_item(item.getItemShortcutName(), 
                                        Integer.toString(item.getQuantity())+"Ks", 
                                        Double.toString(item.getTotalPrice())+"Kč",
                                        Double.toString(Math.round(item.getTotalPrice()*this.get_dph_value()))+"Kč");
        }
    }
    
    public void generate_bill_data()
    {
        String sum_string = "Celkem Včetně DPH:";
                
        this.add_blank_line(3);
        
        /* hlavička */
        bill_header();
        
        this.add_order_item("Zboží", "Ks", "Cena" ,"S DPH");
        this.add_blank_line(1);
        
        bill_content();
        
        this.line_feed('-', 42);
        this.add_string(sum_string);
        
        String price_str = this.get_order_price_with_dph()+"Kč";
        this.line_feed(' ', 42-sum_string.length()-price_str.length());
        this.add_string(price_str);
         
        this.add_blank_line(3);
        this.cut_paper();
    }
    
    public double get_order_price_with_dph()
    {
        return Math.round(this.orderService.getOrderListTotalPrice()*this.get_dph_value());
    }
    
    public double get_dph_value()
    {
        return 1.15;
    }
    
    public String get_order_item_name_by_id(int ID)
    {
         return this.get_item_name_by_ID(ID);
    }
    
    public String get_error_meesage()
    {
        return this.error_message;
    }
    
    public void reset_internal_error()
    {
        this.error_message = "";
    }
    
    public ArrayList get_order_list()
    {
        return this.orderService.getOderList();
    }
    
    public void decrement_item_in_order_list(int index)
    {
        if(this.orderService.decrementItemQuantityByIndex(index) == false)
        {
            this.error_message = "#3 Neznámá pozice objednávky!";
        }
    }
    
    public void increment_item_in_order_list(int index)
    {
        if(index >= 0 && index < this.orderService.getOderList().size())
        {
            int quantity = this.get_available_item_quantity_by_ID(this.orderService.getOderList().get(index).getID());
            
            if(this.orderService.getOderList().get(index).getQuantity() < quantity)
                this.orderService.getOderList().get(index).incrementQuantity();
            else
                this.error_message = "#6 Nedostatek skladových zásob";
        }
        else
        {
            this.error_message = "#3 Neznámá pozice objednávky!";
        }
    }
    
    public void clear_order()
    {
        this.orderService.clear();
        this.clear_print_buffer();
        //reset_error();
    }
    
    public void print_bill()
    {
        if(this.print(this.platform) == false)
        {
            this.error_message = "#4 Tisk účtenky nebyl úspěšný!";
        }
    }
    
    public void print_bill_if_not_printed_in_order()
    {
        if(this.get_print_counter() == 0)
        {
            this.print_bill();
        }
    }
    
    public boolean save_bill_data_for_printing_to_database()
    {
        long date_in_millisec = new Date().getTime();
        return this.save_bill_data(this.get_print_buffer(), date_in_millisec);
    }
    
     public boolean update_item_quantity()
    {
        for(int i=0; i < this.orderService.getListSize(); i++)
        {
            OrderItem item = this.orderService.getOderList().get(i);
            int quantity = this.get_available_item_quantity_by_ID(item.getID());
            
            if(this.update_item_quantity_by_ID(item.getID(), quantity-item.getQuantity()) == false)
            {
                this.error_message = "#7 Chyba při aktualizaci skladových zásob";
                return false;
            }
        }
        
        return true;
    }
    
    public void update_order_list_by_scanner()
    {
        this.orderService.update_order_list_by_scanner();
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
}


