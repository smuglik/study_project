package ru.lesson.lessons;
import java.util.Scanner;

public class InteractRunner {
    public static void main(String [] arg){
        Scanner reader = new Scanner(System.in);
        try{
            Calculator calc = new Calculator();
            String exit = "no";
            while(!exit.equals("yes")){
                System.out.println("Enter first");
                String first = reader.next();
                System.out.println("Enter second");
                String second = reader.next();
                calc.add(Double.valueOf(first), Double.valueOf(second));
                System.out.println("Result: " + calc.getResult());
                calc.cleanResult();
                System.out.println("Exit: yes/no ");
                exit = reader.next();
            }
        }   finally {
            reader.close();
        }
    }
}
