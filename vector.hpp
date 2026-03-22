#ifndef CUSTOM_VECTOR
#define CUSTOM_VECTOR

#include <cstddef>
#include <stdexcept>
namespace stuff {

  template < class T > struct Vector {
    ~Vector();
    Vector();
    Vector(const Vector&);
    Vector(Vector&&);
    Vector& operator=(const Vector&);
    Vector& operator=(Vector&&);
    T& operator[](const Vector &);

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    void pushBack(const T& v);
    void popBack();
    void insert(size_t i, const T& v);
    void erase(size_t i);
    T& at(size_t index);


        private : void
                  expand();
    void expandIfFull();
    T* data_;
    size_t size_, capacity_;
  };

}

template < class T > stuff::Vector< T >::~Vector() { delete[] data_; }

template < class T >
stuff::Vector< T >::Vector() : data_(nullptr), size_(0), capacity_(0)
{
}

template < class T > T& stuff::Vector< T >::at(size_t index)
{
  if (index < size_) {
    return data_[index];
  }
  throw std::out_of_range("index out of bounds");
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

template < class T > void stuff::Vector< T >::expandIfFull()
{
  if (size_ == capacity_) {
    expand();
  }
}

template < class T > void stuff::Vector< T >::pushBack(const T& val)
{
  expandIfFull();
  data_[size_++] = val;
}

template < class T > size_t stuff::Vector< T >::getSize() const noexcept
{
  return size_;
}

template < class T > size_t stuff::Vector< T >::getCapacity() const noexcept
{
  return capacity_;
}

#endif
