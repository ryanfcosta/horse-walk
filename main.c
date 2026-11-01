#include <stdio.h>
#include <stdlib.h>

const int MOVES[8][2] = {
    {-2,-1}, {-2,1}, {2,-1}, {2,1},
    {-1,-2}, {-1,2}, {1,-2}, {1,2}
};

typedef struct {
    int row;
    int col;
    int degree;
} Move;

void printBoard(int **board){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
                    printf("%2d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int walk(int** board, int row, int col){
    if((row < 0 || 8 <= row) ||
       (col < 0 || 8 <= col)){
        return 0;
    }
    if(board[row][col] != 0){
        return 0;
    }
    return 1;
}

int getDegree(int ** board, int row, int col){
    int count = 0;
    for(int i = 0; i < 8; i++){
        if(walk(board, row + MOVES[i][0], col + MOVES[i][1])){
            count ++;
        }
    }
    return count;
}

int knightTour(int** board, int row, int col, int step){
    if(step == 64){
        return 1;
    }

    Move validMoves[8];
    int count = 0;
    
    for(int i = 0; i < 8; i++){
        int next_row = row + MOVES[i][0];
        int next_col = col + MOVES[i][1];

        if (walk(board, next_row, next_col)){
            validMoves[count].row = next_row;
            validMoves[count].col = next_col;
            validMoves[count].degree = getDegree(board, next_row, next_col);
            count++;
        }
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (validMoves[j].degree < validMoves[i].degree) {
                Move temp = validMoves[i];
                validMoves[i] = validMoves[j];
                validMoves[j] = temp;
            }
        }
    }

    for (int i = 0; i < count; i++) {
        int next_row = validMoves[i].row;
        int next_col = validMoves[i].col;

        board[next_row][next_col] = step + 1;
        printBoard(board);

        if (knightTour(board, next_row, next_col, step + 1)) {
            return 1;
        }

        printBoard(board);
        board[next_row][next_col] = 0;
    }

    return 0;
}


int main(void){
    int** board = (int**)malloc(sizeof(int*) * 8);
    for(int i = 0; i < 8; i++){
        board[i] = (int*)malloc(sizeof(int) * 8);
        for(int j = 0; j < 8; j ++){
            board[i][j] = 0;
        }
    }
    board[0][6] = 1;
    printBoard(board);

    knightTour(board, 0, 6, 1);
    printBoard(board);

    for(int i = 0; i < 8; i++){
        free(board[i]);
    }
    free(board);

    return 0;
}