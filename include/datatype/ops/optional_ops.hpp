#pragma once
#include "../optional.hpp"

namespace Phytra{
//If u just use nullopt, then the following wont work without wraping in a optional. So u must wrap it in an optional. This is to avoid ambiguity with type of nullopt. It is a bit inconvinient but it also helps remove additional code. + Meant for internal use only and cases like these are rare(Most of the time it will be std::vector<optional<T>> and not a single optional)
//Unary logical operators for optional types
template<IsOptional T>
inline auto operator!(const T& lhs){
    return (has_value(lhs)) ? optional(!get_value(lhs)) : nullopt;
}

// Comparison operators for optional types
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto operator==(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(get_value(lhs) == get_value(rhs)) : nullopt;
}
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto operator!=(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(get_value(lhs) != get_value(rhs)) : nullopt;
}
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto operator<(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(get_value(lhs) < get_value(rhs)) : nullopt;
}
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto operator>(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(get_value(lhs) > get_value(rhs)) : nullopt;
}
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto operator<=(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(get_value(lhs) <= get_value(rhs)) : nullopt;
}
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto operator>=(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(get_value(lhs) >= get_value(rhs)) : nullopt;
}
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto operator&&(const T0& lhs, const T1& rhs) {
    //Breaks short circuiting. Be careful
    return (has_value(lhs) && has_value(rhs)) ? optional(get_value(lhs) && get_value(rhs)) : nullopt;
}
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto operator||(const T0& lhs, const T1& rhs) {
    //Breaks short circuiting. Be careful
    return (has_value(lhs) && has_value(rhs)) ? optional(get_value(lhs) || get_value(rhs)) : nullopt;
}

//Unary arithmetic operators for optional types
template<IsOptional T>
inline auto operator+(const T& lhs) {
    return (has_value(lhs)) ? optional(+get_value(lhs)) : nullopt;
}
template<IsOptional T>
inline auto operator-(const T& lhs) {
    return (has_value(lhs)) ? optional(-get_value(lhs)) : nullopt;
}
template<IsOptional T>
inline auto operator*(const T& lhs) {
    return (has_value(lhs)) ? optional(*get_value(lhs)) : nullopt;
}

//Binary arithmetic operators for optional types
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto operator+(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(get_value(lhs) + get_value(rhs)) : nullopt;
}
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto operator-(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(get_value(lhs) - get_value(rhs)) : nullopt;
}
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto operator*(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(get_value(lhs) * get_value(rhs)) : nullopt;
}
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto operator/(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(get_value(lhs) / get_value(rhs)) : nullopt;
}
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto operator%(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(get_value(lhs) % get_value(rhs)) : nullopt;
}

//Unary bitwise operators for optional types
template<IsOptional T>
inline auto operator~(const T& lhs) {
    return (has_value(lhs)) ? optional(~get_value(lhs)) : nullopt;
}

//Binary bitwise operators for optional types
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto operator&(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(get_value(lhs) & get_value(rhs)) : nullopt;
}
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto operator|(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(get_value(lhs) | get_value(rhs)) : nullopt;
}
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto operator^(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(get_value(lhs) ^ get_value(rhs)) : nullopt;
}
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto operator<<(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(get_value(lhs) << get_value(rhs)) : nullopt;
}
template<typename T0, typename T1> requires (IsOptional<T0> || IsOptional<T1>)
inline auto operator>>(const T0& lhs, const T1& rhs) {
    return (has_value(lhs) && has_value(rhs)) ? optional(get_value(lhs) >> get_value(rhs)) : nullopt;
}
}