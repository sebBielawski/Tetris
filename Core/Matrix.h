#ifndef MATRIX_H
#define MATRIX_H

#include <cassert>
#include <functional>
#include <vector>


template<typename T>
class Matrix final
{
public:
    Matrix(
        const std::vector<T>& data,
        const std::pair<size_t, size_t>& dimensions);

    size_t columnCount() const;
    size_t rowCount() const;

    T at(size_t row, size_t col) const;
    void set(size_t row, size_t col, T val);

    void forEach(std::function<void(size_t row, size_t col, T val)> onCell) const;

private:
    std::vector<T> _data;
    size_t _colCount;
    size_t _rowCount;
};

template<typename T>
Matrix<T>::Matrix(
        const std::vector<T>& data,
        const std::pair<size_t, size_t>& dimensions) :
    _data(data),
    _rowCount(dimensions.first),
    _colCount(dimensions.second)
{
    assert(data.size() == _rowCount * _colCount);
}


template<typename T>
size_t Matrix<T>::rowCount() const
{ return _rowCount; }


template<typename T>
size_t Matrix<T>::columnCount() const
{ return _colCount; }


template<typename T>
T Matrix<T>::at(size_t row, size_t col) const
{
    size_t index = (row * columnCount()) + col;
    assert(index >= 0);
    assert(index < _data.size());
    return _data.at(index);
}


template<typename T>
void Matrix<T>::set(size_t row, size_t col, T val)
{
    size_t index = (row * columnCount()) + col;
    assert(index >= 0);
    assert(index < _data.size());
    _data[index] = val;
}


template<typename T>
void Matrix<T>::forEach(std::function<void(size_t row, size_t col, T val)> onCell) const
{
    for (size_t row = 0; row < rowCount(); ++row)
    {
        for (size_t col = 0; col < columnCount(); ++col)
        {
            onCell(row, col, at(row, col));
        }
    }
}


#endif // MATRIX_H
