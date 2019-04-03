
package controler.database;

import java.sql.*;


public class Database 
{
    private Connection con;
    private Statement stat;
    private ResultSet rs;

    public Database()
    {
        
    }
    
    
    public boolean connect_db()
    {
        /*
         rs = stat.executeQuery("");
         while(rs.next())
         {
             rs.getString("name");
         }
        */
        
        try
        {
            Class.forName("com.mysql.jdbc.Driver");
            con = DriverManager.getConnection("jdbc:mysql://localhost:3306/phpmyadmin", "phpmyadmin", "asdf1234");
            stat = con.createStatement();
            
            return true;
        }
        catch(ClassNotFoundException | SQLException e)
        {
            System.out.println("Database connection error description: " + e);
            return false;
        }
    }
    
    public boolean is_connected()
    {
        try 
        {
            return !con.isClosed();
        } 
        catch (Exception ex) 
        {
            return false;
        }
    }
}
