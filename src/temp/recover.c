#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Project Bitlocker Recovery Cracker
// By Salar Muhammadi

// Function Prototypes
void usage(void);

char *set_obj(int number);

// Type Define
typedef uint8_t BYTE;

// Global Variables

// Consts
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Check For Valid Argument
    if (argc != 2)
    {
        usage();
        return 1;
    }

    // Remember Filename
    char *fileName = argv[1];

    // Open Image File
    FILE *imageFile = fopen(fileName, "r");
    if (imageFile == NULL)
    {
        printf("Could not open %s.\n", fileName);
        return 1;
    }

    // Object Counter
    int curObj = 0;

    // Image Count Cap in this Function is 999
    char *curImgN = set_obj(curObj);
    if (curImgN == NULL)
    {
        printf("Insufficient Memory!\n");
        free(curImgN);
        fclose(imageFile);
        return 1;
    }
    // Status wether Write File is Open
    BYTE isWFOpen = 0;
    FILE *newImg;

    // Init Buffer
    BYTE *buffer = malloc(sizeof(BYTE) * BLOCK_SIZE);
    if (buffer == NULL)
    {
        printf("Insufficient Memory!\n");
        free(buffer);
        free(curImgN);
        fclose(imageFile);
        return 1;
    }
    // Read File Block Buffered byte By byte
    while (fread(buffer, 1, BLOCK_SIZE, imageFile) == BLOCK_SIZE)
    {
        // Check JPEG Signature
        if (buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255 && (buffer[3] > 223 && buffer[3] < 240))
        {
            if (!isWFOpen)
            {
                newImg = fopen(curImgN, "w");
                fwrite(buffer, 1, BLOCK_SIZE, newImg);
                isWFOpen = 1;
                continue;
            }
            else
            {
                fclose(newImg);
                curImg++;
                free(curImgN);
                curImgN = set_img(curImg);
                if (curImgN == NULL)
                {
                    printf("Insufficient Memory!\n");
                    free(curImgN);
                    free(buffer);
                    fclose(imageFile);
                    return 1;
                }
            }
        }
        if (isWFOpen)
        {
            fwrite(buffer, 1, BLOCK_SIZE, newImg);
        }
    }
    fclose(newImg);
    fclose(imageFile);
    free(buffer);
    free(curImgN);
    return 0;
}

// Print Usage
void usage(void)
{
    printf("Usage: ./recover IMAGE\n");
}

// Set JPEG Pattern Name
char *set_img(int number)
{
    char *str = malloc(8 * sizeof(char));
    if (number < 10)
    {
        sprintf(str, "00%i.jpg", number);
    }
    else if (number < 100)
    {
        sprintf(str, "0%i.jpg", number);
    }
    else
    {
        sprintf(str, "%i.jpg", number);
    }
    return str;
}