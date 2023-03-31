/// @file Container.cpp
/// @author Sujin Lee
/// @date 3/7/2022
/// @note I pledge my word of honor that I have complied with the
/// CSN Academic Integrity Policy while completing this assignment.
/// @brief Source file for pa13.cpp
/// @note 25hr
/// 2022-03-02: Copied from Kevin's lecture

#include <cassert>
#include "Container.h"

/// Copies the elements in the range defiend by [first, last)
/// to another range beginning at dest
static void copy(Container::const_pointer first,
                 Container::const_pointer last,
                 Container::pointer d_first);

/// Returns true if the range [first1,last1) is equal to the range
/// [first2,last2) and false otherwise.
static bool equal(Container::const_pointer first1,
                  Container::const_pointer last1,
                  Container::const_pointer first2,
                  Container::const_pointer last2);

/// Returns a pointer to the first element in the range [first,last) that
/// compares equal to value, or last if no such element found.
static Container::pointer find(Container::pointer first,
                              Container::pointer last,
                              const Container::value_type& value);
// --------------------------------------------------------------

Container::Container(const Container& other)
: Container(other.size()) {
    ::copy(other.begin(), other.end(), begin());  // ::is scope resolution for static function
    used = other.size();
}

// move Copy constructor(&&)
Container::Container(Container&& other)
: capacity(other.capacity), used(other.used), data(other.data) {
    // leave other in a stable state
    other.data = nullptr;
    other.capacity = other.used = 0;
}

Container::Container(const std::initializer_list<value_type>& init)
: Container(init.size()) {
    ::copy(init.begin(), init.end(), begin());
    used = init.size();
}

Container::~Container() {
    delete [] data;
    data = nullptr;
    used = capacity = 0;
}

void Container::push_back(const value_type& value) {
    if (size() == capacity) {
        pointer copy_of_data = new value_type[capacity +=8] ;  // can use auto instead of pointer
        // auto copy_of_data { new value_type[capacity += 8] };  // this is modern way to do 1
        // auto copy_of_data { new value_type[capacity += 8] {} };  // this is modern way to do 2
        // auto copy_of_data new value_type[capacity += 8] {} ;  // this is modern way to do 3
        copy(begin(), end(), copy_of_data);
        delete [] data;
        data = copy_of_data;
    }

    *(data + used++) = value;
}

void Container::erase(pointer pos) {
    if (pos != nullptr) {
        assert(pos >= begin());
        assert(pos < end());
        ::copy(pos + 1, end(), pos);
        --used;
    }
}

void Container::swap(Container& other) {
    size_type temp_size = 0;  // better not use auto
    pointer temp_ptr = nullptr;  // better not use auto
    // auto temp_size = size_type{0}; this will be possible to use auto
    //{} << this initializes default value

    // swap members
    temp_size = capacity;
    capacity = other.capacity;
    other.capacity = temp_size;

    temp_size = used;
    used = other.used;
    other.used = temp_size;

    temp_ptr = data;
    data = other.data;
    other.data = temp_ptr;
}

Container::pointer
Container::find(const value_type& target, pointer pos) {
    auto first = pos == nullptr ? begin() : pos;
    return ::find(first, end(), target);
}

bool equal(const Container& lhs, const Container& rhs) {
    return :: equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

void write(std::ostream& output, const Container& container) {
    output << container;
}
// --------------------------------------------------------------

Container& Container::operator=(const Container& rhs) {
    if (this != &rhs) {
        delete [] data;
        data = new value_type[rhs.size()];
        ::copy(rhs.begin(), rhs.end(), begin());
        used = capacity = rhs.size();
    }
    return *this;
}

/// move operator uses R-Value(&&)
Container& Container::operator=(Container&& rhs) {
    if (this != &rhs) {
        delete [] data;

        // take ownership of rhs contents
        data = rhs.data;
        capacity = rhs.capacity;
        used = rhs.used;

        // leave the donoe in a stable state
        rhs.data = nullptr;
        rhs.capacity = rhs.used = 0;
    }

    return *this;
}

Container& Container::operator+=(const Container& rhs) {
    const auto reqd_size = size() +rhs.size();

    if(capacity < reqd_size) {
        auto copy_of_data = new value_type[reqd_size];
        ::copy(begin(), end(), copy_of_data);
        delete [] data;
        data = copy_of_data;
        capacity = reqd_size;
    }

    ::copy(rhs.begin(), rhs.end(), end()); // append rhs

    used = reqd_size;
    return *this;
}

bool operator==(const Container& lhs, const Container& rhs) {
    return ::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

bool operator!=(const Container& lhs, const Container& rhs) {
    return !(lhs == rhs);
}

Container operator+(const Container& lhs, const Container& rhs) {
    return Container(lhs) += rhs;
}

std::ostream& operator<<(std::ostream& output, const Container& oset) {
    char separator[2] {};

    output << '{';

    for (auto& item : oset) {
        output << separator << item;
        *separator = ',';
    }

    return output << '}';
}


// --------------------------------------------------------------
static void copy(Container::const_pointer first,
                 Container::const_pointer last,
                 Container::pointer d_first) {
    while (first != last) {
        *d_first++ = *first++;
    }
}

static bool equal(Container::const_pointer first1,
                  Container::const_pointer last1,
                  Container::const_pointer first2,
                  Container::const_pointer last2) {
    bool result = last1 - first1 == last2 - first2;  // check same size

    while (result && first1 != last1) {
        result = *first1++ ==*first2++;
    }
    return result;
}

static Container::pointer find(Container::pointer first,
                               Container::pointer last,
                               const Container::value_type& value) {
    auto location = last;

    while (first != location) {
        if (*first == value) {
            location = first;
        }
        else {
            ++first;
        }
    }
    return location;
}


