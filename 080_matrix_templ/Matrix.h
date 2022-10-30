#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0) {}

  Matrix(int r, int c) {
    numRows = r;
    numColumns = c;
    //rows = new IntArray *[numRows];
    for (int i = 0; i < numRows; i++) {
      std::vector<T> res(c);
      rows.push_back(res);
      //rows[i] = new IntArray(numColumns);
    }
  }

  Matrix(const Matrix<T> & rhs) {
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    //rows = new IntArray *[numRows];
    // for (int i = 0; i < numRows; i++) {
    //rows[i] = new IntArray(rhs[i]);
    //}
    rows = rhs.rows;
  }

  ~Matrix() {
    //  for (int i = 0; i < numRows; i++) {
    //delete rows[i];
    //}
    // delete[] rows;
  }

  Matrix<T> & operator=(const Matrix<T> & rhs) {
    if (this != &rhs) {
      rows.clear();
    }
    //delete[] rows;
    numColumns = rhs.numColumns;
    numRows = rhs.numRows;
    rows = rhs.rows;
    //new IntArray *[rhs.numRows];
    // for (int i = 0; i < rhs.numRows; i++) {
    // rows[i] = new IntArray(rhs[i]);
    // }
    return *this;
  }

  int getRows() const {
    int x = numRows;
    return x;
  }

  int getColumns() const {
    int y = numColumns;
    return y;
  }

  const std::vector<T> & operator[](int index) const {
    assert(numRows > index);
    assert(index >= 0);
    return rows[index];
  }

  std::vector<T> & operator[](int index) {
    assert(numRows > index);
    assert(index >= 0);
    return rows[index];
  }

  bool operator==(const Matrix<T> & rhs) const {
    if (numColumns != rhs.numColumns) {
      return false;
    }

    if (numRows != rhs.numRows) {
      return false;
    }
    if (rows != rhs.rows) {
      return false;
    }
    return true;
  }

  Matrix<T> operator+(const Matrix<T> & rhs) const {
    assert(numRows == rhs.numRows);
    assert(numColumns == rhs.numColumns);
    Matrix<T> result(numRows, numColumns);
    for (int i = 0; i < numColumns; i++) {
      for (int j = 0; j < numRows; j++) {
        result[j][i] = rhs[j][i] + (*this)[j][i];
      }
    }
    return result;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  if (rhs.getRows() == 0) {
    s << "[  ]";
    return s;
  }
  else {
    s << "[ ";
    for (int i = 0; i < rhs.getRows() - 1; i++) {
      s << rhs[i] << ",\n";
    }
    s << rhs[rhs.getRows() - 1] << " ]";
  }
  return s;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & rhs) {
  if (rhs.size() != 0) {
    s << "{";
    for (size_t i = 0; i < rhs.size() - 1; i++) {
      s << rhs[i] << ", ";
    }
    s << rhs[rhs.size() - 1] << "}";
  }
  else {
    s << "{}";
  }
  return s;
}

//YOUR CODE GOES HERE!

#endif
