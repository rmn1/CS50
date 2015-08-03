#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

//  AmEx starts with 34 or 37;
// MasterCard starts 51, 52, 53, 54, or 55
//Visa starts with 4

/* verify:
every other digit *2, starting with second to last digit
sum product of those digits + sum of other digits
Sum's last digit is 0 (or % 10 == 0), the number is valid!
*/



int main(int argc, char* argv[])
{
    printf("Enter credit card number for validation: ");
    long long cc_num = GetLongLong();
    char* card_type;
    int sum = 0;
    
    long long n = cc_num;
    while (n > 100)
    {
        n /= 10;
    }
    
    if (n / 10 == 4 || (n >= 51 && n <= 55) || n == 34 || n == 37)
    {
        if (n / 10 == 4)
        {
            card_type = "VISA";
        }
        else if (n >= 51 && n <= 55)
        {
            card_type = "MASTERCARD";
        }
        else if (n == 34 || n == 37)
        {
            card_type = "AMEX";
        }
        
        for (int i = 0; cc_num > 0; i++)
        {
            if  (i % 2 == 0)
            {
                sum += cc_num % 10;
            }
            else
            {
                n = 2*(cc_num % 10);
                if (2*(cc_num % 10) > 9)
                {
                    n = n % 10 + n / 10;
                }
                sum += n;
            }
            cc_num /= 10;
        }
    }
    else
    {
        card_type = NULL;
        printf("INVALID\n");
        return 0;
    } 
    
    if (card_type && !(sum % 10))
    {
        printf("%s\n", card_type);    
    }
    else
    {
        printf("INVALID.\n");
    }
    
    return 0;
}
