#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

class Block
{
protected:
    int x,y;
    int state;
    char matrix[4][4];
public:
    Block() : x(5), y(1) {}

    void rotate(){};

    void block2Board()
    {
        for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                        if (curentBlock[i][j] != ' ')
                                board[y + i][x + j] = curentBlock[i][j];
    }
    void delBlock()
    {
        for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                        if (curentBlock[i][j] != ' ')
                                board[y + i][x + j] = ' ';
    }
};