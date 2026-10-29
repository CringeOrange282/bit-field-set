#include "Bitfield.h"
#include <iostream>
#include <stdexcept>

Bitfield::Bitfield(): _data(nullptr), _size(0){}
Bitfield::Bitfield(size_t _size) :_size(_size) {
    _data = new unsigned int[(_size + 31) / 32]();

}
Bitfield::Bitfield(const Bitfield& other) :_size(other._size) {
    size_t array_size = (_size + 31) / 32;
    _data = new unsigned int[array_size];
    for (size_t i = 0; i < array_size; i++) {
        _data[i] = other._data[i];
    }
}
Bitfield::~Bitfield() {
    delete[] _data;
}

size_t Bitfield::get_index(size_t pos) const{
    return (pos-1) / 32;
}
unsigned int Bitfield::get_mask(size_t pos) const{
    return 1 << (31 - ((pos - 1) % 32));
}
void Bitfield::set_bit(size_t pos) {
    if (pos == 0 || pos > _size) {
        throw std::invalid_argument("");
    }
    else {
        size_t index = get_index(pos);
        unsigned int mask = get_mask(pos);
        _data[index] |= mask;
    }
}

bool Bitfield::get_bit(size_t pos) const{
    size_t index = get_index(pos);
    unsigned int mask = get_mask(pos);
    return (_data[index] & mask);
}
void Bitfield::reset_bit(size_t pos) {
    size_t index = get_index(pos);
    unsigned int mask = get_mask(pos);
    _data[index] = (_data[index] & ~mask);
}

bool Bitfield::operator==(const Bitfield& other) const{
    if (this->_size != other._size) {
        return false;
    }
    for (int i = 0; i < (_size+31)/32; i++) {
        if (this->_data[i] != other._data[i]) {
            return false;
        }
    }
    return true;
}

bool Bitfield::operator!=(const Bitfield& other) const{
    return !(*this==other);
}

Bitfield& Bitfield::operator=(const Bitfield& other) {
    if (this == &other) {
        return *this; 
    }

    delete[] _data;
    _size = other._size;
    size_t array_size = (_size + 31) / 32;
    _data = new unsigned int[array_size];
    for (size_t i = 0; i < array_size; i++) {
        _data[i] = other._data[i];
    }
    return *this; 
}

Bitfield Bitfield::operator|(const Bitfield& other) const{
    if (this->_size != other._size) {
        throw std::logic_error("");
    }
    Bitfield next = Bitfield(other._size);
    for (int i = 0; i < (_size + 31) / 32; i++) {
        next._data[i] = this->_data[i] | other._data[i];
    }
    return next;
}
Bitfield& Bitfield::operator|=(const Bitfield& other) {
    *this = (*this|other);
    return *this;
}
Bitfield Bitfield::operator&(const Bitfield& other) const{
    if (this->_size != other._size) {
        throw std::logic_error("");
    }
    Bitfield next = Bitfield(other._size);
    for (int i = 0; i < (_size + 31) / 32; i++) {
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
    size_t array_size = (this->_size + 31) / 32;

    for (size_t i = 0; i < array_size; i++) {
        next._data[i] = ~this->_data[i];
    }
    return next;
}
