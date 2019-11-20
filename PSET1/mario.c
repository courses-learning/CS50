#include <stdio.h>
#include <cs50.h>

void spaces(int count);
void blocks(int count);

int main(void)
{
    // get number of blocks for tower width
    int req_no = get_int("How many blocks for your Mario tower? ");

    // main loop for printing rows
    for (int x=1; x<=req_no; x++)
    {
        spaces(req_no-x);  // spaces as starting from top
        blocks(x);  // 1st set of blocks
        printf("  ");  // 2 space gap between towers
        blocks(x);  // 2nd set of blocks
        printf("\n");  // new row
    }

}

// function to print spaces by number passed
void spaces(int count)
{
    for (int i=0; i<count; i++)
    {
        printf(" ");
    }
}


// function to print blocks by no passed
void blocks(int count)
{
    for (int i=0; i<count; i++)
    {
        printf("#");
    }
}
