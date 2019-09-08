/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import md_ucetni_system.OrderItem;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author petr
 */
public class OrderItemTest 
{
    private final String itemNameShortcut = "Order I.";
    private final  String itemName = "Order item";
    private final int ID = 1;
    private final double itemPrice = 22.50;
        
    public OrderItemTest() 
    {
    }
    
    @BeforeClass
    public static void setUpClass() 
    {
    }
    
    @AfterClass
    public static void tearDownClass() 
    {
    }
    
    @Before
    public void setUp() 
    {
    }
    
    @After
    public void tearDown() 
    {
    }

   
    
    @Test
    public void TestOrderItemConstructor()
    {
        OrderItem item = new OrderItem(ID, itemName, itemNameShortcut, itemPrice);
        assertEquals(item.getID(), ID);
        assertEquals(item.getQuantity(), 1);
        assertEquals(item.getItemName(), itemName);
        assertEquals(item.getItemShortcutName(), itemNameShortcut);
    }
    
    @Test
    public void TestOrderItemIncrementQuantity()
    {
        OrderItem item = new OrderItem(ID, itemName, itemNameShortcut, itemPrice);
        
        assertTrue(item.incrementQuantity());
        assertEquals(item.getQuantity(), 2); 
    }
    
    @Test
    public void TestOrderItemDecrementQuantityAfterConstruction()
    {
        OrderItem item = new OrderItem(ID, itemName, itemNameShortcut, itemPrice);
        
        assertTrue(item.decrementQuantity());
        assertEquals(item.getQuantity(), 0); 
    }
    
    @Test
    public void TestOrderItemDecrementQuntityThrowZero()
    { 
        OrderItem item = new OrderItem(ID, itemName, itemNameShortcut, itemPrice);
        
        assertTrue(item.decrementQuantity());
        assertFalse(item.decrementQuantity());
    }
}
