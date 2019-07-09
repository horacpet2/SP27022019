/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import controler.Controler;
import java.util.ArrayList;
import java.util.TreeMap;
import junit.framework.TestCase;
import org.junit.Test;

/**
 *
 * @author petr
 */
public class ControlerTest extends TestCase 
{
    
    public ControlerTest(String testName) 
    {
        super(testName);
    }
    
    @Override
    protected void setUp() throws Exception 
    {
        super.setUp();
    }
    
    @Override
    protected void tearDown() throws Exception 
    {
        super.tearDown();
    }

    
   // testy
    
    
    
    
    
    
    public Controler prepareControlerObject()
    {
        Controler controlerReference = new Controler();
        return controlerReference;
    }    
    
    @Test
    public void testAddOrderItemBadID()
    {
        Controler controler = prepareControlerObject();
        assertTrue("Test neplatného ID objednávky", (controler.add_order_item(70) == false));
    }
    
    @Test 
    public void testAddOrderItemGoodID()
    {
        Controler controler = prepareControlerObject();
        assertTrue("Test platného ID objednávky", (controler.add_order_item(1) == true));
    }
    
    @Test
    public void testAddOrderItemAddingNewItemToOrderList()
    {
        Controler controler = prepareControlerObject();
        
        if(controler.add_order_item(1) == true)
        {
            TreeMap list = controler.get_order_list();
            assertEquals("Přiřazení nového prvku do objednávkového listu", 1, list.size());
        }
        else
        {
            assertFalse("Chybné přidání prvku do objednávkového listu", true);
        }
    }
    
    
    @Test
    public void testAddOrderItemAddingExistingItemToOrderList()
    {
        Controler controler = prepareControlerObject();
        
        if((controler.add_order_item(1) == true) && (controler.add_order_item(1)))
        {
            TreeMap list = controler.get_order_list();
            assertEquals("Přiřazení nového prvku do objednávkového listu", 2, list.size());
        }
        else
        {
            assertFalse("Chybné přidání prvku do objednávkového listu", true);
        }
    }
}
