#pragma once
#include <utility>
#include <type_traits>

namespace Phytra{
struct nullopt_t {
    explicit constexpr nullopt_t(int) {}
};
inline constexpr nullopt_t nullopt{0};

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

template<typename T> requires (!std::is_same_v<T, nullopt_t>)
class optional {
    template<typename U> friend const U& get_value(const optional<U>& t);
    T value_{};
    bool has_value_ = false;
public:
    optional() = default;
    optional(nullopt_t) {}
    optional(const T& v) : value_(v), has_value_(true) {}
    optional(T&& v) : value_(std::move(v)), has_value_(true) {}

    optional<T>& operator=(nullopt_t) {
        has_value_ = false;
        return *this;
    }
    optional<T>& operator=(const T& v) {
        value_ = v;
        has_value_ = true;
        return *this;
    }
    optional<T>& operator=(T&& v) {
        value_ = std::move(v);
        has_value_ = true;
        return *this;
    }

    __attribute__((always_inline, hot)) bool has_value() const { return has_value_; }
    inline pair<bool , T> get_value() const & {
        return {has_value_, value_};
    }
    inline pair<bool , T> get_value() && {
        return {has_value_, std::move(value_)};
    }
    __attribute__((always_inline, hot)) T get_value_only() const & {
        return value_;
    }
    __attribute__((always_inline, hot)) T get_value_only() && {
        return std::move(value_);
    }
    inline T get_value_or(const T& default_value) const & {
        return has_value_ ? value_ : default_value;
    }
    inline T get_value_or(const T& default_value) && {
        return has_value_ ? std::move(value_) : default_value;
    }
    inline T get_value_or(T&& default_value) const & {
        return has_value_ ? value_ : std::move(default_value);
    }
    inline T get_value_or(T&& default_value) && {
        return has_value_ ? std::move(value_) : std::move(default_value);
    }
    inline void reset() {
        has_value_ = false;
    }
};
template<typename T>
struct is_optional : std::false_type {};
template<typename U>
struct is_optional<optional<U>> : std::true_type {};
template<typename T>
concept IsOptional = is_optional<T>::value;
template<typename T>
concept IsNotOptional = !is_optional<T>::value;

template<IsOptional T>
__attribute__((always_inline, hot)) bool has_value(const T& t) {
    return t.has_value();
}
template<IsNotOptional T>
__attribute__((always_inline, hot)) bool has_value(const T& t) {
    return true;
}
template<typename U>
__attribute__((always_inline, hot)) const auto& get_value(const optional<U>& t) {
    return t.value_;
}
template<IsNotOptional T>
__attribute__((always_inline, hot)) const T& get_value(const T& t) {
    return t;
}
}