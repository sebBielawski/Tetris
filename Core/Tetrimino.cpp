#include "Tetrimino.h"
#include "Game.h"
#include "Playfield.h"

#include <map>
#include <cstdlib>


struct TetriminoUtils
{
    template<typename T>
    static void rotateClockwiseBy90Degrees(Matrix<T>& m)
    {
        size_t N = std::min(m.rowCount(), m.columnCount());
        for (size_t x = 0; x < N / 2; ++x)
        {
            for (size_t y = x; y < N - x - 1; ++y)
            {
                T temp = m.at(x, y);
                m.set(x, y, m.at(N - 1 - y, x));
                m.set(N - 1 - y, x, m.at(N - 1 - x, N - 1 - y));
                m.set(N - 1 - x, N - 1 - y, m.at(y, N - 1 - x));
                m.set(y, N - 1 - x, temp);
            }
        }
    }

    template<typename T>
    static void rotateCounterClockwiseBy90Degrees(Matrix<T>& m)
    {
        size_t N = std::min(m.rowCount(), m.columnCount());
        for (size_t x = 0; x < N / 2; ++x)
        {
            for (size_t y = x; y < N - x - 1; ++y)
            {
                T temp = m.at(x, y);
                m.set(x, y, m.at(y, N - 1 - x));
                m.set(y, N - 1 - x, m.at(N - 1 - x, N - 1 - y));
                m.set(N - 1 - x, N - 1 - y, m.at(N - 1 - y, x));
                m.set(N - 1 - y, x, temp);
            }
        }
    }
};

Tetrimino Tetrimino::create(uint8_t playfieldColumnCount)
{
    int id = rand() % 7;
    switch (id) {
    case 0:
        return Tetrimino(Id::S, Matrix<bool>({ false, true, true, true, true, false, false, false, false }, {3,3}), playfieldColumnCount);
    case 1:
        return Tetrimino(Id::Z, Matrix<bool>({ true, true, false, false, true, true, false, false, false }, {3,3}), playfieldColumnCount);
    case 2:
        return Tetrimino(Id::I, Matrix<bool>({ false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, false }, {4,4}), playfieldColumnCount);
    case 3:
        return Tetrimino(Id::O, Matrix<bool>({ true, true, true, true }, {2,2}), playfieldColumnCount);
    case 4:
        return Tetrimino(Id::L, Matrix<bool>({ false, false, true, true, true, true, false, false, false }, {3,3}), playfieldColumnCount);
    case 5:
        return Tetrimino(Id::J, Matrix<bool>({ true, false, false, true, true, true, false, false, false }, {3,3}), playfieldColumnCount);
    case 6:
        return Tetrimino(Id::T, Matrix<bool>({ false, true, false, true, true, true, false, false, false }, {3,3}), playfieldColumnCount);
    default:
        assert(false);
        return Tetrimino(Id::S, Matrix<bool>({ false, true, true, true, true, false, false, false, false }, {3,3}), playfieldColumnCount);
    }
}

Tetrimino::Tetrimino(Id id, const Matrix<bool>& matrix, uint8_t playfieldColumnCount)
    :
    _id(id),
    _matrix(matrix),
    _location({ 0, (playfieldColumnCount - static_cast<uint8_t>(matrix.columnCount())) / 2 })
{
}

bool Tetrimino::accept(const Playfield& playfield) const
{
    return playfield.accept(_matrix, _location);
}

void Tetrimino::draw(Game& game, const Playfield& playfield) const
{
    _matrix.forEach([&](size_t row, size_t col, bool val){
        if (val) {
            float width = game.playfieldRectWidth() / playfield.columnCount() * 1.0f;
            float height = game.playfieldRectHeight() / playfield.rowCount() * 1.0f;
            auto x = static_cast<int>(width * (_location.second + col));
            auto y = static_cast<int>(height * (_location.first + row));
            auto w = static_cast<int>(width);
            auto h = static_cast<int>(height);

            std::map<Id, CellId> m = {
                { Id::S, CellId::S },
                { Id::Z, CellId::Z },
                { Id::I, CellId::I },
                { Id::O, CellId::O },
                { Id::L, CellId::L },
                { Id::J, CellId::J },
                { Id::T, CellId::T }
            };

            auto it = m.find(_id);
            assert(it != m.end());
            game.drawPlayfieldCell(it->second, x, y, w, h);
        }
    });
}

void Tetrimino::hardDrop(Playfield& playfield, Game& game)
{
    int row = _location.first;
    while (playfield.accept(_matrix, { row + 1, _location.second }))
    {
        row++;
    }
    _location = { row, _location.second };
    playfield.lock(_matrix, _location);
    game.draw();
}

void Tetrimino::softDrop(Playfield& playfield, Game& game)
{
    std::pair<int, int> p = { _location.first + 1, _location.second };
    if (playfield.accept(_matrix, p))
    {
        _location = p;
    }
    else
    {
        size_t lineCount = playfield.lock(_matrix, _location);
        if (lineCount != 0)
        {
            game.onLines(lineCount);
        }
        game.newTetrimino();
    }
    game.draw();
}

void Tetrimino::rotateClockwise(const Playfield& playfield, Game& game)
{
    Matrix<bool> m = _matrix;
    TetriminoUtils::rotateClockwiseBy90Degrees(m);
    if (playfield.accept(m, _location))
    {
        _matrix = std::move(m);
        game.draw();
    }
}

void Tetrimino::rotateCounterClockwise(const Playfield& playfield, Game& game)
{
    Matrix<bool> m = _matrix;
    TetriminoUtils::rotateCounterClockwiseBy90Degrees(m);
    if (playfield.accept(m, _location))
    {
        _matrix = std::move(m);
        game.draw();
    }
}

void Tetrimino::shiftToLeft(const Playfield& playfield, Game& game)
{
    std::pair<int, int> p = { _location.first, _location.second - 1 };
    if (playfield.accept(_matrix, p))
    {
        _location = p;
        game.draw();
    }
}

void Tetrimino::shiftToRight(const Playfield& playfield, Game& game)
{
    std::pair<int, int> p = { _location.first, _location.second + 1 };
    if (playfield.accept(_matrix, p))
    {
        _location = p;
        game.draw();
    }
}
