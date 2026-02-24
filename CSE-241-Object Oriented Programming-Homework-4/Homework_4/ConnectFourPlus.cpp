#include "ConnectFourPlus.h"


namespace HW4 {
    ConnectFourPlus::ConnectFourPlus() : ConnectFourAbstract(){}
    ConnectFourPlus::ConnectFourPlus(int r, int c) : ConnectFourAbstract(r,c){}
    ConnectFourPlus::ConnectFourPlus(string file_name) : ConnectFourAbstract(file_name){}
    ConnectFourPlus::~ConnectFourPlus(){}


    int ConnectFourPlus::isGameOver(){
        int dx[4] = { -1, 0, 1, 0};
        int dy[4] = { 0, 1, 0, -1};

    bool anyPlayable = false;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {

            if (canPlay(i, j)) {
                anyPlayable = true;
            }

            if (board[i][j].isEmpty() || board[i][j].getSymbol() == '*') 
                continue;

            char currentSymbol = board[i][j].getSymbol();

            for (int dir = 0; dir < 4; dir++) {
                int count = 1;

                int nx = i + dx[dir];
                int ny = j + dy[dir];

                while (nx >= 0 && nx < row && ny >= 0 && ny < col) {
                    if (board[nx][ny].isEmpty() || board[nx][ny].getSymbol() != currentSymbol) 
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
}