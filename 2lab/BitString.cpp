#include "BitString.h"

BitString::BitString() : bits(nullptr),len(0) {}

BitString::BitString(size_t n, unsigned char value) : bits(new unsigned char[n]), len(n) {
    validateBit(value);
    std::fill(bits, bits + n, value);
}

BitString::BitString(const std::initializer_list<unsigned char>& initList)
    : bits(new unsigned char[initList.size()]),len(initList.size()) {
    size_t index = 0;
    for (unsigned char bit : initList) {
        validateBit(bit);
        bits[index++] = bit;
    }
}

BitString::BitString(const std::string& bitString) : bits(new unsigned char[bitString.size()]), len(bitString.size()) {
    for (size_t i = 0; i < bitString.size();i++) {
        if (bitString[i]!= '0' && bitString[i] != '1') {
            throw std::invalid_argument("nonnumer");
        }
        bits[i] = bitString[i] -'0';
    }
}

BitString::BitString(const BitString& other) : bits(nullptr), len(0) {
    allocateAndCopy(other.bits,other.len);
}

BitString::BitString(BitString&& other) noexcept : bits(other.bits),len(other.len) {
    other.bits = nullptr;
    other.len = 0;
}

BitString::~BitString() {
    freeMemory();
}

BitString& BitString::operator=(const BitString& other) {
    if (this != &other) {
        freeMemory();
        allocateAndCopy(other.bits, other.len);
    }
    return *this;
}

BitString& BitString::operator=(BitString&& other) noexcept {
    if (this != &other) {
        freeMemory();
        bits = other.bits;
        len = other.len;
        other.bits = nullptr;
        other.len = 0;
    }
    return *this;
}

BitString BitString::operator+(const BitString& other) const {
    BitString result(len + other.len);
    std::memcpy(result.bits, bits, len);
    std::memcpy(result.bits + len, other.bits, other.len);
    return result;
}

BitString BitString::operator-(const BitString& other) const {
    if (other.len > len) {
        throw std::invalid_argument("Very long");
    }
    BitString result(len - other.len);
    std::memcpy(result.bits, bits, len - other.len);
    return result;
}

BitString BitString::operator&(const BitString& other) const {
    size_t minLen = std::min(len, other.len);
    BitString result(minLen);
    for (size_t i = 0; i < minLen;i++) {
        result.bits[i] = bits[i] & other.bits[i];
    }
    return result;
}

BitString BitString::operator|(const BitString& other) const {
    size_t minLen = std::min(len, other.len);
    BitString result(minLen);
    for (size_t i = 0; i < minLen; i++) {
        result.bits[i] = bits[i] | other.bits[i];
    }
    return result;
}

BitString BitString::operator^(const BitString& other) const {
    size_t minLen = std::min(len, other.len);
    BitString result(minLen);
    for (size_t i = 0; i< minLen; i++) {
        result.bits[i] = bits[i] ^ other.bits[i];
    }
    return result;
}

BitString BitString::operator~() const {
    BitString result(len);
    for (size_t i = 0; i < len; i++) {
        result.bits[i] = ~bits[i] & 1;
    }
    return result;
}

bool BitString::operator==(const BitString& other) const {
    if (len != other.len) return false;
    return std::memcmp(bits,other.bits, len) == 0;
}

bool BitString::operator!=(const BitString& other) const {
    return !(*this == other);
}

bool BitString::operator<(const BitString& other) const {
    size_t minLen = std::min(len,other.len);
    for (size_t i = 0; i < minLen;i++) {
        if (bits[i] != other.bits[i]) return bits[i] <other.bits[i];
    }
    return len < other.len;
}

bool BitString::operator>(const BitString& other) const {
    return other < *this;
}

size_t BitString::size() const {
    return len;
}

void BitString::resize(size_t newSize, unsigned char value) {
    validateBit(value);
    unsigned char* newBits = new unsigned char[newSize];
    std::memcpy(newBits, bits, std::min(len, newSize));
    if (newSize > len) {
        std::fill(newBits + len,newBits + newSize,value);
    }
    freeMemory();
    bits = newBits;
    len = newSize;
}

unsigned char BitString::at(size_t index) const {
    if (index >= len) throw std::out_of_range("long1");
    return bits[index];
}

void BitString::set(size_t index, unsigned char value) {
    if (index >= len) throw std::out_of_range("long2");
    validateBit(value);
    bits[index] = value;
}

void BitString::validateBit(unsigned char value) const {
    if (value != 0 && value != 1) {
        throw std::invalid_argument("nonnumeb2");
    }
}

void BitString::allocateAndCopy(const unsigned char* source, size_t size) {
    bits = new unsigned char[size];
    len = size;
    std::memcpy(bits,source, size);
}

void BitString::freeMemory() {    delete[] bits;
    bits = nullptr;
    len = 0;
}

std::ostream& operator<<(std::ostream& os, const BitString& bitString) {
    for (size_t i = 0; i < bitString.len; i++) {
        os << static_cast<int>(bitString.bits[i]);
    }
    return os;
}
