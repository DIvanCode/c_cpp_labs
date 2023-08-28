#include <iostream>
#include <utility>
#include <cassert>

#include "my_vector.hpp"

namespace product {

class Product {
public:
    Product(std::string name, int quantity, double price);

    bool operator == (Product other);
    friend std::ostream & operator << (std::ostream &out, const Product &product);

private:
    Product() {}

    std::string name_;
    int quantity_;
    double price_;
};

Product::Product(std::string name, int quantity, double price) {
    name_ = std::move(name);
    quantity_ = quantity;
    price_ = price;
}

bool Product::operator == (Product other) {
    return name_ == other.name_ && quantity_ == other.quantity_ && price_ == other.price_;
}

std::ostream & operator << (std::ostream &out, const Product &product) {
    return out << "(" << product.name_ << ": " << product.quantity_ << ", " << product.price_ << ")";
}

}  // namespace product

namespace test {

    template<typename T>
    void test_my_vector(T a, T b) {
        containers::my_vector<T> v;
        assert(v.size() == 0);
        v.push_back(a);
        v.push_back(b);
        assert(v.size() == 2);
        assert(v.capacity() == 2);
        v.push_back(a);
        assert(v.size() == 3);
        assert(v.capacity() == 4);
        v.pop_back();
        v.pop_back();
        assert(v.size() == 1);
        assert(v.capacity() == 4);
        v.clear();
        assert(v.size() == 0);
        assert(v.capacity() == 1);
        v.reserve(3);
        assert(v.capacity() == 4);
        v.push_back(a);
        v.push_back(a);
        v.push_back(b);
        v.push_back(b);
        assert(v[0] == a && v[1] == a && v[2] == b && v[3] == b);
        T &x = v[0];
        x = b;
        std::cerr << x << "\n";
    }

    template<typename T>
    void test_my_vector_default_constructible(T a, T b) {
        containers::my_vector<T> v(2);
        assert(v.size() == 2);
        v.push_back(a);
        v.push_back(b);
        assert(v.size() == 4);
        assert(v.capacity() == 4);
        v.push_back(a);
        assert(v.size() == 5);
        assert(v.capacity() == 8);
        v.pop_back();
        v.pop_back();
        assert(v.size() == 3);
        assert(v.capacity() == 8);
        v.clear();
        assert(v.size() == 0);
        assert(v.capacity() == 1);
        assert(v.empty());
        v.reserve(6);
        assert(v.capacity() == 8);
        v.push_back(a);
        v.push_back(a);
        v.push_back(b);
        v.push_back(b);
        assert(v[0] == a && v[1] == a && v[2] == b && v[3] == b);
        v.resize(2);
        assert(v.size() == 2);
        assert(v.capacity() == 8);
        v.resize(3);
        assert(v[0] == a && v[1] == a && v[2] == T());
        const containers::my_vector<T> u = v;
        u[1] = 2;
        std::cout << u << "\n";
    }
}

int main() {
    test::test_my_vector<int>(5, 10);
    test::test_my_vector<product::Product>(product::Product("asdf", 4, 12.0), product::Product("qwe", -1, 7.5));
    test::test_my_vector_default_constructible<int>(5, 10);
    return 0;
}
