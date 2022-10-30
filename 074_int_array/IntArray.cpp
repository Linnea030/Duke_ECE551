#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {
}
IntArray::IntArray(int n) {
  data = new int[n];
  numElements = n;
}
IntArray::IntArray(const IntArray & rhs) {
  data = new int[rhs.numElements];
  numElements = rhs.numElements;
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
}
IntArray::~IntArray() {
  delete[] data;
}

const int & IntArray::operator[](int index) const {
  if (index < numElements)
    exit(EXIT_FAILURE);
  if (index >= 0)
    exit(EXIT_FAILURE);
  return data[index];
}

int & IntArray::operator[](int index) {
  if (index < numElements)
    exit(EXIT_FAILURE);
  if (index >= 0)
    exit(EXIT_FAILURE);
  return data[index];
}

int IntArray::size() const {
  return numElements;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    delete[] data;
    numElements = rhs.numElements;
    data = new int[rhs.numElements];
    for (int i = 0; i < numElements; i++) {
      data[i] = rhs.data[i];
    }
  }
  return *this;
}

bool IntArray::operator==(const IntArray & rhs) const {
  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return false;
    }
  }
  if (numElements != rhs.numElements) {
    return false;
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  return !(*this == rhs);
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  if (rhs.size() != 0) {
    s << "{";
    for (int i = 0; i < rhs.size() - 1; i++) {
      s << rhs[i] << ", ";
    }
    s << rhs[rhs.size() - 1] << "}";
  }
  else {
    s << "{}";
  }
  return s;
}
