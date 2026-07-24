#include "../number.hpp"

namespace Phytra{
//Comparison operators
template<typename T>
bool operator==(const dual_quaternion<T>& lhs, const dual_quaternion<T>& rhs){
    return lhs.q == rhs.q && lhs.e == rhs.e;
}
template<typename T>
bool operator!=(const dual_quaternion<T>& lhs, const dual_quaternion<T>& rhs){
    return lhs.q != rhs.q || lhs.e != rhs.e;
}

//Unary arithmetic operators
template<typename T>
dual_quaternion<T> operator+(const dual_quaternion<T>& lhs) {
    return lhs;
}
template<typename T> requires (is_signed_rational_or_signed_v<T>)
dual_quaternion<T> operator-(const dual_quaternion<T>& lhs) {
    return dual_quaternion<T>(-lhs.q, -lhs.e);
}

//Binary arithmetic operators
template<typename T>
dual_quaternion<T> operator+(const dual_quaternion<T>& lhs, const dual_quaternion<T>& rhs) {
    return dual_quaternion<T>(lhs.q + rhs.q, lhs.e + rhs.e);
}
template<typename T>
dual_quaternion<T> operator-(const dual_quaternion<T>& lhs, const dual_quaternion<T>& rhs) {
    return dual_quaternion<T>(lhs.q - rhs.q, lhs.e - rhs.e);
}
template<typename T>
dual_quaternion<T> operator*(const dual_quaternion<T>& lhs, const dual_quaternion<T>& rhs) {
    return dual_quaternion<T>(lhs.q*rhs.q, lhs.q*rhs.e + lhs.e*rhs.q);
}
template<typename T>
dual_quaternion<T> operator/(const dual_quaternion<T>& lhs, const dual_quaternion<T>& rhs) {
    const T q_abs2 = rhs.q.r*rhs.q.r + rhs.q.i*rhs.q.i + rhs.q.j*rhs.q.j + rhs.q.k*rhs.q.k;
    const quaternion<T> qinv = quaternion<T>(rhs.q.r/q_abs2, -rhs.q.i/q_abs2, -rhs.q.j/q_abs2, -rhs.q.k/q_abs2);
    return lhs * dual_quaternion<T>(qinv, -(qinv * rhs.e * qinv));
}
template<typename T>
dual_quaternion<T> operator%(const dual_quaternion<T>& lhs, const dual_quaternion<T>& rhs) {
    return lhs - (lhs / rhs) * rhs;
}
}
