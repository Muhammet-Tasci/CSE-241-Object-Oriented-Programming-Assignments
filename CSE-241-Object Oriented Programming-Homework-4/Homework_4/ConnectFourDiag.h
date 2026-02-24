#ifndef CONNECTFOURDIAG_H
#define CONNECTFOURDIAG_H

#include "ConnectFourAbstract.h"

namespace HW4 {

    class ConnectFourDiag : public ConnectFourAbstract {

        public:
        ConnectFourDiag();
        ConnectFourDiag(int r, int c);
        ConnectFourDiag(string file_name);
        ~ConnectFourDiag();

        int isGameOver() override;

    };


}







#endif