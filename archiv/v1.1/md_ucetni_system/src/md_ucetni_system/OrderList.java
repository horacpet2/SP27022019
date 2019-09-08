/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package md_ucetni_system;

import java.util.ArrayList;

/**
 *
 * @author petr
 */
public class OrderList 
{
    private final ArrayList<OrderItem> orderList;
    
    public OrderList()
    {
        this.orderList = new ArrayList<>();
    }
 
    public void addNewItem(int ID, String itemName, String ItemNameShortcut, double itemPrice)
    {
        if(this.containItemWithID(ID) == false)
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
        if(this.containItemWithID(ID))
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
        for(int i=0; i<this.orderList.size(); i++)
        {
            if(this.orderList.get(i).getID() == ID)
                return true;
        }
        
        return false;
    }
    
    public boolean removeItemByIndex(int index)
    {
        if(index >= 0 && index < this.orderList.size())
        {
            this.orderList.remove(index);
            
            return true;            
        }
        else
            return false;
    }
    
    public void clear()
    {
        this.orderList.clear();
    }
    
    public OrderItem findOrderItemByID(int ID)
    {   
        if(this.containItemWithID(ID))
            return this.orderList.get(this.getItemIndexByID(ID));
        else
            return null;
    }
    
    private void putNewItemToOrderList(int ID, String itemName, String ItemNameShortcut, double itemPrice)
    {
        OrderItem newItem = new OrderItem(ID, itemName, ItemNameShortcut, itemPrice);
            
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
        this.orderList.remove(this.getItemIndexByID(ID));
    }
    
    private int getItemIndexByID(int ID)
    {
        for(int i = 0; i < this.orderList.size(); i++)
        {
            if(this.orderList.get(i).getID() == ID)
                return i;
        }
        
        return -1;
    }
    
    private void removeFromItemListIfQuantityEqualsZero(OrderItem item)
    {
        if(item.getQuantity() <= 0)
            removeFromItemList(item.getID());
    }
}
