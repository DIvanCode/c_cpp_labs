#include "Circle.hpp"

#include <cstdio>
#include <stdexcept>
#include <cstring>

Circle::Circle(int id, int x, int y, int radius, const char* label):
    Figure(id, x, y) {
    if (radius < 0)
        throw std::runtime_error(
                "Cannot create Circle with negative radius = " +
                std::to_string(radius) + ")");

    radius_ = radius;

    if (label == nullptr) {
        label_ = new char[1];
    } else {
        label_ = new char[strlen(label) + 1];
        strcpy(label_, label);
    }
}

Circle::~Circle() {
    delete[] label_;
}

void Circle::print() const {
    printf("Circle %d: x = %d y = %d radius = %d label = %s\n", id_, x_, y_, radius_, label_);
}

bool Circle::is_inside(int x, int y) const {
    int squared_distance_from_center = (x - x_) * (x - x_) + (y - y_) * (y - y_);
    return squared_distance_from_center <= radius_ * radius_;
}

void Circle::zoom(int factor) {
    if (factor < 0)
        throw std::runtime_error(
                "Cannot zoom Circle with the negative factor = " +
                std::to_string(factor));

    radius_ *= factor;
}

void Circle::move(int new_x, int new_y) {
    x_ = new_x;
    y_ = new_y;
}