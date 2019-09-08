
package md_ucetni_system;

public class Scanner extends OrderList
{
    boolean scanner_in;
    
    public Scanner()
    {
        super();
        
        this.scanner_in = false;
    }
    
    /*
    ** function return state of input from scanner, return true state if data was inserted via scanner and then set it to false
    */
    public boolean scanner_in_event_state()
    {
        if(this.scanner_in == true)
        {
            this.scanner_in = false;
            return true;
        }
        else
        {
            return false;
        }
    }
    
    /*
    ** function gives an information that, the data are ready to read from serial line
    */
    public boolean scanner_ready_to_read()
    {
        return false;
    }
}
