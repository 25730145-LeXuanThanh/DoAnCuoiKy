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

    virtual void rotate(const vector<vector<char>>& board) = 0;
    
bool canMove(int dx, int dy, const vector<vector<char>>& board)
{
        int H = board.size();
        int W = board[0].size();

    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(matrix[i][j] != ' ')
            {
                int xt = x + j + dx;
                int yt = y + i + dy;
                if(xt < 1 || xt >= W-1 || yt >= H-1) return false;
                if(board[yt][xt] != ' ') return false;
            }
    return true;
    }
void move(int dx, int dy, vector<vector<char>>& board)
{
        if(canMove(dx, dy, board))
        {
        x += dx;
        y += dy;
        }
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

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

    char getCell(int r, int c)
    {
        return matrix[r][c];
    }
};