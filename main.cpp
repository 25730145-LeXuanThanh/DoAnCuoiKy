#include "blocks.cpp"

using namespace std;
#define H 30
#define W 15

vector<vector<char>> board(H, vector<char>(W, ' '));

std::unique_ptr<Block> currentBlock;
std::unique_ptr<Block> nextBlock;

int score = 0, speed = 1000;

char blocks[7][4][4] = {
    {{' ', 'I', ' ', ' '}, {' ', 'I', ' ', ' '}, {' ', 'I', ' ', ' '}, {' ', 'I', ' ', ' '}},
    {{' ', ' ', ' ', ' '}, {' ', 'O', 'O', ' '}, {' ', 'O', 'O', ' '}, {' ', ' ', ' ', ' '}},
    {{' ', 'T', ' ', ' '}, {'T', 'T', 'T', ' '}, {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}},
    {{' ', 'S', 'S', ' '}, {'S', 'S', ' ', ' '}, {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}},
    {{'Z', 'Z', ' ', ' '}, {' ', 'Z', 'Z', ' '}, {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}},
    {{'J', ' ', ' ', ' '}, {'J', 'J', 'J', ' '}, {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}},
    {{' ', ' ', 'L', ' '}, {'L', 'L', 'L', ' '}, {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}}};

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
void block2Board()
{
        for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                        if (blocks[b][i][j] != ' ')
                                board[y + i][x + j] = blocks[b][i][j];
}
void delBlock()
{
        for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                        if (blocks[b][i][j] != ' ')
                                board[y + i][x + j] = ' ';
}
void init()
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

void rotate()
{
        char tmp[4][4];
        for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                        tmp[j][3 - i] = currentBlock[i][j];

        char old[4][4];
        memcpy(old, currentBlock, sizeof(old));
        memcpy(currentBlock, tmp, sizeof(tmp));

        if (!canMove(0, 0))
                memcpy(currentBlock, old, sizeof(old));
}

void removeLine()
{
        for (int i = H - 2; i > 0; i--)
        {
                bool full = true;
                for (int j = 1; j < W - 1; j++)
                        if (board[i][j] == ' ')
                                full = false;

                if (full)
                {
                        score += 100;
                        if (speed > 200)
                                speed -= 5;
                        for (int ii = i; ii > 1; ii--)
                                for (int jj = 1; jj < W - 1; jj++)
                                        board[ii][jj] = board[ii - 1][jj];
                        i++;
                }
        }
}

void spawnBlock()
{
        b = nextBlock;
        nextBlock = rand() % 7;
        for (int i = 0; i < 4; i++)
        {
                for (int j = 0; j < 4; j++)
                {
                        currentBlock[i][j] = blocks[b][i][j];
                }
        }
}

void resetGame()
{
        init();
        score = 0;
        speed = 1000;
        x = 5;
        y = 1;
        spawnBlock();
}

void hardDrop() {
    int dropped = 0;
    while (canMove(0, 1)) {
        y++;
        dropped++;
    }
    score += dropped;
    block2Board();
    removeLine();
    
    x = 5; y = 1;
    spawnBlock();

    if (!canMove(0, 0)) {
                gotoXY(0,H+2);
                cout<<"\033[91mGAME OVER\033[0m\nScore: "<<score<<endl;

                cout<<"\n[R] Restart  [Q] Quit";

            while(1){
            char c=getch();
            if(c=='r'||c=='R'){ resetGame(); break; }
            if(c=='q'||c=='Q') exit(0);}
    }
}

int main()
{
        DWORD lastFall = GetTickCount();

        srand(time(0));

        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD mode = 0;
        GetConsoleMode(hOut, &mode);
        mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, mode);

        hideCursor();
        resetGame();

        while (1)
        {
                delBlock();

                if (kbhit())
                {
                        char c = getch();
                        if (c == 'a' && canMove(-1, 0))
                                x--;
                        if (c == 'd' && canMove(1, 0))
                                x++;
                        if (c == 's' && canMove(0, 1))
                        {
                                y++;
                                score += 1;
                        }
                        if (c == 'w')
                                rotate();
                        if (c == ' ')
                                hardDrop();
                        if (c == 'q')
                                break;
                }

                if (GetTickCount() - lastFall >= speed)
                {
                        if (canMove(0, 1))
                        {
                                y++;
                        }
                        else
                        {

                                block2Board();
                                removeLine();

                                x = 5;
                                y = 1;
                                spawnBlock();

                                if (!canMove(0, 0))
                                {

                                        gotoXY(0, H + 2);
                                        cout << "\033[91mGAME OVER\033[0m\nScore: " << score << endl;

                                        cout << "\n[R] Restart  [Q] Quit";

                                        while (1)
                                        {
                                                char c = getch();
                                                if (c == 'r' || c == 'R')
                                                {
                                                        resetGame();
                                                        break;
                                                }
                                                if (c == 'q' || c == 'Q')
                                                        return 0;
                                        }
                                }
                        }
                        lastFall = GetTickCount();
                }

                block2Board();
                draw();

                Sleep(25);
        }
}