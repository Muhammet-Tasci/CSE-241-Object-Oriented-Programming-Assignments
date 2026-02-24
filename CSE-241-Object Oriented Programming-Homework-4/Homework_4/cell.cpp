#include "cell.h"

namespace HW4 {


    Cell::Cell():symbol('*'){}

    char Cell::getSymbol() const { return symbol;}
    void Cell::setSymbol(char s) {symbol = s;}

    int Cell::getRow() const { return y;}
    void Cell::setRow(int r) {y = r;}

    int Cell::getCol() const { return x;}
    void Cell::setCol(int c){ x = c;}

    int Cell::isEmpty() const { return empty_cell;}
    void Cell::set_empty(int a){empty_cell = a; }


    bool Cell::operator==(const Cell& other){
            if(symbol == other.symbol) return 1;
            return 0;
        }


        Cell Cell::operator++(){
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

            return *this;
        }

        Cell Cell::operator++(int){
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

        Cell Cell::operator--(){
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

            return *this;
        }

        Cell Cell::operator--(int){
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


    ostream& operator <<(ostream& os, const Cell& c){
    os << c.symbol;
    return os;
    }


    istream& operator >>(istream& is, Cell& c){
    is >> c.symbol;
    return is;
}
}