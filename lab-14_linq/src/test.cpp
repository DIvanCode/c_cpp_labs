#include "linq.hpp"
#include <cassert>
#include <vector>

using linq::from;

void from_to_vector() {
    std::vector<int> xs = { 1, 2, 3 };
    std::vector<int> res =
        from(xs.begin(), xs.end())
        .to_vector();
    assert(res == xs);
}

void from_select() {
    const int xs[] = { 1, 2, 3 };
    std::vector<int> res =
        from(xs, xs + 3)
        .select([](int x) { return x + 5; })
        .to_vector();
    std::vector<int> expected = { 6, 7, 8 };
    assert(res == expected);
}

void from_drop_select() {
    const int xs[] = { 1, 2, 3 };
    std::vector<int> res =
        from(xs, xs + 3)
        .drop(1)
        .select([](int x) { return x + 5; })
        .to_vector();
    std::vector<int> expected = { 7, 8 };
    assert(res == expected);
}

void from_drop_until_select() {
    const int xs[] = { 1, 2, 3 };
    std::vector<int> res =
        from(xs, xs + 3)
        .drop(1)
        .until([](int x) { return x <= 2; })
        .select([](int x) { return x + 5; })
        .to_vector();
    std::vector<int> expected = { 7 };
    assert(res == expected);
}

void from_take_until_select() {
    const int xs[] = { 1, 2, 3 };
    std::vector<int> res =
        from(xs, xs + 3)
        .take(2)
        .until([](int x) { return x < 2; })
        .select([](int x) { return x + 5; })
        .to_vector();
    std::vector<int> expected = { 6 };
    assert(res == expected);
}

void from_where() {
    const int xs[] = { 1, 2, 3 };
    std::vector<int> res =
        from(xs, xs + 3)
        .where([](int x) { return x >= 2; })
        .to_vector();
    std::vector<int> expected = { 2, 3 };
    assert(res == expected);
}

void from_where_select() {
    const int xs[] = { 1, 2, 3 };
    std::vector<int> res =
        from(xs, xs + 3)
        .where([](int x) { return x >= 2; })
        .select([](int x) { return x + 5; })
        .to_vector();
    std::vector<int> expected = { 7, 8 };
    assert(res == expected);
}

int main() {
    from_to_vector();
    from_select();
    from_drop_select();
    from_drop_until_select();
    from_take_until_select();
    from_where();
    from_where_select();
    return 0;
}
