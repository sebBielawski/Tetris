#ifndef TETRIMINO_H
#define TETRIMINO_H

#include "Matrix.h"

#include <utility>

class Game;
class Playfield;

class Tetrimino final
{
public:
    enum class Id: uint8_t { S, Z, I, O, L, J, T };
    static Tetrimino create(uint8_t playfieldColumnCount);
    
    bool accept(const Playfield& playfield) const;

    void draw(Game& game, const Playfield& playfield) const;

    void softDrop(Playfield& playfield, Game& game);
    void hardDrop(Playfield& playfield, Game& game);
    void rotateClockwise(const Playfield& playfield, Game& game);
    void rotateCounterClockwise(const Playfield& playfield, Game& game);
    void shiftToLeft(const Playfield& playfield, Game& game);
    void shiftToRight(const Playfield& playfield, Game& game);

private:
    explicit Tetrimino(Id id, const Matrix<bool>& matrix, uint8_t playfieldColumnCount);

    Id _id;
    Matrix<bool> _matrix;
    std::pair<int, int> _location;
};

#endif // TETRIMINO_H
