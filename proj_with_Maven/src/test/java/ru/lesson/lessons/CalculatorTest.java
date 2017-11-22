package ru.lesson.lessons;

import org.junit.Assert;

public class CalculatorTest {
    @org.junit.Test
    public void testAdd() throws Exception {
        Calculator calculator = new Calculator();
        calculator.add(1.0, 2.0);
        Assert.assertEquals(3, calculator.getResult());
    }
    @org.junit.Test
    public void testDiv() throws Exception {
        Calculator calculator = new Calculator();
        calculator.div(2.0, 1.0);
        Assert.assertEquals(2, calculator.getResult());
    }
    @org.junit.Test
    public void testSub() throws Exception {
        Calculator calculator = new Calculator();
        calculator.sub(2.0, 1.0);
        Assert.assertEquals(1,calculator.getResult());
    }
    @org.junit.Test
    public void testMultiply() throws Exception {
        Calculator calculator = new Calculator();
        calculator.multiply(2.0, 1.0);
        Assert.assertEquals(2, calculator.getResult());
    }

}