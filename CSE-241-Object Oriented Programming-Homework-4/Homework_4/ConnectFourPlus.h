#ifndef CONNECTFOURPLUS_H
#define CONNECTFOURPLUS_H

#include "ConnectFourAbstract.h"

namespace HW4 {

    class ConnectFourPlus : public ConnectFourAbstract {

        public:
        ConnectFourPlus();
        ConnectFourPlus(int r, int c);
        ConnectFourPlus(string file_name);
        ~ConnectFourPlus();

        int isGameOver() override;

    };
}




#endif