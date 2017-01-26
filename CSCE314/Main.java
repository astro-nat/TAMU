/*
 Name: Natalie Cluck
 Instructor: Hyunyoung Lee
 Course: CSCE 314-501
 Homework: Assignment 6
 Acknowledgements: Chance Eckert
 */

/****** NOTE *******
 CODE WILL NOT WORK WITH SPACES AFTER SEMICOLONS IN USER INPUT. 
 INPUT MUST RESEMBLE 
 java Main S "r 0 0 1 1;t 0 0 1 1 2 2;c 0 0 3;",
 
 NOT java Main S "r 0 0 1 1; t 0 0 1 1 2 2; c 0 0 3;"
 
 */

// implement Shape class

import java.util.Random;
import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.List;
import java.util.Collections;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.*;

class Point
{
    public double x;
    public double y;
    
    public Point(double x, double y)
    {
        this.x = x;
        this.y = y;
    }
}

abstract class Shape implements Comparable<Shape>
{
    // for testing
    public String name;
    public Point p;
    
    public Shape(String name, Point p)
    {
        this.p = p;
        this.name = name;
    }
    
    Point position()
    {
        return p;
    }
    
    public Shape()
    {
        name = new String("Shape");
        p = new Point(0,0);
    }
    
    abstract public double area();
    abstract public boolean equals(Object s);
    abstract public String toString();
    
    public int compareTo(Shape s)
    {
        if (s.area() < this.area()) return 1;
        else if (this.area() == s.area()) return 0;
        else return -1;
    }
    
    abstract public void draw(Shape s);
}

class Triangle extends Shape
{
    // this will compute the area using the x and y positions
    // fix this later
    
    private Point p2;
    private Point p3;
    
    public Triangle(Point p,Point p2,Point p3)
    {
        super("Triangle", p);
        //this.p.x = p.x;
        //this.p.y = p.y;
        
        this.p2 = p2;
        this.p3 = p3;
    }
    
    @Override
    public String toString()
    {
        return (name + "<(" + p.x + "," + p.y + "), (" + p2.x + "," + p2.y + "), (" + p3.x + "," + p3.y + ")>");
    }
    
    @Override
    public double area()
    {
        double num = (p.x * Math.abs(p2.y - p3.y) + p2.x * Math.abs(p3.y - p.y) + p3.x * Math.abs(p.y - p2.y))/2.0;
        //System.out.println(num);
        return num;
    }
    
    @Override
    public boolean equals(Object obj)
    {
        if (obj == null || obj.getClass() != this.getClass()) return false;
        if (this.position() != ((Triangle)obj).position())
        {
            return false;
        }
        else
        {
            if (p2 != ((Triangle)obj).p2)
            {
                return false;
            }
            else
            {
                if (p3 != ((Triangle)obj).p3)
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
        }
    }
    
    public int hashCode()
    {
        return this.hashCode();
    }
    /*
    @Override
    public boolean equals(Object s)
    {
        //Triangle temp = (Triangle) s;
        
        boolean cond1 = false;
        boolean cond2 = false;
        boolean cond3 = false;
        
        if (s == null) return false;
        else
        {
            if(((Triangle)s).position() == this.position()) cond1 = true;
            if (((Triangle)s).getClass() == this.getClass()) cond2 = true;
            if(((Triangle)s).area() == this.area() && (((this.p2 == ((Triangle)s).p2) || (((Triangle)s).p3 == this.p3))))
            {
                cond3 = true;
            }
        
            return (cond1 && cond2 && cond3);
        }
    }*/
    
    public int compare(Object o1, Object o2)
    {
        Shape area1 = (Triangle)o1;
        Shape area2 = (Triangle)o2;
        return area1.compareTo(area2);
    }
    
    public void draw(Shape s)
    {
        
    }
    
}

class Rectangle extends Shape
{
    private Point p2;
    double w;
    double h;
    
    public Rectangle(Point p,Point p2)
    {
        super("Rectangle",p);
        this.p2 = p2;
        
        w = Math.abs(p2.x - p.x);
        h = Math.abs(p.y - p2.y);
    }
    
    @Override
    public String toString()
    {
        return (name + "<(" + p.x + "," + p.y + "), (" + p2.x + "," + p2.y + ")>");
    }
    
    @Override
    public boolean equals(Object s)
    {
        //Rectangle temp = (Rectangle) s;
        
        boolean cond1 = false;
        boolean cond2 = false;
        boolean cond3 = false;
        
        if (s == null) return false;
        else
        {
            if(((Rectangle)s).position() == this.position()) cond1 = true;
            if (((Rectangle)s).getClass() == this.getClass()) cond2 = true;
            if(((Rectangle)s).area() == this.area() && (((Rectangle)s).p2 == this.p2))
            {
                cond3 = true;
            }
        
            return (cond1 && cond2 && cond3);
        }
    }

    @Override
    public double area()
    {
        return w * h;
    }
    
    public void draw(Shape s)
    {
        //Object obj = new Graphics();
    }
}

class Square extends Shape
{
    private double side;
    
    public Square(Point p, double side)
    {
        super("Square",p);
        this.side = side;
    }
    
    @Override
    public String toString()
    {
        return (name + "<(" + p.x + "," + p.y + "), " + side + ">");
    }
    
    @Override
    public double area()
    {
        return side * side;
    }
    
    @Override
    public boolean equals(Object s)
    {
        boolean cond1 = false;
        boolean cond2 = false;
        boolean cond3 = false;
        
        if (s == null) return false;
        else
        {
            if((((Square)s).position() == this.position())) cond1 = true;
            if (((Square)s).getClass() == this.getClass()) cond2 = true;
            if(((Square)s).area() == this.area())
            {
                cond3 = true;
            }
            
            return (cond1 && cond2 && cond3);
        }
    }
    
    public void draw(Shape s)
    {
        //Object obj = new Graphics();
    }
}

class Circle extends Shape
{
    private double radius;
    
    public Circle(Point p,double radius)
    {
        super("Circle",p);
        
        this.radius = radius;
    }
    
    @Override
    public String toString()
    {
        return (name + "<(" + p.x + "," + p.y + "), " + radius + ">");
    }
    
    @Override
    public double area()
    {
        return radius * radius * 3.14159265;
    }
    
    @Override
    public boolean equals(Object s)
    {
        boolean cond1 = false;
        boolean cond2 = false;
        boolean cond3 = false;
        
        if (s == null) return false;
        else
        {
            if(((Shape)s).position() == this.position()) cond1 = true;
            if (((Shape)s).getClass() == this.getClass()) cond2 = true;
            if((((Shape)s).area() == this.area()))
            {
                cond3 = true;
            }
            
            return (cond1 && cond2 && cond3);
        }
    }
    
    public int compare(Object o1, Object o2)
    {
        Shape area1 = (Circle)o1;
        Shape area2 = (Circle)o2;
        return area1.compareTo(area2);
    }
    
    public void draw(Shape s)
    {
        //Object obj = new Graphics();
    }
}

class LineSegment extends Shape
{
    private Point p2;
    
    public LineSegment(Point p,Point p2)
    {
        super("LineSegment",p);
        
        this.p2 = p2;
    }
    
    @Override
    public String toString()
    {
        return (name + "<(" + p.x + "," + p.y + "), (" + p2.x + "," + p2.y + ")>");
    }
    
    @Override
    public double area()
    {
        return 0.0;
    }
    
    @Override
    public boolean equals(Object s)
    {
        LineSegment temp = (LineSegment) s;
        
        boolean cond1 = false;
        boolean cond2 = false;
        boolean cond3 = false;
        
        if (s == null) return false;
        else
        {
            if(((LineSegment)s).position() == this.position()) cond1 = true;
            if (((LineSegment)s).getClass() == this.getClass()) cond2 = true;
            if((((LineSegment)s).area() == this.area()) && (this.p2 == temp.p2))
            {
                cond3 = true;
            }
            
            return (cond1 && cond2 && cond3);
        }
    }
    
    public void draw(Shape s)
    {
        //Object obj = new Graphics2D();
    }
}

class AreaCalculator
{
    public static void calculate(Shape[] shapes) // loop through array and calculate area of all shapes
    {
        double area = 0;
       
        for(int i = 0; i < shapes.length; i++)
        {
            //System.out.println("i = " + i); // for testing
            area = area + shapes[i].area();
        }
        
        System.out.println("Total area: " + area + "."); // for testing
    }
}

class Main
{
    public static void main(String[] args)
    {
        if (args[0].equals("R"))
        {
            int num = Integer.parseInt(args[1]);
            Random rand = new Random();
            Shape shaperoos[] = new Shape[num];
            
            for(int i = 0; i < num; i++)
            {
                int randshape = rand.nextInt(6);
                // System.out.println(randshape + "\n"); // for testing
                
                switch(randshape)
                {
                    case 1:
                        //System.out.println("Triangle works");
                        Triangle t = new Triangle(new Point(rand.nextInt(101),rand.nextInt(101)),new Point(rand.nextInt(101),rand.nextInt(101)),new Point(rand.nextInt(101),rand.nextInt(101)));
                        shaperoos[i] = t;
                        break;
                    case 2:
                        //System.out.println("Rectangle works");
                        Rectangle r = new Rectangle(new Point(rand.nextInt(101),rand.nextInt(101)),new Point(rand.nextInt(101),rand.nextInt(101)));
                        shaperoos[i] = r;
                        break;
                    case 3:
                        //System.out.println("Circle works");
                        Circle c = new Circle(new Point(rand.nextInt(101),rand.nextInt(101)),rand.nextInt(101));
                        shaperoos[i] = c;
                        break;
                    case 4:
                        //System.out.println("Line works");
                        LineSegment l = new LineSegment(new Point(rand.nextInt(101),rand.nextInt(101)),new Point(rand.nextInt(101),rand.nextInt(101)));
                        shaperoos[i] = l;
                        break;
                    case 5:
                        //System.out.println("Square works");
                        Square s = new Square(new Point(rand.nextInt(101),rand.nextInt(101)),rand.nextInt(101));
                        shaperoos[i] = s;
                        break;
                    default:
                        // for when random generator equals 0
                        i--;
                }
                
                
            }
            
            //for (int i = 0; i < num; i++) System.out.println(shaperoos[i].name); // prints shapes
            
            AreaCalculator.calculate(shaperoos); // calculates area of all shapes
            
            List<Shape> shapes = Arrays.asList(shaperoos);
            Collections.sort(shapes);
            System.out.println(shapes);
        }
        else if (args[0].equals("S"))
        {
            String phrase = new String(args[1]);
            Scanner s = new Scanner(phrase).useDelimiter(";");
            
            List<String> fullshapes = new ArrayList<String>();

            // for individual shape inputs. Ex: "r 0 0 1 1"
            while(s.hasNext())
                {
                    //System.out.println("s.next: " + s.next());
                    fullshapes.add(s.next());
                }
            
            // for final array of shapes. Ex: "Rectangle object, Circle object, etc."
            Shape[] allshapes = new Shape[fullshapes.size()];
            
            // initializes array to prevent NullPointerException
            for(int i = 0; i < allshapes.length; i++)
             {
                 allshapes[i] = new Rectangle(new Point(0,0),new Point (2,2));             //i++;
                 //System.out.println(allshapes[i].name); // for testing
             }
            
            System.out.println("Allshapes size: " + allshapes.length); // for testing
            /*for(int i = 0; i < allshapes.length; i++) // for testing
            {
                System.out.println(allshapes[i].name);
            }*/
        
            //System.out.println("Fullshapes size: " + fullshapes.size()); // for testing
            
            for(int i = 0; i < fullshapes.size(); i++)
            {
                String[] shapeprop = new String[fullshapes.size()];
                shapeprop = fullshapes.toArray(shapeprop);
                
                shapeprop = shapeprop[i].split(" "); // splits shape for individual tokens. Ex: "r",0,0,1,1
                
                //System.out.println("First one: " + shapeprop[0]); // for testing
                
                // this should take care of space in first element. DOESN'T WORK YET.
                int j = 0;
                //if (shapeprop[0] == "") j = 1;
                
                /*for(int t = 0; t < shapeprop.length; t++) // for testing
                {
                    System.out.println("Next: " + shapeprop[t]);
                }*/
                
                //System.out.println("i = " + i); // for testing
                //System.out.println("j = " + j); // for testing
                
                if (shapeprop[j].equals("r"))
                {
                    allshapes[i] = new Rectangle(new Point(Double.parseDouble(shapeprop[j+1]),Double.parseDouble(shapeprop[j+2])),new Point(Double.parseDouble(shapeprop[j+3]),Double.parseDouble(shapeprop[j+4])));
                    //System.out.println("Rectangle Created"); // for testing
                }
                else if (shapeprop[j].equals("t"))
                {
                    allshapes[i] = new Triangle(new Point(Double.parseDouble(shapeprop[j+1]),Double.parseDouble(shapeprop[j+2])),new Point(Double.parseDouble(shapeprop[j+3]),Double.parseDouble(shapeprop[j+4])),new Point(Double.parseDouble(shapeprop[j+5]),Double.parseDouble(shapeprop[j+6])));
                    //System.out.println("Triangle created"); // for testing
                }
                else if (shapeprop[j].equals("s"))
                {
                    allshapes[i] = new Square(new Point(Double.parseDouble(shapeprop[j+1]),Double.parseDouble(shapeprop[j+2])),Double.parseDouble(shapeprop[j+3]));
                    //System.out.println("Square created"); // for testing
                }
                else if (shapeprop[j].equals("c"))
                {
                    allshapes[i] = new Circle(new Point(Double.parseDouble(shapeprop[j+1]),Double.parseDouble(shapeprop[j+2])),Double.parseDouble(shapeprop[j+3]));
                    //System.out.println("circle created"); // for testing
                }
                else if (shapeprop[j].equals("l"))
                {
                    allshapes[i] = new LineSegment(new Point(Double.parseDouble(shapeprop[j+1]),Double.parseDouble(shapeprop[j+2])),new Point(Double.parseDouble(shapeprop[j+3]),Double.parseDouble(shapeprop[j+4])));
                    //System.out.println("Line created"); // for testing
                    
                }
            }
            
            for(int i = 0; i < allshapes.length; i++)
            {
                System.out.println(allshapes[i].toString());
            }
            AreaCalculator.calculate(allshapes); // calculates area of all shapes
            
			// shapes is an array of Shape
        System.out.println("*** To test equals()");
        for ( int i = 0; i < allshapes.length-1; i++ )
            for ( int j = i+1; j <= allshapes.length-1; j++ ) {
                if (allshapes[i].equals(allshapes[j]))
                   System.out.println(allshapes[i].toString() + " equals to " + allshapes[j].toString());
            }
			
            System.out.println("Natural ordering: ");
            List<Shape> shapes = Arrays.asList(allshapes);
            Collections.sort(shapes);
            System.out.println(shapes.toString());
			
			
        }
        
       
    }
}