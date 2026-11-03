#include "Set.h"
#include <stdexcept>
#include <string>

void swap(Set& first, Set& second) noexcept {
    using std::swap;
    swap(first._bitfield, second._bitfield);
    swap(first._name, second._name);
}

Set::Set(size_t _size) {
    _bitfield = Bitfield(_size);
    _name = std::to_string(_size);
}

Set::Set(const Set& other) {
    _bitfield = Bitfield(other._bitfield);
    _name = other._name;
}

Set::Set(Set&& other) noexcept : _bitfield(0), _name("") {
    swap(*this, other);
}

Set::Set(const Bitfield bitfield) {
    _bitfield = Bitfield(bitfield);
    _name = std::to_string(bitfield.get_size());
}

void Set::insert(int elem) {
    if (elem <= 0 || elem > max_power()) {
        throw std::out_of_range("");
    }
    _bitfield.set_bit(elem);
}

void Set::erase(int elem) {
    if (elem <= 0 || elem > max_power()) {
        throw std::out_of_range("");
    }
    _bitfield.reset_bit(elem);
}

Set& Set::operator+=(int elem) {
    insert(elem);
    return *this;
}

Set Set::operator +(int elem) const {
    Set res(*this);
    res += elem;
    return res;
}

Set& Set::operator +=(const Set& other) {
    if (max_power() != other.max_power()) {
        throw std::logic_error("");
    }
    this->_bitfield |= other._bitfield;
    return *this;
}

Set Set::operator +(const Set& other) const {
    if (max_power() != other.max_power()) {
        throw std::logic_error("");
    }
    Set res(*this);
    return res += other;
}

Set& Set::operator -=(int elem) {
    erase(elem);
    return *this;
}

Set Set::operator -(int elem) const {
    Set res(*this);
    res -= elem;
    return res;
}

Set& Set::operator-=(const Set& other) {
    if (max_power() != other.max_power()) {
        throw std::logic_error("");
    }
    this->_bitfield &= ~other._bitfield;
    return *this;
}

Set Set::operator -(const Set& other) const {
    if (max_power() != other.max_power()) {
        throw std::logic_error("");
    }
    Set res(*this);
    return res -= other;
}

Set Set::operator-() const noexcept {
    Set res(*this);
    res._bitfield = ~res._bitfield;
    return res;
}

Set& Set::operator=(const Set& other) noexcept {
    if (this == &other) return *this;
    Set temp(other);
    swap(*this, temp);
    return *this;
}

Set& Set::operator=(Set&& other) noexcept {
    if (this == &other) return *this;
    swap(*this, other);
    return *this;
}

Set& Set::operator*=(const Set& other) {
    if (max_power() != other.max_power()) throw std::logic_error("");
    this->_bitfield &= other._bitfield;
    return *this;
}

Set Set::operator*(const Set& other) const {
    if (max_power() != other.max_power()) throw std::logic_error("");
    Set res(*this);
    return res *= other;
}

bool Set::is_member(int elem) const {
    if (elem <= 0 || elem > max_power()) return false;
    return _bitfield.get_bit(elem);
}

Set::operator Bitfield() const noexcept {
    return _bitfield;
}

std::ostream& operator<<(std::ostream& out, const Set& s) {
    out << "{ ";
    bool first = true;
    for (size_t i = 1; i <= s.max_power(); ++i) {
        if (s.is_member(i)) {
            if (!first) out << ", ";
            out << i;
            first = false;
        }
    }
    out << " }";
    return out;
}

std::istream& operator>>(std::istream& in, Set& s) {
    char ch;
    in >> ch; // —читываем '{'
    if (ch != '{') return in;
    Set temp(s.max_power()); 
    int val;
    while (in >> val) {
        temp.insert(val);
        in >> ch; 
        if (ch == '}') break;
    }
    s = std::move(temp);
    return in;
}

