#include <algorithm>
#include <stdexcept>
#include <cstring>
#include "my_vector.hpp"

MyVector::MyVector() {
    _size = 0;
    _capacity = 2;
    _data = new int[_capacity];
}

MyVector::MyVector(std::size_t init_capacity) {
    _size = 0;
    _capacity = init_capacity;
    _data = new int[_capacity];
}

MyVector::MyVector(MyVector &other) {
    _size = other.size();
    _capacity = other.capacity();

    if (_capacity < 2) throw std::runtime_error("Bad copy.");

    _data = new int[_capacity];

    for (std::size_t i = 0; i < _size; ++i) {
        _data[i] = other.get(i);
    }
}

MyVector::~MyVector() {
    delete[] _data;
}

void MyVector::set(std::size_t index, int value) {
    if (index >= _size) throw std::runtime_error("Index out of a range.");

    _data[index] = value;
}

int MyVector::get(std::size_t index) {
    if (index >= _size) throw std::runtime_error("Index out of a range.");

    return _data[index];
}

std::size_t MyVector::size() {
    return _size;
}

std::size_t MyVector::capacity() {
    return _capacity;
}

void MyVector::reserve(std::size_t new_capacity) {
    if (_capacity >= new_capacity) return;

    int * new_data = new int[new_capacity];
    std::memcpy(new_data, _data, _size * sizeof(int));

    delete[] _data;

    _capacity = new_capacity;
    _data = new_data;
}

void MyVector::resize(std::size_t new_size) {
    if (new_size <= _size) {
        _size = new_size;
        return;
    }

    std::size_t new_capacity;
    if (new_size <= _capacity) new_capacity = _capacity;
    else new_capacity = std::max(new_size, _capacity * 2);

    reserve(new_capacity);

    std::memset(_data + _size, 0, (new_size - _size) * sizeof(int));

    _size = new_size;
    _capacity = new_capacity;
}

void MyVector::push_back(int value) {
    if (_capacity == _size) {
        reserve(_capacity * 2);
    }

    _data[_size++] = value;
}

void MyVector::insert(std::size_t index, int value) {
    if (index > _size) throw std::runtime_error("Index out of a range.");

    resize(_size + 1);

    for (std::size_t i = _size - 1; i > index; --i) {
        _data[i] = _data[i - 1];
    }

    _data[index] = value;
}

void MyVector::erase(std::size_t index) {
    if (index >= _size) throw std::runtime_error("Index out of a range.");

    for (std::size_t i = index; i < _size - 1; ++i) {
        _data[i] = _data[i + 1];
    }

    resize(_size - 1);
}

MyVector & MyVector :: operator = (MyVector &other) {
    if (this != &other) {
        delete[] _data;

        _size = other.size();
        _capacity = other.capacity();

        if (_capacity) _data = new int[_capacity];
        else _data = nullptr;

        for (std::size_t i = 0; i < _size; ++i) {
            _data[i] = other.get(i);
        }
    }

    return *this;
}