#ifndef MY_ARRAY_H_
#define MY_ARRAY_H_

#include <cstddef>
#include <stdexcept>
#include <iostream>

namespace lab_13 {

template<typename T, size_t N>
class my_array {
public:
    T& at(std::size_t index);
    const T& at(std::size_t index) const;
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    bool empty() const;
    size_t size() const;

    void fill(T val);

private:
    T data_[N] {};
};

template<typename T, size_t N>
T& my_array<T, N>::at(size_t index) {
    if (index >= N) {
        throw std::out_of_range(
                "index = " + std::to_string(index) + "; " +
                "N = " + std::to_string(N));
    }

    return data_[index];
}

template<typename T, size_t N>
const T& my_array<T, N>::at(size_t index) const {
    if (index >= N) {
        throw std::out_of_range(
                "index = " + std::to_string(index) + "; " +
                "N = " + std::to_string(N));
    }

    return data_[index];
}


template<typename T, size_t N>
T& my_array<T, N>::operator [](size_t index) {
    return data_[index];
}

template<typename T, size_t N>
const T& my_array<T, N>::operator [](size_t index) const {
    return data_[index];
}

template<typename T, size_t N>
bool my_array<T, N>::empty() const {
    return N == 0;
}

template<typename T, size_t N>
size_t my_array<T, N>::size() const {
    return N;
}

template<typename T, size_t N>
void my_array<T, N>::fill(T val) {
    for (size_t i = 0; i < N; ++i) {
        data_[i] = val;
    }
}

template<typename T, size_t N>
std::istream & operator >> (std::istream &in, my_array<T, N> &arr) {
    for (size_t i = 0; i < N; ++i) {
        in >> arr[i];
    }
    return in;
}

template<typename T, size_t N>
std::ostream & operator << (std::ostream &out, my_array<T, N> &arr) {
    for (size_t i = 0; i < N; ++i) {
        if (i > 0) out << " ";
        out << arr[i];
    }
    return out;
}


class my_bool {
public:
    my_bool(uint8_t * data, size_t pos): data_(data), pos_(pos), value_((*data_ >> pos_) & 1) {}

    my_bool & operator = (bool value) {
        flip();
        value_ = value;
        flip();

        return *this;
    }

    my_bool & operator = (const my_bool &other) {
        if (this == &other) {
            return *this;
        }

        flip();
        value_ = bool(other);
        flip();

        return *this;
    }

    bool operator == (my_bool other) const {
        return value_ == other.value_;
    }

    bool operator != (my_bool other) const {
        return value_ != other.value_;
    }

    bool operator == (bool value) const {
        return value_ == value;
    }

    bool operator != (bool value) const {
        return value_ != value;
    }

    explicit operator const bool &() const {
        return value_;
    }

    friend std::istream & operator >> (std::istream &in, my_bool elem) {
        elem.flip();
        in >> elem.value_;
        elem.flip();
        return in;
    }

    friend std::ostream & operator << (std::ostream &out, my_bool elem) {
        return out << elem.value_;
    }

private:
    uint8_t * data_;
    size_t pos_;
    bool value_;

    void flip() {
        *data_ ^= (value_ << pos_);
    }
};


template<size_t N>
class my_array<bool, N> {
public:
    my_array();

    my_bool at(std::size_t index);
    bool at(std::size_t index) const;
    my_bool operator[](std::size_t index);
    bool operator[](std::size_t index) const;

    bool empty() const;
    size_t size() const;

    void fill(bool val);

private:
    uint8_t data_[(N + 7) / 8];
};

template<size_t N>
my_array<bool, N>::my_array() {
    for (size_t i = 0; i < (N + 7) / 8; ++i) {
        data_[i] = 0;
    }
}

template<size_t N>
my_bool my_array<bool, N>::at(size_t index) {
    if (index >= N) {
        throw std::out_of_range(
                "index = " + std::to_string(index) + "; " +
                "N = " + std::to_string(N));
    }

    return my_bool(data_ + index / 8, index % 8);
}

template<size_t N>
bool my_array<bool, N>::at(size_t index) const {
    if (index >= N) {
        throw std::out_of_range(
                "index = " + std::to_string(index) + "; " +
                "N = " + std::to_string(N));
    }

    return (data_[index / 8] >> (index % 8)) & 1;
}

template<size_t N>
my_bool my_array<bool, N>::operator [](size_t index) {
    return my_bool(data_ + index / 8, index % 8);
}

template<size_t N>
bool my_array<bool, N>::operator [](size_t index) const {
    return (data_[index / 8] >> (index % 8)) & 1;
}

template<size_t N>
bool my_array<bool, N>::empty() const {
    return N == 0;
}

template<size_t N>
size_t my_array<bool, N>::size() const {
    return N;
}

template<size_t N>
void my_array<bool, N>::fill(bool val) {
    uint32_t byte_value = 0;
    if (val) {
        byte_value = 255;
    }

    for (size_t i = 0; i < (N + 7) / 8; ++i) {
        data_[i] = byte_value;
    }
}

template<size_t N>
std::istream & operator >> (std::istream &in, my_array<bool, N> &arr) {
    for (size_t i = 0; i < N; ++i) {
        in >> arr[i];
    }
    return in;
}

template<size_t N>
std::ostream & operator << (std::ostream &out, my_array<bool, N> &arr) {
    for (size_t i = 0; i < N; ++i) {
        if (i > 0) out << " ";
        out << arr[i];
    }
    return out;
}

}  // namespace lab_13

#endif  // MY_ARRAY_H_
