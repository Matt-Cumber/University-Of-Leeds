/*****************************************************************************************************************************

I declare that the following program was written by me and that I have NOT copied any part of this code from any other source.

Name: Matthew Cumber

Email: ll16m23c@leeds.ac.uk

Date: 26/10/17

******************************************************************************************************************************/


#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
  int optionmain=0, optionbilling=0, optionnewbill=0; // optionmain integer entered from mainmenu, option new bill entered from billing menu, option newbill entered from new bill menu
  int run=1, mistake=1, billing=1, newbill=1; // when run=0 the program Terminates, other variables used to make infinte loops as 1 is always true
  int quarterlywaterconsumptioncommercial =0;
  float freshwaterchargescommercial =0, wastewaterchargecommercial =0, standingchargecommercial=0, VAT =0, totaltopaycommercial =0, sumcommercial =0;
  int quarterlywaterconsumptiondomestic =0;
  float freshwaterchargesdomestic =0, wastewaterchargedomestic =0, standingchargedomestic =0, totaltopaydomestic =0;
  int totalfreshwaterdomestic =0, totalfreshwatercommercial =0, totalfreshwaterallcustomers =0;
  float totalrevenuecommercial =0, totalrevenuedomestic =0, totalrevenueallcustomers =0;
  float totalcostcommercial =0, totalcostdomestic =0, totalcostallcustomers =0;
  float sumtotaltopaycommercial =0, countcommercial =0, averagetotaltopaycommercial =0, minimumtotaltopaycommercial =1000000, maximumtotaltopaycommercial =0;
  float countdomestic =0, averagetotaltopaydopmestic =0, minimumtotaltopaydomestic =100000, maximumtotaltopaydomestic =0;
  float incometax =0;
  float profitallcustomers =0;
  float actualprofit =0;

  int menu =0;


while(run==1)   {                                                               //Creates an infinte loop until run=0 and program exit

    printf("\n\n\n\nMAIN MENU\n________________________________\n\nHello, please choose an option:\n 1.Billing\n 2.Quarterly Sums and Statistics\n 3.Quit\n\nEnter choice here as 1, 2 or 3: ");

    scanf("%d", &optionmain);                                                   //Prompts user to make a choice by entering 1, 2 or 3

//If the user enters a number which is not an option (not 1, 2 or 3), this while loop will continue to ask the user to enter another option until it is valid

    while(mistake==1)   {

          if(optionmain>3||optionmain<1) {

              printf("This is not an option, please try again by entering 1, 2 or 3: ");
              scanf("%d", &optionmain);
          }

              else { break; }   // End infinte mistake loop when integer 1, 2 or 3 is entered as they are valid options

          }

//Terminates the program when the user enters 3 by making the while(run==1) condition false

              if(optionmain==3)

                    { printf("Goodbye!\n"); run=0; exit; }

// Start of code for functionality of program when the user chooses either one or two from the MAIN MENU

else {


                            if(optionmain==1) {                                 //This code is run if the user enters 1 in the main menu

          while(billing=1)   {                                                  //Creates a loop to stop the user from reaching the main menu until they enter "2" on the billing menu


                  printf("\n\n\n\nBILLING\n________________________________\n\nPlease choose an option\n 1.Create new bill\n 2.Return to MAIN MENU\n\nEnter your choice here as 1 or 2: ");

                  scanf("%d", &optionbilling);                                  //Promts user to choose an option from the BILLING MENU by entering

//Similar to comment this while loop will be run if a number entered is invalid and will continue to ask the user to enter another option until it is valid

    while(mistake==1)   {

            if(optionbilling>2||optionbilling<1) {

                printf("This is not an option, please try again by entering 1 or 2: ");
                scanf("%d", &optionbilling);

            }

                  else { break; }

            }

          if (optionbilling==2)   { break; } //If the user enters 2 this loop is broken and the program begins from the beginnning i.e. the MAIN MENU


          else {

            while(newbill=1)   {                                                //

                printf("\n\n\n\nNEWBILL\n________________________________\n\nPlease choose an option to select the type of customer or cancel the new bill\n 1.Commercial\n 2.Domestic\n 3.Cancel\n\nEnter your choice here as 1, 2 or 3: ");

                scanf("%d", &optionnewbill);



//Similar to comment  this code will be run if a number entered is invalid and will continue to ask the user to enter another option until it is valid

      while(mistake==1)   {

            if(optionnewbill>3||optionnewbill<1)   {

              printf("This is not an option, please try again by entering 1, 2 or 3: ");
              scanf("%d", &optionnewbill);

            }

                  else { break; }

            }

              if (optionnewbill==3) {                                           //Returns user to BILLING MENU

                break;


              }


              else {

                  if(optionnewbill==1) {                                        //Code for a commercial customer

                    printf("\nPlease enter the amount of quarterly water consumption the commercial customer\nused: ");
                    scanf("%d", &quarterlywaterconsumptioncommercial);


// This code will run if a user attemts to enter a negative integer for quarterly water consumption and continue to ask theuser to enter a value until it is valid

                              while(mistake==1)   {

                                        if(quarterlywaterconsumptioncommercial<0)   {

                                            printf("Please enter a number greater than or equal to 0: ");
                                            scanf("%d", &quarterlywaterconsumptioncommercial);

                                          }

                                                    else { break; }

                                          }

                    totalfreshwatercommercial += quarterlywaterconsumptioncommercial;  // Calculates total fresh water consumption for commercial customers
                    totalfreshwaterallcustomers += quarterlywaterconsumptioncommercial; // Adds the fresh water consumption for this bill to the total fresh water consumption for all customer types





                    freshwaterchargescommercial = quarterlywaterconsumptioncommercial*2.50;  // Calculates fresh water charge for commercial customer, fixed at £2.50 per cubic metre of water
                    wastewaterchargecommercial = (quarterlywaterconsumptioncommercial*0.95)*2.00;  //Calculates waste water charges which is £2 multiplied by 95% of the total water consumption
                    standingchargecommercial = 1.30*91.00;  // Calculate standing charge at a rate of £1.30 per day for commercial customers
                    sumcommercial = 50 + standingchargecommercial + wastewaterchargecommercial + freshwaterchargescommercial;  //Calculates the sum of all charges for commercial customer (£50 is charge for surface water)
                    VAT = sumcommercial * 0.20;  // Calculates VAT at a rate of 20% of the total amount of the bill (only applicable for commercial customers)
                    totaltopaycommercial = sumcommercial + VAT;  // Calculates the total amount the commercial customer has to pay including VAT
                    totalrevenuecommercial += sumcommercial;  // Calcualtes the total revenue by adding the revenue of the current bill to a running total
                    totalcostcommercial += 1.00*quarterlywaterconsumptioncommercial;  // Calculates the total cost for providing water to the commercial customer at a rate of £1 per cubic metre of water
                    sumtotaltopaycommercial += totaltopaycommercial;  // Adds the total amount paid by the commercial customer to a running total to be used later for averages
                    countcommercial++;  // Counts how many commercial customers there are in total


                    if(totaltopaycommercial<minimumtotaltopaycommercial) {
                      minimumtotaltopaycommercial = totaltopaycommercial;  // assigns value of the current bill to the overall minimum commercial bill if it is less than the previous minimum commercial bill
                    }

                    if(totaltopaycommercial>maximumtotaltopaycommercial) {
                      maximumtotaltopaycommercial = totaltopaycommercial;  // assigns value of the current bill to the overall maximum commercial bill if it is less than the previous maximum commercial bill
                    }

                    printf("____________________________________________________");
                    printf("\n\nType of customer is COMMERCIAL\n");
                    printf("Amount of fresh water consumption : %d metres cubed\n", quarterlywaterconsumptioncommercial);
                    printf("Fresh water charges : £%.2f \n", freshwaterchargescommercial);
                    printf("Waste water charges : £%.2f \n", wastewaterchargecommercial);
                    printf("Surface water charges : £50.00 \n");
                    printf("Standing charges : £%.2f \n", standingchargecommercial);
                    printf("Ammount of VAT : £%.2f \n", VAT);
                    printf("Total amount to pay : £%.2f \n", totaltopaycommercial);
                    printf("____________________________________________________\n");

                        break;
                  }  // End brace if line 131

                  else {                                                        //code for a domestic customer


                    printf("\nPlease enter the amount of quarterly water consumption the Domestic customer\nused: ");
                    scanf("%d", &quarterlywaterconsumptiondomestic);

// This code will run if a user attemts to enter a negative integer for quarterly water consumption and continue to ask theuser to enter a value until it is valid

                        while(mistake==1)   {

                                    if(quarterlywaterconsumptiondomestic<0)   {

                                          printf("Please enter a number greater than or equal to 0: ");
                                          scanf("%d", &quarterlywaterconsumptiondomestic);

                                         }

                                                    else { break; }

                                        }



                    totalfreshwaterdomestic += quarterlywaterconsumptiondomestic;  // Calculates the total fresh water consumed by all domestic customers
                    totalfreshwaterallcustomers +=quarterlywaterconsumptiondomestic;  // Adds the fresh water consumption for this bill to an overall total of all fresh water consumption by all types of customers






                      if (quarterlywaterconsumptiondomestic<6) {                //Calculation for domestic water charge for amounts less than 6

                        freshwaterchargesdomestic = 0.20*quarterlywaterconsumptiondomestic;
                      }

                      else {

                                if (quarterlywaterconsumptiondomestic<13){                //Calculation for domestic water charge for amounts less than 13 more than 5

                                  freshwaterchargesdomestic = 0.20*5.00 + (quarterlywaterconsumptiondomestic-5)*0.35;

                                }

                                    else {

                                            if (quarterlywaterconsumptiondomestic<26) {                //Calculation for domestic water charge for amounts less than 26 more than 12

                                              freshwaterchargesdomestic = 0.20*5.00 + 7.00*0.35 + (quarterlywaterconsumptiondomestic-12)*0.50;

                                            }

                                            else {

                                              if (quarterlywaterconsumptiondomestic<41) {                //Calculation for domestic water charge for amounts less than 41 more than 25

                                              freshwaterchargesdomestic = 0.20*5.00 + 7.00*0.35 + 13*0.50 + (quarterlywaterconsumptiondomestic-25)*0.75;

                                            }

                                                else {                //Calculation for domestic water charge for amounts more than 40

                                                  freshwaterchargesdomestic = 0.20*5.00 + 7.00*0.35 + 13*0.50 + 0.75*15 + (quarterlywaterconsumptiondomestic-40)*2.50;
                                                }
                                            }  // End brace else line 245


                                } // End brace else line 237



                      } // End brace else line 229

                      wastewaterchargedomestic = (quarterlywaterconsumptiondomestic*0.95)*0.25;  // Calculates the waste water charge which is 25p multiplied by 95% of the total water consumption
                      standingchargedomestic = 0.10*91;  // Calculates the standing charge at a rate of 10p per day
                      totaltopaydomestic = 10.00 + freshwaterchargesdomestic + wastewaterchargedomestic + standingchargedomestic;  /*Calculates the total bill the domestic customer has to pay by adding together the
                      standing charge, the charge for fresh water, the charge for waste water and the fixed fee of £10*/
                      totalrevenuedomestic += totaltopaydomestic;  // Calculates the total revenue from all domestic customers by adding the total for the current bill to a running total
                      totalcostdomestic += 1.00*quarterlywaterconsumptiondomestic;  // Calculates the cost of providing water to domestic customers at a rate of £1 per 1 cubic metre of water
                      countdomestic++;  //Counts how many domestic customers there are in total



                      if(totaltopaydomestic<minimumtotaltopaydomestic) {
                        minimumtotaltopaydomestic = totaltopaydomestic;  // assigns value of the current bill to the overall minimum domestic bill if it is less than the previous minimum domestic bill
                      }

                      if (totaltopaydomestic>maximumtotaltopaydomestic) {
                        maximumtotaltopaydomestic = totaltopaydomestic;  // assigns value of the current bill to the overall maximum domestic bill if it is more than the previous maximum domestic bill
                      }

                      printf("____________________________________________________");
                      printf("\n\nType of customer is Domestic\n");
                      printf("Amount of fresh water consumption : %d metres cubed\n", quarterlywaterconsumptiondomestic);
                      printf("Fresh water charges : £%.2f \n", freshwaterchargesdomestic);
                      printf("Waste water charges : £%.2f \n", wastewaterchargedomestic);
                      printf("Surface water charges : £10.00 \n");
                      printf("Standing charges : £%.2f \n", standingchargedomestic);
                      printf("Total amount to pay : £%.2f \n", totaltopaydomestic);
                      printf("____________________________________________________\n");

                      break;

                  } // End brace for else code for domestic customer line 193


                } // End brace for else instead of optionnewbill==3 line 129




} // End bracewhile(newbill=1) line 98






} // End brace for else new bill i.e option 1 line 96



} // End brace for while(billing=1) line 71



} // End brace for if(optionmain==1) line 69


// Code run if option two is entered from MAIN MENU

      else {                                                                    // Code for option 2 from mainmenu i.e. Quarterly Sums and Statistics

        if (countcommercial==0 && countdomestic==0)  // Check to see if any bills have been entered into the program, if they have at least one of the counters will not be 0
        {
          printf("\nADD SOME BILLS BEFORE VIEWING QUARTERLY SUMS AND STATISTICS"); // If both counters equal zero then this message is displayed
        }
        else {  // If one of the counters is greater than 0 the code for this option runs

        averagetotaltopaycommercial = sumtotaltopaycommercial/countcommercial;  // Calculates avergae commercial bill
        averagetotaltopaydopmestic = totalrevenuedomestic/countdomestic;  // Calculates average domestic bill
        totalcostallcustomers = totalcostcommercial + totalcostdomestic;  // Calculates the cost of providing water to all the customers
        totalrevenueallcustomers = totalrevenuecommercial + totalrevenuedomestic;  // Calculates the total revenue made from all the customers
        profitallcustomers = totalrevenueallcustomers - totalcostallcustomers;  // Calculates the profit made by the company

        if(profitallcustomers<0)  // If the profit is negative, i.e. a loss, then income tax income tax is not applicable and does not need to be paid
        incometax = 0;
        else {incometax = 0.25*profitallcustomers;}  // Income tax is calcualted at 25% of total profits
        actualprofit = profitallcustomers - incometax;  // Calculates the amount of money the compnay keeps after paying income tax

        printf("_____________________________________________________________________________________________________________________");
        printf("\n\nTotal amount of fresh water consumed by commercial customers   :   %d metres cubed\n\n", totalfreshwatercommercial);
        printf("Total amount of fresh water consumed by domestic customers     :   %d metres cubed\n\n", totalfreshwaterdomestic);
        printf("Total amount of fresh water consumed by all customers          :   %d metres cubed\n\n", totalfreshwaterallcustomers);
        printf("Total revenue from commercial customer bills                   :   £%.2f\n\n", totalrevenuecommercial);
        printf("Total revenue from domestic customer bills                     :   £%.2f\n\n", totalrevenuedomestic);
        printf("Total revenue from all customer bills                          :   £%.2f\n\n", totalrevenueallcustomers);
        printf("Total cost of providing water to commercial customers          :   £%.2f\n\n", totalcostcommercial);
        printf("Total cost of providing water to domestic customers            :   £%.2f\n\n", totalcostdomestic);
        printf("Total cost of providing water to all customers                 :   £%.2f\n\n", totalcostallcustomers);


        if (totalrevenueallcustomers<totalcostallcustomers) {             /* Checks to see if company made a profit or loss from all customers by checking if the revenue made from all customers is less than the cost to
          provide the water to the customers then prints profit or loss accordingly*/
          printf("Total LOSS from all customers                                  :   £%.2f\n\n", (-1.00*profitallcustomers)); // Multiply loss by minus one so that it is printed as a positive value
        }
        else {
          printf("Total PROFIT from all customers                                :   £%.2f\n\n", profitallcustomers);
        }

        if (incometax==0) {
          printf("Income tax paid to Government                                  :   Due to loss, income tax does not need to be paid\n\n");  /*Since income tax is zero, it does not need to be paid and so this is printed
          instead of a value of zero*/
        }
        else {
          printf("Income tax paid to Government                                  :   £%.2f\n\n", incometax);
        }

        printf("Amount of money left after income tax                          :   £%.2f\n\n", actualprofit);
        printf("Minimum commercial bill                                        :   £%.2f\n\n", minimumtotaltopaycommercial);
        printf("Maximum commercial bill                                        :   £%.2f\n\n", maximumtotaltopaycommercial);
        printf("Average commercial bill                                        :   £%.2f\n\n", averagetotaltopaycommercial);
        printf("Minimum domestic bill                                          :   £%.2f\n\n", minimumtotaltopaydomestic);
        printf("Maximum domestic bill                                          :   £%.2f\n\n", maximumtotaltopaydomestic);
        printf("Average domestic bill                                          :   £%.2f\n", averagetotaltopaydopmestic);
        printf("_____________________________________________________________________________________________________________________\n\n");

        printf("\nEnter 1 to return to the main menu:");
        scanf("%d", &menu);

        while (mistake=1) {

        if (menu == 1) {  // If user enters 1 they are returned to the main menu
          break;
        }

        else {
          printf("Please enter 1 to return to the main menu :");  // If user doesn't enter 1 this messaged is displayed until 1 is entered
          scanf("%d", &menu);

            }
          }







} // End brace for else on 330
} // End brace for else on 324

} // End brace for else on line 66

} // End brace for orginal while loop on line 38

  return 0;

}
