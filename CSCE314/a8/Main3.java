import java.lang.Class;
import java.lang.reflect.*;
class Main3 {
    public static class A {
        void foo(int T1, char T2) {}
        int bar(int T1, long T2, float T3) { return 1; }
        static double fii() {return 1.1;}
    }
    static void displayMethodInfo(Object obj) {
        Class c = obj.getClass();
        Method methList[] = c.getDeclaredMethods();
        for (Method m : methList) {
            //name
            System.out.print(m.getName() + " (");
            //class
            if (!(Modifier.isStatic(m.getModifiers())))
                System.out.print(m.getDeclaringClass().toString());
            //type listing
            Type[] tList = m.getGenericParameterTypes();
            for (Type t : tList) {
                if (!(Modifier.isStatic(m.getModifiers()))){
                    System.out.print(", " + t.toString());
                }
                else {
                    System.out.print(t.toString());
                }
            }
            //return type
            System.out.print(") -> " +m.getGenericReturnType().toString());
            System.out.println();
        }
    }
    public static void main(String args[]) {
        A a = new A();
        displayMethodInfo(a);
    }
    
}
