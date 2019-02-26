// Utility to create a "structure of arrays" from a type.
// The members of each type lie consequtive in memory, instead
// of in an interleaved manner:
// struct Vector3 {
//     int x, y, z;
// };
// Array of structs: xyzxyzxyz
// Struct of Arrays: xxxyyyzzz
//
// Note that alignment isnt respected

#include <cstddef>

template <typename T, typename U>
constexpr size_t offset(U T::*member) {
    return reinterpret_cast<size_t>(
        &(reinterpret_cast<T*>(0)->*member)
    );
}

template <typename T, size_t N>
struct SoA {
    std::byte data[N * sizeof(T)];

    template <typename U>
    U& at(U T::*member, size_t i) {
        return *reinterpret_cast<U*>(&this->data[this->byte_offset(member, i)]);
    }

    template <typename U>
    constexpr size_t byte_offset(U T::*member, size_t i) {
        const size_t member_offset = offset(member);
        const size_t data_offset = member_offset * N;

        return data_offset + i * sizeof(U);
    }
};

int main() {
    struct Test {
        int x;
        char y;
        int z;
    };

    SoA<Test, 4> test;
    static_assert(test.byte_offset(&Test::x, 0) == 0);
    static_assert(test.byte_offset(&Test::y, 0) == sizeof(int) * 4);
    static_assert(test.byte_offset(&Test::y, 2) == sizeof(int) * 4 + sizeof(char) * 2);
    static_assert(test.byte_offset(&Test::z, 3) == offsetof(Test, z) * 4 + sizeof(int) * 3);

    return 0;
}
