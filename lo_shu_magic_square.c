#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 3

// Check if a square is a Lo Shu Magic Square
bool isLoShuMagicSquare(int square[SIZE][SIZE], bool print_errors) {
    bool is_magic_square = true;
    
    // Check if numbers 1-9 are used exactly once
    int used[10] = {0}; 
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (square[i][j] < 1 || square[i][j] > 9) return false;
            used[square[i][j]]++;
        }
    }
    for (int i = 1; i <= 9; i++) {
        if (used[i] != 1) return false;
    }

    // Calculate the sum target sum
    int target_sum = 0;
    for (int j = 0; j < SIZE; j++) {
        target_sum += square[0][j];
    }

    // Check rows
    for (int i = 1; i < SIZE; i++) {
        int row_sum = 0;
        for (int j = 0; j < SIZE; j++) {
            row_sum += square[i][j];
        }
        if (row_sum != target_sum){  
            if (print_errors){
                printf("Row %d sum is %d, expected %d\n", i+1, row_sum, target_sum);
            }
            is_magic_square = false;
        }
    }

    // Check columns
    for (int j = 0; j < SIZE; j++) {
        int col_sum = 0;
        for (int i = 0; i < SIZE; i++) {
            col_sum += square[i][j];
        }
        if (col_sum != target_sum){
            if (print_errors){
                printf("Column %d sum is %d, expected %d\n", j, col_sum, target_sum);
            }
            is_magic_square = false;
        }
    }

    // Check main diagonal
    int diag_sum = 0;
    for (int i = 0; i < SIZE; i++) {
        diag_sum += square[i][i];
    }
    if (diag_sum != target_sum){
        if (print_errors){
            printf("Main diagonal sum is %d, expected %d\n", diag_sum, target_sum);
        }
        is_magic_square = false;
    }

    // Check other diagonal
    diag_sum = 0;
    for (int i = 0; i < SIZE; i++) {
        diag_sum += square[i][SIZE-1-i];
    }
    if (diag_sum != target_sum){
        if (print_errors){
            printf("Other diagonal sum is %d, expected %d\n", diag_sum, target_sum);
        }
        is_magic_square = false;
    }

    return is_magic_square;
}

// Print Square
void printSquare(int square[SIZE][SIZE]) {
    printf("[%d %d %d]\n", square[0][0], square[0][1], square[0][2]);
    printf("[%d %d %d]\n", square[1][0], square[1][1], square[1][2]);
    printf("[%d %d %d]\n", square[2][0], square[2][1], square[2][2]);
}

int main() {
    // Part 1
    printf("Part 1: Testing known squares\n\n");
    
    // A valid Lo Shu Magic Square
    int valid_square[SIZE][SIZE] = {
        {4, 9, 2},
        {3, 5, 7},
        {8, 1, 6}
    };
    
    // An invalid square
    int invalid_square[SIZE][SIZE] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Test valid squares
    printf("Testing valid magic square:\n");
    printSquare(valid_square);
    printf("Is it a Lo Shu Magic Square? %s\n\n", 
           isLoShuMagicSquare(valid_square, true) ? "Yes" : "No");

    printf("Testing invalid square:\n");
    printSquare(invalid_square);
    printf("Is it a Lo Shu Magic Square? %s\n\n", 
           isLoShuMagicSquare(invalid_square, true) ? "Yes" : "No");

    // Part 2
    printf("Part 2: Generating random squares until finding a Lo Shu Magic Square\n\n");
    srand(time(NULL));
    
    int count = 0;
    int random_square[SIZE][SIZE];
    bool found = false;
    
    while (!found) {
        // Create array of numbers 1-9
        int numbers[9] = {1,2,3,4,5,6,7,8,9};
        int remaining = 9;
        
        // Randomly place numbers into square
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                int index = rand() % remaining;
                random_square[i][j] = numbers[index];
                
                // Remove used number by moving last number to this position
                numbers[index] = numbers[remaining-1];
                remaining--;
            }
        }
        
        count++;
        
        // Check if it's a Lo Shu Magic Square
        if (isLoShuMagicSquare(random_square, false)) {
            found = true;
            printf("Found Lo Shu Magic Square after testing %d squares!\n\n", count);
            printSquare(random_square);
        }
    }
    return 0;
} 