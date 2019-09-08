/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import md_ucetni_system.OrderList;
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
public class OrderListTest 
{
    
    private final String itemNameShortcut = "Order I.";
    private final  String itemName = "Order item";
    private final int ID = 1;
    private final double itemPrice = 22.50;
    
    
    public OrderListTest() 
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

    /* test-to-pass */
    
    @Test
    public void TestOrderListAddNewItem()
    {
        OrderList list = new OrderList();
        list.addNewItem(ID, itemName, itemNameShortcut, itemPrice);
        
        assertEquals(list.getListSize(), 1);
        
        
    }
    
    @Test 
    public void TestOrderListAddExistingItem()
    {
        OrderList list = new OrderList();
        list.addNewItem(ID, itemName, itemNameShortcut, itemPrice);
        list.addNewItem(ID, itemName, itemNameShortcut, itemPrice);
        
        assertEquals(list.getListSize(), 1);
        assertEquals(list.getOderList().get(0).getQuantity(), 2);
    }
    
    @Test
    public void TestOrderListAddSecondItem()
    {
        OrderList list = new OrderList();
        list.addNewItem(ID, itemName, itemNameShortcut, itemPrice);
        list.addNewItem(ID+1, itemName, itemNameShortcut, itemPrice);
        
        assertEquals(list.getListSize(), 2);
    }
    
    
    @Test
    public void TestOrderListIncrementItemQuantity()
    {
        OrderList list = new OrderList();
        list.addNewItem(ID, itemName, itemNameShortcut, itemPrice);
        
        assertTrue(list.incrementItemQuantityByID(ID));
        assertEquals(list.getOderList().get(0).getQuantity(), 2);
    }
    
    
    @Test 
    public void TestOrderListDecrementItemQuantity()
    {
        OrderList list = new OrderList();
        list.addNewItem(ID, itemName, itemNameShortcut, itemPrice);
        
        assertTrue(list.incrementItemQuantityByID(ID));
        assertTrue(list.decrementItemQuantityByID(ID));
        assertEquals(list.getOderList().get(0).getQuantity(), 1);
    }
    
    @Test
    public void TestListItemDecrementItemQuantityToZero()
    {
        OrderList list = new OrderList();
        list.addNewItem(ID, itemName, itemNameShortcut, itemPrice);
        
        assertTrue(list.decrementItemQuantityByID(ID));
        assertEquals(list.getListSize(), 0);
    }
    
    @Test
    public void TestListItemRemoveItemWithID()
    {
        OrderList list = new OrderList();
        list.addNewItem(ID, itemName, itemNameShortcut, itemPrice);
        
        assertTrue(list.incrementItemQuantityByID(ID));
        assertTrue(list.removeItemByID(ID));
        assertEquals(list.getListSize(), 0);
    }
    
    @Test
    public void TestOrderListClearLst()
    {
        OrderList list = new OrderList();
        list.addNewItem(ID, itemName, itemNameShortcut, itemPrice);
        list.addNewItem(ID, itemName, itemNameShortcut, itemPrice);
        
        list.clear();
        assertEquals(list.getListSize(), 0);
    }
    
    
    
    
    
    
    /* test-to-fail */
    
    @Test 
    public void TestOrderListIncrementItemListWithBadID()
    {
        OrderList list = new OrderList();
        list.addNewItem(ID, itemName, itemNameShortcut, itemPrice);
        
        assertFalse(list.incrementItemQuantityByID(ID+1));
        assertEquals(list.getOderList().get(0).getQuantity(), 1);
    }
    
    @Test
    public void TestOrderListDecrementItemListWithBadID()
    {
        OrderList list = new OrderList();
        list.addNewItem(ID, itemName, itemNameShortcut, itemPrice);
        
        assertFalse(list.decrementItemQuantityByID(ID+1));
        assertEquals(list.getOderList().get(0).getQuantity(), 1);
    }
    
    
    @Test
    public void TestOrderListRemoveItemWithBadID()
    {
        OrderList list = new OrderList();
        list.addNewItem(ID, itemName, itemNameShortcut, itemPrice);
        
        assertFalse(list.removeItemByID(ID+1));
        assertEquals(list.getListSize(), 1);
    }
        
}
