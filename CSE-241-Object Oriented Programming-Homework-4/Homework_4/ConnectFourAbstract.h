#ifndef CONNECTFOURABSTRACT_H
#define CONNECTFOURABSTRACT_H

#include "Cell.h"
#include <string>
#include <fstream>

namespace HW4 {
    class ConnectFourAbstract {
    public:

        // default constructor creates 5x5 board
        ConnectFourAbstract(); 

        // constructor with custom row and column size
        ConnectFourAbstract(int r, int c);

        // constructor to load board from a file
        ConnectFourAbstract(string file_name);

        virtual ~ConnectFourAbstract(); //The destructor must be virtual! (To prevent memory leaks)

        //Common function
        int getWidth() const;
        int getHeight() const;

        void printBoard() const; // display function

        // checks if player or computer can play at given cell
        bool canPlay(int r, int c);
        
        //Let the function be virtual because the game-ending conditions are different in each derived class.
        virtual int isGameOver() = 0;
        

       //functions that run the game
        virtual void play(); // Computer
        virtual void play(int y_val, char letter); // User
        virtual void playGame(); //main game loop

        // comparison operators for board
        bool operator==(const ConnectFourAbstract& other) const;
        bool operator!=(const ConnectFourAbstract& other) const ;

        //File operations
        void loadFromFile(std::string fileName);
        void saveToFile(std::string fileName);

    protected: //We make it protected so that the derived classes can access it.

        Cell** board; // pointer to 2D array of cells
        int row; //row count
        int col; // column count
        
    };


}

#endif