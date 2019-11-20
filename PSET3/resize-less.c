#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // get resize factor and convert to int
    int n = atoi(argv[1]);

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf_orig;
    fread(&bf_orig, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi_orig;
    fread(&bi_orig, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf_orig.bfType != 0x4d42 || bf_orig.bfOffBits != 54 || bi_orig.biSize != 40 ||
        bi_orig.biBitCount != 24 || bi_orig.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // create copies of original headers
    BITMAPINFOHEADER bi_new = bi_orig;
    BITMAPFILEHEADER bf_new = bf_orig;

    // correctly amend header files for new large image
    bi_new.biWidth *= n;
    bi_new.biHeight *= n;

    // determine padding for new resized image
    int padding_new = (4 - (bi_new.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi_new.biSizeImage = ((sizeof(RGBTRIPLE) * bi_new.biWidth) + padding_new) * abs(bi_new.biHeight);
    bf_new.bfSize = bi_new.biSizeImage + bf_new.bfOffBits;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_new, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_new, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding_orig = (4 - (bi_orig.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // set distance to move file pointer back during iteration for vertical resize
    int scanlineLength = (abs(bi_orig.biWidth) * sizeof(RGBTRIPLE)) + padding_orig;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi_orig.biHeight); i < biHeight; i++)
    {
        // print req no rows for height increase
        for (int row = 0; row < n; row++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi_orig.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile n times
                for (int l = 0; l < n; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // skip over padding, if any
            fseek(inptr, padding_orig, SEEK_CUR);

            // add req padding
            for (int k = 0; k < padding_new; k++)
            {
                fputc(0x00, outptr);
            }

            //move pointer back to repeat scanline
            fseek(inptr, (0 - scanlineLength), SEEK_CUR);
        }
        // move pointer ahead to the end of the last scanline to we pickup the next scanline
        fseek(inptr, scanlineLength, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
