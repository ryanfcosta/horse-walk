#include <stdio.h>
#include <stdlib.h>

void printBoard(int **board){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
                    printf("%d ", board[i][j]);
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
    if(board[row][col] == 1){
        return 0;
    }
    return 1;
}

int knightTour(int** board, int row, int col, int step){
    int moves[8][2] = {{-2,-1}, {-2,1}, {2,-1}, {2,1}, {-1,-2}, {-1,2}, {1,-2}, {1,2}};
    if(step == 64){
        return 1;
    }
    for(int i = 0; i < 8; i++){
        int next_row = row + moves[i][0];
        int next_col = col + moves[i][1];

        if(walk(board, next_row, next_col)){
            board[next_row][next_col] = 1;
            if(knightTour(board,  next_row, next_col, step + 1)){
                return 1;
            }
            board[next_row][next_col] = 0;
        }
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