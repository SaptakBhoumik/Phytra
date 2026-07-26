#pragma once
#include <cmath>
#include <type_traits>
#include <numeric>
#include "utils.hpp"
namespace Phytra{
template<typename T> requires (std::is_integral_v<T>)
class rational{
    //For complex and other types, the variables are public for easy read and modify. But here they have to be private because we need to maintain the 
    //invariant that the fraction is always in reduced form and denominator is always positive. 
    //So we have to use a constructor and assignment operator to enforce this invariant.
    T num = 0;
    T den = 1;
    static bool mul_overflows(T a, T b) {
        T r;
        return __builtin_mul_overflow(a, b, &r);
    }

    template<typename F> requires (std::is_floating_point_v<F>)
    static rational<T> from_float(F value, T max_den = std::numeric_limits<T>::max()) {
        //TODO:Handle inf and nan because not sure how to handle it right now. We dont want to throw error. Will depend on the spec
        bool negative = value < 0;
        F x = negative ? -value : value;

        T h_prev = 0, h_cur = 1; // numerator convergents
        T k_prev = 1, k_cur = 0; // denominator convergents

        F b = x;
        for (int i = 0; i < 64; i++) {
            F a_f = std::floor(b);
            if (a_f > static_cast<F>(std::numeric_limits<T>::max())) {
                break;
            }
            T a = static_cast<T>(a_f);

            if (mul_overflows(a, h_cur)) {
                break;
            }
            T h_next = a * h_cur;
            if (h_next > std::numeric_limits<T>::max() - h_prev) {
                break;
            }
            h_next += h_prev;

            if (mul_overflows(a, k_cur)) {
                break;
            }
            T k_next = a * k_cur;
            if (k_next > std::numeric_limits<T>::max() - k_prev) {
                break;
            }
            k_next += k_prev;

            if (k_next == 0 || k_next > max_den) {
                break;
            }

            h_prev = h_cur; h_cur = h_next;
            k_prev = k_cur; k_cur = k_next;

            F remainder = b - a_f;
            if (remainder < std::numeric_limits<F>::epsilon() * b){
                break;
            }
            b = 1 / remainder;
        }

        if (k_cur == 0) { 
            h_cur = 0; k_cur = 1; // degenerate/zero input
        } 

        return rational<T>(static_cast<T>(negative ? -h_cur : h_cur), k_cur);
    }
public:
    using value_type = T;
    rational() = default;
    template<typename U> requires (std::is_integral_v<U>)
    rational(U num, U den = 1){
        if (den < 0) { num = -num; den = -den; }
        auto g = std::gcd(num, den);
        if (g == 0) g = 1;           // guards the (0,0) case below
        this->num = static_cast<value_type>(num/g);
        this->den = static_cast<value_type>(den/g);
    }

    template<typename F> requires (std::is_floating_point_v<F>)
    explicit rational(const F value, T max_den = std::numeric_limits<T>::max()) {
        *this = from_float(value, max_den);
    }
    
    template<typename F> requires (std::is_floating_point_v<F>)
    operator F() const {
        return static_cast<F>(this->num) / static_cast<F>(this->den);
    }

    template<typename U> requires (std::is_integral_v<U>)
    rational<value_type>& operator=(const U num){
        this->num = num;
        this->den = 1;
        return *this;
    }
    template<typename U> requires (std::is_floating_point_v<U>)
    rational<value_type>& operator=(const U num) = delete;

    __attribute__((always_inline, hot)) value_type numerator() const { return num; }
    __attribute__((always_inline, hot)) value_type denominator() const { return den; }
};

template<typename T>
struct is_rational : std::false_type {};
template<typename U>
struct is_rational<rational<U>> : std::true_type {};
template<typename T>
concept IsRational = is_rational<T>::value;
template<typename T>
concept IsNotRational = !is_rational<T>::value;
template <typename T>
constexpr bool is_signed_rational_or_signed_v = std::is_signed_v<T> || []{
    if constexpr (is_rational<T>::value)
        return std::is_signed_v<typename T::value_type>;
    else
        return false;
}();


template<typename Target, typename Source>
constexpr Target convert_to(const Source& s){
    if constexpr (is_rational<Source>::value && is_rational<Target>::value){
        using Inner = typename Target::value_type;
        return Target(static_cast<Inner>(s.numerator()), static_cast<Inner>(s.denominator()));  
    } 
    else if constexpr (is_rational<Source>::value && !is_rational<Target>::value){
        return static_cast<Target>(s.numerator()) / static_cast<Target>(s.denominator());      
    } 
    else if constexpr (std::is_floating_point_v<Source> && is_rational<Target>::value){
        return Target::from_float(static_cast<double>(s));  
    } 
    else if constexpr (!is_rational<Source>::value && is_rational<Target>::value){
        return Target(static_cast<typename Target::value_type>(s));  
    } 
    else {
        return static_cast<Target>(s); 
    }
}

template<typename T> requires (std::is_integral_v<T> || std::is_floating_point_v<T> || is_rational<T>::value)
class complex{
public:
    T r = 0;
    T i = 0;
    complex() = default;
    template<typename U0, typename U1 = T>
    complex(U0 r_in, U1 i_in = U1(0)){
        this->r = convert_to<T>(r_in);
        this->i = convert_to<T>(i_in);
    }

    template<typename U>
    complex<T>& operator=(U r){
        this->r = convert_to<T>(r);
        this->i = 0;
        return *this;
    }

    auto to_eular() const {
        using U = std::conditional_t<std::is_floating_point_v<T> || is_rational<T>::value, T, double>;
        if constexpr (is_rational<T>::value){
            U magnitude = convert_to<U>(std::hypot(static_cast<double>(this->r), static_cast<double>(this->i)));
            U angle = convert_to<U>(std::atan2(static_cast<double>(this->i), static_cast<double>(this->r)));
            return pair(magnitude, angle);
        }
        else{
            U magnitude = std::hypot(this->r, this->i);
            U angle = std::atan2(this->i, this->r);
            return pair(magnitude, angle);
        }
    }
    template<typename U> requires (std::is_floating_point_v<U> || is_rational<U>::value)
    static complex<T> from_eular(const U magnitude, const U angle){
        if constexpr (is_rational<U>::value){
            T r = convert_to<T>(magnitude * std::cos(static_cast<double>(angle)));
            T i = convert_to<T>(magnitude * std::sin(static_cast<double>(angle)));
            return complex<T>(r, i);
        }
        else{
            T r = convert_to<T>(magnitude * std::cos(angle));
            T i = convert_to<T>(magnitude * std::sin(angle));
            return complex<T>(r, i);
        }
    }
    //For most cases size will be <= 2 bytes so I dont think we need dedicated move constructor and move assignment operator.
};
template<typename T>
struct is_complex : std::false_type {};
template<typename U>
struct is_complex<complex<U>> : std::true_type {};
template<typename T>
concept IsComplex = is_complex<T>::value;
template<typename T>
concept IsNotComplex = !is_complex<T>::value;


template<typename T> requires (std::is_integral_v<T> || std::is_floating_point_v<T> || is_rational<T>::value)
class quaternion{
public:
    T r = 0;
    T i = 0;
    T j = 0;
    T k = 0;
    quaternion() = default;
    template<IsNotComplex U0, IsNotComplex U1 = T, IsNotComplex U2 = T, IsNotComplex U3 = T>
    quaternion(U0 r, const U1 i = U1(0), const U2 j = U2(0), const U3 k = U3(0)){
        this->r = convert_to<T>(r);
        this->i = convert_to<T>(i);
        this->j = convert_to<T>(j);
        this->k = convert_to<T>(k);
    }
    quaternion(complex<T> c, const T j = 0, const T k = 0){
        this->r = c.r;
        this->i = c.i;
        this->j = j;
        this->k = k;
    }
    

    template<IsNotComplex U>
    quaternion<T>& operator=(const U r){
        this->r = convert_to<T>(r);
        this->i = 0;
        this->j = 0;
        this->k = 0;
        return *this;
    }
    quaternion<T>& operator=(const complex<T> c){
        this->r = c.r;
        this->i = c.i;
        this->j = 0;
        this->k = 0;
        return *this;
    }
};
template<typename T>
struct is_quaternion : std::false_type {};
template<typename U>
struct is_quaternion<quaternion<U>> : std::true_type {};
template<typename T>
concept IsQuaternion = is_quaternion<T>::value;
template<typename T>
concept IsNotQuaternion = !is_quaternion<T>::value;


template<typename T>
concept IsNotQuaternionOrComplex = !is_quaternion<T>::value && !is_complex<T>::value;

template<typename T> requires (std::is_integral_v<T> || std::is_floating_point_v<T> || is_rational<T>::value)
class dual_quaternion{
public:
    quaternion<T> q;
    quaternion<T> e;

    dual_quaternion() = default;
    template<IsNotQuaternionOrComplex U0, IsNotQuaternionOrComplex U1 = T, IsNotQuaternionOrComplex U2 = T, IsNotQuaternionOrComplex U3 = T, 
             IsNotQuaternionOrComplex U4 = T, IsNotQuaternionOrComplex U5 = T, IsNotQuaternionOrComplex U6 = T, IsNotQuaternionOrComplex U7 = T>
    dual_quaternion(const U0 r, const U1 i = U1(0), const U2 j = U2(0), const U3 k = U3(0), const U4 e_r = U4(0), const U5 e_i = U5(0), const U6 e_j = U6(0), const U7 e_k = U7(0)){
        this->q = quaternion<T>(convert_to<T>(r), convert_to<T>(i), convert_to<T>(j), convert_to<T>(k));
        this->e = quaternion<T>(convert_to<T>(e_r), convert_to<T>(e_i), convert_to<T>(e_j), convert_to<T>(e_k));
    }
    dual_quaternion(const quaternion<T> q, const quaternion<T> e = 0){
        this->q = q;
        this->e = e;
    }
    dual_quaternion(const complex<T> c, const complex<T> e = 0){
        this->q = quaternion<T>(c.r, c.i, 0, 0);
        this->e = quaternion<T>(e.r, e.i, 0, 0);
    }

    template<IsNotQuaternionOrComplex U>
    dual_quaternion<T>& operator=(const U r){
        this->q = quaternion<T>(convert_to<T>(r));
        this->e = quaternion<T>(0);
        return *this;
    }
    dual_quaternion<T>& operator=(const complex<T> c){
        this->q = quaternion<T>(c.r, c.i, 0, 0);
        this->e = quaternion<T>(0);
        return *this;
    }
    dual_quaternion<T>& operator=(const quaternion<T> q){
        this->q = q;
        this->e = quaternion<T>(0);
        return *this;
    }
};
}
