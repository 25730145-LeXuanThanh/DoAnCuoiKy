#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;
#define H 20
#define W 15
char board[H][W] = {};

int x, y, b;

char blocks[][4][4] = {
    {{' ', 'I', ' ', ' '},
     {' ', 'I', ' ', ' '},
     {' ', 'I', ' ', ' '},
     {' ', 'I', ' ', ' '}},
    {{' ', 'I', ' ', ' '},
     {' ', 'I', ' ', ' '},
     {' ', 'I', ' ', ' '},
     {' ', 'I', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', 'O', 'O', ' '},
     {' ', 'O', 'O', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', 'O', 'O', ' '},
     {' ', 'O', 'O', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', 'O', 'O', ' '},
     {' ', 'O', 'O', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', 'O', 'O', ' '},
     {' ', 'O', 'O', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', 'O', 'O', ' '},
     {' ', 'O', 'O', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', 'O', 'O', ' '},
     {' ', 'O', 'O', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', 'O', 'O', ' '},
     {' ', 'O', 'O', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {'I', 'I', 'I', 'I'},
     {' ', ' ', ' ', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', 'O', 'O', ' '},
     {' ', 'O', 'O', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', 'T', ' ', ' '},
     {'T', 'T', 'T', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', 'S', 'S', ' '},
     {'S', 'S', ' ', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {'Z', 'Z', ' ', ' '},
     {' ', 'Z', 'Z', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {'J', ' ', ' ', ' '},
     {'J', 'J', 'J', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', ' ', 'L', ' '},
     {'L', 'L', 'L', ' '},
     {' ', ' ', ' ', ' '}}};

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
}
void block2Board()
{
}
void boardDelBlock()
{
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
