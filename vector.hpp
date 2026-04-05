#ifndef CUSTOM_VECTOR
#define CUSTOM_VECTOR

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
namespace stuff {
  template < class T > struct Vector {
    ~Vector();
    Vector();
    Vector(const Vector&);
    Vector(Vector< T >&& rhs) noexcept;
    explicit Vector(std::initializer_list< T > il);
    Vector& operator=(const Vector&);
    Vector& operator=(Vector< T >&& rhs) noexcept;
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
    void pushBackCount(size_t k, const T& val);
    void reserve(size_t);
    void shrinkToFit();
    template < class IT > void pushBackRange(IT b, size_t c);

  private:
    explicit Vector(size_t);
    void swap(Vector< T >&) noexcept;
    void expand();
    void expandIfFull();
    void unsafePushBack();
    T* data_;
    size_t size_, capacity_;
  };

  template < class T >
  bool operator==(const stuff::Vector< T >& lhs, const stuff::Vector< T >& rhs);
}

template < class T >
template < class IT >
void stuff::Vector< T >::pushBackRange(IT b, size_t c)
{
  if (size_ + c > capacity_) {
    reserve(size_ + c);
  }
  for (size_t i = 0; i < c; ++i) {
    data_[size_++] = *b;
    ++b;
  }
}

template < class T > void stuff::Vector< T >::reserve(size_t new_cap)
{
  if (new_cap < size_)
    return;
  T* nw = new T[new_cap];

  try {
    for (size_t i = 0; i < size_; ++i) {
      nw[i] = data_[i];
    }
  } catch (...) {
    delete[] nw;
    throw;
  }
  delete[] data_;
  data_ = nw;
  capacity_ = new_cap;
}

template < class T > void stuff::Vector< T >::shrinkToFit() { reserve(size_); }

template < class T >
void stuff::Vector< T >::pushBackCount(size_t k, const T& val)
{
  if (size_ + k > capacity_) {
    reserve(size_ + k);
  }
  for (size_t i = 0; i < k; ++i) {
    data_[size_++] = val;
  }
}

template < class T >
stuff::Vector< T >::Vector(std::initializer_list< T > il) : Vector(il.size())
{
  size_t i = 0;
  for (auto it = il.begin(); it != il.end(); ++it) {
    data_[i++] = *it;
  }
}

template < class T >
stuff::Vector< T >::Vector(size_t cap)
    : data_(new T[cap]), size_(0), capacity_(cap)
{
}
template < class T >
stuff::Vector< T >& stuff::Vector< T >::operator=(const Vector< T >& rhs)
{
  Vector< T > cpy = rhs;
  swap(cpy);
  return *this;
}

template < class T >
bool stuff::operator==(
    const stuff::Vector< T >& lhs, const stuff::Vector< T >& rhs)
{
  bool IsEqual = lhs.getSize() == rhs.getSize();

  for (size_t i = 0;
       i < lhs.getSize() && (IsEqual = IsEqual && (lhs[i] == rhs[i])); ++i) {
  }
  return IsEqual;

  return IsEqual;
}

template < class T >
stuff::Vector< T >::Vector(const Vector< T >& rhs)
    : data_(nullptr), size_(rhs.size_), capacity_(rhs.size_)
{
  if (capacity_ > 0) {
    data_ = new T[capacity_];
    for (size_t i = 0; i < size_; ++i) {
      try {
        data_[i] = rhs.data_[i];
      } catch (...) {
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        throw;
      }
    }
  }
}

template < class T > stuff::Vector< T >::~Vector() { delete[] data_; }

template < class T > void stuff::Vector< T >::swap(Vector< T >& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
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
  for (size_t i = size_; i > index; --i) {
    data_[i] = data_[i - 1];
  }
  data_[index] = val;
  size_++;
}

template < class T >
stuff::Vector< T >::Vector(Vector< T >&& rhs) noexcept
    : data_(nullptr), size_(0), capacity_(0)
{
  swap(rhs);
}

template < class T >
stuff::Vector< T >& stuff::Vector< T >::operator=(Vector< T >&& rhs) noexcept
{
  swap(rhs);
  return *this;
}

template < class T > void stuff::Vector< T >::erase(size_t index)
{
  if (index >= size_) {
    throw std::out_of_range("index oout of bounds for erase");
  }

  for (size_t i = index; i < size_ - 1; ++i) {
    data_[i] = data_[i + 1];
  }
  size_--;
}

#endif
