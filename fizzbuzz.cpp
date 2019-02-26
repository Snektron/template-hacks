// Compile-time fizzbuzz that outputs as a compile error

template <typename... Ts>
struct List {};

template <typename L, typename T>
struct ListAppend_;

template <typename... Ts, typename T>
struct ListAppend_<List<Ts...>, T> {
    using Type = List<Ts..., T>;
};

template <typename T, typename L>
using ListAppend = typename ListAppend_<T, L>::Type;

struct FizzBuzz {};

struct Fizz {};

struct Buzz {};

template <unsigned N>
struct Int {};

template <bool Cond, typename Csq, typename Alt>
struct If_;

template <typename Csq, typename Alt>
struct If_<true, Csq, Alt> {
    using Type = Csq;
};

template <typename Csq, typename Alt>
struct If_<false, Csq, Alt> {
    using Type = Alt;
};

template <bool Cond, typename Csq, typename Alt>
using If = typename If_<Cond, Csq, Alt>::Type;

template <unsigned N>
struct GenerateFizzBuzz_ {
    using Element = If<N % 15 == 0, FizzBuzz, If<N % 5 == 0, Buzz, If<N % 3 == 0, Fizz, Int<N>>>>;

    using Type = ListAppend<typename GenerateFizzBuzz_<N - 1>::Type, Element>;
};

template <>
struct GenerateFizzBuzz_<0> {
    using Type = List<>;
};

template <unsigned N>
using GenerateFizzBuzz = typename GenerateFizzBuzz_<N>::Type;

GenerateFizzBuzz<36> x = 0;
