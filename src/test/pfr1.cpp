// requires: C++14
#include <iostream>
#include <string>
#include "boost/pfr/precise.hpp"

struct some_person {
    std::string name;
    unsigned birth_year;
    bool valid;
};


template<class T>
void printMe(T t)
{
    auto count = boost::pfr::tuple_size<T>::value;

    boost::pfr::for_each_field(t, [](auto& field) {
      std::cout << field << std::endl;
    });
}

int main() {
    some_person val{"Edgar Allan Poe", 1809, true};

    std::cout << std::boolalpha
        << boost::pfr::get<0>(val)                // No macro!
        << " was born in " << boost::pfr::get<1>(val)
        << " is " << boost::pfr::get<2>(val);  // Works with any aggregate initializables!

	std::cout << std::endl;
	std::cout << std::endl;

	printMe(val);
}

