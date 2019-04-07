
/*
** chybové stavy:
** 1 - chyba spojení s databází!
** 2 - neznámé ID objednávky!
** 3 - Neznámá pozice objednávky!
** 4 - Tisk účtenky nebyl úspěšný!
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
    private final int platform;
    
    public Controler()
    {
        this.eet_ref = new EET();
        this.printer_ref = new Printer();
        this.scanner_ref = new Scanner();
        this.database_ref = new Database();
        
        this.error_message = new String();        
        this.platform = get_platform(System.getProperty("os.name"));
     
        
        /*
        if(database_ref.connect_db() == false)
            this.error_message = "#1 Chyba spojení s databází!";
        */
    }
    
    
    /************************* public function - class interface **********************/
    
    /*
    ** vrátí obsah chybového bufferu do vrstvy grafického rozhraní pro její zobrazení
    */
    public String get_error_meesage()
    {
        return this.error_message;
    }
    
    /* 
    ** return list of order items 
    */
    public ArrayList get_order_list()
    {
        return this.order_list;
    }
    
   
    
    /*
    ** function add item to item list or increment quantity of existing
    */
    public boolean add_order_item(int ID)
    {
        //if(database_ref.is_connected() == true)
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
    
    /*
    ** reinicializuje data pro tiskárnu
    */
    public void clear_bill_data()
    {
        this.printer_ref.clear_print_buffer();
    }
    
    /*
    ** pro centrální nastavení dph hodnoty
    */
    public double get_dph_value()
    {
        return 1.15;
    }
    
    /*
    ** uloží data pro tisk účtenky do databáze, aby bylo možné jej v případě potřeby vytisknout znovu
    */
    public boolean save_bill_to_database()
    {
        return true;
    }
    
    /*
    ** this function return state from scanner module, which holds information about input from scanner 
    */
    public boolean update_order_list_by_scanner()
    {
        return this.scanner_ref.scanner_in_event_state();
    }
    
    /* 
    ** generates data for print of the bill and sent this data to printer 
    */
    public void print_bill()
    {
        if(this.printer_ref.print(this.platform) == false)
        {
            this.error_message = "#4 Tisk účtenky nebyl úspěšný!";
        }
    }
    
    /* 
    ** decrements quantity of order item in array list, or remove the record from array list if the quantitiy is zero 
    */
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
    
    
    /* 
    ** increments quantity of order item in array list 
    */
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
    
    /*
    ** vypočítá celkovou hodnotu objednávky včetně dph a vrátí ji jako výsledek
    */
    public double get_order_price_with_dph()
    {
        return Math.round(this.get_order_price() * this.get_dph_value());
    }
    
    /*
    ** vypočítá celkovou hodnotu objednávky bez dph a vrátí ji jako výsledek
    */
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
    
    /* 
    ** clear order list 
    */
    public void clear_order()
    {
        this.order_list.clear();
        clear_bill_data(); 
        reset_error();
    }
    
    /*
    ** aby byla účtenka u každé objedávky vždy vytištěna alespoň jednou je ve třítě Printer definováno
    ** počítadlo výtisků pro danou objednávku a pokud je tato funkce zavolána při dokončování objednávky
    ** automaticky vytiskne účtenku v případě, že nebyla vytištena ručně
    */
    public void print_bill_if_not_printed()
    {
        if(this.printer_ref.get_print_counter() == 0)
        {
            this.print_bill();
        }
    }
    
    /* 
    ** reset the error state 
    */
    public void reset_error()
    {
        this.error_message = "";
    }
    
    public int get_available_item_num()
    {
        return 15;
    }    
    /* 
    ** get name of the order name by given ID scanned from bar code or manual inserted via graphic interface 
    */
    public String get_order_item_name_by_code(int ID)
    {
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
            default:
                return "defalult";
        }
    }
    
    /*********************** private functions ***************************/
    
    /*
    ** identifikace základní ceny bez dph pro produkt identifikovaný pomocí hodnoty ID
    */
    private double get_oder_item_price_by_code(int ID)
    {
        switch (ID) {
            case 0:
                return 60.85;
            case 1:
                return 121.70;
            case 2:
                return 182.55;
            case 3:
                return 304.25;
            case 4:
                return 608.50;
            case 5:
                return 78.25;
            case 6:
                return 156.50;
            case 7:
                return 234.75;
            case 8:
                return 391.25;
            case 9:
                return 782.50;
            case 10:
                return 78.25;
            case 11:
                return 156.50;
            case 12:
                return 234.75;
            case 13:
                return 391.25;
            case 14:
                return 782.50;    
            default:
                return 0.0;
        }
    }
    
    
    
    /*
    ** aby byla aplikace můltiplatformní je nutné zjistit na které platfomně byla spuštěna
    ** na základě toho se vrátí číselná hodnota identifikující danou platformu
    ** v aplikaci je platformě závislí kód (viz. tiskárna)
    */
    private int get_platform(String platform_name)
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
