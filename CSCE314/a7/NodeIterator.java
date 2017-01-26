import java.util.Iterator;


public class NodeIterator<T> implements Iterator<T> {
	Node<T> current;

	public NodeIterator (Node<T> n){ current = n;}

	public boolean hasNext() {
		return (current != null);
	}
	@Override
	public T next() {
		Iterator<T> l = current.iterator();
		if(!l.hasNext()) {
			return null;
		}
		else{
			T ret = current.v;
			current = current.next;
			return ret;
		}
	}
	@Override
	public void remove() {throw new UnsupportedOperationException();}


}