/// @file Container.cpp
/// @author Sujin Lee
/// @date 3/7/2022
/// @note I pledge my word of honor that I have complied with the
/// CSN Academic Integrity Policy while completing this assignment.
/// @brief Header file for Container.cpp
/// @note 25hr
/// 2022-03-02: Copied from Kevin's lecture

#ifndef CONTAINER_H
#define CONTAINER_H

#include <initializer_list>
#include <iostream>

class Container{
public:
    /// Member types.
    using value_type = int;
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
[[deprecated]]
bool equal(const Container& lhs, const Container& rhs);

/// Performs stream outpit on Conatiners, using "{1,2,3}" format
[[deprecated]]
void write(std::ostream& output, const Container& container);

/// Equality comparison operators
bool operator==(const Container& lhs, const Container& rhs);
bool operator!=(const Container& lhs, const Container& rhs);

/// Concatenation operator
Container operator+(const Container& lhs, const Container& rhs);

/// Stream insertion operator
std::ostream& operator<<(std::ostream& output, const Container& oset);

#endif // CONTAINER_H

// EOF
