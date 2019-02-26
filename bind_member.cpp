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
    struct Oof {
        int oof(int x) {
            return 10 * x;
        }
    } oof;

    assert(bind_member(oof, &Oof::oof)(10) == 100);
    assert(bind_member(&oof, &Oof::oof)(5) == 50);

    return 0;
}
