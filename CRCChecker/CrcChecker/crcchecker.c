//------------------------------------------------------------------

// University of Central Florida

// CIS3360 - Summer 2015

// Program Author: Angelo Montagner

//------------------------------------------------------------------
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convertHextoBin(char *hexaDecimal);
void binarytoHex(char *binary);
void CrcChecker();

char binary[50000][10];
char strBinary[50000];
char input[50000];
char Lowercaseinput[50000];
char CheckSum[50000];
char testinput[50000];
char LastString[50000];
char *polynomial;
int length=0;
int error=0;
int tempcounter=0;
char* endptr;
int val =0;

int main(int argc, char *argv[])
{
    int i=0,e=0;
    int Linecounter=0;
    //polynomial="1101";
    polynomial="1010010101000";

    strcpy(input, argv[2]);

    printf("CRC Checker by Angelo Montagner \n\n");

    if (strcmp(argv[1], "c") == 0)
    {
        printf("Mode of operation: calculate\n");

        printf("The input string (hex): %s \n", input);

        for(i = 0; i<strlen(input); i++)
        {
            Lowercaseinput[i] = tolower(input[i]);
        }

        convertHextoBin(Lowercaseinput);

        printf("The input string (bin): " );

        for(i=0; i<strlen(input)*4; i++)
        {
            printf("%c" , strBinary[i]);

            Linecounter++;
            if(Linecounter == 4)
            {
                Linecounter = 0;
                printf(" ");
            }

        }

        printf("\n");

        printf("\n");

        printf("The polynomial that was used (binary bit string): ");

        for(i=0; i<strlen(polynomial); i++)
        {
            printf("%c" , polynomial[i]);

            Linecounter++;
            if(Linecounter == 4)
            {
                Linecounter = 0;
                printf(" ");
            }

        }

        printf("\n");

        printf("We will append 12 zeroes at the end of the binary input.\n");

        printf("\n");

        printf("The binary string difference after each XOR step of the CRC calculation: \n");

        length = strlen(strBinary);

        for(i=strlen(strBinary); i<(strlen(polynomial) + length) - 1; i++)
        {
            strBinary[i]='0';
        }

        //Calculate(strBinary,polynomial);
        CrcChecker();

        printf("\n");

        Linecounter=0;

        if (strlen(CheckSum) % 4 == 0)
        {
            printf("The computed CRC for the input is: ");

            for(i=0; i<strlen(CheckSum); i++)
            {
                printf("%c" , CheckSum[i]);

                Linecounter++;
                if(Linecounter == 4)
                {
                    Linecounter = 0;
                    printf(" ");
                }

            }
            printf("(bin) = ");
            binarytoHex(CheckSum);
            printf("\n");
        }
        else
        {

            Linecounter=0;

            printf("The computed CRC for the input is: 0");

            for(i=0; i<strlen(CheckSum); i++)
            {
                printf("%c" , CheckSum[i]);

                Linecounter++;
                if(Linecounter == 4)
                {
                    Linecounter = 0;
                    printf(" ");
                }

            }
            printf("(bin) = ");
            binarytoHex(CheckSum);
            printf("\n");
        }



        printf("\n");
    }
    else if (strcmp(argv[1], "v") == 0)
    {
        printf("Mode of operation: verify\n");

        printf("The input string (hex): %s \n", input);

        for(i = 0; i<strlen(input); i++)
        {
            Lowercaseinput[i] = tolower(input[i]);
        }

        convertHextoBin(Lowercaseinput);

        printf("The input string (bin): " );

        for(i=0; i<strlen(input)*4; i++)
        {
            printf("%c" , strBinary[i]);

            Linecounter++;
            if(Linecounter == 4)
            {
                Linecounter = 0;
                printf(" ");
            }

        }

        printf("\n");

        printf("\n");

        printf("The polynomial that was used (binary bit string): ");

        for(i=0; i<strlen(polynomial); i++)
        {
            printf("%c" , polynomial[i]);

            Linecounter++;
            if(Linecounter == 4)
            {
                Linecounter = 0;
                printf(" ");
            }

        }





        printf("\n");


        printf("The 12-bit CRC observed at the end of the input: ");

        Linecounter=0;
        tempcounter=0;
        for(i=strlen(strBinary) - 12; i<strlen(strBinary); i++)
        {
            printf("%c" , strBinary[i]);
            LastString[tempcounter]=strBinary[i];
            tempcounter++;

            Linecounter++;
            if(Linecounter == 4)
            {
                Linecounter = 0;
                printf(" ");
            }

        }

        printf("(bin) = ");
        binarytoHex(LastString);
        printf("\n");

        //printf(" (bin) = (hex)\n");

        length = strlen(strBinary);

        for(i=strlen(strBinary) - 12; i<strlen(strBinary); i++)
        {
            strBinary[i]='0';
        }

        length = strlen(strBinary)-12;

        //printf("Before Checksum : %s\n", strBinary);

        CrcChecker();

        printf("\n");


        printf("The binary string difference after each XOR step of the CRC calculation: \n\n");

        Linecounter=0;

        if (strlen(CheckSum) % 4 == 0)
        {
            printf("The computed CRC for the input is: ");

            for(i=0; i<strlen(CheckSum); i++)
            {
                printf("%c" , CheckSum[i]);

                Linecounter++;
                if(Linecounter == 4)
                {
                    Linecounter = 0;
                    printf(" ");
                }

            }



            printf("(bin) = ");
            binarytoHex(CheckSum);
            printf("\n");
        }
        else
        {

            Linecounter=0;

            printf("The computed CRC for the input is: 0");

            for(i=0; i<strlen(CheckSum); i++)
            {
                printf("%c" , CheckSum[i]);

                Linecounter++;
                if(Linecounter == 4)
                {
                    Linecounter = 0;
                    printf(" ");
                }

            }

            printf("(bin) = ");
            binarytoHex(CheckSum);

            printf("\n");
        }

        printf("\n");

        if(strcmp(CheckSum,LastString) == 0)
        {

            printf("Did the CRC check pass? (Yes or No): Yes\n");

        }
        else
        {

            printf("Did the CRC check pass? (Yes or No): No\n");
        }

    }



}


void convertHextoBin(char *hexaDecimal)
{

    long int i=0;
    char FourPlaces[5];

    while(hexaDecimal[i])
    {
        switch(hexaDecimal[i])
        {
        case '0':
            strcpy(FourPlaces, "0000");
            break;
        case '1':
            strcpy(FourPlaces, "0001");
            break;
        case '2':
            strcpy(FourPlaces, "0010");
            break;
        case '3':
            strcpy(FourPlaces, "0011");
            break;
        case '4':
            strcpy(FourPlaces, "0100");
            break;
        case '5':
            strcpy(FourPlaces, "0101");
            break;
        case '6':
            strcpy(FourPlaces, "0110");
            break;
        case '7':
            strcpy(FourPlaces, "0111");
            break;
        case '8':
            strcpy(FourPlaces, "1000");
            break;
        case '9':
            strcpy(FourPlaces, "1001");
            break;
        case 'a':
            strcpy(FourPlaces, "1010");
            break;
        case 'b':
            strcpy(FourPlaces, "1011");
            break;
        case 'c':
            strcpy(FourPlaces, "1100");
            break;
        case 'd':
            strcpy(FourPlaces, "1101");
            break;
        case 'e':
            strcpy(FourPlaces, "1110");
            break;
        case 'f':
            strcpy(FourPlaces, "1111");
            break;
        default:
            return 0;
        }
        i++;
        strcat(strBinary, FourPlaces);
    }
}


void CrcChecker()
{
    int i,p;
    int c;

    for(i=0; i<strlen(polynomial); i++)
        CheckSum[i]= strBinary[i];

    do
    {
        if(CheckSum[0]=='1')
        {
            for(c = 1; c < strlen(polynomial); c++)
            {
                if (CheckSum[c] == polynomial[c])
                {
                    CheckSum[c] = '0';
                }else CheckSum[c] = '1';

            }
        }

        for(p=0; p<strlen(polynomial)-1; p++)
            CheckSum[p]=CheckSum[p+1];

        CheckSum[p]=strBinary[i++];

    }
    while(i<=length+strlen(polynomial)-1);
}



void binarytoHex(char *binary)
{
    long int dec;
    long int rm;
    long int qt;
    int i=1,j,temp;
    char hx[50000];

    dec = strtol (binary,NULL,2);

    qt = dec;

    while(qt!=0)
    {
        temp = qt % 16;

        if( temp < 10)
        {
            temp =temp + 48;
        }else temp = temp + 55;

        hx[i++]= temp;
        qt = qt / 16;
    }

    for(j = i -1 ; j> 0; j--)
        printf("%c",hx[j]);

    printf(" (hex)");


}

