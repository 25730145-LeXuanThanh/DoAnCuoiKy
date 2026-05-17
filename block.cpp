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
    
bool canMove(int dx, int dy)
{
        for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                        if (blocks[b][i][j] != ' ')
                        {
                                int xt = x + j + dx;
                                int yt = y + i + dy;
                                if (xt < 1 || xt >= W - 1 || yt >= H - 1)
                                        return false;
                                if (board[yt][xt] != ' ')
                                        return false;
                        }
        return true;
}
void move(int dx, int dy)
    {
        if(canMove(dx, dy))
        {x += dx;
        y += dy;
        }

    void block2Board(vector<vector<char>>& board)
    {
        for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                        if (matrix[i][j] != ' ')
                                board[y + i][x + j] = matrix[i][j];
    }
    void delBlock(vector<vector<char>>& board)
    {
        for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                        if (matrix[i][j] != ' ')
                                board[y + i][x + j] = ' ';
    }
};