#pragma once
#include "../number.hpp"
#include "../ops/ops.hpp"
#include "primitive_math.hpp"
#include "rational_math.hpp"

namespace Phytra{
//Power/root functions
template<typename T>
complex<T> pow(const complex<T> lhs, const complex<T> rhs){
    auto eular = lhs.to_eular();
    complex<T> ln_lhs = complex<T>(ln(eular.first), eular.second);
    complex<T> ln_lhs_times_rhs = ln_lhs * rhs;
    return complex<T>::from_eular(exp(ln_lhs_times_rhs.r), ln_lhs_times_rhs.i);
}
template<typename T>
complex<T> sqrt(const complex<T> lhs){
    using U = std::conditional_t<std::is_floating_point_v<T> || is_rational<T>::value, T, double>;
    auto eular = lhs.to_eular();
    return complex<T>::from_eular(sqrt(U(eular.first)), U(eular.second) / U(2));
}
template<typename T>
complex<T> cbrt(const complex<T> lhs){
    using U = std::conditional_t<std::is_floating_point_v<T> || is_rational<T>::value, T, double>;
    auto eular = lhs.to_eular();
    return complex<T>::from_eular(cbrt(U(eular.first)), U(eular.second) / U(3));
}

template<typename T>
complex<T> exp(const complex<T> lhs){
    return complex<T>::from_eular(exp(lhs.r), lhs.i);
}
template<typename T>
complex<T> exp2(const complex<T> lhs){
    using U = std::conditional_t<std::is_floating_point_v<T> || is_rational<T>::value, T, double>;
    const auto ln_2 = U(0.6931471805599453);
    return complex<T>::from_eular(U(exp(lhs.r))*ln_2, U(lhs.i)*ln_2);
}
template<typename T>
complex<T> expm1(const complex<T> lhs){
    return exp(lhs) - complex<T>(T(1), T(0));
}
template<typename T>
complex<T> expp1(const complex<T> lhs){
    return exp(lhs) + complex<T>(T(1), T(0));
}

template<typename T>
complex<T> ln(const complex<T> lhs){
    auto eular = lhs.to_eular();
    return complex<T>(T(ln(eular.first)), T(eular.second));
}
template<typename T>
complex<T> log2(const complex<T> lhs){
    using U = std::conditional_t<std::is_floating_point_v<T> || is_rational<T>::value, T, double>;
    const auto eular = lhs.to_eular();
    const U ln_2 = U(0.6931471805599453);
    return complex<T>(T(log2(eular.first)), T(U(eular.second) / ln_2));
}
template<typename T>
complex<T> log10(const complex<T> lhs){
    using U = std::conditional_t<std::is_floating_point_v<T> || is_rational<T>::value, T, double>;
    const auto eular = lhs.to_eular();
    const U ln_10 = U(2.302585092994046);
    return complex<T>(T(log10(eular.first)), T(U(eular.second) / ln_10));
}
template<typename T>
complex<T> log(const complex<T> lhs, const complex<T> rhs){
    return ln(lhs) / ln(rhs);
}

template<typename T>
complex<T> ln_1p(const complex<T> lhs){
    return ln(complex<T>(T(1) + lhs.r, lhs.i));
}
template<typename T>
complex<T> log2_1p(const complex<T> lhs){
    using U = std::conditional_t<std::is_floating_point_v<T> || is_rational<T>::value, T, double>;
    const U ln_2 = U(0.6931471805599453);
    const auto ln_1p_lhs = ln_1p(lhs);
    return complex<T>(T(U(ln_1p_lhs.r) / ln_2), T(U(ln_1p_lhs.i) / ln_2));
}
template<typename T>
complex<T> log10_1p(const complex<T> lhs){
    using U = std::conditional_t<std::is_floating_point_v<T> || is_rational<T>::value, T, double>;
    const U ln_10 = U(2.302585092994046);
    const auto ln_1p_lhs = ln_1p(lhs);
    return complex<T>(T(U(ln_1p_lhs.r) / ln_10), T(U(ln_1p_lhs.i) / ln_10));
}
template<typename T>
complex<T> log_1p(const complex<T> lhs, const complex<T> rhs){
    return ln_1p(lhs) / ln(rhs);
}

//Trigonometric functions
template<typename T>
complex<T> sin(const complex<T> lhs){
    const auto i_lhs = complex<T>(-lhs.i, lhs.r);//i*lhs
    const auto e_c = exp(i_lhs);
    const auto e_c_inv = complex<T>(T(1),T(0))/e_c;
    return (e_c - e_c_inv) / complex<T>(T(0), T(2));
}
template<typename T>
complex<T> cos(const complex<T> lhs){
    const auto i_lhs = complex<T>(-lhs.i, lhs.r);//i*lhs
    const auto e_c = exp(i_lhs);
    const auto e_c_inv = complex<T>(T(1),T(0))/e_c;
    return (e_c + e_c_inv) / complex<T>(T(2), T(0));
}
template<typename T>
complex<T> tan(const complex<T> lhs){
    const auto i_lhs = complex<T>(-lhs.i, lhs.r);//i*lhs
    const auto e_c = exp(i_lhs);
    const auto e_c_inv = complex<T>(T(1),T(0))/e_c;
    return ((e_c - e_c_inv)*complex<T>(T(0), T(-1)))/ (e_c + e_c_inv);
}
template<typename T>
complex<T> cosec(const complex<T> lhs){
    const auto i_lhs = complex<T>(-lhs.i, lhs.r);//i*lhs
    const auto e_c = exp(i_lhs);
    const auto e_c_inv = complex<T>(T(1),T(0))/e_c;
    return complex<T>(T(0), T(2)) / (e_c - e_c_inv) ;
}
template<typename T>
complex<T> sec(const complex<T> lhs){
    const auto i_lhs = complex<T>(-lhs.i, lhs.r);//i*lhs
    const auto e_c = exp(i_lhs);
    const auto e_c_inv = complex<T>(T(1),T(0))/e_c;
    return complex<T>(T(2), T(0)) / (e_c + e_c_inv);
}
template<typename T>
complex<T> cot(const complex<T> lhs){
    const auto i_lhs = complex<T>(-lhs.i, lhs.r);//i*lhs
    const auto e_c = exp(i_lhs);
    const auto e_c_inv = complex<T>(T(1),T(0))/e_c;
    return (e_c + e_c_inv) / ((e_c - e_c_inv)*complex<T>(T(0), T(-1)));
}

template<typename T>
complex<T> asin(const complex<T> z){
    const auto iz = complex<T>(-z.i, z.r); // i*z
    const auto sq = sqrt(complex<T>(T(1),T(0)) - z*z);// sqrt(1-z^2)
    const auto ln = log(iz + sq);
    return complex<T>(ln.i, -ln.r); // -i*ln
}
template<typename T>
complex<T> acos(const complex<T> z){
    const auto sq = sqrt(complex<T>(T(1),T(0)) - z*z); // sqrt(1-z^2)
    const auto i_sq = complex<T>(-sq.i, sq.r); // i*sqrt(1-z^2)
    const auto ln = log(z + i_sq);
    return complex<T>(ln.i, -ln.r); // -i*ln
}
template<typename T>
complex<T> atan(const complex<T> z){
    const auto iz = complex<T>(-z.i, z.r); // i*z
    const auto num = complex<T>(T(1),T(0)) - iz; // 1-iz
    const auto den = complex<T>(T(1),T(0)) + iz; // 1+iz
    const auto ln = log(num/den);
    return complex<T>(-ln.i/T(2), ln.r/T(2)); // (i/2)*ln
}
template<typename T>
complex<T> atan2(const complex<T> lhs, const complex<T> rhs){
    return atan(lhs/rhs);
}
template<typename T>
complex<T> asec(const complex<T> z){
    const auto inv_z = complex<T>(T(1),T(0))/z;
    return acos(inv_z);
}
template<typename T>
complex<T> acosec(const complex<T> z){
    const auto inv_z = complex<T>(T(1),T(0))/z;
    return asin(inv_z);
}
template<typename T>
complex<T> acot(const complex<T> z){
    const auto inv_z = complex<T>(T(1),T(0))/z;
    return atan(inv_z);
}
template<typename T>
complex<T> acot2(const complex<T> lhs, const complex<T> rhs){
    return acot(lhs/rhs);
}

template<typename T>
complex<T> sinh(const complex<T> lhs){
    const auto e_c = exp(lhs);
    const auto e_c_inv = complex<T>(T(1),T(0))/e_c;
    return (e_c - e_c_inv) / complex<T>(T(2), T(0));
}
template<typename T>
complex<T> cosh(const complex<T> lhs){
    const auto e_c = exp(lhs);
    const auto e_c_inv = complex<T>(T(1),T(0))/e_c;
    return (e_c + e_c_inv) / complex<T>(T(2), T(0));
}
template<typename T>
complex<T> tanh(const complex<T> lhs){
    const auto e_c = exp(lhs);
    const auto e_c_inv = complex<T>(T(1),T(0))/e_c;
    return (e_c - e_c_inv) / (e_c + e_c_inv);
}
template<typename T>
complex<T> sech(const complex<T> lhs){
    const auto e_c = exp(lhs);
    const auto e_c_inv = complex<T>(T(1),T(0))/e_c;
    return complex<T>(T(2), T(0)) / (e_c + e_c_inv);
}
template<typename T>
complex<T> cosech(const complex<T> lhs){
    const auto e_c = exp(lhs);
    const auto e_c_inv = complex<T>(T(1),T(0))/e_c;
    return complex<T>(T(2), T(0)) / (e_c - e_c_inv);
}
template<typename T>
complex<T> coth(const complex<T> lhs){
    const auto e_c = exp(lhs);
    const auto e_c_inv = complex<T>(T(1),T(0))/e_c;
    return (e_c + e_c_inv) / (e_c - e_c_inv);
}

template<typename T>
complex<T> asinh(const complex<T> z){
    const auto sq = sqrt(z*z + complex<T>(T(1),T(0)));   // sqrt(z^2+1)
    return log(z + sq);
}
template<typename T>
complex<T> acosh(const complex<T> z){
    const auto sq = sqrt(z*z - complex<T>(T(1),T(0)));   // sqrt(z^2-1)
    return log(z + sq);
}
template<typename T>
complex<T> atanh(const complex<T> z){
    const auto num = complex<T>(T(1),T(0)) + z;           // 1+z
    const auto den = complex<T>(T(1),T(0)) - z;           // 1-z
    return log(num/den) / complex<T>(T(2),T(0));
}
template<typename T>
complex<T> asech(const complex<T> z){
    const auto inv_z = complex<T>(T(1),T(0))/z;
    return acosh(inv_z);
}
template<typename T>
complex<T> acosech(const complex<T> z){
    const auto inv_z = complex<T>(T(1),T(0))/z;
    return asinh(inv_z);
}
template<typename T>
complex<T> acoth(const complex<T> z){
    const auto inv_z = complex<T>(T(1),T(0))/z;
    return atanh(inv_z);
}

//Rounding/classification
template<typename T>
T abs(const complex<T> lhs){
    return sqrt(lhs.r*lhs.r + lhs.i*lhs.i);
}

//Other
template<typename T>
complex<T> mod(const complex<T> lhs, const complex<T> rhs){
    return lhs % rhs;
}
template<typename T>
complex<T> hypot(const complex<T> lhs, const complex<T> rhs){
    return sqrt(lhs*lhs + rhs*rhs);
}
}