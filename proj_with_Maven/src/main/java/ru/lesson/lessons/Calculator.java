package ru.lesson.lessons;


public class Calculator {
    private int result;

    /**
     * Считаем сумму
     * @param first первый параметр
     * @param second второй параметр
     */
    public void add(Double first, Double second) {
        this.result = (int) (first + second);
    }
    public void div(Double first, Double second){
        this.result = (int) (first/second);
    }
    public void sub(Double first, Double second){
        this.result = (int) (first - second);
    }
    public void multiply(Double first, Double second){
        this.result = (int) (first * second);
    }
    public int getResult() {
        return  result;
    }
    public void cleanResult(){
        this.result = 0;
    }
}
