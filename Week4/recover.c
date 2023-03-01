#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // open memory card
    FILE *input = fopen(argv[1], "r");

    if (argc != 2)
    {
        printf("Usage: ./recover input_file\n");
        return 1;
    }
    if (input == NULL)
    {
        printf("Input file cannot be opened.\n");
        return 1;
    }

    // initialisation
    BYTE buffer[BLOCK_SIZE];
    FILE *output = NULL;
    int counter = 0;
    // ensure that filename has enough memory/chars to represent the entire ###.jpg including NUL
    char filename[8];

    // repeat till the end of the file: read memory card in blocks of 512 bytes into a buffer
    while (fread(buffer, 1, BLOCK_SIZE, input))
    {
        // look for beginning of a JEPG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if it's not the first file, close the current output file and start a new one
            if (counter > 0)
            {
                fclose(output);
            }
            // create filename
            sprintf(filename, "%03i.jpg", counter);
            // open a new file
            output = fopen(filename, "w");
            counter++;
        }
        // if alread found a JEPG, keep writing to it
        // Note: as the 1st block of input is not a JPEG, directly writing to it will cause segmentation faults
        // The programme should wait untill the 1st JEPG is found and a new file is created in the if block above, i.e. when (open != NULL)
        // then starts to write
        if (counter > 0)
        {
            fwrite(buffer, 1, BLOCK_SIZE, output);
        }

    }

    fclose(input);
    fclose(output);
    return 0;
}