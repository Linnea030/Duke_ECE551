#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {
}

IntMatrix::IntMatrix(int r, int c) {
  numRows = r;
  numColumns = c;
  rows = new IntArray *[numRows];
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(numColumns);
  }
}

IntMatrix::IntMatrix(const IntMatrix & rhs) {
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  rows = new IntArray *[numRows];
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(rhs[i]);
  }
}

IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}

IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
    numColumns = rhs.numColumns;
    numRows = rhs.numRows;
    rows = new IntArray *[rhs.numRows];
    for (int i = 0; i < rhs.numRows; i++) {
      rows[i] = new IntArray(rhs[i]);
    }
  }
  return *this;
}

int IntMatrix::getRows() const {
  int x = numRows;
  return x;
}

int IntMatrix::getColumns() const {
  int y = numColumns;
  return y;
}

const IntArray & IntMatrix::operator[](int index) const {
  assert(numRows > index);
  assert(index >= 0);
  return *rows[index];
}

IntArray & IntMatrix::operator[](int index) {
  assert(numRows > index);
  assert(index >= 0);
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (numColumns != rhs.numColumns) {
    return false;
  }

  if (numRows != rhs.numRows) {
    return false;
  }

  for (int i = 0; i < numRows; i++) {
    if ((*this)[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows == rhs.numRows);
  assert(numColumns == rhs.numColumns);
  IntMatrix result(numRows, numColumns);
  for (int i = 0; i < numColumns; i++) {
    for (int j = 0; j < numRows; j++) {
      result[j][i] = rhs[j][i] + (*this)[j][i];
    }
  }
  return result;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
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
