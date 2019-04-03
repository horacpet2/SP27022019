/*
** je nezbytné aby se v linuxu nastavila opravnění pro přístup do sériové linky lp (line printer).
** Je nutné daného uživatele přidat do skupiny lp pomocí příkazu: sudo usermod -a -G lp <user>
** aby se změny projevily, je nutné restart systému nebo odhlášení a opětovné přihlášení uživatele
** pozor v linuxu se index zařízení na adrese /dev/usb/lpX mění
*/
package controler.printer;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author petr
 */
public final class Printer 
{
    private String printer_cmd;
    private FileOutputStream fop;
    private File file;
    private int print_counter;
    
    /* printer constants */
    private final char GS = 0x1d; 
    private final char NUL = 0x00;
    private final char ESC = 0x1b;
    private final char EOT = 4;
    private final char SOH = 1;
    private final char ETX = 3;
   
    public Printer()
    {
        clear_print_counter();
        clear_print_buffer();

    }

    public int get_print_counter()
    {
        return this.print_counter;
    }
    
    public void clear_print_counter()
    {
        this.print_counter = 0;
    }
    
    /*
    ** vyčistí buffer s tiskovými instrukcemi
    */
    public void clear_print_buffer()
    {
        this.printer_cmd = ESC + "@";
        clear_print_counter();
    }
    
    /*
    ** getter kterým lze získat obsah tiskovoho bufferu
    */
    public String get_print_buffer()
    {
        return this.printer_cmd;
    }
    
    public boolean connect_printer_lin()
    {
        try 
        {
            file = new File("/dev/usb/lp0");
            fop = new FileOutputStream(file);

            return true;
        } 
        catch (FileNotFoundException ex) 
        {
            Logger.getLogger(Printer.class.getName()).log(Level.SEVERE, null, ex);
            return false;
        } 
    } 
    
    public boolean close_printer_connection_lin()
    {
        try 
        {
            fop.close();
            return true;
        } 
        catch (IOException ex) 
        {
            Logger.getLogger(Printer.class.getName()).log(Level.SEVERE, null, ex);
            return false;
        }
    }
    /*
    ** vyšle data s řídícími instrukcemi do tiskárny
    */
    public void print()
    {
        try 
        {
            fop.write(replace_unsupported_characters(printer_cmd).getBytes("cp852"));
            fop.flush();
            this.print_counter++;
        } 
        catch (UnsupportedEncodingException ex) 
        {
            Logger.getLogger(Printer.class.getName()).log(Level.SEVERE, null, ex);
        } 
        catch (IOException ex) 
        {
            Logger.getLogger(Printer.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    /*
    ** přidá daný počet prázdných řádků na účtenku
    */
    public void add_blank_line(int num)
    {
        for(int i = 0; i<num; i++)
        {
            add_string(ESC + "d"+SOH);
        }
    }
    
    /*
    ** uřízne účtenku z tiskárny
    */
    public void cut_paper()
    {
        add_string(GS+"V"+((char)0x41)+ETX);
    }
 
    /*
    ** vytvoří čárový kód na účtenku
    */
    public void print_bar_code(int bar_code_width, int bar_code_high, String bar_code_data)
    {
        set_justisfication(1);
        add_string(GS+"w"+(char) bar_code_width+GS+"h"+(char)bar_code_high+GS+"k"+EOT+bar_code_data+NUL);
        add_blank_line(1);
        add_string(bar_code_data);
    }
    
    /*
    ** nastavení zarovnání textu na daném řádku
    */
    public void set_justisfication(int n)
    {
        add_string(ESC+"a"+(char)n);
    }
    
    /*
    ** vytvoří položku na účtenku 
    */
    public void add_order_item(String item_name, String ks, String item_price, String item_price_dph)
    {
        /* 42 znaků v jednom řádku */
        set_justisfication(0);
        
        if(item_name.length() >= 15)
        {
            int space_pos = item_name.indexOf(' ');
            item_name = item_name.replaceFirst(item_name.substring(0, space_pos), item_name.substring(0, 3)+".");
        }
        
        add_string(item_name);
        
        line_feed(' ', 18-item_name.length());
        
        add_string(ks);
        line_feed(' ', 6-ks.length());
        
        add_string(item_price);
        
        line_feed(' ', 18-item_price_dph.length()-item_price.length());
        add_string(item_price_dph);
        add_blank_line(1);
    }
    
    /*
    ** zapíše řetěžec do přikazového bufferu pro tisk
    */
    public void add_string(String str)
    {
        this.printer_cmd = this.printer_cmd.concat(str);
    }
    
    /*
    ** vyplní řádek z dané pozice daným počtem znaků 
    */
    public void line_feed(char c, int n)
    {
        for(int i = 0; i< n; i++)
        {
            add_string(Character.toString(c));
        }
    }
    
    
    /****************** privátní metody ********************************/
    
    private String replace_unsupported_characters(String cmd)
    {
        String unsupported_characters = "ěščřžýáíéúůÉŠČŘŽÝÁÍÉÚÚ";
        String supported_characters = "escrzyaieuuESCRZYAIEUU";
        
        char[] cmd_array = cmd.toCharArray();
        
        for(int i = 0; i< cmd_array.length; i++)
        {
            for(int j =0; j <unsupported_characters.length(); j++)
            {
                if(cmd_array[i] == unsupported_characters.charAt(j))
                {
                    cmd_array[i] = supported_characters.charAt(j);
                }
            }
        }
        
        return new String(cmd_array);
    }
}
