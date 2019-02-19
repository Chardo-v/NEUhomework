/**
 * @(#)TestCalendar.java
 *
 *
 * @author 
 * @version 1.00 2007/12/10
 */
import java.util.*;
public class TestCalendar {
        
    /**
     * Creates a new instance of <code>TestCalendar</code>.
     */
    public TestCalendar() {
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Calendar c1=Calendar.getInstance();

        System.out.println(c1.get(c1.YEAR)+"��"+(c1.get(c1.MONTH)+1)+
        	"��"+c1.get(c1.DAY_OF_MONTH)+"��");

        c1.add(c1.DAY_OF_YEAR,300);

        System.out.println(c1.get(c1.YEAR)+"��"+(c1.get(c1.MONTH)+1)+
        	"��"+c1.get(c1.DAY_OF_MONTH)+"��:"+c1.get(Calendar.HOUR_OF_DAY));
        	
        c1.add(c1.HOUR_OF_DAY,10);

        System.out.println(c1.get(c1.YEAR)+"��"+(c1.get(c1.MONTH)+1)+
        	"��"+c1.get(c1.DAY_OF_MONTH)+"��:"+ c1.get(c1.HOUR_OF_DAY));

    }
}
