package ru.lesson.lessons;

import java.util.Scanner;

public class ArgRunner {
    public static void main(String [] arg) throws UserException{
        System.out.println("Calculate...");
        Calculator calc = new Calculator();
        Scanner scan = new Scanner(System.in);
        System.out.println("first number: ");
        double first = Double.valueOf(scan.next());
        System.out.println("second number: ");
        double second = Double.valueOf(scan.next());
        calc.multiply(first, second);
        System.out.println("result: " + calc.getResult());
        calc.sub(first, second);
        System.out.println("result: " + calc.getResult());
        calc.add(first, second);
        System.out.println("result: " + calc.getResult());
        calc.div(first, second);
        System.out.println("result: " + calc.getResult());
    }
}
