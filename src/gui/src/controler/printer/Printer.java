
package controler.printer;

import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.print.Doc;
import javax.print.DocFlavor;
import javax.print.DocPrintJob;
import javax.print.PrintException;
import javax.print.PrintService;
import javax.print.PrintServiceLookup;
import javax.print.SimpleDoc;
import javax.print.attribute.HashPrintRequestAttributeSet;
import javax.print.attribute.PrintRequestAttributeSet;
import javax.print.attribute.Size2DSyntax;
import javax.print.attribute.standard.MediaPrintableArea;



/**
 *
 * @author petr
 */
public final class Printer 
{
    private String printer_cmd;
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
    
    /*
    ** předá hodnotu počítadla účtenek
    */
    public int get_print_counter()
    {
        return this.print_counter;
    }
    
    /*
    ** resetuje se počítadlo vytištěných účtenek
    */
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
    
    
    /*
    ** vyšle data s řídícími instrukcemi do tiskárny
    */
    public boolean print(int platform)
    {
        this.print_counter++;
        
        switch (platform) {
            case 0:
                return print_win();
            case 1:
                return print_lin();
            default:
                return false;
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
    
    /*
    ** funkce pro harazení tiskárnou nepodporovaných znaků za podporovanou alternativu    
    */
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
    

    /*
    ** funkce pro odeslání instrukcí do tiskárny a vytištění účtenky pod windows
    ** ve windows beží na pozadí služba, která se stará o odesílání těchto dat do tiskárny
    ** je nunté se připojit na tuto službu, přímé připojení na usb, není možné, protože je
    ** zabrané touto službou
    */
    private boolean print_win()
    {
        DocFlavor flavor = DocFlavor.INPUT_STREAM.AUTOSENSE;

        PrintRequestAttributeSet aset = new HashPrintRequestAttributeSet();
        aset.add(new MediaPrintableArea(100,400,210,160,Size2DSyntax.MM));

        try 
        {
            InputStream is = new ByteArrayInputStream(replace_unsupported_characters(printer_cmd).getBytes("cp852"));
            Doc mydoc = new SimpleDoc(is, flavor, null);
            PrintService defaultService = PrintServiceLookup.lookupDefaultPrintService();

            //print using default
            DocPrintJob job = defaultService.createPrintJob();
            job.print(mydoc, aset);

        } 
        catch (Exception ex)
        {
            Logger.getLogger(Printer.class.getName()).log(Level.SEVERE, null, ex);
            return false;
        }

        return true;
    }
    
    /*
    ** připojení a odeslání instrukcí do tiskárny a vytištění účtenky
    */
    private boolean print_lin()
    {
        try 
        {
            FileOutputStream fop;
            
            if((fop = connect_printer_lin()) != null)
            {
                fop.write(replace_unsupported_characters(printer_cmd).getBytes("cp852"));
                fop.flush();

                return close_printer_connection_lin(fop);
            }
        } 
        catch (UnsupportedEncodingException ex) 
        {
            Logger.getLogger(Printer.class.getName()).log(Level.SEVERE, null, ex);
            return false;
        } 
        catch (IOException ex) 
        {
            Logger.getLogger(Printer.class.getName()).log(Level.SEVERE, null, ex);
            return false;
        }

       return false;
    }

    /*
    ** připojení tiskárny 
    ** je nezbytné aby se v linuxu nastavila opravnění pro přístup do sériové linky lp (line printer).
    ** Je nutné daného uživatele přidat do skupiny lp pomocí příkazu: sudo usermod -a -G lp <user>
    ** aby se změny projevily, je nutné restart systému nebo odhlášení a opětovné přihlášení uživatele
    ** pozor v linuxu se index zařízení na adrese /dev/usb/lpX mění
    */
    private FileOutputStream connect_printer_lin()
    {
        try 
        {
            File file = new File("/dev/usb/lp0");
            FileOutputStream fop = new FileOutputStream(file);

            return fop;
        } 
        catch (FileNotFoundException ex) 
        {
            Logger.getLogger(Printer.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        } 
    } 
    
    /*
    ** odpojení otevřeného spojení do tiskárny pod linuxem 
    */
    private boolean close_printer_connection_lin(FileOutputStream fop)
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
}
