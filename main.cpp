#include "blocks.cpp"

using namespace std;
#define H 30
#define W 15

vector<vector<char>> board(H, vector<char>(W, ' '));

std::unique_ptr<Block> currentBlock;
std::unique_ptr<Block> nextBlock;

int score = 0, speed = 1000;

// ===== COLOR =====
void drawScore();
void drawNext();

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
void draw(){
    string s = "";
    s.clear();

    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            if(board[i][j]=='#') s+="\033[37m##";
            else if(board[i][j]==' ') s+="  ";
            else s+=getColor(board[i][j])+"[]";
        }
        s+="\033[0m\n";
    }
    gotoXY(0,0);
    cout << s;
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
                     << "[]";
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
        currentBlock = move(nextBlock);
        nextBlock = randomBlock();
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
