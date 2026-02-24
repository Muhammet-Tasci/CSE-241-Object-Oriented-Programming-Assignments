#ifndef CELL_H
#define CELL_H

#include <iostream>

namespace HW4 {
    using namespace std;

    class Cell {
        private:
        int x,y; // coordinates of the cell
        int empty_cell; // flag if the cell is empty or blocked
        char symbol; // symbol in the cell O X *

        public:
        Cell(); // default constructor sets symbol to empty *


        // Getter and Setters
        char getSymbol() const;
        void setSymbol(char s);
        int getRow() const;
        void setRow(int r);
        int getCol() const; 
        void setCol(int c);
        int isEmpty() const;
        void set_empty(int a);

        // operator== compares two cells based on symbol
        bool operator==(const Cell& other);

        // prefix increment changes symbol in sequence * -> O -> X -> *
        Cell operator++();

        // postfix increment changes symbol after returning previous value
        Cell operator++(int);

        // prefix decrement changes symbol in reverse sequence * <- O <- X <- *
        Cell operator--();

        // postfix decrement changes symbol after returning previous value
        Cell operator--(int);

        // friend operator for outputting cell symbol to ostream
        friend ostream& operator <<(ostream& os, const Cell& c);

        // friend operator for reading symbol from istream
        friend istream& operator >>(istream& is, Cell& c);

    };


}






#endif