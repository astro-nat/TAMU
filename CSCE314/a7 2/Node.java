import java.util.Iterator;
import java.util.LinkedList;

public final class Node<T> implements Iterable<T> { // Problem 1 Task 2
    public final T v;
    public Node<T> next;
    public Node() { v = null; next = null; }
    public Node (T val, Node<T> link) { v = val; next = link; }
    
    // Problem 1 Task 1
    public class NodeIterator<T> implements Iterator<T>
    {
        public Node<T> curr;
        
        public NodeIterator(Node<T> n) { curr = n; }
        
        public boolean hasNext() { return (curr != null); }
        
        @Override
        public T next()
        {
            Iterator<T> l = curr.iterator();
            if(!l.hasNext())
            {
                return null;
            }
            else
            {
                T ret = curr.v;
                curr = curr.next;
                return ret;
            }
        }
    }
    
    public Iterator<T> iterator() { return new NodeIterator<T>(this);}
}

