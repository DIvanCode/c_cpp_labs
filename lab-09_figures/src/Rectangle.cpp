#include "Rectangle.hpp"

#include <cstdio>
#include <stdexcept>

Rectangle::Rectangle(int id, int x, int y, int width, int height):
    Figure(id, x, y) {
    if (width < 0 || height < 0)
        throw std::runtime_error(
                "Cannot create Rectangle with negative width or height (width = " +
                std::to_string(width) + ", height = " +
                std::to_string(height) + ")");

    width_ = width;
    height_ = height;
}

void Rectangle::print() const {
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id_, x_, y_, width_, height_);
}

bool Rectangle::is_inside(int x, int y) const {
    return 2 * x_ - width_ <= 2 * x &&
        2 * x <= 2 * x_ + width_ &&
        2 * y_ - height_ <= 2 * y &&
        2 * y <= 2 * y_ + height_;
}

void Rectangle::zoom(int factor) {
    if (factor < 0)
        throw std::runtime_error(
                "Cannot zoom Rectangle with the negative factor = " +
                std::to_string(factor));

    width_ *= factor;
    height_ *= factor;
}

void Rectangle::move(int new_x, int new_y) {
    x_ = new_x;
    y_ = new_y;
}