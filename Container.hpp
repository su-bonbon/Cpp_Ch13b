/// @file Container.hpp
/// @author Sujin Lee
/// @date 3/7/2022
/// @note I pledge my word of honor that I have complied with the
/// CSN Academic Integrity Policy while completing this assignment.
/// @brief HPP file for pa13.cpp
/// @note 25hr
/// 2022-03-02: Created by Sujin Lee

#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <initializer_list>
#include <iostream>
#include <cassert>


template <class T>
class Container{
public:
    /// Member types.
    using value_type = T;
    using size_type = std::size_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;

    /// Default ctor
    Container(size_type count = 0)
    : capacity(count), used(0), data(new value_type[count]) {}

    /// Copy ctor
    Container(const Container& other);

    /// Move ctor
    Container(Container&& other);

    /// Initializer List ctor
    Container(const std::initializer_list<value_type>& init);

    /// Destructor
    ~Container();

    // Copy assigment
    Container& operator=(const Container& rhs);

    // Move assignment
    Container& operator=(Container&& rhs);

    // Append another container to this
    Container& operator+=(const Container& rhs);

    /// Check if the container has no element, || begin() == end()
    /// @return true if the container is empty, false otherwise.
    bool empty() const { return begin() == end(); }

    /// Return the number of elements in the container
    size_type size() const { return used; }

    /// Return a pointer to the first element
    pointer begin() { return data; }
    const_pointer begin() const { return data; }

    /// Returns a pointer to the end
    /// the element following the last element
    pointer end() { return begin() + size(); }
    const_pointer end() const { return begin() + size(); }

    /// Adds an element to the end
    void push_back(const value_type& value);

    /// Removes a signle item from the container
    void erase(pointer pos);

    /// After this call, size() return ZERO
    /// The capacity remains unchanged
    void clear() { used = 0; }

    /// Exchanges the contents of the container with those of other.
    void swap(Container& other);

    /// Find the first element equal to the given target.
    /// Search begins ar pos
    /// @return pointer to the element if found, or end() if no found
    pointer find(const value_type& target, pointer pos = nullptr);

private:
    size_type capacity;
    size_type used;
    pointer data;
};

// related non-member functions

/// Check the contents of lhs and rhs are equal, that is, they have the same
/// number of elements and each element in lhs compares equal with the element
/// in rhs at the same position
template <class T>
[[deprecated]]
bool equal(const Container<T>& lhs, const Container<T>& rhs);

/// Performs stream outpit on Conatiners, using "{1,2,3}" format
template <class T>
[[deprecated]]
void write(std::ostream& output, const Container<T>& container);

/// Equality comparison operators
template <class T>
bool operator==(const Container<T>& lhs, const Container<T>& rhs);

template <class T>
bool operator!=(const Container<T>& lhs, const Container<T>& rhs);

/// Concatenation operator
template <class T>
Container<T> operator+(const Container<T>& lhs, const Container<T>& rhs);

/// Stream insertion operator
template <class T>
std::ostream& operator<<(std::ostream& output, const Container<T>& oset);

// ABOVE COPIED FROM CONTAINER_H

// ===========================================================================================================//

/// Copies the elements in the range defiend by [first, last)
/// to another range beginning at dest
template <class T>
static void copy(typename Container<T>::const_pointer first,
                 typename Container<T>::const_pointer last,
                 typename Container<T>::pointer d_first);

/// Returns true if the range [first1,last1) is equal to the range
/// [first2,last2) and false otherwise.
template <class T>
static bool equal(typename Container<T>::const_pointer first1,
                  typename Container<T>::const_pointer last1,
                  typename Container<T>::const_pointer first2,
                  typename Container<T>::const_pointer last2);

/// Returns a pointer to the first element in the range [first,last) that
/// compares equal to value, or last if no such element found.
template <class T>
static typename Container<T>::pointer find(typename Container<T>::pointer first,
                                           typename Container<T>::pointer last,
                                           const typename Container<T>::value_type& value);

/// Swaps the values a and b.
template <class T>
static void swap(Container<T>& lhs, Container<T>& rhs);

// --------------------------------------------------------------
template <class T>
Container<T>::Container(const Container<T>& other)
: Container<T>(other.size()) {
    ::copy<T>(other.begin(), other.end(), begin());  // ::is scope resolution for static function
    used = other.size();
}

// move Copy constructor(&&)
template <class T>
Container<T>::Container(Container<T>&& other)
: capacity(other.capacity), used(other.used), data(other.data) {
    // leave other in a stable state
    other.data = nullptr;
    other.capacity = other.used = 0;
}
template <class T>
Container<T>::Container(const std::initializer_list<value_type>& init)
: Container<T>(init.size()) {
    ::copy<T>(init.begin(), init.end(), begin());
    used = init.size();
}
template <class T>
Container<T>::~Container() {
    delete [] data;
    data = nullptr;
    used = capacity = 0;
}
template <class T>
void Container<T>::push_back(const value_type& value) {
    if (size() == capacity) {
        pointer copy_of_data = new value_type[capacity +=8] ;  // can use auto instead of pointer
        // auto copy_of_data { new value_type[capacity += 8] };  // this is modern way to do 1
        // auto copy_of_data { new value_type[capacity += 8] {} };  // this is modern way to do 2
        // auto copy_of_data new value_type[capacity += 8] {} ;  // this is modern way to do 3
        ::copy<T>(begin(), end(), copy_of_data);
        delete [] data;
        data = copy_of_data;
    }

    *(data + used++) = value;
}
template <class T>
void Container<T>::erase(pointer pos) {
    if (pos != nullptr) {
        assert(pos >= begin());
        assert(pos < end());
        ::copy<T>(pos + 1, end(), pos);
        --used;
    }
}
template <class T>
void Container<T>::swap(Container<T>& other) {
    ::swap<T>(*this, other);
}
template <class T>
typename Container<T>::pointer
Container<T>::find(const value_type& target, pointer pos) {
    auto first = pos == nullptr ? begin() : pos;
    return ::find<T>(first, end(), target);
}
template <class T>
bool equal(const Container<T>& lhs, const Container<T>& rhs) {
    return ::equal<T>(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
template <class T>
void write(std::ostream& output, const Container<T>& container) {
    output << container;
}

// --------------------------------------------------------------
template <class T>
Container<T>& Container<T>::operator=(const Container<T>& rhs) {
    if (this != &rhs) {
        delete [] data;
        data = new value_type[rhs.size()];
        ::copy<T>(rhs.begin(), rhs.end(), begin());
        used = capacity = rhs.size();
    }
    return *this;
}

/// move operator uses R-Value(&&)
template <class T>
Container<T>& Container<T>::operator=(Container<T>&& rhs) {
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
template <class T>
Container<T>& Container<T>::operator+=(const Container<T>& rhs) {
    const auto reqd_size = size() +rhs.size();

    if(capacity < reqd_size) {
        auto copy_of_data = new value_type[reqd_size];
        ::copy<T>(begin(), end(), copy_of_data);
        delete [] data;
        data = copy_of_data;
        capacity = reqd_size;
    }

    ::copy<T>(rhs.begin(), rhs.end(), end()); // append rhs

    used = reqd_size;
    return *this;
}
template <class T>
bool operator==(const Container<T>& lhs, const Container<T>& rhs) {
    return ::equal<T>(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
template <class T>
bool operator!=(const Container<T>& lhs, const Container<T>& rhs) {
    return !(lhs == rhs);
}
template <class T>
Container<T> operator+(const Container<T>& lhs, const Container<T>& rhs) {
    return Container<T>(lhs) += rhs;
}
template <class T>
std::ostream& operator<<(std::ostream& output, const Container<T>& oset) {
    char separator[2] {};

    output << '{';

    for (auto& item : oset) {
        output << separator << item;
        *separator = ',';
    }

    return output << '}';
}


// --------------------------------------------------------------
template <class T>
static void copy(typename Container<T>::const_pointer first,
                 typename Container<T>::const_pointer last,
                 typename Container<T>::pointer d_first) {
    while (first != last) {
        *d_first++ = *first++;
    }
}

template <class T>
static bool equal(typename Container<T>::const_pointer first1,
                  typename Container<T>::const_pointer last1,
                  typename Container<T>::const_pointer first2,
                  typename Container<T>::const_pointer last2) {
    bool result = last1 - first1 == last2 - first2;  // check same size

    while (result && first1 != last1) {
        result = *first1++ ==*first2++;
    }
    return result;
}

template <class T>
static typename Container<T>::pointer find(typename Container<T>::pointer first,
                                           typename Container<T>::pointer last,
                                           const typename Container<T>::value_type& value) {
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

template <class T>
static void swap(Container<T>& lhs, Container<T>& rhs) {
    Container<T> temp = lhs;
    lhs = rhs;
    rhs = temp;
}


#endif // CONTAINER_H

// EOF
