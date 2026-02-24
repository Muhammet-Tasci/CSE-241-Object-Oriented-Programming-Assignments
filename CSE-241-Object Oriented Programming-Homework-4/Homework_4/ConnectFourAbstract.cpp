#include "ConnectFourAbstract.h"

namespace HW4 {

    ConnectFourAbstract::ConnectFourAbstract(){
        row = 5;
        col = 5;
        board = new Cell*[row];

        for(int i = 0; i<row;i++){
            board[i] = new Cell[col];
        }

        for(int i = 0; i<row;i++){
            for(int k = 0; k<col;k++){
                board[i][k].setRow(i);
                board[i][k].setCol(k);
                board[i][k].set_empty(0); // initially all cells are playable
                
            }
        }
    }


    ConnectFourAbstract::ConnectFourAbstract(int row_v,int col_v){
        if(row_v < 4 && col_v < 4){
            cout << "Invalid board size. Default board created due to incorrect input. (5,5)"<< endl;
        //default constructor 
        row = 5;
        col = 5;
        board = new Cell*[row];

        for(int i = 0; i<row;i++){
            board[i] = new Cell[col];
        }

        for(int i = 0; i<row;i++){
            for(int k = 0; k<col;k++){
                board[i][k].setRow(i);
                board[i][k].setCol(k);
                board[i][k].set_empty(0); 
                
            }
        }

        }else{
            row = row_v;
            col = col_v;
            board = new Cell*[row];

        for(int i = 0; i<row;i++){
            board[i] = new Cell[col];
        }

        for(int i = 0; i<row;i++){
            for(int k = 0; k<col;k++){
                board[i][k].setRow(i);
                board[i][k].setCol(k);
                board[i][k].set_empty(0);
            }
        }
        }
    }



    ConnectFourAbstract::ConnectFourAbstract(string file_name){
        ifstream file(file_name);
        int max_col = 0;
        row = 0;
        string line;
        while(getline(file,line)){
            if(line.size() > max_col) max_col = line.size();
            row++;
        }
        col = max_col;

        board = new Cell*[row];
        for(int i = 0; i<row;i++){
            board[i] = new Cell[col];
        }

        for(int i = 0; i<row;i++){
            for(int k = 0; k<col;k++){
                board[i][k].setRow(i);
                board[i][k].setCol(k);
            }
        }

        file.clear();
        file.seekg(0,ios::beg);

        int row_index = 0;
        while(getline(file,line)){
            int col_index = 0;
            for(; col_index<line.size(); col_index++){
                if(line[col_index] == ' '){
                    board[row_index][col_index].set_empty(1); // blocked cell
                    board[row_index][col_index].setSymbol(' ');
                    }else{
                        if(line[col_index] == '*'){
                        board[row_index][col_index].set_empty(0); // playable empty cell
                        board[row_index][col_index].setSymbol('*');
                    }else{
                        cout << "Incorrect format detected in file. Program closing..." << endl;
                        exit(0);
                    }
                }
            }
            for(;col_index < col; col_index++){
            board[row_index][col_index].set_empty(1); // fill missing columns as blocked
            board[row_index][col_index].setSymbol(' ');
            }

            row_index++;
        }
        file.close();

    }


    ConnectFourAbstract::~ConnectFourAbstract(){
    for(int i=0; i<row;i++){
        delete[] board[i];
    }
    delete[] board;
    board = nullptr;
    }


    int ConnectFourAbstract::getWidth() const{return col;}
    int ConnectFourAbstract::getHeight() const{return row;}

    void ConnectFourAbstract::printBoard() const {
        char ch = 'a';
        cout<< " ";
        for(int i = 0; i < col;i++ ){
            cout<< ch;
            ch++;
        }
        cout << endl;
        for(int i = 0; i<row; i++){
            if(row >= 10 && i < 9 ) cout << 0;
            cout<< i+1;
            for(int k = 0; k<col; k++){
                if(board[i][k].isEmpty()){
                    cout<<" "; // blocked cell printed as space
                }else{
                    cout<<board[i][k]; // cell symbol printed
                }

            }
            cout<<endl;
        }
        cout<<endl<<endl;

    }


    bool ConnectFourAbstract::canPlay(int r, int c) {
    if (r < 0 || r >= row || c < 0 || c >= col)
        return false;

    if (board[r][c].isEmpty())
        return false;

    if (board[r][c].getSymbol() != '*')
        return false;

    // Gravity (board shape-aware)
    if (r + 1 == row || board[r+1][c].getSymbol() == ' ' || board[r+1][c].getSymbol() == 'X' || board[r+1][c].getSymbol() == 'O') {
        return true;
    }else{
        return false;
    }

    }


    void ConnectFourAbstract::play(int y_val, char letter){
    int y_index = y_val - 1;
    int x_index = letter - 'a';

    if(!canPlay(y_index,x_index)){
        cin.ignore(1000, '\n');
        cout<< "Invalid move. Your turn has passed."<<endl;
    }else{

    board[y_index][x_index].setSymbol('O');
    }

    }




    void ConnectFourAbstract::play(){
        int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
        int dy[8] = {-1,  0,  1, 1, 1, 0, -1,-1};

    // 1) CAN THE COMPUTER WIN?
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (!canPlay(i, j)) continue;
            board[i][j].setSymbol('X'); // Simulation
            if (isGameOver() == 1) {
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
                return;
            }
        }
    }

    // 4) IF NONE → First valid move
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (canPlay(i, j)) {
                board[i][j].setSymbol('X');
                return;
            }
        }
    }
        

    }



    void ConnectFourAbstract::playGame() {

    cout << endl << "Game loaded successfully!"<<endl<<endl;
    printBoard();

    while (true) {

        //Player Turn
        cout << "Your move (row col, e.g., 5 A): ";
        int rowInput;
        char colInput;
        if (!(cin >> rowInput >> colInput)) {
            cout << "Invalid input! Please enter a Number and a Letter (e.g., 5 A)." << endl;
            cin.clear();
            cin.ignore(1000, '\n'); 
            continue; // Döngünün başına dön, tekrar sor.
        }

        play(rowInput, colInput);
        printBoard();

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


bool ConnectFourAbstract::operator==(const ConnectFourAbstract& other) const {
    if (row != other.row || col != other.col)
        return false;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j].getSymbol() != other.board[i][j].getSymbol() ||
                board[i][j].isEmpty() != other.board[i][j].isEmpty()) {
                return false;
            }
        }
    }
    return true;
}

bool ConnectFourAbstract::operator!=(const ConnectFourAbstract& other) const {
    return !ConnectFourAbstract::operator==(other);
}



void ConnectFourAbstract::loadFromFile(string file_name) {
    ifstream file(file_name);
    if (!file) {
        cout << "Cannot open file to load." << endl;
        return;
    }

    if (board != nullptr) {
        for (int i = 0; i < row; i++)
            delete[] board[i];
        delete[] board;
        board = nullptr;
    }

    int max_col = 0;
    row = 0;
    string line;
    while (getline(file, line)) {
        if (line.size() > max_col) max_col = line.size();
        row++;
    }
    col = max_col;

    board = new Cell*[row];
    for (int i = 0; i < row; i++)
        board[i] = new Cell[col];

    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            board[i][j].setRow(row), board[i][j].setCol(col);

    file.clear();
    file.seekg(0, ios::beg);

    int row_index = 0;
    while (getline(file, line)) {
        int col_index = 0;
        for (; col_index < line.size(); col_index++) {
            char ch = line[col_index];
            if (ch == ' ') {
                board[row_index][col_index].set_empty(1);
                board[row_index][col_index].setSymbol(' ');
            } else if (ch == '*' || ch == 'X' || ch == 'O') {
                board[row_index][col_index].set_empty(0);
                board[row_index][col_index].setSymbol(ch);
            } else {
                cout << "Incorrect format detected in file. Program closing..." << endl;
                exit(0);
            }
        }
        for (; col_index < col; col_index++) {
            board[row_index][col_index].set_empty(1);
            board[row_index][col_index].setSymbol(' ');
        }
        row_index++;
    }

    file.close();
    cout << "Board loaded from " << file_name << endl;
}



void ConnectFourAbstract::saveToFile(string file_name) {
    ofstream file(file_name);
    if (!file) {
        cout << "Cannot open file to save." << endl;
        return;
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j].isEmpty())
                file << ' ';
            else
                file << board[i][j];
        }
        file << endl;
    }

    file.close();
    cout << "Board saved to " << file_name << endl;
}



}