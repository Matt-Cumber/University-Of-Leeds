import java.util.*;
import java.io.*;

/*---STUDENT ACCOUNT INHERITS FROM BANKACCOUNT---*/
public class StudentAccount extends BankAccount {

  /*---CONSTRUCTOR NO BALANCE---*/
  public StudentAccount(int ID,String Name) {
    super(ID,Name);
  }

  /*---CONSTRUCTOR---*/
  public StudentAccount(int ID,String Name,int Balance) {
    super(ID,Name,Balance);
  }

  /*---OVERRIDE PREVIOUS SET BALANCE TO ALLOW FOR OVERDRAFT---*/
  @Override public void setBalance(int Balance) {
    if(Balance < -250) {
      throw new IllegalArgumentException("Balance must be greater than -250");
    }
    super.setBalance(Balance);
  }

  /*---OVERRIDE WITHDRAW METHOD SO IT NOW INCLUDES AN OVERDRAFT LIMIT OF 250---*/
  @Override public void withdraw(int amount) {
    if(amount < 0) {
      throw new IllegalArgumentException("Tried to withdraw an amount less than 0");
    }
    else if((getBalance() - amount) < -250) {
      throw new IllegalArgumentException("Tried to withdraw an amount over overdraft limit");
    }
    int balance = getBalance();
    balance -= amount;
    setBalance(balance);
    System.out.println("Successful withdrawal");
  }

  /*---OVERRIDE PREVIOUS METHOD TO CHANGE ACCOUNT TYPE---*/
  @Override public String toString() {
    String string;
    string = "Account type : Student, Account ID : " + getId() + ", Holder Name: " + getName() + ", Balance : " + getBalance();
    return string;
  }

}
