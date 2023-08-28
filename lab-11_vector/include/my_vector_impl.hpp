#include <type_traits>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <stdexcept>
#include <ostream>

#include "my_vector.hpp"

namespace containers {

template<typename T>
T* my_vector<T>::create_array(std::size_t n) {
    return (T*) calloc(n, sizeof(T));
}

template<typename T>
my_vector<T>::my_vector() {
    size_ = 0;
    capacity_ = 1;

    array_ = create_array(capacity_);
}

template<typename T>
my_vector<T>::my_vector(std::size_t n) {
    size_ = n;

    capacity_ = 1;
    while (capacity_ < n)
        capacity_ <<= 1;

    array_ = create_array(capacity_);
    for (size_t i = 0; i < n; ++i)
        new(array_ + i) T();
}

template<typename T>
void my_vector<T>::copy_data(const my_vector<T> &other) {
    size_ = other.size_;
    capacity_ = other.capacity_;

    array_ = create_array(capacity_);
    for (size_t i = 0; i < size_; ++i)
        new (array_ + i) T(other[i]);
}

template<typename T>
my_vector<T>::my_vector(const my_vector<T> &other) {
    if (this == &other)
        return;
    copy_data(other);
}

template<typename T>
void my_vector<T>::delete_array_content() {
    if (std::is_destructible<T>::value)
        for (size_t i = 0; i < size_; ++i)
            array_[i].~T();
}

template<typename T>
void my_vector<T>::delete_array() {
    delete_array_content();
    free(array_);
}

template<typename T>
my_vector<T>& my_vector<T>::operator=(const my_vector<T> &other) {
    if (this == &other)
        return *this;

    delete_array();
    copy_data(other);

    return *this;
}

template<typename T>
my_vector<T>::~my_vector() {
    delete_array();
}

template<typename T>
std::size_t my_vector<T>::size() const {
    return size_;
}

template<typename T>
std::size_t my_vector<T>::capacity() const {
    return capacity_;
}

template<typename T>
bool my_vector<T>::empty() const {
    return size_ == 0;
}

template<typename T>
void my_vector<T>::resize(std::size_t n) {
    if (n <= size_) {
        if (std::is_destructible<T>::value) {
            for (size_t i = n; i < size_; ++i) {
                array_[i].~T();
            }
        }
        size_ = n;
        return;
    }

    reserve(n);

    for (size_t i = size_; i < n; ++i)
        new(array_ + i) T();

    size_ = n;
}

template<typename T>
void my_vector<T>::reserve(std::size_t n) {
    if (capacity_ >= n)
        return;

    std::size_t new_capacity = capacity_;
    while (new_capacity < n)
        new_capacity <<= 1;

    T* new_array = create_array(new_capacity);
    for (size_t i = 0; i < size_; ++i)
        new(new_array + i) T(array_[i]);

    delete_array();

    capacity_ = new_capacity;
    array_ = new_array;
}

template<typename T>
void my_vector<T>::push_back(T t) {
    if (capacity_ == size_)
        reserve(capacity_ << 1);

    new(array_ + size_) T(t);
    ++size_;
}

template<typename T>
void my_vector<T>::pop_back() {
    if (size_ == 0)
        throw std::runtime_error("cannot do pop_back due to my_vector is empty");

    size_--;
    if (std::is_destructible<T>::value)
        array_[size_].~T();
}

template<typename T>
void my_vector<T>::clear() {
    delete_array_content();

    size_ = 0;
}

template<typename T>
T &my_vector<T>::operator[](std::size_t index) const {
    if (index >= size_)
        throw std::runtime_error("index out of range");

    return array_[index];
}

template<typename T>
std::ostream & operator<<(std::ostream &out, my_vector<T> v) {
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0)
            out << " ";
        out << v[i];
    }

    return out;
}

} // namespace containers