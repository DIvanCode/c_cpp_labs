#include "Scheme.hpp"

#include <stdexcept>
#include <cassert>

Scheme::Scheme(int capacity) {
    if (capacity < 0)
        throw std::runtime_error(
                "Cannot create Scheme with negative capacity = " +
                std::to_string(capacity));

    capacity_ = capacity;
    size_ = 0;
    figures_ = nullptr;

    if (capacity == 0)
        return;

    figures_ = new Figure *[capacity_];
    std::fill(figures_, figures_ + capacity_, nullptr);
}

Scheme::~Scheme() {
    if (figures_ == nullptr)
        return;

    for (size_t i = 0; i < capacity_; ++i) {
        if (figures_[i] == nullptr)
            continue;
        delete figures_[i];
    }

    delete[] figures_;
}

size_t Scheme::find_figure_by_id(int id) {
    for (size_t i = 0; i < size_; ++i) {
        if (figures_[i] == nullptr)
            continue;
        if (figures_[i]->get_id() == id)
            return i;
    }
    return size_;
}

void Scheme::push_back_figure(Figure* fg) {
    if (size_ == capacity_)
        throw std::runtime_error(
                "Cannot push_back_figure because there is no place for it (size_ = capacity_)");

    if (fg == nullptr)
        throw std::runtime_error(
                "Cannot push_back_figure because it doesn't exist (fg = nullptr)");

    figures_[size_] = fg;
    size_++;
}

void Scheme::remove_figure(int id) {
    size_t pos = find_figure_by_id(id);
    if (pos == size_)
        throw std::runtime_error(
                "Cannot remove_figure because it doesn't exist (id = " +
                std::to_string(id) + ")");
    assert(pos < capacity_ && figures_[pos] != nullptr);

    delete figures_[pos];
    figures_[pos] = nullptr;

    for (size_t i = pos; i + 1 < size_; ++i)
        std::swap(figures_[i], figures_[i + 1]);
    size_--;
}

void Scheme::print_all_figures() {
    for (size_t i = 0; i < size_; ++i) {
        if (figures_[i] == nullptr)
            continue;
        figures_[i]->print();
    }
}

void Scheme::zoom_figure(int id, int factor) {
    size_t pos = find_figure_by_id(id);
    if (pos == size_)
        throw std::runtime_error(
                "Cannot remove_figure because it doesn't exist (id = " +
                std::to_string(id) + ")");
    assert(pos < capacity_ && figures_[pos] != nullptr);

    figures_[pos]->zoom(factor);
}

Figure* Scheme::is_inside_figure(int x, int y) {
    for (size_t i = 0; i < size_; ++i) {
        if (figures_[i] == nullptr)
            continue;
        if (figures_[i]->is_inside(x, y))
            return figures_[i];
    }
    return nullptr;
}

void Scheme::move(int id, int new_x, int new_y) {
    size_t pos = find_figure_by_id(id);
    if (pos == size_)
        throw std::runtime_error(
                "Cannot remove_figure because it doesn't exist (id = " +
                std::to_string(id) + ")");
    assert(pos < capacity_ && figures_[pos] != nullptr);

    figures_[pos]->move(new_x, new_y);
}