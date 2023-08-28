#include "Figure.hpp"

Figure::Figure(int id, int x, int y) {
    id_ = id;
    x_ = x;
    y_ = y;
}

Figure::~Figure() {}

int Figure::get_id() {
    return id_;
}