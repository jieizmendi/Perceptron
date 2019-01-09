//#include "JMatrix.hpp"

/****************************
 * Constructors
****************************/
template <class T>
JMatrix<T>::JMatrix() : std::vector<T>() {}

template <class T>
JMatrix<T>::JMatrix(const size_t &n_rows, const size_t &n_cols) : std::vector<T>(n_rows * n_cols)
{
    _n_rows = n_rows;
    _n_cols = n_cols;
}

template <class T>
JMatrix<T>::JMatrix(const size_t &n_rows, const size_t &n_cols, const T &constant) : std::vector<T>(n_rows * n_cols, constant)
{
    _n_rows = n_rows;
    _n_cols = n_cols;
}

template <class T>
JMatrix<T>::JMatrix(const size_t &n_rows, const size_t &n_cols, std::function<T()> f) : std::vector<T>(n_rows * n_cols)
{
    _n_rows = n_rows;
    _n_cols = n_cols;
    for (auto it = this->begin(); it != this->end(); it++)
    {
        *it = f();
    }
}

template <class T>
void JMatrix<T>::resize(const size_t &n_rows, const size_t &n_cols)
{
    std::vector<T>::resize(n_rows * n_cols);
    _n_rows = n_rows;
    _n_cols = n_cols;
}

/****************************
 * Operators
****************************/
template <class T>
inline T &JMatrix<T>::at(const size_t &i_rows, const size_t &i_cols)
{
    return (*this)[_n_rows * i_cols + i_rows];
}

template <class T>
inline const T &JMatrix<T>::at(const size_t &i_rows, const size_t &i_cols) const
{
    return (*this)[_n_rows * i_cols + i_rows];
}

template <class T>
inline const JVector<T> JMatrix<T>::col(const size_t &index) const
{
    JVector<T> result(_n_rows);
    for (size_t i = 0; i < _n_rows; i++)
    {
        result.at(i) = this->at(i, index);
    }
    return result;
}

template <class T>
inline const JVector<T> JMatrix<T>::row(const size_t &index) const
{
    JVector<T> result(_n_cols);
    for (size_t i = 0; i < _n_cols; i++)
    {
        result.at(i) = this->at(index, i);
    }
    return result;
}

template <class T>
inline const size_t JMatrix<T>::RowsSize() const
{
    return _n_rows;
}

template <class T>
inline const size_t JMatrix<T>::ColsSize() const
{
    return _n_cols;
}

template <class T>
void JMatrix<T>::operator*=(const T &value)
{
    for (auto it = this->begin(); it != this->end(); it++)
    {
        *it *= value;
    }
}

template <class T>
void JMatrix<T>::operator*=(const JMatrix &value)
{
    if (this->size() != value.size())
        return;

    auto it = this->begin();
    auto _it = value.begin();
    while (it != this->end() || _it != value.end())
    {
        *it *= (*_it);
        it++;
        _it++;
    }
}

template <class T>
void JMatrix<T>::operator/=(const T &value)
{
    for (auto it = this->begin(); it != this->end(); it++)
    {
        *it /= value;
    }
}

template <class T>
void JMatrix<T>::operator/=(const JMatrix &value)
{
    if (this->size() != value.size())
        return;

    auto it = this->begin();
    auto _it = value.begin();
    while (it != this->end() || _it != value.end())
    {
        *it /= (*_it);
        it++;
        _it++;
    }
}

template <class T>
void JMatrix<T>::operator-=(const T &value)
{
    for (auto it = this->begin(); it != this->end(); it++)
    {
        *it -= value;
    }
}

template <class T>
void JMatrix<T>::operator-=(const JMatrix &value)
{
    if (this->size() != value.size())
        return;

    auto it = this->begin();
    auto _it = value.begin();
    while (it != this->end() || _it != value.end())
    {
        *it -= (*_it);
        it++;
        _it++;
    }
}

/****************************
 * Functions
****************************/
template <class T>
void JMatrix<T>::ConsolePrint()
{
    if (_n_rows == 0 || _n_cols == 0)
        return;

    TextTable t('-', '|', '+');

    for (size_t i = 0; i < _n_rows; i++)
    {
        for (size_t j = 0; j < _n_cols; j++)
        {
            t.add(std::to_string(this->at(i, j)));
        }
        t.endOfRow();
    }
    std::cout << t;
}

template <class T>
void JMatrix<T>::ConsolePrint(std::string str)
{
    if (_n_rows == 0 || _n_cols == 0)
        return;

    TextTable t('-', '|', '+');

    t.add(str);

    if (_n_cols > 1)
        for (int j = 0; j < _n_cols - 1; j++)
            t.add("");
    t.endOfRow();

    for (size_t i = 0; i < _n_rows; i++)
    {
        for (size_t j = 0; j < _n_cols; j++)
        {
            t.add(std::to_string(this->at(i, j)));
        }
        t.endOfRow();
    }
    std::cout << t;
}

template <class T>
void JMatrix<T>::Fill(T value)
{
    std::fill(this->begin(), this->end(), value);
}

template <class T>
void JMatrix<T>::Fill(std::function<T()> f)
{
    for (auto it = this->begin(); it != this->end(); it++)
    {
        *it = f();
    }
}