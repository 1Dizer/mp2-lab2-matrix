// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <cstdlib>
#include <stdexcept>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
        throw out_of_range("Vector size is too large");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      sz = v.sz;
      pMem = new T[sz];
      for (int i = 0; i < sz; ++i)
          pMem[i] = v.pMem[i];
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = 0;
      pMem = nullptr;
      std::swap(sz, v.sz);
      std::swap(pMem, v.pMem);
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v)
          return *this;
      sz = v.sz;
      delete[] pMem;
      pMem = new T[sz];
      for (int i = 0; i < sz; ++i)
          pMem[i] = v.pMem[i];
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this == &v)
          return *this;

      delete[] pMem;
      sz = v.sz;
      pMem = v.pMem;
      v.sz = 0;
      v.pMem = nullptr;
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      if (ind >= sz)
          throw out_of_range("Index out of range");
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      if (ind >= sz)
          throw out_of_range("Index out of range");
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz)
          throw out_of_range("Index out of range");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz)
          throw out_of_range("Index out of range");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (this == &v)
          return true;
      if (sz != v.sz)
          return false;
      for (int i = 0; i < sz; ++i)
          if (pMem[i] != v.pMem[i])
              return false;
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector tmp(sz);
      for (int i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] + val;
      return tmp;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector tmp(sz);
      for (int i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] - val;
      return tmp;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector tmp(sz);
      for (int i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] * val;
      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw sz - v.sz;

      TDynamicVector<T> tmp = *this;
      for (int i = 0; i < sz; ++i)
          tmp.pMem[i] = pMem[i] + v.pMem[i];

      return tmp;
  }

  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw invalid_argument("Vector sizes must be equal");
      TDynamicVector<T> tmp = *this;
      for (int i = 0; i < sz; ++i)
          tmp.pMem[i] = pMem[i] - v.pMem[i];

      return tmp;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz)
          throw invalid_argument("Vector sizes must be equal");
      T sum = T();
      for (int i = 0; i < sz; i++)
          sum += pMem[i] * v.pMem[i];
      return sum;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
    size_t size() const noexcept { return sz; }

    bool operator!=(const TDynamicMatrix& m) const noexcept
    {
        return !(*this == m);
    }
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if (s > MAX_MATRIX_SIZE)
        throw out_of_range("Matrix size is too large");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (this == &m)
          return true;
      if (sz != m.sz)
          return false;
      else {
          for(int i = 0; i < sz; i++)
          {
              for (int j = 0; j < sz; j++) {
                  if (pMem[i][j] != m[i][j])
                      return false;
              }
          }
      }
      return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix<T> res(sz);
      for (int i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] * val;
      }
      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (v.size() != sz)
          throw invalid_argument("Vector sizes must be equal");
      TDynamicVector<T> res(sz);
      for (int i = 0; i < sz; ++i) {
          T sum = T();
          for (int j = 0; j < sz; ++j) {
              sum += pMem[i][j] * v[j];
          }
          res[i] = sum;
      }
      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw invalid_argument("Vector sizes must be equal");
      TDynamicMatrix<T> tmp(sz);
      for (int i = 0; i < sz; i++) {
          tmp.pMem[i] = m.pMem[i] + pMem[i];
      }
      return tmp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw invalid_argument("Vector sizes must be equal");
      TDynamicMatrix<T> tmp(sz);
      for (int i = 0; i < sz; i++) {
          
              tmp.pMem[i] = pMem[i] - m.pMem[i];
      }
      return tmp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw invalid_argument("Vector sizes must be equal");
      TDynamicMatrix<T> tmp(sz);
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++) {
              T sum = T();
              for (int k = 0; k < sz; k++) {
                  sum += pMem[i][k] * m.pMem[k][j];
              }
              tmp[i][j] = sum;
          }
      }
      return tmp;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; ++i)
          istr >> v.pMem[i];
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; ++i)
          ostr << v.pMem[i] << endl;
      return ostr;
  }
};

#endif
