#include "blocks.cpp"

using namespace std;
#define H 30
#define W 15

vector<vector<char>> board(H, vector<char>(W, ' '));

std::unique_ptr<Block> currentBlock;
std::unique_ptr<Block> nextBlock;

int score = 0, speed = 1000;

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

unique_ptr<Block> randomBlock()
{
        int r = rand() % 7;
        switch (r) {
        case 0: return make_unique<Iblock>();
        case 1: return make_unique<Jblock>();
        case 2: return make_unique<Lblock>();
        case 3: return make_unique<Oblock>();
        case 4: return make_unique<Sblock>();
        case 5: return make_unique<Tblock>();
        case 6: return make_unique<Zblock>();
        default: return make_unique<Tblock>();
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

void init()
{
        for (int i = 0; i < H; i++)
                for (int j = 0; j < W; j++)
                        if (i == 0 || i == H - 1 || j == 0 || j == W - 1)
                                board[i][j] = '#';
                        else
                                board[i][j] = ' ';

        currentBlock = randomBlock();
        nextBlock = randomBlock();
}
// ===== DRAW =====
void drawBoard()
{
        string s = "";
        s.clear();

        for (int i = 0; i < H; i++)
        {
                for (int j = 0; j < W; j++)
                {
                        if (board[i][j] == '#') s += "\033[37m";
                        if(i==0 && j==0) s += "┌─";
                        else if(i==0 && j==W-1) s += "┐";
                        else if(i==H-1 && j==0) s += "└─";
                        else if(i==H-1 && j==W-1) s += "┘";
                        else if(i==0 || i==H-1) s += "──";
                        else if(j==0 || j==W-1) s += "│ ";
                        else if(board[i][j]==' ') s+="\033[0m. ";
                        else s+=getColor(board[i][j])+"▓▓";
                }
                if (i != H - 1) s += "\033[0m\n";
        }
        gotoXY(0, 0);
        cout << s;
        cout.flush();
}

void drawScore()
{
    static int lastScore = -1;
    if (score == lastScore)
        return;
    lastScore = score;
    int uiX = W * 2 + 4;
    gotoXY(uiX, 2);
    cout << "\033[37m";
    cout << "SCORE: " << score << "     ";
    cout.flush();
}

void drawNext()
{
    static Block* lastNext = nullptr;
    if (nextBlock.get() == lastNext)
    return;
    lastNext = nextBlock.get();
    int uiX = W * 2 + 4;

    gotoXY(uiX, 5);
    cout << "\033[37mNEXT";

    for (int i = 0; i < 4; i++)
    {
        gotoXY(uiX, 7 + i);
        cout << "        ";
    }

    for (int i = 0; i < 4; i++)
        {
        gotoXY(uiX, 7 + i);
        for (int j = 0; j < 4; j++) 
        {
            char cell = nextBlock->getCell(i, j);
            if (cell != ' ')
            {
                cout << getColor(cell)
                     << "▓▓";
            }
            else
            {
                cout << "  ";
            }
        }
        }
    cout << "\033[0m";
    cout.flush();
}

void drawGameOver()
{
    int uiX = W * 2 + 4;
    gotoXY(uiX, 13);
    cout << "\033[91mGAME OVER\033[0m";
    gotoXY(uiX, 15);
    cout << "Score: " << score;
    gotoXY(uiX, 17);
    cout << "[R] Restart";
    gotoXY(uiX, 18);
    cout << "[Q] Quit";
    cout.flush();
}

void clearGameOver()
{
    int uiX = W * 2 + 4;

    for (int y = 13; y <= 18; y++)
    {
        gotoXY(uiX, y);
        cout << "                ";
    }

    cout.flush();
}

void removeLine()
{
        int linesCleared = 0;
        for (int i = H - 2; i > 0; i--)
        {
                bool full = true;
                for (int j = 1; j < W - 1; j++)
                        if (board[i][j] == ' ')
                                full = false;

                if (full)
                {
                        linesCleared++;
                        if (speed > 200)
                                speed -= 5;
                        for (int ii = i; ii > 1; ii--)
                                for (int jj = 1; jj < W - 1; jj++)
                                        board[ii][jj] = board[ii - 1][jj];
                        i++;
                }
        }
        switch(linesCleared)
        {
        case 1: score += 100; break;
        case 2: score += 300; break;
        case 3: score += 500; break;
        }
}

void spawnBlock()
{
        currentBlock = move(nextBlock);
        nextBlock = randomBlock();
}

void resetGame()
{
        init();
        score = 0;
        speed = 1000;
        clearGameOver();
        spawnBlock();
}

void hardDrop()
{
        int dropped = 0;
        while (currentBlock->canMove(0, 1, board)) {
        currentBlock->move(0, 1, board);
        dropped++;
        }
        score += dropped;
        currentBlock->block2Board(board);
        removeLine();

        spawnBlock();
}

int main()
{
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
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
                currentBlock->delBlock(board);

                if (kbhit())
                {
                        char c = getch();
                        if (c == 'a')
                                currentBlock->move(-1, 0, board);
                        if (c == 'd')
                                currentBlock->move(1, 0, board);
                        if (c == 's')
                        {
                                currentBlock->move(0, 1, board);
                                score += 1;
                        }
                        if (c == 'w')
                                currentBlock->rotate();
                        if (c == ' ')
                                hardDrop();
                        if (c == 'q')
                                break;
                }

                 if(GetTickCount() - lastFall >= speed){
        if (currentBlock->canMove(0, 1, board)) {
        currentBlock->move(0, 1, board);
        }
        else
        {
           
            currentBlock->block2Board(board);
            removeLine();

            
            spawnBlock();

           

            if(!currentBlock->canMove(0, 0, board)){
                drawGameOver();

            while(1){
            char c=getch();
            if(c=='r'||c=='R'){ resetGame(); break; }
            if(c=='q'||c=='Q') return 0;}
            }
        }
            lastFall = GetTickCount();
    }
                 currentBlock->block2Board(board);
                drawBoard();
                drawScore();
                drawNext();

                Sleep(25);
        }
}
