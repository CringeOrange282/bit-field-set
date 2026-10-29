#pragma once
#include <cstddef> 

class Bitfield {
    unsigned int* _data;
    size_t _size;
public:
    Bitfield();
    Bitfield(size_t _size);
    Bitfield(const Bitfield&);
    ~Bitfield();

    void set_bit(size_t pos);
    bool get_bit(size_t pos) const;
    void reset_bit(size_t pos);

    bool operator==(const Bitfield& other) const;
    bool operator!=(const Bitfield& other) const;

    Bitfield& operator=(const Bitfield& other);

    Bitfield operator|(const Bitfield& other) const;
    Bitfield operator&(const Bitfield& other) const;

    Bitfield& operator|=(const Bitfield& other);
    Bitfield& operator&=(const Bitfield& other);

    Bitfield operator~() const;

private:
    unsigned int get_mask(size_t pos) const;
    size_t get_index(size_t pos) const;
};
