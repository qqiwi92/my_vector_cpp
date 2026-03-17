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

template < class T > stuff::Vector< T >::~Vector() {}

template < class T >
stuff::Vector< T >::Vector() : data_(), capacity_(), size_()
{
}

#endif
