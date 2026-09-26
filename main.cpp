#include <iostream>
using namespace std;

void printBoard(int **board){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            cout << board[i][j];
        }
        cout << endl;
    }
    cout <<endl;
}

bool walk(int** board, int row, int col){
    if((row < 0 || 8 <= row) ||
       (col < 0 || 8 <= col)){
        return false;
    }
    if(board[row][col] == 1){
        return false;
    }
    return true;
}

bool knightTour(int** board, int row, int col, int step){
    //cout<< step  << endl;
    int moves[8][2] = {{-2,-1}, {-2,1}, {2,-1}, {2,1}, {-1,-2}, {-1,2}, {1,-2}, {1,2}};
    if(step == 64){
        return true;
    }
    for(int i = 0; i < 8; i++){
        int next_row = row + moves[i][0];
        int next_col = col + moves[i][1];

        if(walk(board, next_row, next_col)){
            board[next_row][next_col] = 1;
            if(knightTour(board,  next_row, next_col, step + 1)){
                return true;
            }
            board[next_row][next_col] = 0;
        }
    }
    return false;
}


int main(void){
    int** board = new int*[8];
    for(int i = 0; i < 8; i++){
        board[i] = new int[8];
        for(int j = 0; j < 8; j ++){
            board[i][j] = 0;
        }
    }
    board[0][6] = 1;
    printBoard(board);

    knightTour(board, 0, 6, 1);
    printBoard(board);

    for(int i = 0; i < 8; i++){
        delete[] board[i];
    }
    delete[] board;

    return 0;
}