#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>

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
};