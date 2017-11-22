package ru.lesson.lessons;

import javax.jws.soap.SOAPBinding;

public class UserException extends Exception {
    public UserException(final String message){
        super(message);
    }
}
