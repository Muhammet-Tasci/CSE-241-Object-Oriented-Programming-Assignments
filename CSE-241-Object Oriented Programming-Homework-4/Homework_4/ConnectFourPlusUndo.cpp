#include "ConnectFourPlusUndo.h"
#include <sstream>
namespace HW4 {

    ConnectFourPlusUndo::ConnectFourPlusUndo() : ConnectFourPlus() {
        moves = new int[25];
        capacity = 25;
        movecount= 0;
    }
    ConnectFourPlusUndo::ConnectFourPlusUndo(int r, int c) : ConnectFourPlus(r,c) {
        moves = new int[r*c];
        capacity = r*c;
        movecount = 0;
    }
    ConnectFourPlusUndo::ConnectFourPlusUndo(string file_name) : ConnectFourPlus(file_name){
        capacity = row * col; 
        if (capacity == 0) capacity = 100;
        moves = new int[capacity];
        movecount = 0;
    }



    void ConnectFourPlusUndo::play(int y_val, char letter){
    int y_index = y_val - 1;
    int x_index = letter - 'a';

    if(!canPlay(y_index,x_index)){
        cout<< "Invalid move. Your turn has passed."<<endl;
    }else{
    board[y_index][x_index].setSymbol('O');
    moves[movecount] = x_index;
    movecount++;
    }

    }



    void ConnectFourPlusUndo::play(){
        int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
        int dy[8] = {-1,  0,  1, 1, 1, 0, -1,-1};

    // 1) CAN THE COMPUTER WIN?
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (!canPlay(i, j)) continue;
            board[i][j].setSymbol('X'); // Simulation
            if (isGameOver() == 1) {
                moves[movecount] = j;
                movecount++;
                return;
            }
            board[i][j].setSymbol('*'); //bring back
        }
    }

    // 2) BLOCK THE PLAYER (Will he win?)
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (!canPlay(i, j)) continue;
            board[i][j].setSymbol('O');// Try the player's move
            if (isGameOver() == 1) {
                board[i][j].setSymbol('X');
                moves[movecount] = j;
                movecount++;
                return;
            }
            board[i][j].setSymbol('*');//bring back
        }
    }

    // 3) STRATEGIC MOVE (Is there an X next to it?)
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (!canPlay(i, j)) continue;
            bool nearComputer = false;
            for (int d = 0; d < 8; d++) {
                int nx = i + dx[d];
                int ny = j + dy[d];
                if (nx >= 0 && nx < row && ny >= 0 && ny < col) {
                    if (board[nx][ny].isEmpty() == 0 &&
                        board[nx][ny].getSymbol() == 'X') {
                        nearComputer = true;
                        break;
                    }
                }
            }

            if (nearComputer) {
                board[i][j].setSymbol('X');
                moves[movecount] = j;
                movecount++;
                return;
            }
        }
    }

    // 4) IF NONE → First valid move
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (canPlay(i, j)) {
                board[i][j].setSymbol('X');
                moves[movecount] = j;
                movecount++;
                return;
            }
        }
    }
        

    }





    void ConnectFourPlusUndo::playGame() {
   
    cout << endl << "Game loaded successfully!"<<endl<<endl;
    printBoard();

    string line;
    int rowInput;
    char colInput; 

    cin.ignore();
    while (true) {
        
        //Player Turn
        cout << "Your move (row letter) or undo: ";
        getline(cin, line);
       
        if (line == "UNDO" || line == "undo") {
            undo();

            printBoard();
            continue;
        } 
        else {
            stringstream ss(line); 
            
            // Satırın tamamı ss içinde olduğu için hepsini ss'ten çekebiliriz
            if (ss >> rowInput >> colInput) { 
                // Hem sayıyı hem harfi başarıyla okuduysa
                play(rowInput, colInput); // rowVal int, colVal char gider
                printBoard();
            } 
            else {
                play(-1,'W'); //Sending a position that is definitively invalid in order to indicate an error.
                printBoard();
            }
        }


        int status = isGameOver(); // check if game finished
        if (status == 1 || status == 2) {
            cout << "Game Over!" << endl;
            saveToFile("saved_board.txt");
            return;
        }

        //Computer Turn
        cout << "Computer is thinking..."<<endl;
        play();
        printBoard();

        status = isGameOver(); // check again after computer
        if (status == 1 || status == 2) {
            cout << "Game Over!" << endl;
            saveToFile("saved_board.txt");
            return;
        }

    }
    }



    void ConnectFourPlusUndo::undo(){
        int x_coord;

        if(movecount <= 0) {
            cout<< "There are none played move." << endl;
            return;
        }

        for(int k = 0; k<2; k++ ) {
            if(movecount > 0){
        for(int i = 0; i<row;i++ ){
            if(board[i][moves[movecount-1]].getSymbol() != '*' && board[i][moves[movecount-1]].getSymbol() != ' '){
                x_coord = i;
                break;
            } 
        }

        board[x_coord][moves[movecount-1]].setSymbol('*');
        movecount--;
    }
}
    cout<<"The moves have been undone." << endl;

    }



    ConnectFourPlusUndo::~ConnectFourPlusUndo(){
        delete[] moves;
    }



}