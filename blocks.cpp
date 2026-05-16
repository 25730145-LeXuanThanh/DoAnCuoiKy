#include "block.cpp"

class Iblock : public Block
{
public:
    Iblock() : Block()
    {
        state = 0;
        updateBlock();
    }

    void rotate() override
    {
            if(state == 0) state = 1;
        else if(state == 1 ) state = 0;
        updateBlock();
    }

        void updateBlock()
    {
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++) matrix[i][j] = ' ';

        if (state == 0)
        {
        matrix[0][1] = matrix[1][1] = matrix[2][1] = matrix[3][1] = 'I';
        }
        else if(state == 1)
        {
        matrix[1][0] = matrix[1][1] = matrix[1][2] = matrix[1][3] = 'I';
        }
    }
};


class Oblock : public Block
{
public:
    Oblock() : Block()
    {
        state = 0;
        updateBlock();
    }

    void rotate() override
    {
           
    }

    void updateBlock()
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                matrix[i][j] = ' ';

        matrix[0][0] = matrix[0][1] = matrix[1][0] = matrix[1][1] = 'O';
    }
};

class Tblock : public Block
{
public:
    Tblock() : Block()
    {
        state = 0;
        updateBlock();
    }

    void rotate() override
    {
        if(state >= 0 && state < 3) state++;
        else if(state == 3 ) state = 0;
        updateBlock();
    }

    void updateBlock()
    {
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++) matrix[i][j] = ' ';

        switch (state)
        {
        case 0:
            matrix[1][0] = matrix[1][1] = matrix[1][2] = matrix[2][1] = 'T';
            break;
        case 1:
            matrix[0][1] = matrix[1][1] = matrix[2][1] = matrix[1][0] = 'T';
            break;
        case 2:
            matrix[1][0] = matrix[1][1] = matrix[1][2] = matrix[0][1] = 'T';
            break;
        case 3:
            matrix[0][1] = matrix[1][1] = matrix[2][1] = matrix[1][2] = 'T';
            break;
        }
    }
};

class Jblock : public Block
{
public:
    Jblock() : Block()
    {
        state = 0;
        updateBlock();
    }

    void rotate() override
    {
        if(state >= 0 && state < 3) state++;
        else if(state == 3 ) state = 0;
        updateBlock();
    }

    void updateBlock()
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                matrix[i][j] = ' ';

        switch(state)
        {
        case 0:
        matrix[0][1] = matrix[1][1] = matrix[2][1] = matrix[2][0] = 'J';
        break;
        case 1:
        matrix[1][0] = matrix[1][1] = matrix[1][2] = matrix[0][0] = 'J';
        break;
        case 2:
        matrix[0][1] = matrix[0][2] = matrix[1][1] = matrix[2][1] = 'J';
        break;
        case 3:
        matrix[1][0] = matrix[1][1] = matrix[1][2] = matrix[2][2] = 'J';
        break;
        }
    }
};

class Sblock : public Block
{
public:
    Sblock() : Block()
    {
        state = 0;
        updateBlock();
    }

    void rotate() override
    {
            if(state == 0) state = 1;
        else if(state == 1 ) state = 0;
        updateBlock();
    }

    void updateBlock()
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                matrix[i][j] = ' ';

        switch (state)
        {
        case 0:
            matrix[1][1] = matrix[1][2] = matrix[2][0] = matrix[2][1] = 'S';
            break;
        case 1:
            matrix[0][1] = matrix[1][1] = matrix[1][2] = matrix[2][2] = 'S';
            break;
        }
    }
};

class Lblock : public Block
{
public:
    Lblock() : Block()
    {
        state = 0;
        updateBlock();
    }

    void rotate() override
    {
        if(state >= 0 && state < 3) state++;
        else if(state == 3 ) state = 0;
        updateBlock();
    }

    void updateBlock()
    {
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++) matrix[i][j] = ' ';

        switch(state)
        {
        case 0:
        matrix[0][1] = matrix[1][1] = matrix[2][1] = matrix[2][2] = 'L';
        break;
        case 1:
        matrix[1][0] = matrix[1][1] = matrix[1][2] = matrix[2][0] = 'L';
        break;
        case 2:
        matrix[0][0] = matrix[0][1] = matrix[1][1] = matrix[2][1] = 'L';
        break;
        case 3:
        matrix[1][0] = matrix[1][1] = matrix[1][2] = matrix[0][2] = 'L';
        break;
        }
    }
};

class Zblock : public Block
{
public:
    Zblock() : Block()
    {
        state = 0;
        updateBlock();
    }

    void rotate() override
    {
            if(state == 0) state = 1;
        else if(state == 1 ) state = 0;
        updateBlock();
    }

    void updateBlock()
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                matrix[i][j] = ' ';

        switch (state)
        {
        case 0:
            matrix[1][0] = matrix[1][1] = matrix[2][1] = matrix[2][2] = 'Z';
            break;
        case 1:
            matrix[0][2] = matrix[1][2] = matrix[1][1] = matrix[2][1] = 'Z';
            break;
        }
    }
};