/*
** výchozí uživatel pro pokladní systém je 'cashdesk' a heslo 'asdfghjkl'
**
*/



import java.sql.*;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;


public class Database 
{
    private Connection con;
    private Statement stat;
    private ResultSet rs;

    public Database()
    {
        
    }
    
    public boolean connect_db()
    {
        try
        {
            Class.forName("com.mysql.jdbc.Driver");
            con = DriverManager.getConnection("jdbc:mysql://localhost:3306/property", "cashdesk", "asdfghjkl");
            stat = con.createStatement();
            
            return true;
        }
        catch(ClassNotFoundException | SQLException e)
        {
            System.out.println("Database connection error description: " + e);
            return false;
        }
    }
    
    public String get_item_name_by_ID(int ID)
    {
        if(this.is_connected() == true)
        {
            try 
            {
                rs = stat.executeQuery("select item_name from available_items where item_id="+Integer.toString(ID)+";");

                if(rs.next())
                {
                    return rs.getString(1);
                }
            } 
            catch (SQLException ex) 
            {
                return null;
            }
        }
        
        return null;
    }
    
    /*
    ** funkce vrátí počet položek (řádků) v databázové tabulce available_items kde se
    ** uchovávají informace o dostupních prodejních položkách
    ** tato funkce je distribuována controler třídou do vrstvy view kde se 
    ** používá především v kontruktoru pro inicializaci karty pro manuální vstup objednávek
    */
    public int get_available_item_quantity()
    {
        if(this.is_connected() == true)
        {
            try 
            {
                rs = stat.executeQuery("select count(*) rows from available_items;");

                if(rs.next())
                     return rs.getInt(1);
                else
                    
                return 0;
            } 
            catch (SQLException ex) 
            {
                Logger.getLogger(Database.class.getName()).log(Level.SEVERE, null, ex);
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    
    /*
    ** vrátí uloženou hodnotu ceny za dané položky (bez dph)
    */
    public double get_item_price_by_ID(int ID)
    {
        if(this.is_connected() == true)
        {
            try 
            {
                rs = stat.executeQuery("select item_price from available_items where item_id="+Integer.toString(ID)+";");

                if(rs.next())
                     return rs.getDouble(1);
                else
                    
                return 0.0;
            } 
            catch (SQLException ex) 
            {
                Logger.getLogger(Database.class.getName()).log(Level.SEVERE, null, ex);
                return 0.0;
            }
        }
        else
        {
            return 0.0;
        }
    }
    
    /*
    ** funkce vrátí dostupné množství skladových zásob dané položky
    */
    public int get_available_item_quantity_by_ID(int ID)
    {
        if(this.is_connected() == true)
        {
            try 
            {
                rs = stat.executeQuery("select item_quantiti from available_items where item_id="+Integer.toString(ID)+";");

                if(rs.next())
                     return rs.getInt(1);
            } 
            catch (SQLException ex) 
            {
                Logger.getLogger(Database.class.getName()).log(Level.SEVERE, null, ex);
                return -1;
            }
        }

        return -1;
    }
    
    /*
    ** dekrementuje hodnotu množství dané položky na skladě, nikdy ne méně než nula
    */
    public boolean update_item_quantity_by_ID(int ID, int new_amount)
    {
        if(this.is_connected() == true)
        {
            try
            {
                String query = " update available_items set item_quantiti="+Integer.toString(new_amount)+" where item_id="+Integer.toString(ID)+";";
                PreparedStatement preparedStmt = this.con.prepareStatement(query); 

                preparedStmt.execute();
                return true;
            } 
            catch (SQLException ex) 
            {
                Logger.getLogger(Database.class.getName()).log(Level.SEVERE, null, ex);
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    
    /*
    ** funkce uloží příkaz pro tisk účtenky a vrátí hodnotu true a nebo hodnotu false v případě, že se účtenku nepodařilo uložit
    */
    public boolean save_bill_data(String bill_cmd, long ID)
    {
        if(this.is_connected())
        {
            try 
            {
                String query = " insert into bill_cmd (bill_id, cmd) values (?, ?);";
                PreparedStatement preparedStmt = this.con.prepareStatement(query); 
                
                preparedStmt.setLong(1, ID);
                preparedStmt.setString(2, bill_cmd);
                preparedStmt.execute();
                
                return true;
            } 
            catch (SQLException ex) 
            {
                Logger.getLogger(Database.class.getName()).log(Level.SEVERE, null, ex);
                return false;
            }
        }
        
        return false;
    }
    
    /*
    ** funkce vrátí řetězec pro tisk účtenek
    */
    public String get_bill_data(long key)
    {   
        if(this.is_connected() == true)
        {
            String bill_data = null;

            try 
            {
                rs = stat.executeQuery("select cmd from bill_cmd where bill_id="+Long.toString(key)+";");
                if(rs.next())
                {
                    bill_data = rs.getString(1);
                }

                return bill_data;
            } 
            catch (SQLException ex) 
            {
                Logger.getLogger(Database.class.getName()).log(Level.SEVERE, null, ex);
                return null;
            }
        }
        else
        {
            return null;
        }
    }
    
    /*
    ** funkce vrátí seznam uložených účtenek a data kdy byli vytištěný
    */
    public ArrayList get_bill_list()
    {
        if(this.is_connected() == true)
        {
            try 
            {
                ArrayList bill_list = new ArrayList();

                rs = stat.executeQuery("select 'cmd' from bill_cmd;");
                while(rs.next())
                {
                    bill_list.add(rs.getLong(1));
                }   

                return bill_list;
            } 
            catch (SQLException ex) 
            {
                return null;
            }
        }
        else
        {
            return null;
        }
    }
    
    /*
    ** funkce vrátí hodnotu true, pokud je databáze připojená
    */
    public boolean is_connected()
    {
        try 
        {
            return !con.isClosed();
        } 
        catch (Exception ex) 
        {
            return false;
        }
    }
}


/*
** po instalaci mysql databáze je výchozí uživatel root a nemá přidělené žádné heslo, v linuxu se při spuštění mysql z příkazové řádky 
** přihlašuje jméno aktuálně přihlášeného uživatele. Pro přihlášení pod jiným uživatelem je nutné zadat příkaz ve formátu:
** > mysql -u <uživatelské jméno> -p

** Výpis všech uživatelů v databázi: select user, host from mysql.user;
** Nový uživatele je vytvořen pomocí příkazu: create user '<uživatelské jméno>'@'localhost' identified by <password>;
** Přizazení všech potřebných oprávnění pro vykonávání příkazů se provede příkazem: grant all privileges on *.* to '<uživatelské jméno>'@'localhost';
** Vypsat seznam všech databází: show databases;
** Vytvořit novou databázi: create database <jméno databáze>
** Otevření databáze pro čtení a zápis: use <jméno databáze>
** pro výpis všech tabulek v databázi slouží příkaz: show tables
** pro výpis struktury databázové tabulky slouží příkaz: describe <jméno tabulky>
** vložení nové položky: insert into available_items  values(1, 'Žitná mouka 5Kg', 60.85, 999);
** vymazání položky z tabulky: delete from available_items where item_id=<identifikátor>;

*/