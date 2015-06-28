#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void) {
   int change;
   
   // loop getting input from user and verifying it is a positive number
   do {
       printf("How much change is owed?\n");
       float float_change = GetFloat();
       change = round(float_change*100);  
   } while (change <= 0);
   
   int min_coins = 0;
   // quarters
   min_coins = change / 25;
   change -= min_coins * 25;
       
   // dimes
   min_coins += (change / 10);
   change -= (change / 10) * 10;
       
   // nickels
   min_coins += (change / 5);
   change -= (change / 5) * 5;
       
   // pennies
   min_coins += change; 
       
   printf("%d\n", min_coins);
   return 0;
}
