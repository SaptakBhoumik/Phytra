#pragma once
#include "../number.hpp"
#include "../ops/ops.hpp"
#include "primitive_math.hpp"
#include "rational_math.hpp"
#include "complex_math.hpp"

namespace Phytra{
//Power/root functions
template<typename T>
quaternion<T> pow(const quaternion<T> lhs, const quaternion<T> rhs){
    const auto lh_lhs = ln(lhs);
    const auto lh_lhs_times_rhs = lh_lhs * rhs;
    return exp(lh_lhs_times_rhs);
}
template<typename T>
quaternion<T> sqrt(const quaternion<T> lhs){
    const auto lh_lhs = ln(lhs);
    const auto lh_lhs_div_2 = quaternion<T>(lh_lhs.r / T(2), lh_lhs.i / T(2), lh_lhs.j / T(2), lh_lhs.k / T(2));
    return exp(lh_lhs_div_2);
}
template<typename T>
quaternion<T> cbrt(const quaternion<T> lhs){
    const auto lh_lhs = ln(lhs);
    const auto lh_lhs_div_3 = quaternion<T>(lh_lhs.r / T(3), lh_lhs.i / T(3), lh_lhs.j / T(3), lh_lhs.k / T(3));
    return exp(lh_lhs_div_3);
}

template<typename T>
quaternion<T> exp(const quaternion<T> lhs){
    const auto exp_r = exp(lhs.r);
    const auto abs_v = sqrt(lhs.i*lhs.i + lhs.j*lhs.j + lhs.k*lhs.k);
    if(double(abs_v) < 1e-10){
        return quaternion<T>(exp_r, T(0), T(0), T(0));
    }
    const auto exp_r_cos_abs_v = exp_r*cos(abs_v);
    const auto exp_r_sin_abs_v = exp_r*sin(abs_v);
    return quaternion<T>(exp_r_cos_abs_v, exp_r_sin_abs_v*lhs.i / abs_v, exp_r_sin_abs_v*lhs.j / abs_v, exp_r_sin_abs_v*lhs.k / abs_v);
}
template<typename T>
quaternion<T> exp2(const quaternion<T> lhs){
    const auto ln_2 = T(0.6931471805599453);
    return exp(quaternion<T>(lhs.r * ln_2, lhs.i * ln_2, lhs.j * ln_2, lhs.k * ln_2));
}
template<typename T>
quaternion<T> expm1(const quaternion<T> lhs){
    return exp(lhs) - quaternion<T>(T(1), T(0), T(0), T(0));
}
template<typename T>
quaternion<T> expp1(const quaternion<T> lhs){
    return exp(lhs) + quaternion<T>(T(1), T(0), T(0), T(0));
}

template<typename T>
quaternion<T> ln(const quaternion<T> lhs){
    const auto abs_lhs = sqrt(lhs.r*lhs.r + lhs.i*lhs.i + lhs.j*lhs.j + lhs.k*lhs.k);
    const auto abs_v = sqrt(lhs.i*lhs.i + lhs.j*lhs.j + lhs.k*lhs.k);
    if(double(abs_v) < 1e-10){
        return quaternion<T>(ln(abs_lhs), T(0), T(0), T(0));
    }
    const auto angle = atan2(abs_v , lhs.r);
    return quaternion<T>(ln(abs_lhs), angle * lhs.i / abs_v, angle * lhs.j / abs_v, angle * lhs.k / abs_v);
}
template<typename T>
quaternion<T> log2(const quaternion<T> lhs){
    const auto ln_2 = T(0.6931471805599453);
    const auto ln_lhs = ln(lhs);
    return quaternion<T>(ln_lhs.r / ln_2, ln_lhs.i / ln_2, ln_lhs.j / ln_2, ln_lhs.k / ln_2);
}
template<typename T>
quaternion<T> log10(const quaternion<T> lhs){
    const auto ln_10 = T(2.302585092994046);
    const auto ln_lhs = ln(lhs);
    return quaternion<T>(ln_lhs.r / ln_10, ln_lhs.i / ln_10, ln_lhs.j / ln_10, ln_lhs.k / ln_10);
}
template<typename T>
quaternion<T> log(const quaternion<T> lhs, const quaternion<T> rhs){
    return ln(lhs) / ln(rhs);
}

template<typename T>
quaternion<T> ln_1p(const quaternion<T> lhs){
    return ln(quaternion<T>(T(1) + lhs.r, lhs.i, lhs.j, lhs.k));
}
template<typename T>
quaternion<T> log2_1p(const quaternion<T> lhs){
    return log2(quaternion<T>(T(1) + lhs.r, lhs.i, lhs.j, lhs.k));
}
template<typename T>
quaternion<T> log10_1p(const quaternion<T> lhs){
    return log10(quaternion<T>(T(1) + lhs.r, lhs.i, lhs.j, lhs.k));
}
template<typename T>
quaternion<T> log_1p(const quaternion<T> lhs, const quaternion<T> rhs){
    return log(quaternion<T>(T(1) + lhs.r, lhs.i, lhs.j, lhs.k), rhs);
}


//Trigonometric functions
template<typename T>
quaternion<T> sin(const quaternion<T> lhs){
    const auto abs_v = sqrt(lhs.i*lhs.i + lhs.j*lhs.j + lhs.k*lhs.k);
    const auto sin_a  = sin(lhs.r);
    const auto cos_a  = cos(lhs.r);
    const auto cosh_v = cosh(abs_v);

    if(double(abs_v) < 1e-10){
        return quaternion<T>(sin_a , T(0), T(0), T(0)); 
    } 
    const T coeff = sinh(abs_v) / abs_v;

    const auto real  = sin_a * cosh_v;
    const auto scale = cos_a * coeff;

    return quaternion<T>(real, scale*lhs.i, scale*lhs.j, scale*lhs.k);
}
template<typename T>
quaternion<T> cos(const quaternion<T> lhs){
    const auto abs_v = sqrt(lhs.i*lhs.i + lhs.j*lhs.j + lhs.k*lhs.k);
    const auto sin_a  = sin(lhs.r);
    const auto cos_a  = cos(lhs.r);
    const auto cosh_v = cosh(abs_v);

    if(double(abs_v) < 1e-10){
        return quaternion<T>(cos_a , T(0), T(0), T(0)); 
    } 
    const T coeff = sinh(abs_v) / abs_v;

    const auto real  = cos_a * cosh_v;
    const auto scale = -sin_a * coeff;

    return quaternion<T>(real, scale*lhs.i, scale*lhs.j, scale*lhs.k);
}
template<typename T>
quaternion<T> tan(const quaternion<T> lhs){
    return sin(lhs) / cos(lhs);
}
template<typename T>
quaternion<T> sec(const quaternion<T> lhs){
    return quaternion<T>(T(1)) / cos(lhs);
}
template<typename T>
quaternion<T> cosec(const quaternion<T> lhs){
    return quaternion<T>(T(1)) / sin(lhs);
}
template<typename T>
quaternion<T> cot(const quaternion<T> lhs){
    return cos(lhs) / sin(lhs);
}
template<typename T>
quaternion<T> asin(const quaternion<T> lhs){
    const auto abs_v = sqrt(lhs.i*lhs.i + lhs.j*lhs.j + lhs.k*lhs.k);
    if(double(abs_v) < 1e-10){
        return quaternion<T>(T(std::asin(double(lhs.r))), T(0), T(0), T(0));
    }
    complex<T> c(double(lhs.r), double(abs_v));
    complex<T> r = asin(c);
    const auto coeff = r.i / abs_v;
    return quaternion<T>(r.r, coeff*lhs.i, coeff*lhs.j, coeff*lhs.k);
}
template<typename T>
quaternion<T> acos(const quaternion<T> lhs){
    const auto abs_v = sqrt(lhs.i*lhs.i + lhs.j*lhs.j + lhs.k*lhs.k);
    if(double(abs_v) < 1e-10){
        return quaternion<T>(T(std::acos(double(lhs.r))), T(0), T(0), T(0));
    }
    complex<T> c(double(lhs.r), double(abs_v));
    complex<T> r = acos(c);
    const auto coeff = r.i / abs_v;
    return quaternion<T>(r.r, coeff*lhs.i, coeff*lhs.j, coeff*lhs.k);
}
template<typename T>
quaternion<T> atan(const quaternion<T> lhs){
    const auto abs_v = sqrt(lhs.i*lhs.i + lhs.j*lhs.j + lhs.k*lhs.k);
    if(double(abs_v) < 1e-10){
        return quaternion<T>(T(std::atan(double(lhs.r))), T(0), T(0), T(0));
    }
    complex<T> c(double(lhs.r), double(abs_v));
    complex<T> r = atan(c);
    const auto coeff = r.i / abs_v;
    return quaternion<T>(r.r, coeff*lhs.i, coeff*lhs.j, coeff*lhs.k);
}
template<typename T>
quaternion<T> atan2(const quaternion<T> lhs, const quaternion<T> rhs){
    return atan(lhs / rhs);
}
template<typename T>
quaternion<T> asec(const quaternion<T> lhs){
    return acos(quaternion<T>(T(1)) / lhs);
}
template<typename T>
quaternion<T> acosec(const quaternion<T> lhs){
    return asin(quaternion<T>(T(1)) / lhs); 
}
template<typename T>
quaternion<T> acot(const quaternion<T> lhs){
    return atan(quaternion<T>(T(1)) / lhs);
}
template<typename T>
quaternion<T> acot2(const quaternion<T> lhs, const quaternion<T> rhs){
    return atan2(rhs, lhs);
}

template<typename T>
quaternion<T> sinh(const quaternion<T> lhs){    
    const auto exp_r = exp(lhs);
    const auto exp_r_inv = quaternion<T>(T(1), T(0), T(0), T(0)) / exp_r;
    const auto num = (exp_r - exp_r_inv);
    return quaternion<T>(num.r/T(2), num.i/T(2), num.j/T(2), num.k/T(2));
}
template<typename T>
quaternion<T> cosh(const quaternion<T> lhs){
    const auto exp_r = exp(lhs);
    const auto exp_r_inv = quaternion<T>(T(1), T(0), T(0), T(0)) / exp_r;
    const auto num = (exp_r + exp_r_inv);
    return quaternion<T>(num.r/T(2), num.i/T(2), num.j/T(2), num.k/T(2));
}
template<typename T>
quaternion<T> tanh(const quaternion<T> lhs){
    const auto exp_r = exp(lhs);
    const auto exp_r_inv = quaternion<T>(T(1), T(0), T(0), T(0)) / exp_r;
    const auto num = (exp_r - exp_r_inv);
    const auto den = (exp_r + exp_r_inv);
    return num / den;
}
template<typename T>
quaternion<T> sech(const quaternion<T> lhs){
    const auto exp_r = exp(lhs);
    const auto exp_r_inv = quaternion<T>(T(1), T(0), T(0), T(0)) / exp_r;
    const auto den = (exp_r + exp_r_inv);
    return quaternion<T>(T(2), T(0), T(0), T(0)) / den;
}
template<typename T>
quaternion<T> cosech(const quaternion<T> lhs){
    const auto exp_r = exp(lhs);
    const auto exp_r_inv = quaternion<T>(T(1), T(0), T(0), T(0)) / exp_r;
    const auto den = (exp_r - exp_r_inv);
    return quaternion<T>(T(2), T(0), T(0), T(0)) / den;
}
template<typename T>
quaternion<T> coth(const quaternion<T> lhs){
    const auto exp_r = exp(lhs);
    const auto exp_r_inv = quaternion<T>(T(1), T(0), T(0), T(0)) / exp_r;
    const auto num = (exp_r + exp_r_inv);
    const auto den = (exp_r - exp_r_inv);
    return num / den;
}

template<typename T>
quaternion<T> asinh(const quaternion<T> lhs){
    const auto one = quaternion<T>(T(1), T(0), T(0), T(0));
    return ln(lhs + sqrt(lhs*lhs + one));
}
template<typename T>
quaternion<T> acosh(const quaternion<T> lhs){
    const auto one = quaternion<T>(T(1), T(0), T(0), T(0));
    return ln(lhs + sqrt(lhs - one) * sqrt(lhs + one));
}
template<typename T>
quaternion<T> atanh(const quaternion<T> lhs){
    const auto one  = quaternion<T>(T(1),   T(0), T(0), T(0));
    const auto half = quaternion<T>(T(0.5), T(0), T(0), T(0));
    return half * ln((one + lhs) / (one - lhs));
}
template<typename T>
quaternion<T> asech(const quaternion<T> lhs){
    return acosh(quaternion<T>(T(1), T(0), T(0), T(0)) / lhs);
}
template<typename T>
quaternion<T> acosech(const quaternion<T> lhs){
    return asinh(quaternion<T>(T(1), T(0), T(0), T(0)) / lhs);
}
template<typename T>
quaternion<T> acoth(const quaternion<T> lhs){
    return atanh(quaternion<T>(T(1), T(0), T(0), T(0)) / lhs);
}


//Rounding/classification
template<typename T>
T abs(const quaternion<T> lhs){
    return sqrt(lhs.r*lhs.r + lhs.i*lhs.i + lhs.j*lhs.j + lhs.k*lhs.k);
}

//Other binary functions
template<typename T>
quaternion<T> mod(const quaternion<T> lhs, const quaternion<T> rhs){
    return lhs % rhs;
}
template<typename T>
quaternion<T> hypot(const quaternion<T> lhs, const quaternion<T> rhs){
    return sqrt(lhs*lhs + rhs*rhs);
}
}