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

    T& operator[](size_t) noexcept;
    const T& operator[](size_t) const noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    void pushBack(const T& v);
    void popBack();
    void insert(size_t i, const T& v);
    void erase(size_t i);
    T& at(size_t index);
    const T& at(size_t index) const;

  private:
    void swap(Vector< T >&);
    void expand();
    void expandIfFull();
    T* data_;
    size_t size_, capacity_;
  };
}

template < class T > stuff::Vector< T >::~Vector() { delete[] data_; }
template < class T > void stuff::Vector< T >::swap(Vector< T >& v)
{
  std::swap(data_, v.data_);
}

template < class T >
stuff::Vector< T >::Vector() : data_(nullptr), size_(0), capacity_(0)
{
}

template < class T > const T& stuff::Vector< T >::at(size_t index) const
{
  if (index >= size_)
    throw std::out_of_range("index out of bounds");
  return data_[index];
}

template < class T > T& stuff::Vector< T >::at(size_t index)
{
  return const_cast< T& >(static_cast< const Vector< T >& >(*this).at(index));
}

template < class T > bool stuff::Vector< T >::isEmpty() const noexcept
{
  return !size_;
}

template < class T > void stuff::Vector< T >::expand()
{
  size_t nw_capacity = capacity_ + (capacity_ >> 1) + 1;
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
    throw;
  }
}

template < class T > void stuff::Vector< T >::expandIfFull()
{
  if (size_ == capacity_) {
    expand();
  }
}

template < class T > T& stuff::Vector< T >::operator[](size_t i) noexcept
{
  return data_[i];
}

template < class T >
const T& stuff::Vector< T >::operator[](size_t i) const noexcept
{
  return data_[i];
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

template < class T > void stuff::Vector< T >::popBack()
{
  if (size_) {
    size_--;
  }
}

template < class T > void stuff::Vector< T >::insert(size_t index, const T& val)
{
  if (index > size_) {
    throw std::out_of_range(
        "Wrong place to insert (maybe i'm gonna add something interesting like "
        "adding it to the end in this case or just place it the that  position "
        "and fill the gap with garbage ");
  }

  expandIfFull();
  data_[size_] = data_[size_ - 1];
  for (size_t i = size_; i > index; --i) {
    data_[i] = data_[i - 1];
  }
  data_[index] = val;
  size_++;
}

template < class T > void stuff::Vector< T >::erase(size_t index)
{
  if (index >= size_) {
    throw std::out_of_range(
        "Wrong place to insert (maybe i'm gonna add something interesting like "
        "adding it to the end in this case or just place it the that  position "
        "and fill the gap with garbage ");
  }

  data_[size_] = data_[size_ - 1];
  for (size_t i = size_ - 1; i > index; --i) {
    data_[i - 1] = data_[i];
  }
  size_--;
}

#endif
