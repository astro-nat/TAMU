import java.util.Iterator;
import java.util.Arrays;
import java.util.*;

public class LinkedList<T> implements Iterable<T> // Problem 2 Task 1
{
    public Node<T> head;
    
    // Problem 2 Task 2
    public LinkedList()
    {
        head = null;
    };
    
    public Iterator<T> iterator()
    {
        return (Iterator<T>) (new NodeIterator<T> (this.head));
    }
    public LinkedList(Iterable<T> iterable)
    {
        head = null;
        for( T e : iterable)
        {
            if(head == null)
            {
                head = new Node<T>(e,head);
            }
            else
            {
                Node<T> curr = head;
                while(curr.next != null)
                {
                    curr = curr.next;
                }
                curr.next = new Node<T>(e,null);
            }
        }
    };
    
    // Problem 2 Task 3
    public LinkedList<T> reverse()
    {
        LinkedList<T> reversed = new LinkedList<T>();
        for(T e : this)
        {
            reversed.head = new Node<T>(e,reversed.head);
        }
        return reversed;
    };
    
    public String toString() {
        Node<T> current = head;
        String output = "[";
        while (current != null) {
            output += current.v;
            if(current.next != null) { output += ","; }
            current = current.next;
        }
        output += "]";
        return output;
    }
}

