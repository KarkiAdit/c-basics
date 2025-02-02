#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Functions for AND, NAND, and XOR gates
int checkAndGate(int a, int b);
int checkNAndGate(int a, int b);
int checkXORGate(int a, int b);

// Functions for Hexadecimal, Octal, and Binary to Deciaml conversions
int hexToDec(char num[]);
int octToDec(int num);
int binToDec(int num);

// Functions for Decimal to Hexadecimal, Octal, and Binary conversions
void decToHex(int num, char hexStr[]);
int decToOct(int num);
int decToBin(int num);

int main()
{
    // The logic gates test
    int a[5] = {1, 0, 1, 0, 1};
    int b[5] = {0, 1, 1, 0, 0};
    // The AND gate check
    for (int i = 0; i < 5; i++)
    {
        printf("\n %d AND %d = %d", a[i], b[i], checkAndGate(a[i], b[i]));
    };
    printf("\n");
    // The NAND gate check
    for (int i = 0; i < 5; i++)
    {
        printf("\n %d NAND %d = %d", a[i], b[i], checkNAndGate(a[i], b[i]));
    };
    printf("\n");
    // The XOR gate check
    for (int i = 0; i < 5; i++)
    {
        printf("\n %d XOR %d = %d", a[i], b[i], checkXORGate(a[i], b[i]));
    };

    // The number system conversion tests
    printf("\n");
    printf("\n %s", "Other number systems to decimal system");
    printf("\n The decimal equivalent of hexadecimal no. %s is %d", "A5CD", hexToDec("A5CD"));
    printf("\n The decimal equivalent of octal no. %d is %d", 777, octToDec(777));
    printf("\n The decimal equivalent of binary no. %d is %d", 1110, binToDec(1110));
    printf("\n");
    printf("\n %s", "Decimal system to other number systems");
    int decimal = 555;
    char hexStr[20];
    decToHex(decimal, hexStr);
    printf("\n The hexadecimal equivalent of decimal no. %d is %s", decimal, hexStr);
    printf("\n The octal equivalent of decimal no. %d is %d", decimal, decToOct(decimal));
    printf("\n The binary equivalent of decimal no. %d is %d", decimal, decToBin(decimal));
    return 0;
}

int checkAndGate(int a, int b)
{
    if (a == 1 && b == 1)
        return 1;
    else
        return 0;
}

int checkNAndGate(int a, int b)
{
    return !checkAndGate(a, b);
}

int checkXORGate(int a, int b)
{
    if (a == b)
        return 0;
    else
        return 1;
}

int hexToDec(char num[])
{
    int dec = 0;
    int len = strlen(num);
    for (int i = 0; i < len; i++)
    {
        char curr = num[i];
        curr = toupper(curr);
        int hexValue;
        if (curr >= '0' && curr <= '9')
        {
            hexValue = curr - '0'; // '0' to '9' are just their ASCII values minus '0'
        }
        else if (curr >= 'A' && curr <= 'F')
        {
            hexValue = curr - 'A' + 10; // 'A' to 'F' correspond to 10 to 15
        }
        else
        {
            return -1; // Invalid hex character
        }
        // Update decimal value, each digit in hex represents a power of 16
        dec = dec + hexValue * (pow(16, len - i - 1));
    }
    return dec;
}

int octToDec(int num)
{
    if (num < 0)
        return -1; // Invalid for negative numbers
    int dec = 0;
    int p = 0; // Represents the power of 8
    while (num > 0)
    {
        int lastDigit = num % 10;
        if (lastDigit > 7)
            return -1; // Invalid for digits bigger than 7
        dec += lastDigit * pow(8, p);
        p += 1;
        num /= 10;
    }
    return dec;
}

int binToDec(int num)
{
    if (num < 0)
        return -1; // Invalid for negative numbers
    int dec = 0;
    int p = 0; // Represents the power of 2
    while (num > 0)
    {
        int lastDigit = num % 10;
        if (lastDigit > 1)
            return -1; // Invalid for digits bigger than 1
        dec += lastDigit * pow(2, p);
        p += 1;
        num /= 10;
    }
    return dec;
}

void decToHex(int num, char hexStr[])
{
    if (num < 0)
    {
        hexStr[0] = '\0'; // Invalid case
        return;
    }
    int i = 0;
    if (num == 0)
    {
        hexStr[i++] = '0';
        hexStr[i] = '\0';
        return;
    }
    while (num > 0)
    {
        int hexValue = num % 16;
        if (hexValue < 10)
            hexStr[i++] = '0' + hexValue;
        else
            hexStr[i++] = 'A' + (hexValue - 10);

        num /= 16;
    }
    hexStr[i] = '\0';
    // Reverse the string since we computed digits in reverse order
    int start = 0, end = i - 1;
    while (start < end)
    {
        char temp = hexStr[start];
        hexStr[start] = hexStr[end];
        hexStr[end] = temp;
        start++;
        end--;
    }
}

int decToOct(int num)
{
    if (num < 0)
        return -1; // Invalid for negative numbers
    int oct = 0;
    int p = 0; // Represents the power of 10
    while (num > 0)
    {
        int lastDigit = num % 8;
        oct += lastDigit * pow(10, p);
        p += 1;
        num /= 8;
    }
    return oct;
}

int decToBin(int num)
{
    if (num < 0)
        return -1; // Invalid for negative numbers
    int bin = 0;
    int p = 0; // Represents the power of 10
    while (num > 0)
    {
        int lastDigit = num % 2;
        bin += lastDigit * pow(10, p);
        p += 1;
        num /= 2;
    }
    return bin;
}