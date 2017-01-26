import java.util.LinkedList;
import java.util.List;
import java.util.Collection;

public class Shop<T> {
    List<T> stock;
    public Shop() { stock = new java.util.LinkedList<T>(); }
    void sell(T item) {
        stock.add(item);
    }
    public T buy() {
        return (T) stock.remove(0);
    }
    void sell(Collection<? extends T> items) {
        for (T e : items) {
            stock.add(e);
        } }
    void buy(int n, Collection<? super T> items) {
        for (T e : stock.subList(0, n)) {
            items.add(e);
        }
        for (int i=0; i<n; ++i) stock.remove(0);
    }
    
    void print() {
        System.out.println("The shop currently has " + stock + "  in stock.");
        
    }
}
