#include "../number.hpp"

namespace Phytra{
//Comparison operators
template<typename T>
inline bool operator==(const complex<T> lhs, const complex<T> rhs){
    return (lhs.r == rhs.r) && (lhs.i == rhs.i);
}
template<typename T>
inline bool operator!=(const complex<T> lhs, const complex<T> rhs){
    return (lhs.r != rhs.r) || (lhs.i != rhs.i);
}

//Unary arithmetic operators
template<typename T>
inline complex<T> operator+(const complex<T> lhs) {
    return lhs;
}
template<typename T> requires (is_signed_rational_or_signed_v<T>)
inline complex<T> operator-(const complex<T> lhs) {
    return complex<T>(-lhs.r, -lhs.i);
}

//Binary arithmetic operators
template<typename T>
inline complex<T> operator+(const complex<T> lhs, const complex<T> rhs) {
    return complex<T>(lhs.r + rhs.r, lhs.i + rhs.i);
}
template<typename T>
inline complex<T> operator-(const complex<T> lhs, const complex<T> rhs) {
    return complex<T>(lhs.r - rhs.r, lhs.i - rhs.i);
}
template<typename T>
inline complex<T> operator*(const complex<T> lhs, const complex<T> rhs) {
    return complex<T>(lhs.r * rhs.r - lhs.i * rhs.i, lhs.r * rhs.i + lhs.i * rhs.r);
}
template<typename T>
inline complex<T> operator/(const complex<T> lhs, const complex<T> rhs) {
    const auto denom = rhs.r * rhs.r + rhs.i * rhs.i;
    return complex<T>((lhs.r * rhs.r + lhs.i * rhs.i) / denom, (lhs.i * rhs.r - lhs.r * rhs.i) / denom);
}
template<typename T>
inline complex<T> operator%(const complex<T> lhs, const complex<T> rhs) {
    const auto denom = rhs.r * rhs.r + rhs.i * rhs.i;
    return complex<T>((lhs.r * rhs.r + lhs.i * rhs.i) % denom, (lhs.i * rhs.r - lhs.r * rhs.i) % denom);
}
}