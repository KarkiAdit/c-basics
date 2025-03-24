#include <stdio.h>

int read_input() {
    printf("Step 1: Reading input...\n");
    return 10;
}

int process_data() {
    printf("Step 2: Processing data...\n");
    return 20;
}

int generate_output() {
    printf("Step 3: Generating output...\n");
    return 30;
}

void pipeline(int input, int processed, int output) {
    printf("Inside pipeline:\n");
    printf("  Input value: %d\n", input);
    printf("  Processed value: %d\n", processed);
    printf("  Output value: %d\n", output);
}

int main() {
    pipeline(read_input(), process_data(), generate_output());
    return 0;
}
