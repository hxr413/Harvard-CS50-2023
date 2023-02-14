#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Ask user to input credit card number
    long cardnum;
    do
    {
        printf("Please input your credit card number with no hyphens.\n");
        cardnum = get_long("Number: ");
    }
    while (cardnum < 0);

    //Validate credit card number
    //1. Whether the number is invalid: Luhn’s Algorithm
    int digitnum = 0, digit = 0, sum = 0, digit2 = 0;
    while (cardnum > 0)
    {
        digit2 = digit;
        digit = cardnum % 10;
        digitnum++;

        if (digitnum % 2 == 0)
        {
            sum = sum + (digit * 2) % 10 + (digit * 2) / 10;
        }
        else //(digitnum % 2 == 1)
        {
            sum = sum + digit;
        }
        cardnum = cardnum / 10;
    }

    //2. What type of card it is
    string type;
    if (cardnum < 4000000000000)
    {
        type = "INVALID";
    }

    if (sum % 10 != 0)
    {
        type = "INVALID";
    }
    else //(sum % 10 == 0)
    {
        if (digitnum == 15 && digit == 3 && (digit2 == 4 || digit2 == 7)) //2.1 American Express: 15 digits, start with 34 or 37
        {
            type = "AMEX";
        }
        else
        {
            if (digitnum == 16 && digit == 5 && (digit2 <= 5 && digit2 >= 1)) //2.2 MasterCard: 16 digits, start with 51-55
            {
                type = "MASTERCARD";
            }
            else
            {
                if ((digitnum == 13 || digitnum == 16) && digit == 4) //2.3 Visa: 13 or 16 digits, start with 4
                {
                    type = "VISA";
                }
            }
        }
    }
    printf("%s\n", type);
}