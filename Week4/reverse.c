#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, 1, HEADER_SIZE, input);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(header) == 0)
    {
        printf("Not a .wav file.\n");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&header, HEADER_SIZE, 1, output);

    // Use get_block_size to calculate size of block
    // TODO #7
    int BLOCK_SIZE = get_block_size(header);

    // Write reversed audio to file
    // TODO #8

    // 1. declare an array to store each block we read in
    int buffer[BLOCK_SIZE];

    // 2. iterate through the input file audio data

    // sets a pointer at the end of the file
    fseek(input, (-1 * BLOCK_SIZE), SEEK_END);
    int counter = 2;

    // start at the end and move backwards, be sure not to copy from the header
    while (ftell(input) >= HEADER_SIZE)
    {
        fread(&buffer, 1, BLOCK_SIZE, input);
        fwrite(&buffer, 1, BLOCK_SIZE, output);
        fseek(input, (-1 * counter * BLOCK_SIZE), SEEK_END);
        counter++;
    }

    fclose(input);
    fclose(output);
    return 0;
}

int check_format(WAVHEADER header)
{
    // TODO #4
    // If a .wav file, return 1
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 1;
    }

    // Otherwise
    return 0;
}

// Return an integer representing the block size of the given WAV file, in bytes
int get_block_size(WAVHEADER header)
{
    // TODO #7
    // block size = number of channels * bytes per sample
    int block_size = header.numChannels * header.bitsPerSample / 8;
    return block_size;
}