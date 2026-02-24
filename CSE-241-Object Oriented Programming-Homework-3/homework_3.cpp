#include <iostream>
#include <fstream>

using namespace std;

// ConnectFour class handles the game logic and board management
class ConnectFour {

    public:

    // Cell class represents a single cell on the board
    class Cell {
        private:
        int x,y; // coordinates of the cell
        int empty_cell; // flag if the cell is empty or blocked
        char symbol; // symbol in the cell O X *

        public:
        Cell():symbol('*'){} // default constructor sets symbol to empty *

        friend class ConnectFour; // ConnectFour can access private members of Cell

        // operator== compares two cells based on symbol
        bool operator==(const Cell& other){
            if(symbol == other.symbol) return 1;
            return 0;
        }

        // prefix increment changes symbol in sequence * -> O -> X -> *
        Cell operator++(){
            if(symbol == '*'){
                symbol = 'O';
                return *this;
            }
            if(symbol == 'O'){
                symbol = 'X';
                return *this;
            }
            if(symbol == 'X'){
                symbol = '*';
                return *this;
            }
        }

        // postfix increment changes symbol after returning previous value
        Cell operator++(int){
            Cell temp;
            temp = *this;
            if(symbol == '*'){
                symbol = 'O';
            }
            if(symbol == 'O'){
                symbol = 'X';
            }
            if(symbol == 'X'){
                symbol = '*';
            }
            return temp;
        }

        // prefix decrement changes symbol in reverse sequence * <- O <- X <- *
        Cell operator--(){
             if(symbol == '*'){
                symbol = 'X';
                return *this;
            }
            if(symbol == 'X'){
                symbol = 'O';
                return *this;
            }
            if(symbol == 'O'){
                symbol = '*';
                return *this;
            }

        }

        // postfix decrement changes symbol after returning previous value
        Cell operator--(int){
            Cell temp;
            temp = *this;
             if(symbol == '*'){
                symbol = 'X';
            }
            if(symbol == 'X'){
                symbol = 'O';
            }
            if(symbol == 'O'){
                symbol = '*';
            }
            return temp;

        }

        // friend operator for outputting cell symbol to ostream
        friend ostream& operator <<(ostream& os, const Cell& c);
        // friend operator for reading symbol from istream
        friend istream& operator >>(istream& is, Cell& c);

    };

    // default constructor creates 5x5 board
    ConnectFour(){
        row = 5;
        col = 5;
        board = new Cell*[row];

        for(int i = 0; i<row;i++){
            board[i] = new Cell[col];
        }

        for(int i = 0; i<row;i++){
            for(int k = 0; k<col;k++){
                board[i][k].y = row;
                board[i][k].x = col;
                board[i][k].empty_cell = 0; // initially all cells are playable
                
            }
        }
    }

    // constructor with custom row and column size
    ConnectFour(int row_v,int col_v){
        if(row_v < 4 && col_v < 4){
            cout << "Invalid board size. Default board created due to incorrect input. (5,5)"<< endl;
            ConnectFour(); // fallback to default board
        }else{
            row = row_v;
            col = col_v;
            board = new Cell*[row];

        for(int i = 0; i<row;i++){
            board[i] = new Cell[col];
        }

        for(int i = 0; i<row;i++){
            for(int k = 0; k<col;k++){
                board[i][k].y = row;
                board[i][k].x = col;
                board[i][k].empty_cell = 0;
            }
        }
        }
    }

    // constructor to load board from a file
    ConnectFour(string file_name){
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
                board[i][k].y = row;
                board[i][k].x = col;
            }
        }

        file.clear();
        file.seekg(0,ios::beg);

        int row_index = 0;
        while(getline(file,line)){
            int col_index = 0;
            for(; col_index<line.size(); col_index++){
                if(line[col_index] == ' '){
                    board[row_index][col_index].empty_cell = 1; // blocked cell
                    board[row_index][col_index].symbol = ' ';
                    }else{
                        if(line[col_index] == '*'){
                        board[row_index][col_index].empty_cell = 0; // playable empty cell
                        board[row_index][col_index].symbol = '*';
                    }else{
                        cout << "Incorrect format detected in file. Program closing..." << endl;
                        exit(0);
                    }
                }
            }
            for(;col_index < col; col_index++){
            board[row_index][col_index].empty_cell = 1; // fill missing columns as blocked
            board[row_index][col_index].symbol = ' ';
            }

            row_index++;
        }
        file.close();

    }

    // prints current board to console
    void printBoard(){
        char ch = 'a';
        cout<< " ";
        for(int i = 0; i < col;i++ ){
            cout<< ch;
            ch++;
        }
        cout << endl;
        for(int i = 0; i<row; i++){
            cout<< i+1;
            for(int k = 0; k<col; k++){
                if(board[i][k].empty_cell){
                    cout<<" "; // blocked cell printed as space
                }else{
                    cout<<board[i][k]; // cell symbol printed
                }

            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }

    // checks if player or computer can play at given cell
    bool canPlay(int r, int c) {
    if (r < 0 || r >= row || c < 0 || c >= col)
        return false;

    if (board[r][c].empty_cell == 1)
        return false;

    if (board[r][c].symbol != '*')
        return false;

    // Gravity (board shape-aware)
    if (r + 1 == row || board[r+1][c].symbol == ' ' || board[r+1][c].symbol == 'X' || board[r+1][c].symbol == 'O') {
        return true;
    }else{
        return false;
    }

}


// checks if game is over
int isGameOver() {
    int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int dy[8] = {-1,  0,  1, 1, 1, 0, -1, -1};

    bool anyPlayable = false;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {

            if (canPlay(i, j)) {
                anyPlayable = true;
            }

            if (board[i][j].empty_cell || board[i][j].symbol == '*') 
                continue;

            char currentSymbol = board[i][j].symbol;

            for (int dir = 0; dir < 8; dir++) {
                int count = 1;

                int nx = i + dx[dir];
                int ny = j + dy[dir];

                while (nx >= 0 && nx < row && ny >= 0 && ny < col) {
                    if (board[nx][ny].empty_cell || board[nx][ny].symbol != currentSymbol) 
                        break;

                    count++;
                    if (count == 4) {
                        if (currentSymbol == 'X')
                            cout << "Computer (X) wins!" << endl;
                        else
                            cout << "Player (O) wins!" << endl;

                        return 1; // game won
                    }

                    nx += dx[dir];
                    ny += dy[dir];
                }
            }
        }
    }

    if (!anyPlayable) {
        cout << "Draw! No moves left." << endl;
        return 2;
    }

    return 0; // game continues
}

// plays player move
void play(int y_val, char letter){
    int y_index = y_val - 1;
    int x_index = letter - 'a';

    if(!canPlay(y_index,x_index)){
        cout<< "Invalid move. Your turn has passed."<<endl;
    }else{

    board[y_index][x_index].symbol = 'O';
    }
}

// computer move logic
void playComputer() {
    int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int dy[8] = {-1,  0,  1, 1, 1, 0, -1,-1};

    // 1) CAN THE COMPUTER WIN?
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (!canPlay(i, j)) continue;
            board[i][j].symbol = 'X'; // Simulation
            if (isGameOver() == 1) {
                board[i][j].symbol = 'X'; 
                return;
            }
            board[i][j].symbol = '*'; //bring back
        }
    }

    // 2) BLOCK THE PLAYER (Will he win?)
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (!canPlay(i, j)) continue;
            board[i][j].symbol = 'O';// Try the player's move
            if (isGameOver() == 1) {
                board[i][j].symbol = 'X';
                return;
            }
            board[i][j].symbol = '*';
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
                    if (board[nx][ny].empty_cell == 0 &&
                        board[nx][ny].symbol == 'X') {
                        nearComputer = true;
                        break;
                    }
                }
            }

            if (nearComputer) {
                board[i][j].symbol = 'X';
                return;
            }
        }
    }

    // 4) IF NONE → First valid move
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (canPlay(i, j)) {
                board[i][j].symbol = 'X';
                return;
            }
        }
    }
}

// comparison operators for board
bool operator==(const ConnectFour& other) const {
    if (row != other.row || col != other.col)
        return false;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j].symbol != other.board[i][j].symbol ||
                board[i][j].empty_cell != other.board[i][j].empty_cell) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const ConnectFour& other) const {
    return !(*this == other);
}

// save board to file
void saveToFile(string file_name) {
    ofstream file(file_name);
    if (!file) {
        cout << "Cannot open file to save." << endl;
        return;
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j].empty_cell == 1)
                file << ' ';
            else
                file << board[i][j].symbol;
        }
        file << endl;
    }

    file.close();
    cout << "Board saved to " << file_name << endl;
}

// load board from file
void loadFromFile(string file_name) {
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
            board[i][j].y = row, board[i][j].x = col;

    file.clear();
    file.seekg(0, ios::beg);

    int row_index = 0;
    while (getline(file, line)) {
        int col_index = 0;
        for (; col_index < line.size(); col_index++) {
            char ch = line[col_index];
            if (ch == ' ') {
                board[row_index][col_index].empty_cell = 1;
                board[row_index][col_index].symbol = '*';
            } else if (ch == '*' || ch == 'X' || ch == 'O') {
                board[row_index][col_index].empty_cell = 0;
                board[row_index][col_index].symbol = ch;
            } else {
                cout << "Incorrect format detected in file. Program closing..." << endl;
                exit(0);
            }
        }
        for (; col_index < col; col_index++) {
            board[row_index][col_index].empty_cell = 1;
            board[row_index][col_index].symbol = '*';
        }
        row_index++;
    }

    file.close();
    cout << "Board loaded from " << file_name << endl;
}

// destructor deletes dynamically allocated board
~ConnectFour(){
    for(int i=0; i<row;i++){
        delete[] board[i];
    }
    delete[] board;
    board = nullptr;
}

private:
    Cell** board; // pointer to 2D array of cells
    int row; // row count
    int col; // column count

};

// main game loop function
void playGame() {
    string fileName;
    cout << "Enter board file name: ";
    cin >> fileName;

    ConnectFour game(fileName); // create game from file

    cout << endl << "Game loaded successfully!"<<endl<<endl;
    game.printBoard();

    while (true) {

        //Player Turn
        cout << "Your move (row letter): ";
        int rowInput;
        char colInput;
        cin >> rowInput >> colInput;

        game.play(rowInput, colInput);
        game.printBoard();

        int status = game.isGameOver(); // check if game finished
        if (status == 1 || status == 2) {
            cout << "Game Over!" << endl;
            game.saveToFile("saved_board.txt");
            return;
        }

        //Computer Turn
        cout << "Computer is thinking..."<<endl;
        game.playComputer();
        game.printBoard();

        status = game.isGameOver(); // check again after computer
        if (status == 1 || status == 2) {
            cout << "Game Over!" << endl;
            game.saveToFile("saved_board.txt");
            return;
        }
    }
   
}

// output operator prints cell symbol
ostream& operator <<(ostream& os, const ConnectFour::Cell& c){
    os << c.symbol;
    return os;
}

// input operator reads cell symbol
istream& operator >>(istream& is, ConnectFour::Cell& c){
    is >> c.symbol;
    return is;
}

// main entry point
int main() {
    playGame();
    return 0;
}
