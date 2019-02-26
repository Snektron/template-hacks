// Functionality to access a private member of a class, in completely
// defined c++. Credit to github.com/BIsHetAntwoord

#include <cassert>

// Class we want to access
class Oof {
    int oof = 10;
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

struct Oof_tag {
    using type = int Oof::*;
};

// Explicitly instantiate the template
// C++ allows fetching pointers to private members during explicit template instantiation
// We will use this to bypass the private access modifier in a type-safe manner
template struct private_access_init<Oof_tag, &Oof::oof>;

int main() {
    Oof oof;
    assert(oof.*private_access<Oof_tag>::value == 10);
    return 0;
}
