// Functionality to access a private member of a class, in completely
// defined c++. Credit to github.com/BIsHetAntwoord

#include <cassert>

// Class we want to access
class A {
    int a = 10;
};

// Base storage for the eventual value pointer to a private variable
template <typename AccessTag>
struct private_access
{
    static typename AccessTag::type value;
};

template <typename AccessTag>
typename AccessTag::type private_access<AccessTag>::value;

// Instance the members in static initializer of another structure
template <typename AccessTag, typename AccessTag::type field>
struct private_access_init
{
    private_access_init() {private_access<AccessTag>::value = field;}
    static private_access_init instance; //On instantiation, call the constructor
};

// Define the static data member for initialization
template <typename AccessTag, typename AccessTag::type field>
private_access_init<AccessTag, field> private_access_init<AccessTag, field>::instance;

struct A_tag {
    using type = int A::*;
};

// Explicitly instantiate the template
// C++ allows fetching pointers to private members during explicit template instantiation
// We will use this to bypass the private access modifier in a type-safe manner
template struct private_access_init<A_tag, &A::a>;

int main() {
    A a;
    assert(a.*private_access<A_tag>::value == 10);
    return 0;
}
