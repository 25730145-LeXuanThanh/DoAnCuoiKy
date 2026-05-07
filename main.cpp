#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define H 40
#define W 15

char board[H][W];

int x, y, b, nextBlock, score = 0;
int speed = 200;

// ===== BLOCK =====
char blocks[7][4][4] = {
    {{' ','I',' ',' '},{' ','I',' ',' '},{' ','I',' ',' '},{' ','I',' ',' '}},
    {{' ',' ',' ',' '},{' ','O','O',' '},{' ','O','O',' '},{' ',' ',' ',' '}},
    {{' ','T',' ',' '},{'T','T','T',' '},{' ',' ',' ',' '},{' ',' ',' ',' '}},
    {{' ','S','S',' '},{'S','S',' ',' '},{' ',' ',' ',' '},{' ',' ',' ',' '}},
    {{'Z','Z',' ',' '},{' ','Z','Z',' '},{' ',' ',' ',' '},{' ',' ',' ',' '}},
    {{'J',' ',' ',' '},{'J','J','J',' '},{' ',' ',' ',' '},{' ',' ',' ',' '}},
    {{' ',' ','L',' '},{'L','L','L',' '},{' ',' ',' ',' '},{' ',' ',' ',' '}}
};