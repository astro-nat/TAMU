
import java.util.concurrent.locks.*;
class Counter {
    Integer counter = 0;
    Lock lock = new ReentrantLock();
    Condition newData = lock.newCondition();
    
    public Integer increment() {
        lock.lock();
        try {
            ++counter;
            newData.signalAll();
            System.out.print(counter);
            System.out.print(" ");
            return counter;
        }
        finally {
            lock.unlock();
        }
    }
    
    public Integer get() {
        lock.lock();
        try {
            newData.await();
            return counter;
        }
        catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            return 0;
        }
        finally {
            lock.unlock();
        }
    }
}

public class Main2 {
    public static void main(String[] args)
    {
        final Counter c = new Counter();
        
        new Thread(new Runnable() {
            public void run() {
                for(;;) {
                    c.increment();
                    try{
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                        return;
                    }
                }
            }
        }).start();
        
	       new Thread(new Runnable() {
               public void run() {
                   for(;;) {
                       Integer i = c.get();
                       if (i % 7 == 0) {
                           System.out.println("");
                           System.out.println("7 second message");
                       }
                   }
               }
           }).start();
	       
	       new Thread(new Runnable() {
               public void run() {
                   for (;;) {
                       Integer i = c.get();
                       if (i % 15 == 0) {
                           System.out.println("");
                           System.out.println("15 second message");
                       }
                   }
               }
           }).start();
    }
}

