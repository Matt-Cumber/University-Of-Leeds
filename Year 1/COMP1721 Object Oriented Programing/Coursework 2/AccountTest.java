import java.util.*;
import java.io.*;

public class AccountTest {
  public static void main(String[] args) {

    /*---CREATE ARRAY LIST---*/
    List<BankAccount> accounts = new ArrayList<>();

    /*---CREATE DIFFERENT ACCOUNTS---*/
    SavingsAccount savings1 = new SavingsAccount(1,"Louise",5000,0.15);
    SavingsAccount savings2 = new SavingsAccount(2,"Jessica",7500,0.04);
    BankAccount b1 = new BankAccount(3,"Joe",20000);
    StudentAccount student1 = new StudentAccount(4,"Matt",250);
    StudentAccount student2 = new StudentAccount(5,"Lucy",100);

    /*---ADD ACCOUNTS TO THE LIST---*/
    accounts.add(savings1);
    accounts.add(savings2);
    accounts.add(b1);
    accounts.add(student1);
    accounts.add(student2);

    /*---PRINT ACCOUNTS---*/
    for(BankAccount account: accounts) {
      System.out.println(account.toString());
    }

    /*---MANIPULATE ACCOUNTS---*/
    savings1.applyInterest();
    savings1.deposit(1000);
    try {
      savings2.deposit(3000);
    } catch(IllegalArgumentException error) {
      System.out.println(error);
    }
    savings2.withdraw(2000);
    b1.deposit(2500);
    b1.withdraw(500);
    student1.deposit(100);
    student1.withdraw(500);
    try {
      student2.withdraw(500);
    } catch(IllegalArgumentException error) {
      System.out.println(error);
    }
    student2.withdraw(350);

    /*---PRINT ACCOUNTS---*/
    for(BankAccount account: accounts) {
      System.out.println(account.toString());
    }

  }
}
