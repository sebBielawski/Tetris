#ifndef GAME_H
#define GAME_H

#include "Playfield.h"
#include "Tetrimino.h"

#include <inttypes.h>

enum class CellId: uint8_t { S, Z, I, O, L, J, T, Locked };

class Game
{
    friend class Tetrimino;
    friend class Playfield;

protected:
    Game();

    virtual void draw() final;

    virtual void softDrop() final;
    virtual void hardDrop() final;
    virtual void rotateClockwise() final;
    virtual void rotateCounterClockwise() final;
    virtual void leftShift() final;
    virtual void rightShift() final;

    virtual int playfieldRectHeight() const = 0;
    virtual int playfieldRectWidth() const = 0;
    virtual void drawBackground() = 0;
    virtual void drawPlayfieldCell(CellId id, int x, int y, int w, int h) = 0;
    virtual void updateGraphics() = 0;
    virtual void onLines(size_t lineCount) = 0;
    virtual void onGameOver() = 0;

private:
    void newTetrimino();

    Playfield _playfield;
    Tetrimino _currentTetrimino;
};

#endif // GAME_H
