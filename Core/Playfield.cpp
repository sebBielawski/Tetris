#include "Playfield.h"
#include "Game.h"

#include <vector>

template<typename T>
static Matrix<T> makeMatrix(const std::pair<uint8_t, uint8_t>& dimensions, T fillValue)
{
    size_t n = dimensions.first * dimensions.second;
    return Matrix<T>(std::vector<bool>(n, fillValue), dimensions);
}

Playfield::Playfield(const std::pair<uint8_t, uint8_t>& dimensions)
    :
    _matrix(makeMatrix(dimensions, false))
{
}

size_t Playfield::columnCount() const
{
    return _matrix.columnCount();
}

size_t Playfield::rowCount() const
{
    return _matrix.rowCount();
}

bool Playfield::accept(const Matrix<bool>& matrix, const std::pair<int, int>& location) const
{
    for (size_t r = 0; r < matrix.rowCount(); ++r)
    {
        for (size_t c = 0; c < matrix.columnCount(); ++c)
        {
            if (matrix.at(r, c))
            {
                size_t row = r + location.first;
                size_t col = c + location.second;
                if (row >= _matrix.rowCount() || col >= _matrix.columnCount() || _matrix.at(row, col))
                {
                    return false;
                }
            }
        }
    }
    return true;
}

size_t Playfield::lock(const Matrix<bool>& matrix, const std::pair<int, int>& location)
{
    matrix.forEach([&](size_t row, size_t col, bool val){
        if (val) {
            _matrix.set(row + location.first, col + location.second, true);
        }
    });

    size_t lineCount = 0;
    for (size_t row = _matrix.rowCount() - 1; row > 0; --row)
    {
        bool line = true;
        for (size_t col = 0; line && col < _matrix.columnCount(); ++col)
        {
            line &= _matrix.at(row, col);
        }
        if (line)
        {
            lineCount++;
            for (size_t i = row; i > 0; --i)
            {
                for (size_t j = 0; j < _matrix.columnCount(); ++j)
                {
                    _matrix.set(i, j, _matrix.at(i - 1, j));
                }
            }
            for (size_t c = 0; c < _matrix.columnCount(); ++c)
            {
                _matrix.set(0, c, false);
            }
            row++;
        }
    }
    return lineCount;
}

void Playfield::draw(Game& game) const
{
    _matrix.forEach([&](size_t row, size_t col, bool val){
        if (val) {
            float width = game.playfieldRectWidth() / columnCount() * 1.0f;
            float height = game.playfieldRectHeight() / rowCount() * 1.0f;
            auto x = static_cast<int>(width * col);
            auto y = static_cast<int>(height * row);
            auto w = static_cast<int>(width);
            auto h = static_cast<int>(height);
            game.drawPlayfieldCell(CellId::Locked, x, y, w, h);
        }
    });
}
