#pragma once
#include <cmath>
namespace Phytra{
template <typename T>
concept Arithmetic = std::integral<T> || std::floating_point<T>;
template <typename T>
concept FloatArithmetic = std::floating_point<T>;

//Power/root functions 
template<Arithmetic T>
__attribute__((always_inline, hot)) T pow(const T lhs, const T rhs){
    return std::pow(static_cast<double>(lhs), static_cast<double>(rhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T sqrt(const T lhs){
    return std::sqrt(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T cbrt(const T lhs){
    return std::cbrt(static_cast<double>(lhs));
}

template<Arithmetic T>
__attribute__((always_inline, hot)) T exp(const T lhs){
    return std::exp(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T exp2(const T lhs){
    return std::exp2(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T expm1(const T lhs){
    return std::expm1(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T expp1(const T lhs){
    return std::exp(static_cast<double>(lhs)) + 1.0;
}

template<Arithmetic T>
__attribute__((always_inline, hot)) T ln(const T lhs){
    return std::log(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T log2(const T lhs){
    return std::log2(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T log10(const T lhs){
    return std::log10(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T log(const T lhs, const T rhs){
    return std::log(static_cast<double>(lhs)) / std::log(static_cast<double>(rhs));
}

template<Arithmetic T>
__attribute__((always_inline, hot)) T ln_1p(const T lhs){
    return std::log1p(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T log2_1p(const T lhs){
    constexpr double ln2 = 0.6931471805599453;
    return std::log1p(static_cast<double>(lhs)) / ln2;
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T log10_1p(const T lhs){
    constexpr double ln10 = 2.302585092994046;
    return std::log1p(static_cast<double>(lhs)) / ln10;
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T log_1p(const T lhs, const T rhs){
    return std::log1p(static_cast<double>(lhs)) / std::log(static_cast<double>(rhs));
}

//Trigonometric functions
template<Arithmetic T>
__attribute__((always_inline, hot)) T sin(const T lhs){
    return std::sin(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T cos(const T lhs){
    return std::cos(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T tan(const T lhs){
    return std::tan(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T sec(const T lhs){
    return 1.0 / std::cos(static_cast<double>(lhs));    
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T cosec(const T lhs){
    return 1.0 / std::sin(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T cot(const T lhs){
    return 1.0 / std::tan(static_cast<double>(lhs));
}

template<Arithmetic T>
__attribute__((always_inline, hot)) T asin(const T lhs){
    return std::asin(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T acos(const T lhs){
    return std::acos(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T atan(const T lhs){
    return std::atan(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T atan2(const T lhs, const T rhs){
    return std::atan2(static_cast<double>(lhs), static_cast<double>(rhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T asec(const T lhs){
    return std::acos(1.0 / static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T acosec(const T lhs){
    return std::asin(1.0 / static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T acot(const T lhs){
    return std::atan(1.0 / static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T acot2(const T lhs, const T rhs){
    return std::atan2(static_cast<double>(rhs), static_cast<double>(lhs));
}

template<Arithmetic T>
__attribute__((always_inline, hot)) T sinh(const T lhs){
    return std::sinh(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T cosh(const T lhs){
    return std::cosh(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T tanh(const T lhs){
    return std::tanh(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T sech(const T lhs){
    return 1.0 / std::cosh(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T cosech(const T lhs){
    return 1.0 / std::sinh(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T coth(const T lhs){
    return 1.0 / std::tanh(static_cast<double>(lhs));
}

template<Arithmetic T>
__attribute__((always_inline, hot)) T asinh(const T lhs){
    return std::asinh(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T acosh(const T lhs){
    return std::acosh(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T atanh(const T lhs){
    return std::atanh(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T asech(const T lhs){
    return std::acosh(1.0 / static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T acosech(const T lhs){
    return std::asinh(1.0 / static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T acoth(const T lhs){
    return std::atanh(1.0 / static_cast<double>(lhs));
}

//Rounding/classification functions
template<FloatArithmetic T>
__attribute__((always_inline, hot)) T floor(const T lhs){
    return std::floor(static_cast<double>(lhs));
}
template<FloatArithmetic T>
__attribute__((always_inline, hot)) T ceil(const T lhs){
    return std::ceil(static_cast<double>(lhs));
}
template<FloatArithmetic T>
__attribute__((always_inline, hot)) T round(const T lhs){
    return std::round(static_cast<double>(lhs));
}
template<FloatArithmetic T>
__attribute__((always_inline, hot)) T round_even(const T lhs){
    T rounded = std::round(static_cast<double>(lhs));
    if (std::fabs(std::fabs(static_cast<double>(lhs) - static_cast<double>(rounded)) - 0.5) < 1e-10) {
        if (static_cast<long long>(rounded) % 2 != 0) {
            rounded += (lhs > 0) ? 1 : -1;
        }
    }
    return rounded;
}
template<FloatArithmetic T>
__attribute__((always_inline, hot)) T trunc(const T lhs){
    return std::trunc(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T abs(const T lhs){
    if constexpr (std::is_floating_point_v<T>){
        return std::fabs(static_cast<double>(lhs));
    }
    else if constexpr (std::is_unsigned_v<T>){
        return lhs;
    }
    else{
        return std::abs(lhs);
    }
}
template<FloatArithmetic T>
__attribute__((always_inline, hot)) bool isnan(const T lhs){
    return std::isnan(static_cast<double>(lhs));
}
template<FloatArithmetic T>
__attribute__((always_inline, hot)) bool isinf(const T lhs){
    return std::isinf(static_cast<double>(lhs));
}
template<FloatArithmetic T>
__attribute__((always_inline, hot)) bool isfinite(const T lhs){
    return std::isfinite(static_cast<double>(lhs));
}
template<FloatArithmetic T>
__attribute__((always_inline, hot)) bool isnormal(const T lhs){ 
    return std::isnormal(static_cast<double>(lhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) bool signbit(const T lhs){
    if constexpr (std::is_floating_point_v<T>){
        return std::signbit(static_cast<double>(lhs));
    }
    else{
        return lhs < 0;
    }
}

//Other binary functions for optional types
template<Arithmetic T>
__attribute__((always_inline, hot)) T min(const T lhs, const T rhs){
    return std::min(lhs, rhs);
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T max(const T lhs, const T rhs){
    return std::max(lhs, rhs);
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T mod(const T lhs, const T rhs){
    if constexpr (std::is_floating_point_v<T>){
        return std::fmod(static_cast<double>(lhs), static_cast<double>(rhs));
    }
    else{
        return lhs % rhs;
    }
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T hypot(const T lhs, const T rhs){
    return std::hypot(static_cast<double>(lhs), static_cast<double>(rhs));
}
template<Arithmetic T>
__attribute__((always_inline, hot)) T copysign(const T lhs, const T rhs){
    if constexpr (std::is_floating_point_v<T>){
        return std::copysign(static_cast<double>(lhs), static_cast<double>(rhs));
    }
    else{
        return (rhs < 0) ? -std::abs(lhs) : std::abs(lhs);
    }
}
}