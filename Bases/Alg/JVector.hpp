//#include <bits/stdc++.h>

template <typename T>
class JVector : public std::vector<T>
{
public:
  JVector();
  JVector(const size_t &);
  JVector(const size_t &, const size_t &);
  JVector(const size_t &, std::function<T()>);

  inline T &at(const size_t &);
  inline const T &at(const size_t &) const;

  void operator*=(const T &);
  void operator*=(const JVector &);
  void operator/=(const T &);
  void operator/=(const JVector &);
  void operator+=(const T &);
  void operator+=(const JVector &);
  void operator-=(const T &);
  void operator-=(const JVector &);

  inline JVector<T> operator*(const T &)const;
  inline JVector<T> operator*(const JVector<T> &)const;
  inline JVector<T> operator/(const T &) const;
  inline JVector<T> operator/(const JVector<T> &) const;
  inline JVector<T> operator+(const T &) const;
  inline JVector<T> operator+(const JVector<T> &) const;
  inline JVector<T> operator-(const T &) const;
  inline JVector<T> operator-(const JVector<T> &) const;

  void Fill(T);
  void Fill(std::function<T()>);
  void Operate(std::function<T(T)>);
  JVector<T> OnFunction(std::function<T(T)>);

  T Max();
  //T MaximumValue();
  //T MaximumIndex();
  T Summation();

  void ConsolePrint();
  void ConsolePrint(std::string);
};

#include "JVector.cpp"