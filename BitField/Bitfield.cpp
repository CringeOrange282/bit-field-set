#include "Bitfield.h"
#include <iostream>
#include <stdexcept>

constexpr size_t BITS_PER_ELEMENT = sizeof(unsigned int) * 8;


Bitfield::Bitfield() : _data(nullptr), _size(0) {}
Bitfield::Bitfield(size_t _size) : _size(_size) {
    if (_size == 0) {
        _data = nullptr;
    }
    else {
        _data = new unsigned int[(_size + BITS_PER_ELEMENT - 1) / BITS_PER_ELEMENT]();
    }
}

Bitfield::Bitfield(const Bitfield& other) : _size(other._size) {
    if (_size == 0) {
        _data = nullptr;
    }
    else {
        size_t array_size = (_size + BITS_PER_ELEMENT - 1) / BITS_PER_ELEMENT;
        _data = new unsigned int[array_size];
        for (size_t i = 0; i < array_size; i++) {
            _data[i] = other._data[i];
        }
    }
}

Bitfield::~Bitfield() {
    delete[] _data;
}

size_t Bitfield::get_size() const noexcept {
    return _size;
}

size_t Bitfield::get_index(size_t pos) const {
    return (pos) / BITS_PER_ELEMENT;
}
unsigned int Bitfield::get_mask(size_t pos) const {
    return 1U << (BITS_PER_ELEMENT - 1 - ((pos) % BITS_PER_ELEMENT));
}
void Bitfield::set_bit(size_t pos) {
    if (pos >= _size) {
        throw std::invalid_argument("Bitfield::set_bit: Position out of range");
    }
    else {
        size_t index = get_index(pos);
        unsigned int mask = get_mask(pos);
        _data[index] |= mask;
    }
}

bool Bitfield::get_bit(size_t pos) const {
    if (pos >= _size) {
        throw std::invalid_argument("Bitfield::get_bit: Position out of range");
    }
    size_t index = get_index(pos);
    unsigned int mask = get_mask(pos);
    return (_data[index] & mask);
}
void Bitfield::reset_bit(size_t pos) {
    if (pos >= _size) {
        throw std::invalid_argument("Bitfield::reset_bit: Position out of range");
    }
    size_t index = get_index(pos);
    unsigned int mask = get_mask(pos);
    _data[index] = (_data[index] & ~mask);
}

bool Bitfield::operator==(const Bitfield& other) const {
    if (this->_size != other._size) {
        return false;
    }
    for (size_t i = 0; i < (_size + BITS_PER_ELEMENT - 1) / BITS_PER_ELEMENT; i++) {
        if (this->_data[i] != other._data[i]) {
            return false;
        }
    }
    return true;
}

bool Bitfield::operator!=(const Bitfield& other) const {
    return !(*this == other);
}

Bitfield& Bitfield::operator=(const Bitfield& other) {
    if (this == &other) {
        return *this;
    }

    delete[] _data;
    _size = other._size;

    if (_size == 0 || other._data == nullptr) {
        _data = nullptr;
    }
    else{
        size_t array_size = (_size + BITS_PER_ELEMENT - 1) / BITS_PER_ELEMENT;
        _data = new unsigned int[array_size];
        for (size_t i = 0; i < array_size; i++) {
            _data[i] = other._data[i];
        }
    }
    return *this;
}

Bitfield Bitfield::operator|(const Bitfield& other) const {
    if (this->_size != other._size) {
        throw std::logic_error("Bitfield::operator|: Bitfield sizes must be equal");
    }
    Bitfield next = Bitfield(other._size);
    for (size_t i = 0; i < (_size + BITS_PER_ELEMENT - 1) / BITS_PER_ELEMENT; i++) {
        next._data[i] = this->_data[i] | other._data[i];
    }
    return next;
}
Bitfield& Bitfield::operator|=(const Bitfield& other) {
    *this = (*this | other);
    return *this;
}
Bitfield Bitfield::operator&(const Bitfield& other) const {
    if (this->_size != other._size) {
        throw std::logic_error("Bitfield::operator&: Bitfield sizes must be equal");
    }
    Bitfield next = Bitfield(other._size);
    for (size_t i = 0; i < (_size + BITS_PER_ELEMENT - 1) / BITS_PER_ELEMENT; i++) {
        next._data[i] = this->_data[i] & other._data[i];
    }
    return next;
}
Bitfield& Bitfield::operator&=(const Bitfield& other) {
    *this = *this & other;
    return *this;
}
Bitfield Bitfield::operator~() const {
    Bitfield next(this->_size);
    size_t array_size = (this->_size + BITS_PER_ELEMENT - 1) / BITS_PER_ELEMENT;
    for (size_t i = 0; i < array_size; i++) {
        next._data[i] = ~this->_data[i];
    }
    next.clear_bits();
    return next;
}

void Bitfield::clear_bits() {
    if (_size == 0) return;
    size_t total_bits = ((_size + BITS_PER_ELEMENT - 1) / BITS_PER_ELEMENT) * BITS_PER_ELEMENT;
    size_t unused_bits = total_bits - _size;
    if (unused_bits > 0) {
        unsigned int mask = ~0U;
        mask <<= unused_bits;
        _data[(_size + BITS_PER_ELEMENT - 1) / BITS_PER_ELEMENT - 1] &= mask;
    }
}

std::ostream& operator<<(std::ostream& out, const Bitfield& bf) {
    for (size_t i = 0; i < bf.get_size(); ++i) {
        out << (bf.get_bit(i) ? '1' : '0');
    }
    return out;
}

std::istream& operator>>(std::istream& in, Bitfield& bf) {
    std::string str;
    if (in >> str) {
        Bitfield temp(str.length());
        for (size_t i = 0; i < str.length(); ++i) {
            if (str[i] == '1') temp.set_bit(i);
        }
        bf = std::move(temp);
    }
    return in;
}
