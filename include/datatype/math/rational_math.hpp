#pragma once
#include "../number.hpp"
#include "primitive_math.hpp"
#include "../ops/ops.hpp"
namespace Phytra{
//Power/root functions
template<typename T>
rational<T> pow(const rational<T> lhs, const rational<T> rhs){
    return rational<T>(pow(static_cast<double>(lhs), static_cast<double>(rhs)));
}
template<typename T>
rational<T> sqrt(const rational<T> lhs){
    return rational<T>(sqrt(static_cast<double>(lhs)));
}
template<typename T>
rational<T> cbrt(const rational<T> lhs){
    return rational<T>(cbrt(static_cast<double>(lhs)));
}

template<typename T>
rational<T> exp(const rational<T> lhs){
    return rational<T>(exp(static_cast<double>(lhs)));
}
template<typename T>
rational<T> exp2(const rational<T> lhs){
    return rational<T>(exp2(static_cast<double>(lhs)));
}
template<typename T>
rational<T> expm1(const rational<T> lhs){
    return rational<T>(expm1(static_cast<double>(lhs)));
}
template<typename T>
rational<T> expp1(const rational<T> lhs){
    return rational<T>(expp1(static_cast<double>(lhs)));
}

template<typename T>
rational<T> ln(const rational<T> lhs){
    return rational<T>(ln(static_cast<double>(lhs)));
}
template<typename T>
rational<T> log2(const rational<T> lhs){
    return rational<T>(log2(static_cast<double>(lhs)));
}
template<typename T>
rational<T> log10(const rational<T> lhs){
    return rational<T>(log10(static_cast<double>(lhs)));
}
template<typename T>
rational<T> log(const rational<T> lhs, const rational<T> rhs){
    return rational<T>(log(static_cast<double>(lhs) ,static_cast<double>(rhs)));
}

template<typename T>
rational<T> ln_1p(const rational<T> lhs){
    return rational<T>(ln_1p(static_cast<double>(lhs)));
}
template<typename T>
rational<T> log2_1p(const rational<T> lhs){
    return rational<T>(log2_1p(static_cast<double>(lhs)));
}
template<typename T>
rational<T> log10_1p(const rational<T> lhs){
    return rational<T>(log10_1p(static_cast<double>(lhs)));
}
template<typename T>
rational<T> log_1p(const rational<T> lhs, const rational<T> rhs){
    return rational<T>(log_1p(static_cast<double>(lhs), static_cast<double>(rhs)));
}

//Trigonometric functions
template<typename T>
rational<T> sin(const rational<T> lhs){
    return rational<T>(sin(static_cast<double>(lhs)));
}
template<typename T>
rational<T> cos(const rational<T> lhs){
    return rational<T>(cos(static_cast<double>(lhs)));
}
template<typename T>
rational<T> tan(const rational<T> lhs){
    return rational<T>(tan(static_cast<double>(lhs)));
}
template<typename T>
rational<T> sec(const rational<T> lhs){
    return rational<T>(sec(static_cast<double>(lhs)));
}
template<typename T>
rational<T> cosec(const rational<T> lhs){
    return rational<T>(cosec(static_cast<double>(lhs)));
}
template<typename T>
rational<T> cot(const rational<T> lhs){
    return rational<T>(cot(static_cast<double>(lhs)));
}

template<typename T>
rational<T> asin(const rational<T> lhs){
    return rational<T>(asin(static_cast<double>(lhs)));
}
template<typename T>
rational<T> acos(const rational<T> lhs){
    return rational<T>(acos(static_cast<double>(lhs)));
}
template<typename T>
rational<T> atan(const rational<T> lhs){
    return rational<T>(atan(static_cast<double>(lhs)));
}
template<typename T>
rational<T> atan2(const rational<T> lhs, const rational<T> rhs){
    return rational<T>(atan2(static_cast<double>(lhs), static_cast<double>(rhs)));
}
template<typename T>
rational<T> asec(const rational<T> lhs){
    return rational<T>(asec(static_cast<double>(lhs)));
}
template<typename T>
rational<T> acosec(const rational<T> lhs){
    return rational<T>(acosec(static_cast<double>(lhs)));
}
template<typename T>
rational<T> acot(const rational<T> lhs){
    return rational<T>(acot(static_cast<double>(lhs)));
}
template<typename T>
rational<T> acot2(const rational<T> lhs, const rational<T> rhs){
    return rational<T>(acot2(static_cast<double>(lhs), static_cast<double>(rhs)));
}

template<typename T>
rational<T> sinh(const rational<T> lhs){
    return rational<T>(sinh(static_cast<double>(lhs)));
}
template<typename T>
rational<T> cosh(const rational<T> lhs){
    return rational<T>(cosh(static_cast<double>(lhs)));
}
template<typename T>
rational<T> tanh(const rational<T> lhs){
    return rational<T>(tanh(static_cast<double>(lhs)));
}
template<typename T>
rational<T> sech(const rational<T> lhs){
    return rational<T>(sech(static_cast<double>(lhs)));
}
template<typename T>
rational<T> cosech(const rational<T> lhs){
    return rational<T>(cosech(static_cast<double>(lhs)));
}
template<typename T>
rational<T> coth(const rational<T> lhs){
    return rational<T>(coth(static_cast<double>(lhs)));
}

template<typename T>
rational<T> asinh(const rational<T> lhs){
    return rational<T>(asinh(static_cast<double>(lhs)));
}
template<typename T>
rational<T> acosh(const rational<T> lhs){
    return rational<T>(acosh(static_cast<double>(lhs)));
}
template<typename T>
rational<T> atanh(const rational<T> lhs){
    return rational<T>(atanh(static_cast<double>(lhs)));  
}
template<typename T>
rational<T> asech(const rational<T> lhs){
    return rational<T>(asech(static_cast<double>(lhs)));
}
template<typename T>
rational<T> acosech(const rational<T> lhs){
    return rational<T>(acosech(static_cast<double>(lhs)));
}
template<typename T>
rational<T> acoth(const rational<T> lhs){
    return rational<T>(acoth(static_cast<double>(lhs)));
}

//Rounding/classification functions
template<typename T>
rational<T> floor(const rational<T> lhs){
    T n = lhs.numerator();
    T d = lhs.denominator(); //always > 0 by invariant
    T q = n / d;
    T r = n % d;
    if (r != 0  && n < 0) {
        --q;
    }
    return rational<T>(q);
}
template<typename T>
rational<T> ceil(const rational<T> lhs){
    T n = lhs.numerator();
    T d = lhs.denominator();   // always > 0 by invariant
    T q = n / d;
    T r = n % d;
    if (r != 0 &&  n > 0) {
        ++q;  // round up only when positive and inexact
    }
    return rational<T>(q);
}
template<typename T>
rational<T> round(const rational<T> lhs){
    T n = lhs.numerator();
    T d = lhs.denominator();
    T q = n / d;
    T r = n % d;
    if (r == 0) return rational<T>(q);

    T ar = (r < 0) ? -r : r; // |r| is always < d, so this never overflows
    if (ar >= d - ar) {// equivalent to 2*|r| >= d, without risking overflow
        q += (n < 0) ? -1 : 1;// ties round away from zero, matching std::round
    }
    return rational<T>(q);
}
template<typename T>
rational<T> round_even(const rational<T> lhs){
    T n = lhs.numerator();
    T d = lhs.denominator();   // always > 0 by invariant
    T q = n / d;
    T r = n % d;
    if (r == 0) {
        return rational<T>(q);
    }

    T ar = (r < 0) ? -r : r;      // |r| < d always, so no overflow risk
    T other = q + ((n < 0) ? -1 : 1);

    if (ar > d - ar) {
        q = other;                 // not a tie, round to nearer as usual
    } 
    else if (ar == d - ar) {
        if (q % 2 != 0) {
            q = other; // exact tie: pick whichever candidate is even
        }
    }
    // else ar < d - ar: q is already nearer, leave as is

    return rational<T>(q);
}
template<typename T>
rational<T> trunc(const rational<T> lhs){
    // Integer division already truncates toward zero — this IS trunc.
    return rational<T>(lhs.numerator() / lhs.denominator());
}
template<typename T>
rational<T> abs(const rational<T> lhs){
    return rational<T>(abs(lhs.numerator()), lhs.denominator());
}
//TODO:Decide if we want to implement isnan and stuff like that
template<typename T>
bool signbit(const rational<T> lhs){
    return lhs.numerator() < 0;
}

//Other binary functions
template<typename T>
rational<T> min(const rational<T> lhs, const rational<T> rhs){
    return (lhs < rhs) ? lhs : rhs;
}
template<typename T>
rational<T> max(const rational<T> lhs, const rational<T> rhs){
    return (lhs > rhs) ? lhs : rhs;
}
template<typename T>
rational<T> mod(const rational<T> lhs, const rational<T> rhs){
    return lhs % rhs;
}
template<typename T>
rational<T> hypot(const rational<T> lhs, const rational<T> rhs){
    return rational<T>(hypot(static_cast<double>(lhs), static_cast<double>(rhs)));
}
template<typename T>
rational<T> copysign(const rational<T> lhs, const rational<T> rhs){
    if (signbit(rhs)) {
        return -abs(lhs);
    }
    return abs(lhs);
}
}