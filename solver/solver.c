#include <stdio.h>
#include <stdbool.h>

#define SIZE 9

bool is_valid(int board[SIZE][SIZE], int row, int col, int num) {
    for (int x = 0; x < SIZE; x++) {
        if (board[row][x] == num) return false; 
        if (board[x][col] == num) return false;
    }

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) return false;
        }
    }

    return true;
}

bool solve_sudoku(int board[SIZE][SIZE]) {
    int row = -1, col = -1;
    bool isEmpty = true;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                row = i;
                col = j;
                isEmpty = false;
                break;
            }
        }
        if (!isEmpty) break;
    }

    if (isEmpty) return true;

    for (int num = 1; num <= SIZE; num++) {
        if (is_valid(board, row, col, num)) {
            board[row][col] = num;
            if (solve_sudoku(board)) return true;
            board[row][col] = 0;
        }
    }

    return false;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./solver <filename>\n");
        return 1;
    }

    char *input_filename = argv[1];
    char output_filename[255];
    sprintf(output_filename, "%s.result", input_filename);

    FILE *input_file = fopen(input_filename, "r");
    if (!input_file) {
        perror("Failed to open input file");
        return 1;
    }

    int board[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            char c;
            fscanf(input_file, " %c", &c);
            if (c == '.') {
                board[i][j] = 0;
            } else {
                board[i][j] = c - '0';
            }
        }
    }
    fclose(input_file);

    if (solve_sudoku(board)) {
        FILE *output_file = fopen(output_filename, "w");
        if (!output_file) {
            perror("Failed to open output file");
            return 1;
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                fprintf(output_file, "%d", board[i][j]);
                if (j % 3 == 2 && j != SIZE - 1) fprintf(output_file, " ");
            }
            fprintf(output_file, "\n");
            if (i % 3 == 2 && i != SIZE - 1) fprintf(output_file, "\n");
        }
        fclose(output_file);
    } else {
        printf("No solution exists.\n");
    }

    return 0;
}