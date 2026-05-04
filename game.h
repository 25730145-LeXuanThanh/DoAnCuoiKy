#include "game.h"
#include <random>

// -------------------------------------------------------
// Constructor / Destructor
// -------------------------------------------------------

Game::Game()
    : grid(Grid()),
      blocks(GetAllBlocks()),
      currentBlock(GetRandomBlock()),
      nextBlock(GetRandomBlock()),
      gameOver(false),
      score(0)
{
    InitAudioDevice();
    music     = LoadMusicStream("Sounds/music.mp3");
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound  = LoadSound("Sounds/clear.mp3");
    PlayMusicStream(music);
}

Game::~Game()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

// -------------------------------------------------------
// Block helpers
// -------------------------------------------------------

Block Game::GetRandomBlock()
{
    if (blocks.empty())
        blocks = GetAllBlocks();

    int index = rand() % blocks.size();
    Block block = blocks[index];
    blocks.erase(blocks.begin() + index);
    return block;
}

std::vector<Block> Game::GetAllBlocks()
{
    return { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
}

// -------------------------------------------------------
// Draw
// -------------------------------------------------------

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11, 11);   // offset cho lưới chính

    // Vẽ preview khối tiếp theo
    switch (nextBlock.id)
    {
    case 3: nextBlock.Draw(255, 290); break;  // I – cần dịch nhỏ hơn
    case 4: nextBlock.Draw(255, 280); break;  // O
    default:nextBlock.Draw(270, 270); break;
    }
}

// -------------------------------------------------------
// Input
// -------------------------------------------------------

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed != 0)
    {
        Reset();
        return;
    }

    switch (keyPressed)
    {
    case KEY_LEFT:  MoveBlockLeft();  break;
    case KEY_RIGHT: MoveBlockRight(); break;
    case KEY_DOWN:  MoveBlockDown();  UpdateScore(0, 1); break;
    case KEY_UP:    RotateBlock();    break;
    default: break;
    }
}

// -------------------------------------------------------
// Block movement
// -------------------------------------------------------

void Game::MoveBlockLeft()
{
    if (!gameOver)
    {
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || !BlockFits())
            currentBlock.Move(0, 1);
    }
}

void Game::MoveBlockRight()
{
    if (!gameOver)
    {
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || !BlockFits())
            currentBlock.Move(0, -1);
    }
}

void Game::MoveBlockDown()
{
    if (!gameOver)
    {
        currentBlock.Move(1, 0);
        if (IsBlockOutside() || !BlockFits())
        {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.IsCellOutside(item.row, item.column))
            return true;
    }
    return false;
}

void Game::RotateBlock()
{
    if (!gameOver)
    {
        currentBlock.Rotate();
        if (IsBlockOutside() || !BlockFits())
            currentBlock.UndoRotation();
        else
            PlaySound(rotateSound);
    }
}

// -------------------------------------------------------
// LockBlock – phần Khôi viết từ đây xuống
// -------------------------------------------------------

void Game::LockBlock()
{
    // 1. Ghi các ô của currentBlock vào lưới
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }

    // 2. Lấy khối tiếp theo
    currentBlock = nextBlock;
    nextBlock    = GetRandomBlock();

    // 3. Xoá các hàng đầy và tính điểm
    int rowsCleared = grid.ClearFullRows();
    if (rowsCleared > 0)
    {
        PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
    }

    // 4. Kiểm tra game over – nếu khối mới ngay lập tức không fit → thua
    if (!BlockFits())
    {
        gameOver = true;
    }
}

// -------------------------------------------------------
// BlockFits
// -------------------------------------------------------

bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (!grid.IsCellEmpty(item.row, item.column))
            return false;
    }
    return true;
}

// -------------------------------------------------------
// Reset
// -------------------------------------------------------

void Game::Reset()
{
    grid.Initialize();
    blocks      = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock    = GetRandomBlock();
    score        = 0;
    gameOver     = false;
}

// -------------------------------------------------------
// UpdateScore
// -------------------------------------------------------

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    // Bảng điểm chuẩn Tetris
    switch (linesCleared)
    {
    case 1: score += 100; break;
    case 2: score += 300; break;
    case 3: score += 500; break;
    default: break;
    }
    score += moveDownPoints;
}
