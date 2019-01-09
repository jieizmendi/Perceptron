//#include "JVector.hpp"

/****************************************
 * Constructors
****************************************/
template <class T>
JVector<T>::JVector() : std::vector<T>() {}

template <class T>
JVector<T>::JVector(const size_t &size) : std::vector<T>(size) {}

template <class T>
JVector<T>::JVector(const size_t &size, const size_t &constant) : std::vector<T>(size, constant) {}

template <class T>
JVector<T>::JVector(const size_t &size, std::function<T()> f) : std::vector<T>(size)
{
    for (auto it = this->begin(); it != this->end(); it++)
    {
        *it = f();
    }
}

/****************************************
 * Operators
****************************************/
template <class T>
inline T &JVector<T>::at(const size_t &index)
{
    return (*this)[index];
}

template <class T>
inline const T &JVector<T>::at(const size_t &index) const
{
    return (*this)[index];
}

template <class T>
void JVector<T>::operator*=(const T &value)
{
    for (auto it = this->begin(); it != this->end(); it++)
    {
        *it *= value;
    }
}

template <class T>
void JVector<T>::operator*=(const JVector &value)
{
    if (this->size() != value.size())
        std::logic_error(std::string("Different sizes"));

    for (size_t i = 0; i != this->size(); i++)
        this->at(i) *= value.at(i);
}

template <class T>
void JVector<T>::operator/=(const T &value)
{
    for (auto it = this->begin(); it != this->end(); it++)
    {
        *it /= value;
    }
}

template <class T>
void JVector<T>::operator/=(const JVector &value)
{
    if (this->size() != value.size())
        std::logic_error(std::string("Different sizes"));

    for (size_t i = 0; i != this->size(); i++)
        this->at(i) /= value->at(i);
}

template <class T>
void JVector<T>::operator+=(const T &value)
{
    for (auto it = this->begin(); it != this->end(); it++)
    {
        *it += value;
    }
}

template <class T>
void JVector<T>::operator+=(const JVector &value)
{
    if (this->size() != value.size())
        std::logic_error(std::string("Different sizes"));

    for (size_t i = 0; i != this->size(); i++)
        this->at(i) += value.at(i);
}

template <class T>
void JVector<T>::operator-=(const T &value)
{
    for (auto it = this->begin(); it != this->end(); it++)
    {
        *it -= value;
    }
}

template <class T>
void JVector<T>::operator-=(const JVector &value)
{
    if (this->size() != value.size())
        std::logic_error(std::string("Different sizes"));

    for (size_t i = 0; i != this->size(); i++)
        this->at(i) -= value->at(i);
}

template <class T>
inline JVector<T> JVector<T>::operator*(const T &value) const
{
    JVector<T> result(this->size());

    for (size_t i = 0; i != this->size(); i++)
        result.at(i) = this->at(i) * value;

    return result;
}

template <class T>
inline JVector<T> JVector<T>::operator*(const JVector &value) const
{
    if (this->size() != value.size())
        std::logic_error(std::string("Different sizes"));

    JVector<T> result(this->size());

    for (size_t i = 0; i != this->size(); i++)
        result.at(i) = this->at(i) * value.at(i);

    return result;
}

template <class T>
inline JVector<T> JVector<T>::operator/(const T &value) const
{
    JVector<T> result(this->size());

    for (size_t i = 0; i != this->size(); i++)
        result.at(i) = this->at(i) / value;

    return result;
}

template <class T>
inline JVector<T> JVector<T>::operator/(const JVector &value) const
{
    if (this->size() != value.size())
        std::logic_error(std::string("Different sizes"));

    JVector<T> result(this->size());

    for (size_t i = 0; i != this->size(); i++)
        result.at(i) = this->at(i) / value->at(i);

    return result;
}

template <class T>
inline JVector<T> JVector<T>::operator+(const T &value) const
{
    JVector<T> result(this->size());

    for (size_t i = 0; i != this->size(); i++)
        result.at(i) = this->at(i) + value;

    return result;
}

template <class T>
inline JVector<T> JVector<T>::operator+(const JVector &value) const
{
    if (this->size() != value.size())
        std::logic_error(std::string("Different sizes"));

    JVector<T> result(this->size());

    for (size_t i = 0; i != this->size(); i++)
        result.at(i) = this->at(i) + value->at(i);

    return result;
}

template <class T>
inline JVector<T> JVector<T>::operator-(const T &value) const
{
    JVector<T> result(this->size());

    for (size_t i = 0; i != this->size(); i++)
        result.at(i) = this->at(i) - value;

    return result;
}

template <class T>
inline JVector<T> JVector<T>::operator-(const JVector &value) const
{
    if (this->size() != value.size())
        std::logic_error(std::string("Different sizes"));

    JVector<T> result(this->size());

    for (size_t i = 0; i != this->size(); i++)
        result.at(i) = this->at(i) - value.at(i);

    return result;
}

template <class T>
T JVector<T>::Summation()
{
    T result = 0.0;
    for (auto it = this->begin(); it != this->end(); it++)
        result += *it;
}

template <class T>
T JVector<T>::Max()
{
    auto pos = std::max_element(std::begin(this), std::end(this));
    return (*this)[pos];
}

template <class T>
void JVector<T>::ConsolePrint()
{
    TextTable t('-', '|', '+');

    for (auto i = 0; i < this->size(); i++)
    {
        t.add(std::to_string(this->at(i)));
        t.endOfRow();
    }
    std::cout << t;
}

template <class T>
void JVector<T>::ConsolePrint(std::string str)
{
    TextTable t('-', '|', '+');
    t.add(str);
    t.endOfRow();

    for (auto i = 0; i < this->size(); i++)
    {
        t.add(std::to_string(this->at(i)));
        t.endOfRow();
    }
    std::cout << t;
}

template <class T>
void JVector<T>::Fill(T value)
{
    std::fill(this->begin(), this->end(), value);
}

template <class T>
void JVector<T>::Fill(std::function<T()> f)
{
    for (auto it = this->begin(); it != this->end(); it++)
        *it = f();
}

template <class T>
void JVector<T>::Operate(std::function<T(T)> f)
{
    for (auto it = this->begin(); it != this->end(); it++)
        *it = f(*it);
}

template <class T>
JVector<T> JVector<T>::OnFunction(std::function<T(T)> f)
{
    JVector<T> result(this->size());

    for (auto i = 0; i < this->size(); i++)
        result.at(i) = f(this->at(i));
    
    return result;
}
