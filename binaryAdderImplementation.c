#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Helper functions
int checkXORGate(int a, int b);
bool isBinary(int a);
void testHalfAdder();
void testFullAdder();

// Half and full adder
int *halfAdder(int a, int b);
int *fullAdder(int a, int b, int carryIn);

// Test function
int main()
{
    // Half adder test
    testHalfAdder();
    // Full Adder Test
    testFullAdder();
}

int *halfAdder(int a, int b)
{
    int *adder = (int *)malloc(2 * sizeof(int)); // Allocating memory on the heap
    if (!adder)
        return NULL; // Memory allocation check
    // The sum of a and b
    adder[0] = checkXORGate(a, b);
    // The carry from adding a and b
    adder[1] = a + b == 2 ? 1 : 0;
    return adder;
}

int *fullAdder(int a, int b, int carryIn)
{
    int *adder = (int *)malloc(2 * sizeof(int)); // Allocating memory on the heap
    if (!adder)
        return NULL; // Memory allocation check
    int *halfAddition = halfAdder(a, b);
    // The sum
    adder[0] = checkXORGate(halfAddition[0], carryIn);
    // The carry out
    adder[1] = (halfAddition[1]) | (carryIn & halfAddition[0]);
    return adder;
}

int checkXORGate(int a, int b)
{
    return a == b ? 0 : 1;
}

bool isBinary(int a)
{
    return (a == 0 || a == 1);
}

void testHalfAdder()
{
    printf("Lets do half adder.\n");
    int a, b;
    printf("Enter a number: ");
    scanf("%d", &a);
    printf("Enter another number: ");
    scanf("%d", &b);
    // Discard non-binary numbers
    if (isBinary(a) && isBinary(b))
    {
        int *halfAddition = halfAdder(a, b);
        int sum = halfAddition[0];
        int carry = halfAddition[1];
        printf("The sum of %d and %d is %d with %d as carry\n", a, b, halfAddition[0], halfAddition[1]);
    }
    else
    {
        printf("Either one or both of you numbers are not binary.\n");
    }
}

void testFullAdder()
{
    printf("\nA B Cin | Sum Cout\n");
    printf("------------------\n");
    for (int a = 0; a <= 1; a++)
    {
        for (int b = 0; b <= 1; b++)
        {
            for (int carryIn = 0; carryIn <= 1; carryIn++)
            {
                int *result = fullAdder(a, b, carryIn);
                if (result)
                {
                    printf("%d %d  %d  |  %d   %d\n", a, b, carryIn, result[0], result[1]);
                    free(result); // Free memory
                }
            }
        }
    }
}