#include <stdio.h>
#include <cs50.h>
#include <math.h>

int check(int);

int main(void)
{
    // set dollars variable and get user input for this which must be +ve
    float dollars = 0;
    do
    {
        dollars = get_float("How many dollars do you need? $");
    }
    while (dollars <= 0);

    // change dollars to cents and set coin counter
    int cents = round(dollars * 100);
    int coin_tot = 0;

    // main check loop calling function to return coin to use
    while (cents > 0)
    {
        int sub = check(cents);
        coin_tot++;
        cents -= sub;
    }

    // show final number of coins problem would take
    printf("%i\n", coin_tot);
}

// function when passed cents amount will return value of largest coin that may be taken away
int check(int money)
{
    if (money >= 25)
    {
        return 25;
    }
    else if (money >= 10)
    {
        return 10;
    }
    else if (money >= 5)
    {
        return 5;
    }
    else
    {
        return 1;
    }
}
