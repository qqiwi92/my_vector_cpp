#ifndef VECTOR
#define VECTOR

#include <cstddef>

namespace stuff {

  template < class T > struct Vector {
    ~Vector();
    Vector();

    bool isEmpty() const noexcept;

  private:
    T* data_;
    size_t size_, capacity_;
  };

}

template < class T > stuff::Vector< T >::~Vector() { delete[] data_; }

template < class T >
stuff::Vector< T >::Vector() : data_(nullptr), size_(0), capacity_(0)
{
}

template < class T > bool stuff::Vector< T >::isEmpty() const noexcept
{
  return !size_;
}

#endif
