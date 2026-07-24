#include "../optional.hpp"

namespace Phytra{
//Element wise mathematical functions for optional types
//For a lot of function we use diffrent name than the norm. Like log means it needs a base and stuff like that. We will provide std:: cmath wrapper for all the functions for integer/double
//MAinly because of naming and convention diffrence. Keep it in mind as a future TODO:
//Power/root functions for optional types
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto pow(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(pow(get_value(lhs), get_value(rhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto sqrt(const T& lhs) {
    return (has_value(lhs)) ? optional(sqrt(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto cbrt(const T& lhs) {
    return (has_value(lhs)) ? optional(cbrt(get_value(lhs))) : nullopt;
}

template<typename T> requires (IsOptional<T>)
inline auto exp(const T& lhs) {
    return (has_value(lhs)) ? optional(exp(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto exp2(const T& lhs) {
    return (has_value(lhs)) ? optional(exp2(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto expm1(const T& lhs) {
    return (has_value(lhs)) ? optional(expm1(get_value(lhs))) : nullopt;
}

template<typename T> requires (IsOptional<T>)
inline auto ln(const T& lhs) {
    return (has_value(lhs)) ? optional(ln(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto log2(const T& lhs) {
    return (has_value(lhs)) ? optional(log2(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto log10(const T& lhs) {
    return (has_value(lhs)) ? optional(log10(get_value(lhs))) : nullopt;
}
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto log(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(log(get_value(lhs), get_value(rhs))) : nullopt;
}

template<typename T> requires (IsOptional<T>)
inline auto ln_1p(const T& lhs) {
    return (has_value(lhs)) ? optional(ln_1p(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto log2_1p(const T& lhs) {
    return (has_value(lhs)) ? optional(log2_1p(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto log10_1p(const T& lhs) {
    return (has_value(lhs)) ? optional(log10_1p(get_value(lhs))) : nullopt;
}
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto log_1p(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(log_1p(get_value(lhs), get_value(rhs))) : nullopt;
}

//Trigonometric functions for optional types
template<typename T> requires (IsOptional<T>)
inline auto sin(const T& lhs) {
    return (has_value(lhs)) ? optional(sin(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto cos(const T& lhs) {
    return (has_value(lhs)) ? optional(cos(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto tan(const T& lhs) {
    return (has_value(lhs)) ? optional(tan(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto sec(const T& lhs) {
    return (has_value(lhs)) ? optional(sec(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto cosec(const T& lhs) {
    return (has_value(lhs)) ? optional(cosec(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto cot(const T& lhs) {
    return (has_value(lhs)) ? optional(cot(get_value(lhs))) : nullopt;
}

template<typename T> requires (IsOptional<T>)
inline auto asin(const T& lhs) {
    return (has_value(lhs)) ? optional(asin(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto acos(const T& lhs) {
    return (has_value(lhs)) ? optional(acos(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto atan(const T& lhs) {
    return (has_value(lhs)) ? optional(atan(get_value(lhs))) : nullopt;
}
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto atan2(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(atan2(get_value(lhs), get_value(rhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto asec(const T& lhs) {
    return (has_value(lhs)) ? optional(asec(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto acosec(const T& lhs) {
    return (has_value(lhs)) ? optional(acosec(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto acot(const T& lhs) {
    return (has_value(lhs)) ? optional(acot(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto acot2(const T& lhs, const T& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(acot2(get_value(lhs), get_value(rhs))) : nullopt;
}

template<typename T> requires (IsOptional<T>)
inline auto sinh(const T& lhs) {
    return (has_value(lhs)) ? optional(sinh(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto cosh(const T& lhs) {
    return (has_value(lhs)) ? optional(cosh(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto tanh(const T& lhs) {
    return (has_value(lhs)) ? optional(tanh(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto sech(const T& lhs) {
    return (has_value(lhs)) ? optional(sech(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto cosech(const T& lhs) {
    return (has_value(lhs)) ? optional(cosech(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto coth(const T& lhs) {
    return (has_value(lhs)) ? optional(coth(get_value(lhs))) : nullopt;
}

template<typename T> requires (IsOptional<T>)
inline auto asinh(const T& lhs) {
    return (has_value(lhs)) ? optional(asinh(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto acosh(const T& lhs) {
    return (has_value(lhs)) ? optional(acosh(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto atanh(const T& lhs) {
    return (has_value(lhs)) ? optional(atanh(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto asech(const T& lhs) {
    return (has_value(lhs)) ? optional(asech(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto acosech(const T& lhs) {
    return (has_value(lhs)) ? optional(acosech(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto acoth(const T& lhs) {
    return (has_value(lhs)) ? optional(acoth(get_value(lhs))) : nullopt;
}

//Rounding/classification functions for optional types
template<typename T> requires (IsOptional<T>)
inline auto floor(const T& lhs) {
    return (has_value(lhs)) ? optional(floor(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto ceil(const T& lhs) {
    return (has_value(lhs)) ? optional(ceil(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto round(const T& lhs) {
    return (has_value(lhs)) ? optional(round(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto trunc(const T& lhs) {
    return (has_value(lhs)) ? optional(trunc(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto abs(const T& lhs) {
    return (has_value(lhs)) ? optional(abs(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto fabs(const T& lhs) {
    return (has_value(lhs)) ? optional(fabs(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto isnan(const T& lhs) {
    return (has_value(lhs)) ? optional(isnan(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto isinf(const T& lhs) {
    return (has_value(lhs)) ? optional(isinf(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto isfinite(const T& lhs) {
    return (has_value(lhs)) ? optional(isfinite(get_value(lhs))) : nullopt;
}
template<typename T> requires (IsOptional<T>)
inline auto signbit(const T& lhs) {
    return (has_value(lhs)) ? optional(signbit(get_value(lhs))) : nullopt;
}

//Other binary functions for optional types
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto min(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(min(get_value(lhs), get_value(rhs))) : nullopt;
}
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto max(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(max(get_value(lhs), get_value(rhs))) : nullopt;
}
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto fmod(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(fmod(get_value(lhs), get_value(rhs))) : nullopt;
}
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto hypot(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(hypot(get_value(lhs), get_value(rhs))) : nullopt;
}
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto copysign(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(copysign(get_value(lhs), get_value(rhs))) : nullopt;
}
//TODO:Reduction ops and other stuff for string and tensor types
}