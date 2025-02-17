#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

// Helper functions
bool isBinary(int num);
int xorGate(int a, int b);

// Half and full adder
int *halfAdder(int a, int b);
int *fullAdder(int a, int b, int carryIn);

// Function to perform four-bit binary addition
int *fourBitAdder(int a, int b);

// Main function to test the four-bit adder
// Takes two binary numbers as input
// Performs addition using four full adder operations in sequence from LSB to MSB
int main()
{
    printf("Let's perform addition for two four-bit binary numbers.\n");
    int num1, num2;
    printf("Enter a 4-bit binary number (e.g., 1011): ");
    scanf("%d", &num1);
    printf("Enter another 4-bit binary number (e.g., 0101): ");
    scanf("%d", &num2);

    // Perform addition only if both inputs are valid binary numbers
    if (isBinary(num1) && isBinary(num2))
    {
        int *fourBitAddition = fourBitAdder(num1, num2);
        printf("The sum of %d and %d is %d with %d as carry\n", num1, num2, fourBitAddition[0], fourBitAddition[1]);
    }
    else
    {
        printf("One or both of the entered numbers are not valid 4-bit binary numbers.\n");
        // Indicate that no binary addition operation was performed
        return -1;
    }
    return 0;
}

// Validates if all the given number has all binary digits (only 0s and 1s)
bool isBinary(int num)
{
    int noOfDigits = 0;
    while (num > 0)
    {
        int digit = num % 10; // Extract the last digit
        if ((digit != 0 && digit != 1) || noOfDigits >= 4)
        {
            return false; // Not a valid binary digit OR too many digits
        }

        num /= 10;    // Remove the last digit
        noOfDigits++; // Count this digit
    }
    return true;
}

// Carries out XOR operation for two given bits.
// Returns 1 if the two input bits are different, and 0 if they are the same.
int xorGate(int a, int b)
{
    return a == b ? 0 : 1;
}

// Carries out half addition for two given bits.
// Returns an array of two integers. The first element is the sum of the two input bits, and the second is the carry.
int *halfAdder(int a, int b)
{
    int *adder = (int *)malloc(2 * sizeof(int)); // Allocating memory on the heap
    if (!adder)
        return NULL; // Memory allocation check
    // The sum of a and b
    adder[0] = xorGate(a, b);
    // The carry from adding a and b
    adder[1] = a + b == 2 ? 1 : 0;
    return adder;
}

// Carries out full addition for two given bits and a carryin.
// Returns an array of two integers. The first element is the sum of the three input bits (two bits and a carry-in), and the second is the carry-out.
int *fullAdder(int a, int b, int carryIn)
{
    int *adder = (int *)malloc(2 * sizeof(int)); // Allocating memory on the heap
    if (!adder)
        return NULL; // Memory allocation check
    int *halfAddition = halfAdder(a, b);
    // The sum
    adder[0] = xorGate(halfAddition[0], carryIn);
    // The carry out
    adder[1] = (halfAddition[1]) | (carryIn & halfAddition[0]);
    return adder;
}

// Carries out addition for four bit binary numbers.
// Returns sum and a carry out.
int *fourBitAdder(int a, int b)
{
    int *adder = (int *)malloc(2 * sizeof(int)); // Allocating memory on the heap
    if (!adder)
        return NULL; // Memory allocation check
    adder[0] = 0;    // Initializes the 4-bit sum of a and b.
    adder[1] = 0;    // Initializes the carry-out of the 4-bit addition of a and b.
    int pos = 0;     // Stores the current digit's position (power of 10).
    // Carry out four bit addition (LSB to MSB)
    while (a > 0 || b > 0 || pos < 4)
    {
        int lastDigitA = a % 10;
        int lastDigitB = b % 10;
        int *fullAddition = fullAdder(lastDigitA, lastDigitB, adder[1]); // Performs full addition of the current digits and the carry-in.
        adder[0] += fullAddition[0] * pow(10, pos);                      // Adds the current digit's sum to the overall sum.
        adder[1] = fullAddition[1];                                      // Updates the carry-out for the next digit's addition.
        a /= 10;
        b /= 10;
        pos++; // Increments the digit position.
    }
    return adder;
}