#pragma once

#include "Figure.hpp"

#include <cstddef>

class Scheme {
public:
    Scheme(int capacity); 
    ~Scheme();

    void push_back_figure(Figure* fg);
    void remove_figure(int id); // элементы смещаются влево

    void print_all_figures();
    void zoom_figure(int id, int factor);
    Figure* is_inside_figure(int x, int y); // если внутри нескольких фигур, то возвращается любая из них; если таких фигур нет, то возвращается nullptr
    void move(int id, int new_x, int new_y);

private:
    size_t capacity_;
    size_t size_;

    Figure** figures_; // размер массива задается в конструкторе и больше не растет

    size_t find_figure_by_id(int id);
};
