/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package md_ucetni_system;

import java.util.ArrayList;
import java.util.TreeMap;

/**
 *
 * @author petr
 */
public class OrderList 
{
    private final ArrayList<OrderItem> orderList;
    private final TreeMap<Integer, Integer> idTable;
    
    public OrderList()
    {
        this.orderList = new ArrayList<>();
        this.idTable = new TreeMap<>();
    }
 
    public void addNewItem(int ID, String itemName, String ItemNameShortcut, double itemPrice)
    {
        if(this.idTable.containsKey(ID) == false)
            putNewItemToOrderList(ID, itemName, ItemNameShortcut, itemPrice);
        else
            incrementItemQuantityByID(ID);
    }
    
    public boolean incrementItemQuantityByID(int ID)
    {
        OrderItem item = findOrderItemByID(ID);

        return incrementItemIfNontNull(item);
    }
    
    public boolean incrementItemQuantityByIndex(int index)
    {
        if(index >= 0 && index < this.orderList.size())
            return incrementItemIfNontNull(this.orderList.get(index));
        else
            return false;
    }
    
    public boolean decrementItemQuantityByID(int ID)
    {
        OrderItem item = findOrderItemByID(ID);        
 
        return decrementItemIfNotNull(item);
    }
    
    public boolean decrementItemQuantityByIndex(int index)
    {
        if(index >= 0 && index < this.orderList.size())
            return decrementItemIfNotNull(this.orderList.get(index));
        else
            return false;
            
    }
    
    public double getOrderListTotalPrice()
    {
        double totalPrice = 0.0;
        
        for(int i=0; i < this.orderList.size(); i++)
        {
            totalPrice += orderList.get(i).getTotalPrice();
        }
        
        return totalPrice;
    }
    
    public int getListSize()
    {
        return this.orderList.size();
    }
    
    public ArrayList<OrderItem> getOderList()
    {
        return this.orderList;
    }
    
    public boolean removeItemByID(int ID)
    {
        if(this.idTable.containsKey(ID))
        {
            removeFromItemList(ID);
            return true;
        }
        else
        {
            return false;
        }
    }
    
    public boolean containItemWithID(int ID)
    {
        return this.idTable.containsKey(ID);
    }
    
    public boolean removeItemByIndex(int index)
    {
        if(index >= 0 && index < this.orderList.size())
        {
            this.idTable.remove(this.orderList.get(index).getID());
            this.orderList.remove(index);
            
            return true;            
        }
        else
            return false;
    }
    
    public void clear()
    {
        this.orderList.clear();
        this.idTable.clear();
    }
    
    public OrderItem findOrderItemByID(int ID)
    {   
        if(this.idTable.containsKey(ID))
            return this.orderList.get(this.idTable.get(ID));
        else
            return null;
    }
    
    private void putNewItemToOrderList(int ID, String itemName, String ItemNameShortcut, double itemPrice)
    {
        OrderItem newItem = new OrderItem(ID, itemName, ItemNameShortcut, itemPrice);
            
        this.idTable.put(ID,this.orderList.size());
        this.orderList.add(newItem);
    }
    
    private boolean incrementItemIfNontNull(OrderItem item)
    {
        if(item != null)
        {
            item.incrementQuantity();
            return true;
        }
        else
        {
            return false;
        }
    }
    
    private boolean decrementItemIfNotNull(OrderItem item)
    {
        if(item != null)
        {
            item.decrementQuantity();
            removeFromItemListIfQuantityEqualsZero(item);
            return true;
        }
        else
        {
            return false;
        }
    }
    
    private void removeFromItemList(int ID)
    {
        this.orderList.remove((int) this.idTable.get(ID));
        this.idTable.remove(ID);
    }
    
    private void removeFromItemListIfQuantityEqualsZero(OrderItem item)
    {
        if(item.getQuantity() <= 0)
            removeFromItemList(item.getID());
    }
}