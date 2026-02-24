#ifndef CONNECTFOURPLUSUNDO_H
#define CONNECTFOURPLUSUNDO_H


#include "ConnectFourPlus.h"

namespace HW4 {

    class ConnectFourPlusUndo : public ConnectFourPlus {

        public:
        ConnectFourPlusUndo();
        ConnectFourPlusUndo(int r, int c);
        ConnectFourPlusUndo(string file_name);
        ~ConnectFourPlusUndo();

        void playGame() override; //The play function will be overridden in order to integrate the undo feature
        void play() override;
        void play(int y_val, char letter);
        
        void undo(); // Ne Function : Delete last moves.

        private:
        int* moves;
        int movecount;
        int capacity;


    };


}







#endif