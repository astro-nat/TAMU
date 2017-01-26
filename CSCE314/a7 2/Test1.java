// Name: Natalie Cluck
// Instructor: Dr. Hyunyoung Lee
// Course: CSCE314
// Assignment: Assignment 7
// Acknowledgements: Chance Eckert, Chris Ridley

import java.util.*;

// Problem 1 Task 3
class Test1
{
    public static void main(String[] args)
    {
        Node<Integer> first = new Node<Integer>(1,null);
        Node<Integer> last = first;
        
        last.next = new Node<Integer>(2,null);
        last = last.next;
        last.next = new Node<Integer>(3,null);
        last = last.next;
        last.next = new Node<Integer>(4,null);
        last = last.next;
        last.next = new Node<Integer>(5,null);
        
        int sum = sum(first);
        System.out.println("Sum is: " + sum);
        print(first);
        
    }
    
    public static int sum(Node<Integer> linked)
    {
        int sum = 0;
        for (Integer z : linked)
        {
            sum = sum + z;
        }
        return sum;
    }
    
    public static void print(Node<Integer> linked)
    {
        for (Integer l : linked)
            System.out.println(l);
    }
}