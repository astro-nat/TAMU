import java.util.Collection;
import java.util.LinkedList;
import java.util.*;

public class Test3
{
    public static void main(String args[])
    {
        final Shop<Integer> listint = new Shop<Integer>();
        listint.sell(1);
        listint.sell(2);
        listint.sell(3);
        listint.print();
        final Collection<Integer> num = new TreeSet<Integer>();
        listint.buy(2,num);
        for(Integer e : num)
        {
            System.out.println("Purchased: " + e);
        }
        
        final Shop<Object> fruit = new Shop<Object>();
        fruit.sell("bananas");
        fruit.sell("apples");
        fruit.sell("papaya");
        fruit.sell(1234);
        fruit.print();
        final Collection<Object> tree = new TreeSet<Object>();
        fruit.buy(2,tree);
        for(Object e : tree)
        {
            System.out.println("Purchased: " + e);
        }
        
        final Shop<String> cars = new Shop<String>();
        cars.sell("Toyota");
        cars.sell("Honda");
        cars.sell("Saturn");
        cars.sell("Jaguar");
        cars.sell("Hyundai");
        cars.print();
        Set<String> carbuy = new HashSet<String>();
        cars.buy(2,carbuy);
        for(String e : carbuy)
        {
            System.out.println("Purchased: " + e);
        }
        
        final Shop<Number> age = new Shop<Number>();
        age.sell(1);
        age.sell(2);
        age.sell(3);
        age.sell(4);
        age.sell(5);
        age.print();
        final SortedSet<Number> years = new TreeSet<Number>();
        age.buy(3,years);
        for (Number e : years)
        {
            System.out.println("Purchased: " + e);
        }
        
        final Shop<String> instruments = new Shop<String>();
        instruments.sell("piano");
        instruments.sell("guitar");
        instruments.sell("saxaphone");
        instruments.sell("bass");
        instruments.print();
        final Queue<String> collect = new LinkedList<String>();
        instruments.buy(3,collect);
        for(String e : collect)
        {
            System.out.println("Purchased: " + e);
        }
        
       
    }
}