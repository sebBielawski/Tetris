#ifndef PLAYFIELD_H
#define PLAYFIELD_H

#include "Matrix.h"

class Game;
class Playfield final
{
    friend class Tetrimino;
public:
    explicit Playfield(const std::pair<uint8_t, uint8_t>& dimensions);
    void draw(Game& game) const;
    size_t columnCount() const;

private:
    size_t rowCount() const;
    bool accept(const Matrix<bool>& matrix, const std::pair<int, int>& location) const;
    size_t lock(const Matrix<bool>& matrix, const std::pair<int, int>& location);

    Matrix<bool> _matrix;
};


#endif // PLAYFIELD_H
