#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>
#include <string.h>

int bufferCheck(int buf0, int buf1, int buf2, int buf3);
typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // use fopen to open card file & check values arent null
    FILE *card_ptr = fopen(argv[1], "r");
    if (card_ptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    // set buffer variable to hold 512 bytes e.g. JPG FAT
    BYTE buffer[512];

    // set initial variables
    int fileNum = 0;
    int check = 0;
    bool foundFirst = false;
    FILE *outptr = NULL;
    char filename[8];
    int i = 0;

    // main loop reads 512 bytes as FATs into buffer
    while (fread(buffer, 512, 1, card_ptr) == 1)
    {
        // check if start of jpg
        check = bufferCheck(buffer[0], buffer[1], buffer[2], buffer[3]);

        // found 1st jpg
        if (check == 1 && foundFirst == false)
        {
            // create filename & open file to write
            sprintf(filename, "%03i.jpg", fileNum);
            outptr = fopen(filename, "w");
            // write buffer to output file
            fwrite(&buffer, 512, 1, outptr);
            // change variable to log first file has been found
            foundFirst = true;
        }
        // still on previous jpg so write next buffer/FAT block to output file
        else if (check == 0 && foundFirst == true)
        {
            fwrite(&buffer, 512, 1, outptr);
        }
        // found start of new jpg
        else if (check == 1 && foundFirst == true)
        {
            // close previous output file
            fclose(outptr);

            // increase filename and create/open new output file
            fileNum++;
            sprintf(filename, "%03i.jpg", fileNum);
            outptr = fopen(filename, "w");

            // write buffer to new output file
            fwrite(&buffer, 512, 1, outptr);
        }
    }

}

// function - pass first 4 bytes of buffer - Returns 1 if start of JPEG and 0 if not
int bufferCheck(int buf0, int buf1, int buf2, int buf3)
{
    if (buf0 == 0xff &&
        buf1 == 0xd8 &&
        buf2 == 0xff &&
        (buf3 & 0xf0) == 0xe0)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}
