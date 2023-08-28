#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <cstddef>
#include <ostream>

namespace containers {

template<typename T>
class my_vector {
public:
    my_vector();
    explicit my_vector(std::size_t n);
    my_vector(const my_vector &other);
    my_vector<T>& operator=(const my_vector &other);
    ~my_vector();

    std::size_t size() const;
    std::size_t capacity() const;
    bool empty() const;

    void resize(std::size_t n);
    void reserve(std::size_t n);

    void push_back(T t);
    void pop_back();
    void clear();

    T &operator [](std::size_t index) const;

private:
    size_t capacity_;
    size_t size_;
    T* array_;

    void copy_data(const my_vector &other);
    void delete_array_content();
    void delete_array();
    T* create_array(std::size_t n);
};

template<typename T> std::ostream & operator<<(std::ostream &out, my_vector<T> v);

}

#include "my_vector_impl.hpp"

#endif  // MY_VECTOR_H_
