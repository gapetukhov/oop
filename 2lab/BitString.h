#ifndef BITSTRING_H
#define BITSTRING_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <initializer_list>
#include <cstring> 

class BitString {
public:
    BitString();
    BitString(size_t n, unsigned char value = 0);
    BitString(const std::initializer_list<unsigned char>& bits);
    BitString(const std::string& bitString);
    BitString(const BitString& other);
    BitString(BitString&& other) noexcept;
    ~BitString();

    BitString& operator=(const BitString& other);
    BitString& operator=(BitString&& other) noexcept;

    BitString operator+(const BitString& other) const;
    BitString operator-(const BitString& other) const;
    BitString operator&(const BitString& other) const;
    BitString operator|(const BitString& other) const;
    BitString operator^(const BitString& other) const;
    BitString operator~() const;

    bool operator==(const BitString& other) const;
    bool operator!=(const BitString& other) const;
    bool operator<(const BitString& other) const;
    bool operator>(const BitString& other) const;

    size_t size() const;
    void resize(size_t newSize, unsigned char value = 0);
    unsigned char at(size_t index) const;
    void set(size_t index, unsigned char value);

    friend std::ostream& operator<<(std::ostream& os, const BitString& bitString);

private:
    unsigned char* bits; 
    size_t len;       

    void validateBit(unsigned char value) const;
    void allocateAndCopy(const unsigned char* source, size_t size);
    void freeMemory();
};

#endif 
