#pragma once
#include "Bitfield.h"
#include <string>

class Set {
    Bitfield _bitfield;
    std::string _name;
public:
    Set(size_t);
    Set(const Set&);
    Set(Set&&) noexcept;
    Set(const Bitfield&);

    operator Bitfield() const noexcept;
    void insert(int);
    void erase(int);

    Set& operator +=(int);
    Set& operator -=(int);
    Set operator +(int) const;
    Set operator -(int) const;

    Set operator +(const Set&) const;
    Set operator -(const Set&) const;
    Set& operator+=(const Set&);
    Set& operator-=(const Set&);

    inline size_t max_power() const noexcept {
        return _name.empty() ? _bitfield.get_size() : std::stoull(_name);
    }
    Set operator -() const noexcept;
    Set& operator =(const Set&) noexcept;
    Set& operator =(Set&&) noexcept;

    Set operator *(const Set&) const;
    Set& operator *=(const Set&);

    bool is_member(int elem) const;
    friend void swap(Set& first, Set& second) noexcept;

    friend std::ostream& operator<<(std::ostream& out, const Set& s);
    friend std::istream& operator>>(std::istream& in, Set& s);
};
