import java.util.*;
import java.util.List;

class PostBox implements Runnable {
    static final int MAX_SIZE = 10;
    
    class Message {
        String sender;
        String recipient;
        String msg;
        Message(String sender, String recipient, String msg) {
            this.sender = sender;
            this.recipient = recipient;
            this.msg = msg;
        }
    }
    
    private final LinkedList<Message> messages;
    private LinkedList<Message> myMessages;
    private String myId;
    private boolean stop = false;
    
    public PostBox(String myId) {
        messages = new LinkedList<Message>();
        this.myId = myId;
        this.myMessages = new LinkedList<Message>();
        new Thread(this).start();
    }
    
    public PostBox(String myId, PostBox p) {
        this.myId = myId;
        this.messages = p.messages;
        this.myMessages = new LinkedList<Message>();
        new Thread(this).start();
    }
    
    public String getId() { return myId; }
    public void stop() {
        if (!stop)
            stop = true;
    }
    
    public void send(String recipient, String msg) {
        messages.add(new Message(this.getId(), recipient, msg));
    }
    
    public List<String> retrieve() {
        LinkedList<String> lst = new LinkedList<String>();
        
        synchronized(myMessages){
            Iterator<Message> iter = myMessages.iterator();
            while (iter.hasNext()){
                while (iter.hasNext()){
                    Message m = iter.next();
                    if (m.recipient.equals(this.getId())){
                        String sd = new String (m.sender + " : " + m.msg + " Recipient: " + m.recipient);
                        lst.add(sd);
                    }
                }
            }
        }
        this.myMessages.clear();
        return lst;
    }
    
    public void run() {
        // loop forever
        // 1. approximately onece every second move all messages addressed to this post box from the shared message queue to the private myMessages queue
        // 2. also approximately once every second, if the message queue has more than MAX_SIZE messages, delete oldest messages so that size is at most MAX_SIZE
        for (;;){
            try{
                synchronized (messages) {
                    synchronized (myMessages) {
                        Iterator<Message> i = messages.iterator();
                        while (i.hasNext()) {
                            Message m = i.next();
                            if (m.recipient == getId()) {
                                myMessages.add(m);
                                i.remove();
                            }
                        }
                        synchronized(messages){
                            while(messages.size() > MAX_SIZE){
                                i.remove();
                            }
                        }
                        synchronized(messages){
                            while(messages.size() > MAX_SIZE){
                                i.remove();
                            }
                        }
                    }
                }
                Thread.sleep(1000);
            }
            catch (InterruptedException e) {System.out.println(e);}
        }
    }
}

public class Main1 {
    static void pause(long n) {
        try { Thread.sleep(n); } catch (InterruptedException e) {}
    }
    
    public static void main (String[] args) {
        final String bond = "Bond";
        final String blofeld = "Blofeld";
        final String osato = "Mr. Osato";
        
        final PostBox pBond = new PostBox(bond);
        final PostBox pBlofeld = new PostBox(blofeld, pBond);
        final PostBox pOsato = new PostBox(osato, pBond);
        
        // send out some messages on another thread
        new Thread( new Runnable() {
            public void run() {
                pBond.send(blofeld, "Yes, this is my second life"); pause(1000);
                pBlofeld.send(bond, "You only live twice, Mr. Bond."); pause(500);
                String msg = "I gave Number 11 the strictest orders to eliminate him.";
                pOsato.send(blofeld, msg); pause(2000);
                pOsato.send(bond, msg);
                for (int i=0; i<20; ++i) pOsato.send(bond, "flooding the message queue...");
            }
        }).start();
        
        PostBox[] boxes = { pBond, pBlofeld, pOsato };
        long startTime = System.currentTimeMillis();
        
        // poll for messages in a tight loop for 5 secs
        while (true) {
            for (PostBox box : boxes) {
                for (String m : box.retrieve()) System.out.println(m);
            }
            if (System.currentTimeMillis() - startTime > 5000) break;
        }
        
        // stop each mailbox
        for (PostBox box : boxes) {
            box.stop(); 
        }
    }
}