import java.util.*;
import java.io.*;

public class BankAccount {

  /*---FIELDS---*/
  private int id;
  private String name;
  private int balance;

  /*---CONSTRUCTOR WITH NO BALANCE---*/
  public BankAccount(int ID,String Name) {
    setID(ID);
    setName(Name);
  }

  /*---CONSTRUCTOR---*/
  public BankAccount(int ID,String Name,int Balance) {
    setID(ID);
    setName(Name);
    setBalance(Balance);
  }

  /*---SETS ID CHECKING ID IS > 0---*/
  public void setID(int ID) {
    if(ID < 0) {
      throw new IllegalArgumentException("ID must be greater than 0");
    }
    id = ID;
  }

  /*---SETS NAME CHECKING NAME LENGTH > 0---*/
  public void setName(String Name) {
    if(Name.length() < 0) {
      throw new IllegalArgumentException("Name must contain at least one character");
    }
    name = Name;
  }

  /*---SETS BALANCE---*/
  public void setBalance(int Balance) {
    balance = Balance;
  }

  /*---GETS ID---*/
  public int getId() {
    return id;
  }

  /*---GETS NAME---*/
  public String getName() {
    return name;
  }

  /*---GETS BALANCE---*/
  public int getBalance() {
    return balance;
  }

  /*---DEPOSITS MONEY INTO AN ACCOUNT CHECKING THE AMOUNT DEPOSITED > 0---*/
  public void deposit(int amount) {
    if(amount < 0) {
      throw new IllegalArgumentException("Tried to deposit an amount less than 0");
    }
    balance += amount;
    System.out.println("Successful deposit");
  }

  /*---WITHDRAWS MONEY FROM AN ACCOUNT CHECKING THE AMOUNT WITHDRAWED < BALANCE AND > 0---*/
  public void withdraw(int amount) {
    if(amount < 0) {
      throw new IllegalArgumentException("Tried to withdraw an amount less than 0");
    }
    else if(amount > getBalance()) {
      throw new IllegalArgumentException("Tried to withdraw an amount greater than current balance");
    }
    balance -= amount;
    System.out.println("Successful withdrawal");
  }

  /*---PRINT THE ACCOUNT AS A STRING---*/
  public String toString() {
    String string;
    string = "Account type : Current, Account ID : " + getId() + ", Holder Name: " + getName() + ", Balance : " + getBalance();
    return string;
  }

}
