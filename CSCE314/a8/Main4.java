import java.lang.Class;
import java.lang.reflect.*;
import java.lang.String;
class Main4 {
    //class to test in
    public static class MyClass {
        public static boolean ffoo(int T1, char T2) { return false;}
        public static int bbar(int T1, long T2, float T3) { return 1; }
        public static int test1() { return 1; }
        public static int test2(int T1, long T2, float T3) { return 1; }
        public static boolean test3() { return false; }
        public static boolean test4() { return true; }
        public static boolean test5() { return false; }
    }
    //function to use
    static void compare(Object obj) {
        
        Class c = obj.getClass();
        Method mL[] = c.getDeclaredMethods();
        for (Method m : mL) {
            String mN = m.getName();
            Type[] mTL = m.getGenericParameterTypes();
            String mR = m.getGenericReturnType().toString();
            
            if (mN.substring(0,4).equals("test") && mTL.length == 0 && mR.equals("boolean"))
                System.out.println("OK: " + mN);
            else System.out.println("FAILED!: " + mN );
        }
    }
    //Main
    public static void main(String args[]) {
        MyClass ag = new MyClass();
        compare(ag);
    }
}
