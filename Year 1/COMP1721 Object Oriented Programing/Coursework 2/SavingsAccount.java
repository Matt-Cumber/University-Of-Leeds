import java.util.*;
import java.io.*;

/*---SAVINGS ACCOUNT INHERITS FROM BANKACCOUNT---*/
public class SavingsAccount extends BankAccount {

  /*---FIELDS---*/
  private double InterestRate;

  /*---CONSTRUCTOR NO BALANCE---*/
  public SavingsAccount(int ID,String Name,double InterestRate) {
      super(ID,Name);
      setInterestRate(InterestRate);
 }

 /*---CONSTRUCTOR---*/
 public SavingsAccount(int ID,String Name,int Balance,double InterestRate) {
     super(ID,Name,Balance);
     setInterestRate(InterestRate);
}

/*---SET INTEREST RATE CHECKING > 0---*/
 public void setInterestRate(double Interestrate) {
   if(Interestrate < 0) {
     throw new IllegalArgumentException("");
   }
   InterestRate = Interestrate;
 }

 /*---OVERRIDE PREVIOUS SET BALANCE TO THROW EXCEPTION---*/
 @Override public void setBalance(int Balance) {
   if(Balance < 0) {
     throw new IllegalArgumentException("Balance must be greater than 0");
   }
   super.setBalance(Balance);
 }

 /*---GET INTEREST RATE---*/
 public double getInterestRate() {
   return InterestRate;
 }

 /*---APPLIES INTEREST TO SAVINGS ACCOUNT---*/
 public void applyInterest() {
   Double interest;
   int balance = getBalance();
   interest = getBalance() * getInterestRate();
   balance += interest.intValue();
   setBalance(balance);
   System.out.println("Successfully added interest");
 }

 /*---OVERRIDE PREVIOUS DEPOSIT METHOD TO ADD NEW RULE WHICH PREVENTS BALANCE EXCEEDING 10000---*/
 @Override public void deposit(int amount) {
   if(amount < 0) {
     throw new IllegalArgumentException("Tried to deposit an amount less than 0");
   }
   else if(getBalance() + amount > 10000) {
     throw new IllegalArgumentException("Tried to deposit an amount which set account balance greater than 10000");
   }
   int balance = getBalance();
   balance += amount;
   setBalance(balance);
   System.out.println("Successful deposit");
 }

 /*---OVERRIDE PREVIOUS METHOD TO CHANGE ACCOUNT TYPE---*/
 @Override public String toString() {
   String string;
   string = "Account type : Savings, Account ID : " + getId() + ", Holder Name: " + getName() + ", Balance : " + getBalance() + ", Interest Rate : " + getInterestRate();
   return string;
 }
}
