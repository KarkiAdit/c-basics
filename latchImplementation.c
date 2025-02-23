#include <stdio.h>

typedef struct
{
    int Q;
    int Qn;
} BasicSRLatch; // The Basic SR Latch definition

// The input states for truth table
const int INPUT_STATES[][2] = {
    {0, 0},
    {1, 0},
    {0, 1},
    {1, 1},
};

// All Latch update functions
void updateSRLatch(BasicSRLatch *srLatch, int S, int R);
void updateGatedSRLatch(BasicSRLatch *srLatch, int S, int R, int E);
void updateDLatch(BasicSRLatch *srLatch, int D);
void updateGatedDLatch(BasicSRLatch *srLatch, int D, int E);

// Latch Truth table test functions
void testSRLatch();
void testGatedSRLatch();
void testDLatch();
void testGatedDLatch();

int main()
{
    // Print truth tables for every latch.
    testSRLatch();
    testGatedSRLatch();
    testDLatch();
    testGatedDLatch();
    return 0;
}

void updateSRLatch(BasicSRLatch *srLatch, int S, int R)
{
    // Both S and R equals 1 is an invalid state.
    if (S == 1 && R == 1)
    {
        printf("S = 1 and R = 1 is an invalid state. State is unchanged.\n");
        return;
    }
    // SR logic for the valid states.
    if (S == 1 && R == 0)
    {
        srLatch->Q = 1;
        srLatch->Qn = 0;
        printf("Latch set. \n");
        return;
    }
    else if (S == 0 && R == 1)
    {
        srLatch->Q = 0;
        srLatch->Qn = 1;
        printf("Latch resetted.\n");
        return;
    }
    // Both S and R equals 0 retains state.
    printf("For S = 0 and R = 0 state is unchanged.\n");
};

void updateGatedSRLatch(BasicSRLatch *srLatch, int S, int R, int E)
{
    // If E is low, retain the current state.
    if (E == 0)
    {
        printf("Enable (E) is 0. Latch state retained.\n");
        return;
    };
    // Carry SR logic for a high E.
    updateSRLatch(srLatch, S, R);
};

void updateDLatch(BasicSRLatch *srLatch, int D)
{
    // Carry out the SR logic with lowed Data input as Set.
    updateSRLatch(srLatch, !D, D);
};

void updateGatedDLatch(BasicSRLatch *srLatch, int D, int E)
{
    // If Enable bit is set, retain the current state.
    if (E == 0)
    {
        printf("Enable (E) is 0. Latch state retained.\n");
        return;
    };
    // Carry D Latch logic if Enable bit is high.
    updateDLatch(srLatch, D);
};

void testSRLatch()
{
    BasicSRLatch srLatch = {0, 1}; // The previous states
    printf("The initial latch state: Q = %d, Qn = %d\n", srLatch.Q, srLatch.Qn);
    for (int i = 0; i < 4; i++)
    {
        int prevQ = srLatch.Q;
        int prevQn = srLatch.Qn;
        int S = INPUT_STATES[i][0];
        // Print the previous states
        printf("Prev Q = %d, Prev Qn = %d \n", prevQ, prevQn);
        int R = INPUT_STATES[i][1];
        updateSRLatch(&srLatch, S, R);
        // Print the truth values for current set/reset
        printf("S | R | Q | Qn\n");
        printf("%d | %d | %d | %d\n\n", S, R, srLatch.Q, srLatch.Qn);
    }
}

void testGatedSRLatch()
{
    BasicSRLatch gatedSRLatch = {0, 1}; // The previous states
    int E;                              // The enable bit
    printf("The initial latch state: Q = %d, Qn = %d\n", gatedSRLatch.Q, gatedSRLatch.Qn);
    for (E = 0; E <= 1; E++)
    {
        printf("When Enable (E) is %d.\n", E);
        for (int i = 0; i < 4; i++)
        {
            int prevQ = gatedSRLatch.Q;
            int prevQn = gatedSRLatch.Qn;
            int S = INPUT_STATES[i][0];
            // Print the previous states
            printf("Prev Q = %d, Prev Qn = %d \n", prevQ, prevQn);
            int R = INPUT_STATES[i][1];
            updateGatedSRLatch(&gatedSRLatch, S, R, E);
            // Print the truth values for current set/reset
            printf("S | R | Q | Qn\n");
            printf("%d | %d | %d | %d\n\n", S, R, gatedSRLatch.Q, gatedSRLatch.Qn);
        }
    }
}

void testDLatch()
{
    BasicSRLatch dLatch = {0, 1}; // The previous states
    int D;                        // The Data input
    printf("The initial latch state: Q = %d, Qn = %d\n", dLatch.Q, dLatch.Qn);
    for (D = 0; D <= 1; D++)
    {
        printf("When the Data input is %d.\n", D);
        int prevQ = dLatch.Q;
        int prevQn = dLatch.Qn;
        // Print the previous states
        printf("Prev Q = %d, Prev Qn = %d \n", prevQ, prevQn);
        int S = !D;
        int R = D;
        updateDLatch(&dLatch, D);
        // Print the truth values for current set/reset
        printf("S | R | Q | Qn\n");
        printf("%d | %d | %d | %d\n\n", S, R, dLatch.Q, dLatch.Qn);
    }
}

void testGatedDLatch()
{
    BasicSRLatch gatedDLatch = {0, 1}; // The previous states
    int E;                             // The enable bit
    int D;                             // The Data input
    printf("The initial latch state: Q = %d, Qn = %d\n", gatedDLatch.Q, gatedDLatch.Qn);
    for (E = 0; E <= 1; E++)
    {
        for (D = 0; D <= 1; D++)
        {
            printf("When Enable (E) is %d.\n", E);
            printf("When the Data input is %d.\n", D);
            int prevQ = gatedDLatch.Q;
            int prevQn = gatedDLatch.Qn;
            // Print the previous states
            printf("Prev Q = %d, Prev Qn = %d \n", prevQ, prevQn);
            int S = !D;
            int R = D;
            updateGatedDLatch(&gatedDLatch, D, E);
            // Print the truth values for current set/reset
            printf("S | R | Q | Qn\n");
            printf("%d | %d | %d | %d\n\n", S, R, gatedDLatch.Q, gatedDLatch.Qn);
        }
    }
}