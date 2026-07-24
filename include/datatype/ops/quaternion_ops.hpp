#include "../number.hpp"

namespace Phytra{
//Comparison operators
template<typename T>
bool operator==(const quaternion<T>& lhs, const quaternion<T>& rhs){
    return (lhs.r == rhs.r) && (lhs.i == rhs.i) && (lhs.j == rhs.j) && (lhs.k == rhs.k);
}
template<typename T>
bool operator!=(const quaternion<T>& lhs, const quaternion<T>& rhs){
    return (lhs.r != rhs.r) || (lhs.i != rhs.i) || (lhs.j != rhs.j) || (lhs.k != rhs.k);
}

//Unary arithmetic operators
template<typename T>
quaternion<T> operator+(const quaternion<T>& lhs) {
    return lhs;
}
template<typename T> requires (is_signed_rational_or_signed_v<T>)
quaternion<T> operator-(const quaternion<T>& lhs) {
    return quaternion<T>(-lhs.r, -lhs.i, -lhs.j, -lhs.k);
}

//Binary arithmetic operators
template<typename T>
quaternion<T> operator+(const quaternion<T>& lhs, const quaternion<T>& rhs) {
    return quaternion<T>(lhs.r + rhs.r, lhs.i + rhs.i, lhs.j + rhs.j, lhs.k + rhs.k);
}
template<typename T>
quaternion<T> operator-(const quaternion<T>& lhs, const quaternion<T>& rhs) {
    return quaternion<T>(lhs.r - rhs.r, lhs.i - rhs.i, lhs.j - rhs.j, lhs.k - rhs.k);
}
template<typename T>
quaternion<T> operator*(const quaternion<T>& lhs, const quaternion<T>& rhs) {
    return quaternion<T>(lhs.r*rhs.r-lhs.i*rhs.i-lhs.j*rhs.j-lhs.k*rhs.k,
                          lhs.r*rhs.i+lhs.i*rhs.r+lhs.j*rhs.k-lhs.k*rhs.j,
                          lhs.r*rhs.j-lhs.i*rhs.k+lhs.j*rhs.r+lhs.k*rhs.i,
                          lhs.r*rhs.k+lhs.i*rhs.j-lhs.j*rhs.i+lhs.k*rhs.r);
}
template<typename T>
quaternion<T> operator/(const quaternion<T>& lhs, const quaternion<T>& rhs) {
    const auto denom = rhs.r*rhs.r+rhs.i*rhs.i+rhs.j*rhs.j+rhs.k*rhs.k;
    return lhs * quaternion<T>(rhs.r/denom, -rhs.i/denom, -rhs.j/denom, -rhs.k/denom);
}
template<typename T>
quaternion<T> operator%(const quaternion<T>& lhs, const quaternion<T>& rhs) {
    return lhs - (lhs / rhs) * rhs;
}
}