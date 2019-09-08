/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package md_ucetni_system;

/**
 *
 * @author petr
 */



public class OrderItem 
{
    private final String itemName;
    private final String itemShortcutName;
    private final double itemPrice;
    private int quantity;
    private final int ID;
    
    
    public OrderItem(int ID, String itemName, String itemShortcutName, double itemPrice)
    {
        this.ID = ID;
        this.quantity = 1;
        this.itemName = itemName;
        this.itemShortcutName = itemShortcutName;
        this.itemPrice = itemPrice;        
    }
    
    public String getItemName() 
    {
        return itemName;
    }

    public String getItemShortcutName() 
    {
        return itemShortcutName;
    }

    public double getItemPrice() 
    {
        return itemPrice;
    }

    public int getQuantity() 
    {
        return quantity;
    }

    public int getID() 
    {
        return ID;
    }
    
    public double getTotalPrice()
    {
        return this.quantity*this.itemPrice;
    }
    
    public boolean incrementQuantity()
    {
        this.quantity++;
        return true;
    }
            
    public boolean decrementQuantity()
    {
        if( this.quantity > 0)
        {
            this.quantity--;
            return true;
        }
        else
        {
            return false;
        }
    }
            
}
