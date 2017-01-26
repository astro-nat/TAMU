import java.util.Iterator;

final class Node<T> {
	public final T v;
	public Node<T> next;
	public Node (T val, Node<T> link) { v = val; next = link; }
}

class NodeIterator<T> implements Iterable<T>
{
	private Node<T> n;
	private T v;
	private Node<T> next;
	
	public NodeIterator (Node<T> n) 
	{
		this.n = n;
		this.v = n.v;
		this.next = n.next;
	};
	
	public boolean hasNext() 
	{ 
		return n.next != null;
	};
	
	T next() 
	{ 
		return next.v; 
	};
	
	@Override
	public NodeIterator<T> iterator()
	{
		NodeIterator<T>  it = new NodeIterator<T>() {};
		 
		return it;
	}
}

class Main7 {
	public static void main(String[] args)
	{
		System.out.println("Hello, world!");
	}
}