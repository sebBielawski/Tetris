#include "Game.h"


Game::Game() :
    _playfield({ 22, 10 }),
    _currentTetrimino(Tetrimino::create(static_cast<uint8_t>(_playfield.columnCount())))
{ 
}

void Game::draw()
{
    drawBackground();
    _playfield.draw(*this);
    _currentTetrimino.draw(*this, _playfield);
    updateGraphics();
}

void Game::newTetrimino()
{
    Tetrimino t = Tetrimino::create(static_cast<uint8_t>(_playfield.columnCount()));
    if (t.accept(_playfield))
    {
        _currentTetrimino = t;
    }
    else
    {
        onGameOver();
    }
}

void Game::softDrop()
{
    _currentTetrimino.softDrop(_playfield, *this);
}

void Game::hardDrop()
{
    _currentTetrimino.hardDrop(_playfield, *this);
}

void Game::rotateClockwise()
{
    _currentTetrimino.rotateClockwise(_playfield, *this);
}

void Game::rotateCounterClockwise()
{
    _currentTetrimino.rotateCounterClockwise(_playfield, *this);
}

void Game::leftShift()
{
    _currentTetrimino.shiftToLeft(_playfield, *this);
}

void Game::rightShift()
{
    _currentTetrimino.shiftToRight(_playfield, *this);
}

