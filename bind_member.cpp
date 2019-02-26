// Function to bind an instance to a member function pointer,
// creating a free standing function value.
// This should be shorter/more efficient[citation needed]/
// easier to write and und understand than std::bind and placeholders

#include <utility>
#include <cassert>

template <typename T, typename R, typename... Args>
auto bind_member(T& t, R(T::*fn)(Args...)) {
    return [&t, fn](Args&&... args) {
        return (t.*fn)(std::forward<Args>(args)...);
    };
}

template <typename T, typename R, typename... Args>
auto bind_member(T* t, R(T::*fn)(Args...)) {
    return [t, fn](Args&&... args) {
        return (t->*fn)(std::forward<Args>(args)...);
    };
}

int main() {
    struct Test {
        int test(int x) {
            return 10 * x;
        }
    } test;

    assert(bind_member(test, &Test::test)(10) == 100);
    assert(bind_member(&test, &Test::test)(5) == 50);

    return 0;
}
