#ifndef VECTOR
#define VECTOR

#include <cstddef>

template <class T>
struct Vector {
    T* data;
    size_t size, capacity;
}

#endif