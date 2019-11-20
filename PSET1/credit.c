#include <stdio.h>
#include <cs50.h>
#include <math.h>

int lastDigit(long int);
string checkType(int);

int main(void)
{
    // get and store credit card no which must be +ve
    long int card_no = 0;
    do
    {
        card_no = get_long("Please enter the credit card no to check: ");
    }
    while (card_no <= 0);

    // set variables
    long int reducedCard = card_no; // running card no with dropped final digit
    int nDigits = floor(log10(labs(card_no))) + 1; // length of original card no
    int odds = 0; // running total of odd sum starting from last digit
    int evens = 0; // running total of even sum starting from last digit
    string type = "";

    for (int i = 0; i < nDigits; i++)
    {
        //odd number - add all odds
        odds += lastDigit(reducedCard);
        reducedCard /= 10;

        // check if at last 2 digits
        if (reducedCard > 9 && reducedCard < 100)
        {
            type = checkType(reducedCard);
        }

        //even number - double each even no and add digits only e.g. split if > 10 so 11 = 1+1
        int no = lastDigit(reducedCard) * 2;
        if (no < 10)
        {
            evens += no;
        }
        else
        {
            evens += lastDigit(no) + 1;
        }
        reducedCard /= 10;

        // check if at last 2 digits
        if (reducedCard > 9 && reducedCard < 100)
        {
            type = checkType(reducedCard);
        }

    }
    if ((evens + odds) % 10 == 0 && nDigits > 12 && nDigits < 17)
    {
        printf("%s\n", type);
    }
    else
    {
        printf("INVALID\n");
    }
}

// function passed number returns last digit
int lastDigit(long int noInput)
{
    return noInput % 10;
}

string checkType(int noInput)
{
    if (noInput == 34 || noInput == 37)
    {
        return ("AMEX");
    }
    else if (noInput > 50 && noInput < 56)
    {
        return ("MASTERCARD");
    }
    else if (noInput / 10 == 4)
    {
        return ("VISA");
    }
    else
    {
        return ("INVALID");
    }
}
