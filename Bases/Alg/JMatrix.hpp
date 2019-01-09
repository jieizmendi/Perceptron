template <typename T>
class JMatrix : std::vector<T>
{
  size_t _n_cols;
  size_t _n_rows;

public:
  //Constructors
  JMatrix();
  JMatrix(const size_t &, const size_t &);
  JMatrix(const size_t &, const size_t &, const T &);
  JMatrix(const size_t &, const size_t &, std::function<T()>);

  void resize(const size_t &, const size_t &);

  //Operators
  inline T &at(const size_t &, const size_t &);
  inline const T &at(const size_t &, const size_t &) const;

  inline const JVector<T> col(const size_t &) const;
  inline const JVector<T> row(const size_t &) const;

  inline const size_t RowsSize() const;
  inline const size_t ColsSize() const;

  void operator*=(const T &);
  void operator*=(const JMatrix<T> &);
  void operator*=(const JVector<T> &);
  void operator/=(const T &);
  void operator/=(const JMatrix<T> &);
  void operator/=(const JVector<T> &);
  void operator+=(const T &);
  void operator+=(const JMatrix<T> &);
  void operator+=(const JVector<T> &);
  void operator-=(const T &);
  void operator-=(const JMatrix<T> &);
  void operator-=(const JVector<T> &);

  inline JMatrix<T> operator*(const T &)const;
  inline JMatrix<T> operator*(const JMatrix<T> &)const;
  inline JMatrix<T> operator*(const JVector<T> &)const;
  inline JMatrix<T> operator/(const T &) const;
  inline JMatrix<T> operator/(const JMatrix<T> &) const;
  inline JMatrix<T> operator/(const JVector<T> &) const;
  inline JMatrix<T> operator+(const T &) const;
  inline JMatrix<T> operator+(const JMatrix<T> &) const;
  inline JMatrix<T> operator+(const JVector<T> &) const;
  inline JMatrix<T> operator-(const T &) const;
  inline JMatrix<T> operator-(const JMatrix<T> &) const;
  inline JMatrix<T> operator-(const JVector<T> &) const;

  void Fill(T);
  void Fill(std::function<T()>);

  //Printers
  void ConsolePrint();
  void ConsolePrint(std::string);
};

#include "JMatrix.cpp"