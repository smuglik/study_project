package ru.lesson.lessons;


import java.util.Scanner;

public class Calculate {
    public static void main(String [] arg) {
        Scanner scan = new Scanner(System.in);
        Calculator calc = new Calculator();
        System.out.println("Calculate...");
        System.out.println("first number: ");
        double first = Double.valueOf(scan.next());
        System.out.println("second number: ");
        double second = Double.valueOf(scan.next());
       // int first = Integer.valueOf(arg[0]);
        calc.multiply(first,second);
        System.out.println("result: " + calc.getResult());
        calc.sub(first, second);
        System.out.println("result: " + calc.getResult());
        calc.add(first,second);
        System.out.println("result: " + calc.getResult());
        calc.div(first, second);
        System.out.println("result: " + calc.getResult());
    }
}
