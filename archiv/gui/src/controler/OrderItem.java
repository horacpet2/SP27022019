
package controler;

public final class OrderItem 
{
    int ID;
    String name;
    String item_shortcute_for_bill;
    double price;
    int quantity;
    
    public OrderItem(int ID, String name, String item_shortcute_for_bill, double price)
    {
        this.name = name;
        this.ID = ID;
        this.item_shortcute_for_bill = item_shortcute_for_bill;
        this.price = price;
        this.quantity = 1;
    }  
    
    /*
    ** return order item quantity
    */
    public int get_quantity()
    {
        return this.quantity;
    }
    
    public String get_item_shortcute_name()
    {
        return this.item_shortcute_for_bill;
    }
    /*
    ** increment order item quantity
    */
    public boolean increment_quantity()
    {
        this.quantity++;
        return true;
    }
    
    /*
    ** decrement order item quantitiy if the quantity is greater than zero
    */
    public boolean decrement_quantity()
    {
        if(this.quantity >=0)
        {
            this.quantity --;
            return true;
        }
        else
        {
            return false;
        }
    }
    
    /*
    ** return base price of the item kind
    */
    public double get_base_price()
    {
        return this.price;
    }
    
    /*
    ** count and return total prise of this order item, based on the item quantity
    */
    public double get_total_price()
    {
        return this.price*this.quantity;
    }
    
    /*
    ** return id of the order item for its recognision
    */
    public int get_id()
    {
        return this.ID;
    }
    
    /*
    ** return name of the order item, based on its ID
    */
    public String get_order_name()
    {
        return this.name;
    }
}
