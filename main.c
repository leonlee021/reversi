#include "reversi.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printOutBoard(char board[][26],int n){
    char alphabets[] = {'a','b','c','d','e','f','g','h','i','j',
                        'k','l','m','n','o','p','q','r','s','t',
                        'u','v','w','x','y','z','\0'};
    //printf("\n");
    printf("  ");
        for (int i=0;i<n;i++){
            printf("%c",alphabets[i]);
        }
        printf("\n");
        for (int i=0;i<n;i++){
            printf("%c ",alphabets[i]);
            for (int j=0;j<n;j++){
                printf("%c",board[i][j]);
            }
            printf("\n");
        }
}

void printBoard(char board[][26], int n){
    char alphabets[] = {'a','b','c','d','e','f','g','h','i','j',
                        'k','l','m','n','o','p','q','r','s','t',
                        'u','v','w','x','y','z','\0'};
    for (int i=0;i<n/2;i++){
        for (int j=0;j<n;j++){
            board[i][j] = 'U';
            board[j][i] = 'U';
        }
    }
    board[(n)/2-1][n/2-1]='W';
    board[n/2-1][n/2]='B';
    board[n/2][n/2-1]='B';
    board[n/2][n/2]='W';
    for (int i=n;i>n/2;i--){
        for (int j=0;j<n;j++){
            board[i][j] = 'U';
            board[j][i] = 'U';
        }
    }
    printOutBoard(board,n);
    return;
}

void configurateBoard(char board[][26], int n, char input_move[]){
    char alphabets[] = {'a','b','c','d','e','f','g','h','i','j',
                        'k','l','m','n','o','p','q','r','s','t',
                        'u','v','w','x','y','z','\0'};
    for (int i=0;i<n;i++){
        if (alphabets[i]==input_move[1]){
            for (int j=0;j<n;j++){
                if (alphabets[j]==input_move[2]){
                    board[i][j] = input_move[0];
                }
            }
        }
    }
    return;
}

int checkScoreHelper(char board[][26],int n, int row, int col, char colour, int deltaRow, int deltaCol){
    int direction[3] = {-1, 0, 1};
    int local_score = 0;
    if (colour=='W'){
        while (board[row + deltaRow][col + deltaCol]=='B'){
            row = row + deltaRow;
            col = col + deltaCol;
            local_score++;
        }
    }
    else if (colour=='B'){
        while (board[row + deltaRow][col + deltaCol]=='W'){
            row = row + deltaRow;
            col = col + deltaCol;
            local_score++;
        }
    }
    return local_score;
}

int checkScore(char board[][26], int n, char computer_move[3], char colour, int row, int column, int deltaRow, int deltaCol){
    char alphabets[] = {'a','b','c','d','e','f','g','h','i','j',
                        'k','l','m','n','o','p','q','r','s','t',
                        'u','v','w','x','y','z','\0'};
    int direction[3] = {-1, 0, 1};
    int total_score = 0;
    total_score = total_score + checkScoreHelper(board,n,row,column,colour,deltaRow,deltaCol);
    for (int i = 0;i<3;i++){
        for (int j = 0;j<3;j++){
            if (direction[i] != deltaRow || direction[j] != deltaCol){
                if (checkLegalInDirection(board,n,row,column,colour,direction[i],direction[j])){
                    total_score = total_score + checkScoreHelper(board,n,row,column,colour,direction[i],direction[j]);
                    }
            }
        }
    }
        return total_score;
    }

void applyComputerMove(char board[][26], int n, char colour, char* str){
    char alphabets[] = {'a','b','c','d','e','f','g','h','i','j',
                        'k','l','m','n','o','p','q','r','s','t',
                        'u','v','w','x','y','z','\0'};
    char best_move[3];
    int direction[] = {-1, 0, 1};
    int best_score = 0;
    int local_score = 0;
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            if (board[i][j] == 'U'){
                for (int k=0;k<3;k++){
                    for (int m=0;m<3;m++){
                        if (checkLegalInDirection(board,n,i,j,colour,
                            direction[k],direction[m])){
                                const char* row = &alphabets[i];
                                const char* column = &alphabets[j];
                                char* row_column;
                                row_column = malloc(strlen(row)+strlen(column)+1);
                                strcpy(row_column,row);
                                strcat(row_column,column);
                                local_score = checkScore(board,n,row_column,colour,i,j,direction[k],direction[m]);
                                free(row_column);
                                if ((i==0 && j==0) || (i==n-1 && j==0) || (i==0 && j==n-1) || (i == n-1 && j==n-1)){
                                    local_score = local_score + 3;
                                }
                                else if ((i==1 && j==0) || (i==n-2 && j==0) || (i==0 && j==1) || (i==0 && j==n-2) || 
                                        (i==1 && j==1) || (i==1 && j==n-1) || (i==n-1 && j==1) || (i==n-1 && j==n-1)){
                                    local_score = local_score - 3;
                                }
                                else if ((i>n/4 && i<(3*n)/4)){
                                    local_score = local_score + 1;
                                }
                                if (local_score > best_score){
                                    best_score = local_score;
                                    best_move[0] = alphabets[i];
                                    best_move[1] = alphabets[j];
                                }
                }
             }
        }
            }
        }
    }
    
    const char* best_row = &best_move[0];
    const char* best_column = &best_move[1];
    char* best_row_column;
    best_row_column = malloc(strlen(best_row)+strlen(best_column)+1);
    strcpy(best_row_column,best_row);
   strcpy(str,best_row_column);
}


bool positionInBounds(int n, int row, int col){
    if (-1 < row && row < n && -1 < col && col < n){
        return true;
    }
    else{
        return false;
    }
}

void flipTiles(char board[][26],int n, int row, int col, char colour, int deltaRow, int deltaCol){
    int direction[3] = {-1, 0, 1};
    if (colour=='W'){
        do{
            row = row + deltaRow;
            col = col + deltaCol;
            board[row][col] = 'W';
        } while (board[row + deltaRow][col + deltaCol]=='B');
    }
    else if (colour=='B'){
        do{
            row = row + deltaRow;
            col = col + deltaCol;
            board[row][col] = 'B';
        } while (board[row + deltaRow][col + deltaCol]=='W');
    }
}

bool checkLegalInDirection(char board[][26], int n, int row, int col,
                            char colour, int deltaRow, int deltaCol){
    int count = 0;
    if (colour == 'W' && positionInBounds(n,row + deltaRow,col+deltaCol)){
        do{
            row = row + deltaRow;
            col = col + deltaCol;
            count++;
        } while (board[row][col]=='B' && positionInBounds(n,row,col) && positionInBounds(n,row + deltaRow,col+deltaCol));
        if (board[row][col] == 'W' && count > 1){
            return true;
        }
        else if (board[row][col] == 'U'){
            return false;
        }
        else{
            return false;
        }
    }
    else if (colour == 'B' && positionInBounds(n,row + deltaRow,col+deltaCol)){
        do{
            row = row + deltaRow;
            col = col + deltaCol;
            count++;
        } while (board[row][col]=='W' && positionInBounds(n,row,col) && positionInBounds(n,row + deltaRow,col+deltaCol));
        if (board[row][col] == 'B' && count > 1){
            return true;
        }
        else if (board[row][col] == 'U'){
            return false;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}


void applyMove(char board[][26],int n,char entered_move[],char colour){
    char alphabets[] = {'a','b','c','d','e','f','g','h','i','j',
                        'k','l','m','n','o','p','q','r','s','t',
                        'u','v','w','x','y','z','\0'};
    int direction[3] = {-1, 0, 1};
    int row = 0, column = 0;
    for (int i=0;i<26;i++){
        if (entered_move[0]==alphabets[i]){
            row = i;
        }
    }
    for (int j=0;j<26;j++){
        if (entered_move[1]==alphabets[j]){
            column = j;
        }
    }
    if (positionInBounds(n,row,column)==false){
        printf("Invalid move.\n");
        return;
    }
    if (board[row][column]=='U'){
        for (int k=0;k<3;k++){
            for (int m=0;m<3;m++){
                if (checkLegalInDirection(board,n,row,column,colour,direction[k],direction[m])){
                    board[row][column] = colour;
                    flipTiles(board,n,row,column,colour,direction[k],direction[m]);
                    if (k < 2 || m < 2){
                        for (int h = k;h<3;h++){
                            for (int t = m;t<3;t++){
                                if (checkLegalInDirection(board,n,row,column,colour,direction[h],direction[t])){
                                    flipTiles(board,n,row,column,colour,direction[h],direction[t]);
                                }
                            }
                        }
                    }
                    return;
                }
            }
        }
    }
    else{
        return;
    }
}

bool availableMoves(char board[][26],int n, char colour){
    char alphabets[] = {'a','b','c','d','e','f','g','h','i','j',
                        'k','l','m','n','o','p','q','r','s','t',
                        'u','v','w','x','y','z','\0'};
    int direction[] = {-1, 0, 1};
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            if (board[i][j] == 'U'){
                for (int k=0;k<3;k++){
                    for (int m=0;m<3;m++){
                        if (checkLegalInDirection(board,n,i,j,colour,direction[k],direction[m])){
                            return true;
                            }
                         }
                    }
                }
            }
        }
    return false;
}

void endGame(char board[][26], int n){
    int white_count = 0;
    int black_count = 0;
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            if (board[i][j] == 'W'){
                white_count++;
                continue;
            }
            else if (board[i][j] == 'B'){
                black_count++;
                continue;
            }
        }
    }
    if (white_count > black_count){
        printf("W player wins.");
        return;
    }
    else if (black_count > white_count){
        printf("B player wins.");
        return;
    }
    else if (white_count==black_count){
        printf("Draw!");
        return;
    }
}

void computerMove(char board[][26], int n, char colour){
    char computer_move[3];
    if (colour == 'W'){
        printf("Computer places W at ");
        applyComputerMove(board,n,colour,computer_move);
        printf("%s",computer_move);
        printf(".\n");
        applyMove(board,n,computer_move,colour);
        printOutBoard(board,n);
    }
    else if (colour == 'B'){
        printf("Computer places B at ");
        applyComputerMove(board,n,colour,computer_move);
        printf("%s",computer_move);
        printf(".\n");
        applyMove(board,n,computer_move,colour);
        printOutBoard(board,n);
    }
}


bool validMoveCheck(char board[][26],int n, char colour, char entered_move[4]){
    char alphabets[] = {'a','b','c','d','e','f','g','h','i','j',
                        'k','l','m','n','o','p','q','r','s','t',
                        'u','v','w','x','y','z','\0'};
    int direction[3] = {-1, 0, 1};
    int row = 0, column = 0;
    int count = 0;
    if (colour == 'B'){
        for (int i=0;i<26;i++){
            if (entered_move[0]==alphabets[i]){
                row = i;
                }
        }
        for (int j=0;j<26;j++){
            if (entered_move[1]==alphabets[j]){
                column = j;
            }
        }
        if (positionInBounds(n,row,column)==false){
            return false;
        }
        if (board[row][column]=='U'){
            for (int k=0;k<3;k++){
                for (int m=0;m<3;m++){
                    if (checkLegalInDirection(board,n,row,column,colour,direction[k],direction[m])){
                        count++;
                    }
            }
            }
            if (count == 0){
                return false;
            }
            else{
                return true;
            }
        }
    }
    else if (colour == 'W'){
        for (int i=0;i<26;i++){
            if (entered_move[0]==alphabets[i]){
                row = i;
                }
        }
        for (int j=0;j<26;j++){
            if (entered_move[1]==alphabets[j]){
                column = j;
            }
        }
        if (positionInBounds(n,row,column)==false){
            return false;
        }
        if (board[row][column]=='U'){
            for (int k=0;k<3;k++){
                for (int m=0;m<3;m++){
                    if (checkLegalInDirection(board,n,row,column,colour,direction[k],direction[m])){
                        count++;
                }
            }
            }
            if (count == 0){
                return false;
            }
            else{
                return true;
            }
        }
    }
}


void userMove(char board[][26],int n, char colour, int *check){
    char alphabets[] = {'a','b','c','d','e','f','g','h','i','j',
                        'k','l','m','n','o','p','q','r','s','t',
                        'u','v','w','x','y','z','\0'};
    int direction[3] = {-1, 0, 1};
    int row = 0, column = 0;
    int count = 0;
    char entered_move[4];
    if (colour == 'B'){
        printf("Enter move for colour B (RowCol): ");
        scanf("%s",entered_move);
        if (validMoveCheck(board,n,colour,entered_move)){
            applyMove(board,n,entered_move,'B');
            printOutBoard(board,n);
        }
        else{
            printf("Invalid move.\n");
            printf("W player wins.");
            *check = 1;
        }
    }
    else if (colour == 'W'){
        printf("Enter move for colour W (RowCol): ");
        scanf("%s",entered_move);
        if (validMoveCheck(board,n,colour,entered_move)){
            applyMove(board,n,entered_move,'W');
            printOutBoard(board,n);
        }
        else{
            printf("Invalid move.\n");
            printf("B player wins.");
            *check = 1;
        }
    }
}

int main(void){
    char alphabets[] = {'a','b','c','d','e','f','g','h','i','j',
                        'k','l','m','n','o','p','q','r','s','t',
                        'u','v','w','x','y','z','\0'};
    char board_array[27][27] = {};
    int dimension = 0;
    int check = 0;
    char computer_colour[2];
    char board_config[4];
    char colour_array[] = {'W','B','\0'};
    char computer_move[3];
    printf("Enter the board dimension: ");
    scanf("%d",&dimension);
    printf("Computer plays (B/W) : ");
    scanf("%s",computer_colour);
    printBoard(board_array,dimension);
    if (computer_colour[0]=='W'){
        while (check == 0){
            userMove(board_array,dimension,'B',&check);
        while (check == 0){
            computerMove(board_array,dimension,computer_colour[0]);
            while (check == 0 && availableMoves(board_array,dimension,'B') || availableMoves(board_array,dimension,'W')){
                if (check == 0 && availableMoves(board_array,dimension,'B')){
                    userMove(board_array,dimension,'B', &check);
                    if (check == 0 && availableMoves(board_array,dimension,'W')){
                        computerMove(board_array,dimension,computer_colour[0]);
                    }
                    else if (check == 0 && availableMoves(board_array,dimension,'W')==false && availableMoves(board_array,dimension,'B')){
                        printf("W player has no valid move.\n"); 
                    }
                }
                else if (check == 0 && availableMoves(board_array,dimension,'B')==false && availableMoves(board_array,dimension,'W')){
                    printf("B player has no valid move.\n");
                    computerMove(board_array,dimension,computer_colour[0]);
                }
            }
            if (check == 0){
                endGame(board_array,dimension);
                return 0;
        }
            }
            return 0;
            }
            return 0;
    }
    else if (computer_colour[0]=='B'){
        while (check == 0){
            computerMove(board_array,dimension,computer_colour[0]);
            userMove(board_array,dimension,'W',&check);
            while (check == 0 && (availableMoves(board_array,dimension,'B') || availableMoves(board_array,dimension,'W'))){
                if (check == 0 && availableMoves(board_array,dimension,'B')){
                    computerMove(board_array,dimension,computer_colour[0]);
                    if (check == 0 && availableMoves(board_array,dimension,'W')){
                        userMove(board_array,dimension,'W',&check);
                }
                    else if (check == 0 && availableMoves(board_array,dimension,'W')==false && availableMoves(board_array,dimension,'B')){
                        printf("W player has no valid move.\n"); 
                    }
            }
                else if (check == 0 && availableMoves(board_array,dimension,'B')==false && availableMoves(board_array,dimension,'W')){
                    userMove(board_array,dimension,'W',&check);
                }
        }
        if (check == 0){
            endGame(board_array,dimension);
            return 0;
        }
        }
        return 0;
    }
    return 0;
 }
