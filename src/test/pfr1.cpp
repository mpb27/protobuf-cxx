// requires: C++14
#include <iostream>
#include <string>
#include "boost/pfr/precise.hpp"

struct book {
    std::string title;
    int year_published;
};

struct some_person {
    std::string name;
    unsigned birth_year;
    bool valid;
    book first_book;
};


std::ostream& operator << (std::ostream &o, const book &a)
{
    o << "title: " << a.title << "\tyear: " << a.year_published << std::endl;
    return o;
}

// use  std::optional  as the result to allow for null values?
//  check CppCon 2017 Kate Gregory "10 core guidelines..." talk on youtube 32m:20s
//  also consider std::optional<std::reference_wrapper<>>
// or std::shared_ptr ?
// also consider using gsl::owner like container (marking only, 0 weight) to specify what is a field?


template<class T>
void printMe(const T& t)
{
    auto count = boost::pfr::tuple_size<T>::value;

    boost::pfr::for_each_field(t, [](auto& field) {
        //if constexpr (typeid(book) == typeid(field)) {
           // printMe(field);
        //}
        //else {
            std::cout << field << std::endl;
        //}
    });

	std::cout << std::endl;	    
}

template<class T>
void populateMe(T& t)
{
    //boost::pfr::for_each_field(t, [](auto& field) {
    //  std::cout << field << std::endl;
    //});	
    boost::pfr::get<0>(t) = "Margaret Eleanor Atwood";
    boost::pfr::get<1>(t) = 1939;
    boost::pfr::get<2>(t) = false;
    boost::pfr::get<3>(t) = {"Double Persephone", 1961};
}

template <class T>
T createMe()
{
    T t;  // zero initializated? dont like
    boost::pfr::get<0>(t) = "Edgar Allan Poe";
    boost::pfr::get<1>(t) = 1809;
    boost::pfr::get<2>(t) = true;
    boost::pfr::get<3>(t) = {"None", 1};
    return t;
}

template <class T>
void modifyMe(T& t)
{
    boost::pfr::for_each_field(t, [](auto& field) {
        //if (decltype(field) == decltype(std::string)) {
        // https://stackoverflow.com/questions/24855160/how-to-tell-if-a-c-template-type-is-c-style-string
        if constexpr(std::is_same<decltype(field), std::string&>::value) {
            //std::cout << "found string: " << field << "\n";
            field = "Richard Bachman";
        }
    });
}


int main() {
    //some_person val{"Edgar Allan Poe", 1809, true, {"None", 1}};
    auto val = createMe<some_person>();

    /*
    std::cout << std::boolalpha
        << boost::pfr::get<0>(val)                // No macro!
        << " was born in " << boost::pfr::get<1>(val)
        << " is " << boost::pfr::get<2>(val);  // Works with any aggregate initializables!
	std::cout << std::endl;
    */

	printMe(val);

	populateMe(val);

	printMe(val);

    modifyMe(val);

    printMe(val);
}

