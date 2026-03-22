#ifndef CUSTOM_VECTOR
#define CUSTOM_VECTOR

#include <cstddef>

namespace stuff {

  template < class T > struct Vector {
    ~Vector();
    Vector();
    Vector(const Vector&);
    Vector(Vector&&);
    Vector& operator=(const Vector&);
    Vector& operator=(Vector&&);

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    void pushBack(const T& v);
    void popBack();
    void insert(size_t i, const T& v);
    void erase(size_t i);

  private:
    void expand();
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

template < class T > void stuff::Vector< T >::expand()
{
  size_t nw_capacity = 3 / 2 * (capacity_ + 1);
  T* nw = nullptr;
  try {

    nw = new T[nw_capacity];
    for (size_t i = 0; i < size_; ++i) {
      nw[i] = data_[i];
    }
    delete[] data_;
    data_ = nw;
    capacity_ = nw_capacity;
    
  } catch (...) {
    delete[] nw;
  }
}

template < class T > void stuff::Vector< T >::pushBack(const T& val) {}

#endif
