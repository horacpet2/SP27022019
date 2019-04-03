/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package epson_prototype;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Locale;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author petr
 * je nezbytné aby se v linuxu nastavila opravnění pro přístup do sériové linky lp (line printer).
 * Je nutné daného uživatele přidat do skupiny lp pomocí příkazu: sudo usermod -a -G lp <user>
 * aby se změny projevily, je nutné restart systému nebo odhlášení a opětovné přihlášení uživatele
 */
public final class epson 
{
    private String printer_cmd;
    private FileOutputStream fop;
    private File file;
    
    
    
    
    /* printer constants */
    private char GS = 0x1d; 
    private char NUL = 0x00;
    private char ESC = 0x1b;
    private char EOT = 4;
    private char SOH = 1;
    private char ETX = 3;
    
    
    
    
    void add_blank_line(int num)
    {
        for(int i = 0; i<num; i++)
        {
            add_string(ESC + "d"+SOH);
        }
    }
    void cut_paper()
    {
        add_string(GS+"V"+((char)0x41)+ETX);
    }
 
    void print_bar_code(int bar_code_width, int bar_code_high, String bar_code_data)
    {
        set_justisfication(1);
        add_string(GS+"w"+(char) bar_code_width+GS+"h"+(char)bar_code_high+GS+"k"+EOT+bar_code_data+NUL);
        add_blank_line(1);
        add_string(bar_code_data);
        
    }
     
    void print_in_hex(String str)
    {
        for(int i=0;i<str.length();i++)
        {
            System.out.print(Integer.toHexString((int)str.charAt(i))+" ");  
        }
    }
    
    void set_justisfication(int n)
    {
        add_string(ESC+"a"+(char)n);
    }
    
    void add_order_item(String item_name, String item_price)
    {
        /* 42 znaků v jednom řádku */
        set_justisfication(0);
        add_string(item_name);
        line_feed('.', 42-(item_name.length()+item_price.length()));
        add_string(item_price);
        add_blank_line(1);
    }
    
    void add_string(String str)
    {
        this.printer_cmd = this.printer_cmd.concat(str);
    }
    void line_feed(char c, int n)
    {
        for(int i = 0; i< n; i++)
        {
            add_string(Character.toString(c));
        }
    }
    
    public epson()
    { 
        Locale.forLanguageTag("cs_CZ");
        this.printer_cmd = ESC + "@";
        
        try 
        {
            file = new File("/dev/usb/lp1");
            fop = new FileOutputStream(file);

            add_blank_line(1);
            add_order_item("Mouka chlebova", "24 Kc");
            add_blank_line(1);
            print_bar_code(2, 100,"987654321");
            add_blank_line(1);
           
            add_blank_line(1);
            cut_paper();
            
            System.out.println(this.printer_cmd);
            print_in_hex(this.printer_cmd);     
            
            fop.write(printer_cmd.getBytes("cp852"));
            fop.flush();
            fop.close();
            
        } 
        catch (FileNotFoundException ex) 
        {
            Logger.getLogger(epson.class.getName()).log(Level.SEVERE, null, ex);
        } 
        catch (IOException ex) 
        {
            Logger.getLogger(epson.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}

