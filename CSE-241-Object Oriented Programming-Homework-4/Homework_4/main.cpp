#include <iostream>
#include <string>
#include "ConnectFourPlus.h"
#include "ConnectFourDiag.h"
#include "ConnectFourPlusUndo.h"

// Include the namespace
using namespace HW4;
using namespace std;

int main() {
    // Power of Polymorphism: We can hold all derived classes with a Base Class pointer.
    ConnectFourAbstract* game = nullptr;

    char gameMode;
    char boardType;

    // --- STEP 1: GAME MODE SELECTION ---
    cout << "============================================" << endl;
    cout << "   CONNECT FOUR GAME - CSE241 HW#4" << endl;
    cout << "============================================" << endl;
    cout << "Select Game Mode:" << endl;
    cout << "[P] ConnectFour Plus (Only Horizontal/Vertical)" << endl;
    cout << "[D] ConnectFour Diag (Only Diagonal)" << endl;
    cout << "[U] ConnectFour Plus Undo (Plus + Undo Feature)" << endl;
    cout << "Choice: ";
    
    while (true) {
        cin >> gameMode;
        cin.ignore(1000, '\n');
        // Convert lowercase input to uppercase
        if (gameMode >= 'a' && gameMode <= 'z') gameMode -= 32;

        if (gameMode == 'P' || gameMode == 'D' || gameMode == 'U') {
            break;
        }
        cout << "Invalid selection! Please enter P, D, or U: ";
    }

    // --- STEP 2: BOARD TYPE SELECTION ---
    cout << "\nSelect Board Initialization:" << endl;
    cout << "[1] Default Board (5x5)" << endl;
    cout << "[2] Custom Board (Enter Rows and Cols)" << endl;
    cout << "[3] Load from File" << endl;
    cout << "Choice: ";

    while (true) {
        cin >> boardType;
        cin.ignore(1000, '\n');
        if (boardType == '1' || boardType == '2' || boardType == '3') {
            break;
        }
        cout << "Invalid selection! Please enter 1, 2, or 3: ";
    }

    // --- STEP 3: OBJECT CREATION ---
    
    // Necessary variables
    int r = 0, c = 0;
    string filename;

    // Get necessary info from the user
    if (boardType == '2') {
        cout << "Enter Rows and Columns (e.g. 6 7): ";
        cin >> r >> c;
    } 
    else if (boardType == '3') {
        cout << "Enter filename (e.g. board.txt): ";
        cin >> filename;
    }

    // Create the correct class using "new" according to the selected mode
    switch (gameMode) {
        case 'P': // PLUS MODE
            if (boardType == '1')      game = new ConnectFourPlus();
            else if (boardType == '2') game = new ConnectFourPlus(r, c);
            else                       game = new ConnectFourPlus(filename);
            break;

        case 'D': // DIAG MODE
            if (boardType == '1')      game = new ConnectFourDiag();
            else if (boardType == '2') game = new ConnectFourDiag(r, c);
            else                       game = new ConnectFourDiag(filename);
            break;

        case 'U': // UNDO MODE
            if (boardType == '1')      game = new ConnectFourPlusUndo();
            else if (boardType == '2') game = new ConnectFourPlusUndo(r, c);
            else                       game = new ConnectFourPlusUndo(filename);
            break;
    }

    // --- STEP 4: START THE GAME ---
    if (game != nullptr) {
        // Regardless of which class was created, since they all derive from the Abstract class,
        // calling playGame() is sufficient.
        // If 'Undo' was selected, the overridden playGame runs.
        // For others, the Abstract class's playGame runs.
        
        game->playGame();

        // Memory cleanup after the game ends
        delete game; 
        game = nullptr;
    } else {
        cout << "Critical Error: Game could not be initialized." << endl;
    }

    return 0;
}