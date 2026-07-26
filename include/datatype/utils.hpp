#pragma once
#include <utility>

namespace Phytra{
template<typename T0, typename T1>
struct pair {
    T0 first;
    T1 second;
    pair() = default;
    pair(const T0& f, const T1& s) : first(f), second(s) {}
    pair(T0&& f, const T1& s) : first(std::move(f)), second(s) {}
    pair(const T0& f, T1&& s) : first(f), second(std::move(s)) {}
    pair(T0&& f, T1&& s) : first(std::move(f)), second(std::move(s)) {}
};
}