#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
#define H 30
#define W 15

char currentBlock[4][4];
char board[H][W] = {};

int x, y, b, nextBlock, score = 0, speed = 1000;


char blocks[7][4][4] = {
    {{' ','I',' ',' '},{' ','I',' ',' '},{' ','I',' ',' '},{' ','I',' ',' '}},
    {{' ',' ',' ',' '},{' ','O','O',' '},{' ','O','O',' '},{' ',' ',' ',' '}},
    {{' ','T',' ',' '},{'T','T','T',' '},{' ',' ',' ',' '},{' ',' ',' ',' '}},
    {{' ','S','S',' '},{'S','S',' ',' '},{' ',' ',' ',' '},{' ',' ',' ',' '}},
    {{'Z','Z',' ',' '},{' ','Z','Z',' '},{' ',' ',' ',' '},{' ',' ',' ',' '}},
    {{'J',' ',' ',' '},{'J','J','J',' '},{' ',' ',' ',' '},{' ',' ',' ',' '}},
    {{' ',' ','L',' '},{'L','L','L',' '},{' ',' ',' ',' '},{' ',' ',' ',' '}}
};

// ===== COLOR =====
string getColor(char c)
{
        switch (c)
        {
        case 'I':
                return "\033[96m";
        case 'O':
                return "\033[93m";
        case 'T':
                return "\033[95m";
        case 'S':
                return "\033[92m";
        case 'Z':
                return "\033[91m";
        case 'J':
                return "\033[94m";
        case 'L':
                return "\033[33m";
        default:
                return "\033[0m";
        }
}
void gotoXY(int x, int y)
{
        COORD c = {(SHORT)x, (SHORT)y};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void hideCursor()
{
        CONSOLE_CURSOR_INFO ci;
        ci.bVisible = FALSE;
        ci.dwSize = 100;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}

bool canMove(int dx, int dy)
{
        for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (blocks[b][i][j] != ' ') {
                int xt = x + j + dx;
                int yt = y + i + dy;
                if (xt < 1 || xt >= W-1 || yt >= H-1 ) return false;
                if (board[yt][xt] != ' ') return false;
            }
    return true;
}
void block2Board()
{
        for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
        if (blocks[b][i][j] != ' ')
                board[y+i][x+j] = blocks[b][i][j];
}
void boardDelBlock()
{
        for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
        if (blocks[b][i][j] != ' ')
                board[y+i][x+j] = ' ';
}
void initBoard()
{
        for (int i = 0; i < H; i++)
                for (int j = 0; j < W; j++)
                        if (i == 0 || i == H - 1 || j == 0 || j == W - 1)
                                board[i][j] = '#';
                        else
                                board[i][j] = ' ';
}
void draw()
{
        system("cls");

        for (int i = 0; i < H; i++, cout << endl)
                for (int j = 0; j < W; j++)
                        cout << board[i][j];
}

void rotate(){
    char tmp[4][4];
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            tmp[j][3-i] = currentBlock[i][j];

    char old[4][4];
    memcpy(old, currentBlock, sizeof(old));
    memcpy(currentBlock, tmp, sizeof(tmp));

    if(!canMove(0,0))
        memcpy(currentBlock, old, sizeof(old));
}

void removeLine()
{
}

int main()
{
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);

        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

        SetConsoleMode(hOut, dwMode);
        srand(time(0));
        x = 5;
        y = 0;
        b = rand() % 7;
        initBoard();
        while (1)
        {
                boardDelBlock();
                if (kbhit())
                {
                        char c = getch();
                        if (c == 'a' && canMove(-1, 0))
                                x--;
                        if (c == 'd' && canMove(1, 0))
                                x++;
                        if (c == 'x' && canMove(0, 1))
                                y++;
                        if (c == 'q')
                                break;
                }
                if (canMove(0, 1))
                        y++;
                else
                {
                        block2Board();
                        removeLine();
                        x = 5;
                        y = 0;
                        b = rand() % 7;
                }
                block2Board();
                draw();
                _sleep(500);
        }
        return 0;
}
