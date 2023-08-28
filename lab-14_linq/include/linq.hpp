#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>

namespace linq {
namespace impl {

template<typename T, typename Iter>
class range_enumerator;
template<typename T>
class drop_enumerator;
template<typename T>
class take_enumerator;
template<typename T, typename U, typename F>
class select_enumerator;
template<typename T, typename P>
class until_enumerator;
template<typename T>
class until_eq_enumerator;
template<typename T, typename P>
class where_enumerator;
template<typename T>
class where_neq_enumerator;

template<typename T>
class enumerator {
public:
    virtual T operator*() = 0;
    virtual T operator++() = 0;
    virtual explicit operator bool() = 0;

    template<typename U = T, typename F>
    auto select(F func) {
        return select_enumerator<T, U, F>(*this, func);
    }

    auto drop(int count) {
        return drop_enumerator<T>(*this, count);
    }

    auto take(int count) {
        return take_enumerator<T>(*this, count);
    }

    template<typename P>
    auto until(P predicate) {
        return until_enumerator<T, P>(*this, predicate);
    }

    auto until_eq(T value) {
        return until_eq_enumerator<T>(*this, value);
    }

    template<typename P>
    auto where(P predicate) {
        return where_enumerator<T, P>(*this, predicate);
    }

    auto where_neq(T value) {
        return where_neq_enumerator<T>(*this, value);
    }

    std::vector<T> to_vector() {
        std::vector<T> result;
        while (*this) {
            result.push_back(this->operator++());
        }
        return result;
    }

    template<typename Iter>
    void copy_to(Iter it) {
        while (this->operator bool()) {
            *it = this->operator++();
            it++;
        }
    }
};

template<typename T, typename Iter>
class range_enumerator : public enumerator<T> {
public:
    range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {
    }

    T operator*() override {
        return static_cast<T>(*begin_);
    }

    T operator++() override {
        auto to_return = *begin_;
        begin_++;
        return to_return;
    }

    explicit operator bool() override {
        return begin_ != end_;
    }

private:
    Iter begin_, end_;
};

template<typename T>
class drop_enumerator : public enumerator<T> {
public:
    drop_enumerator(enumerator<T> &parent, int count) : parent_(&parent), count_(count) {
    }

    T operator*() override {
        shift();
        return parent_->operator*();
    }

    T operator++() override {
        auto value = this->operator *();
        parent_->operator++();
        return value;
    }

    explicit operator bool() override {
        shift();
        return parent_->operator bool();
    }

private:
    enumerator<T> *parent_;
    int count_;

    void shift() {
        while ((parent_->operator bool()) && count_ > 0) {
            parent_->operator ++();
            --count_;
        }
    }
};

template<typename T>
class take_enumerator : public enumerator<T> {
public:
    take_enumerator(enumerator<T> &parent, int count) : parent_(&parent), count_(count) {
    }

    T operator*() override {
        return parent_->operator*();
    }

    T operator++() override {
        count_--;
        return parent_->operator++();
    }

    explicit operator bool() override {
        return count_ > 0 && parent_->operator bool();
    }

private:
    enumerator<T> *parent_;
    int count_;
};

template<typename T, typename U, typename F>
class select_enumerator : public enumerator<U> {
public:
    select_enumerator(enumerator<T> &parent, F &func) : parent_(&parent), func_(std::move(func)) {
    }

    U operator*() override {
        return static_cast<U>(func_(parent_->operator*()));
    }

    U operator++() override {
        auto value = this->operator*();
        parent_->operator++();
        return value;
    }

    explicit operator bool() override {
        return parent_->operator bool();
    }

private:
    enumerator<T> *parent_;
    F func_;
};

template<typename T, typename P>
class until_enumerator : public enumerator<T> {
public:
    until_enumerator(enumerator<T> &parent, P &predicate) : parent_(&parent), predicate_(std::move(predicate)) {
    }

    T operator*() override {
        return parent_->operator*();
    }

    T operator++() override {
        return parent_->operator++();
    }

    explicit operator bool() override {
        return parent_->operator bool() && predicate_(parent_->operator*());
    }

private:
    enumerator<T> *parent_;
    P predicate_;
};

template<typename T>
class until_eq_enumerator : public enumerator<T> {
public:
    until_eq_enumerator(enumerator<T> &parent, T value) : parent_(&parent), value_(value) {
    }

    T operator*() override {
        return parent_->operator*();
    }

    T operator++() override {
        return parent_->operator++();
    }

    explicit operator bool() override {
        return parent_->operator bool() && parent_->operator*() != value_;
    }

private:
    enumerator<T> *parent_;
    T value_;
};

template<typename T, typename P>
class where_enumerator : public enumerator<T> {
public:
    where_enumerator(enumerator<T> &parent, P &predicate) : parent_(&parent), predicate_(std::move(predicate)) {
    }

    T operator*() override {
        shift();
        return parent_->operator*();
    }

    T operator++() override {
        auto value = this->operator*();
        parent_->operator++();
        return value;
    }

    explicit operator bool() override {
        shift();
        return parent_->operator bool();
    }

private:
    enumerator<T> *parent_;
    P predicate_;

    void shift() {
        while ((parent_->operator bool()) && !predicate_(parent_->operator*())) {
            parent_->operator++();
        }
    }
};

template<typename T>
class where_neq_enumerator : public enumerator<T> {
public:
    where_neq_enumerator(enumerator<T> &parent, T value) : parent_(&parent), value_(value) {
    }

    T operator*() override {
        shift();
        return parent_->operator*();
    }

    T operator++() override {
        auto value = this->operator*();
        parent_->operator++();
        return value;
    }

    explicit operator bool() override {
        shift();
        return parent_->operator bool();
    }

private:
    enumerator<T> *parent_;
    T value_;

    void shift() {
        while ((parent_->operator bool()) && parent_->operator*() == value_) {
            parent_->operator++();
        }
    }
};

} // namespace impl

template<typename T>
auto from(T begin, T end) {
    return impl::range_enumerator<typename std::iterator_traits<T>::value_type, T>(begin, end);
}

} // namespace linq

#endif
