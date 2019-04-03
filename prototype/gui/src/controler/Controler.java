/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controler;

/**
 *
 * @author petr
 */
public class Controler 
{
    private EET eet_ref;
    private Printer printer_ref;
    private Scanner scanner_ref;
    
    
    
    
    public void Conteroler()
    {
        this.eet_ref = new EET();
        this.printer_ref = new Printer();
        this.scanner_ref = new Scanner();
    }
}
