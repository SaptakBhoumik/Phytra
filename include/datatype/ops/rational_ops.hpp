#pragma once
#include "../number.hpp"
#include "../promote.hpp"

namespace Phytra{
//Comparison operators
template<typename T>
inline bool operator==(const rational<T> lhs, const rational<T> rhs){
    return (lhs.numerator() == rhs.numerator()) && (lhs.denominator() == rhs.denominator());
}
template<typename T>
inline bool operator!=(const rational<T> lhs, const rational<T> rhs){
    return (lhs.numerator() != rhs.numerator()) || (lhs.denominator() != rhs.denominator());
}
template<typename T>
inline bool operator<(const rational<T> lhs, const rational<T> rhs){
    const auto lhs_num = static_cast<double_width_t<T>>(lhs.numerator());
    const auto rhs_num = static_cast<double_width_t<T>>(rhs.numerator());

    const auto lhs_den = static_cast<double_width_t<T>>(lhs.denominator());
    const auto rhs_den = static_cast<double_width_t<T>>(rhs.denominator());

    return (lhs_num * rhs_den) < (rhs_num * lhs_den);
}
template<typename T>
inline bool operator<=(const rational<T> lhs, const rational<T> rhs){
    const auto lhs_num = static_cast<double_width_t<T>>(lhs.numerator());
    const auto rhs_num = static_cast<double_width_t<T>>(rhs.numerator());

    const auto lhs_den = static_cast<double_width_t<T>>(lhs.denominator());
    const auto rhs_den = static_cast<double_width_t<T>>(rhs.denominator());

    return (lhs_num * rhs_den) <= (rhs_num * lhs_den); 
}
template<typename T>
inline bool operator>(const rational<T> lhs, const rational<T> rhs){
    const auto lhs_num = static_cast<double_width_t<T>>(lhs.numerator());
    const auto rhs_num = static_cast<double_width_t<T>>(rhs.numerator());

    const auto lhs_den = static_cast<double_width_t<T>>(lhs.denominator());
    const auto rhs_den = static_cast<double_width_t<T>>(rhs.denominator());

    return (lhs_num * rhs_den) > (rhs_num * lhs_den);
}
template<typename T>
inline bool operator>=(const rational<T> lhs, const rational<T> rhs){
    const auto lhs_num = static_cast<double_width_t<T>>(lhs.numerator());
    const auto rhs_num = static_cast<double_width_t<T>>(rhs.numerator());

    const auto lhs_den = static_cast<double_width_t<T>>(lhs.denominator());
    const auto rhs_den = static_cast<double_width_t<T>>(rhs.denominator());

    return (lhs_num * rhs_den) >= (rhs_num * lhs_den);
}

//Unary arithmetic operators
template<typename T>
inline rational<T> operator+(const rational<T> lhs) {
    return lhs;
}
template<typename T> requires (std::is_signed_v<T>)
inline rational<T> operator-(const rational<T> lhs) {
    return rational<T>(-lhs.numerator(), lhs.denominator());
}

//Binary arithmetic operators
template<typename T>
inline rational<T> operator+(const rational<T> lhs, const rational<T> rhs) {
    const auto lhs_num = static_cast<double_width_t<T>>(lhs.numerator());
    const auto rhs_num = static_cast<double_width_t<T>>(rhs.numerator());

    const auto lhs_den = static_cast<double_width_t<T>>(lhs.denominator());
    const auto rhs_den = static_cast<double_width_t<T>>(rhs.denominator());
    
    return rational<T>(lhs_num * rhs_den + rhs_num * lhs_den, lhs_den * rhs_den);
}
template<typename T>
inline rational<T> operator-(const rational<T> lhs, const rational<T> rhs) {
    const auto lhs_num = static_cast<double_width_t<T>>(lhs.numerator());
    const auto rhs_num = static_cast<double_width_t<T>>(rhs.numerator());

    const auto lhs_den = static_cast<double_width_t<T>>(lhs.denominator());
    const auto rhs_den = static_cast<double_width_t<T>>(rhs.denominator());
    
    return rational<T>(lhs_num * rhs_den - rhs_num * lhs_den, lhs_den * rhs_den);
}
template<typename T>
inline rational<T> operator*(const rational<T> lhs, const rational<T> rhs) {
    const auto lhs_num = static_cast<double_width_t<T>>(lhs.numerator());
    const auto rhs_num = static_cast<double_width_t<T>>(rhs.numerator());

    const auto lhs_den = static_cast<double_width_t<T>>(lhs.denominator());
    const auto rhs_den = static_cast<double_width_t<T>>(rhs.denominator());
    
    return rational<T>(lhs_num * rhs_num, lhs_den * rhs_den);
}
template<typename T>
inline rational<T> operator/(const rational<T> lhs, const rational<T> rhs) {
    const auto lhs_num = static_cast<double_width_t<T>>(lhs.numerator());
    const auto rhs_num = static_cast<double_width_t<T>>(rhs.numerator());

    const auto lhs_den = static_cast<double_width_t<T>>(lhs.denominator());
    const auto rhs_den = static_cast<double_width_t<T>>(rhs.denominator());
    
    return rational<T>(lhs_num * rhs_den, lhs_den * rhs_num);
}
template<typename T>
inline rational<T> operator%(const rational<T> lhs, const rational<T> rhs) {
    const auto lhs_num = static_cast<double_width_t<T>>(lhs.numerator());
    const auto rhs_num = static_cast<double_width_t<T>>(rhs.numerator());

    const auto lhs_den = static_cast<double_width_t<T>>(lhs.denominator());
    const auto rhs_den = static_cast<double_width_t<T>>(rhs.denominator());
    
    return rational<T>(lhs_num * rhs_den % (rhs_num * lhs_den), lhs_den * rhs_den);
}
}