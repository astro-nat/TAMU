import java.util.*;

// Problem 2 Task 4
public class Test2
{
    public static void main(String args[])
    {
        LinkedList<Integer> empty_list = new LinkedList<Integer>();
        LinkedList<Integer> list = new LinkedList<Integer>(Arrays.asList(1, 2, 3, 4, 5, 6));
        
        System.out.println(empty_list);
        System.out.println(empty_list.reverse());
        System.out.println(list);
        System.out.println(list.reverse());
        
        int sum = 0;
        for (int e : list) { sum += e; }
        System.out.println(sum);
    }
}
