#pragma once
#include <type_traits>
#include <numeric>
namespace Phytra{
template<typename T> requires (std::is_integral_v<T>)
class rational{
    //Assumes T is a integral type. Not tensor
public:
    using value_type = T;
    value_type num = 0;
    value_type den = 1;
    rational() = default;
    rational(const value_type num, const value_type den = 1){
        if (den < 0) { num = -num; den = -den; }
        auto g = std::gcd(num, den);
        if (g == 0) g = 1;           // guards the (0,0) case below
        this->num = num / g;
        this->den = den / g;
    }

    rational<value_type>& operator=(const value_type num){
        this->num = num;
        this->den = 1;
    }
};
template<typename T>
struct is_rational : std::false_type {};
template<typename U>
struct is_rational<rational<U>> : std::true_type {};
template<typename T>
concept IsRational = is_rational<T>::value;
template<typename T>
concept IsNotRational = !is_rational<T>::value;

template<typename Target, typename Source>
constexpr Target convert_to(const Source& s){
    if constexpr (is_rational<Source>::value && is_rational<Target>::value){
        using Inner = typename Target::value_type;
        return Target(static_cast<Inner>(s.num), static_cast<Inner>(s.den));  
    } 
    else if constexpr (is_rational<Source>::value && !is_rational<Target>::value){
        return static_cast<Target>(s.num) / static_cast<Target>(s.den);      
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
    T r = 0;
    T i = 0;
    T j = 0;
    T k = 0;
    T e_r = 0;
    T e_i = 0;
    T e_j = 0;
    T e_k = 0;

    dual_quaternion() = default;
    template<IsNotQuaternionOrComplex U0, IsNotQuaternionOrComplex U1 = T, IsNotQuaternionOrComplex U2 = T, IsNotQuaternionOrComplex U3 = T, 
             IsNotQuaternionOrComplex U4 = T, IsNotQuaternionOrComplex U5 = T, IsNotQuaternionOrComplex U6 = T, IsNotQuaternionOrComplex U7 = T>
    dual_quaternion(const U0 r, const U1 i = U1(0), const U2 j = U2(0), const U3 k = U3(0), const U4 e_r = U4(0), const U5 e_i = U5(0), const U6 e_j = U6(0), const U7 e_k = U7(0)){
        this->r = convert_to<T>(r);
        this->i = convert_to<T>(i);
        this->j = convert_to<T>(j);
        this->k = convert_to<T>(k);
        this->e_r = convert_to<T>(e_r);
        this->e_i = convert_to<T>(e_i);
        this->e_j = convert_to<T>(e_j);
        this->e_k = convert_to<T>(e_k);
    }
    dual_quaternion(const quaternion<T> q, const quaternion<T> e = 0){
        this->r = q.r;
        this->i = q.i;
        this->j = q.j;
        this->k = q.k;
        this->e_r = e.r;
        this->e_i = e.i;
        this->e_j = e.j;
        this->e_k = e.k;
    }
    dual_quaternion(const complex<T> c, const complex<T> e = 0){
        this->r = c.r;
        this->i = c.i;
        this->j = 0;
        this->k = 0;
        this->e_r = e.r;
        this->e_i = e.i;
        this->e_j = 0;
        this->e_k = 0;
    }

    template<IsNotQuaternionOrComplex U>
    dual_quaternion<T>& operator=(const U r){
        this->r = convert_to<T>(r);
        this->i = 0;
        this->j = 0;
        this->k = 0;
        this->e_r = 0;
        this->e_i = 0;
        this->e_j = 0;
        this->e_k = 0;
        return *this;
    }
    dual_quaternion<T>& operator=(const complex<T> c){
        this->r = c.r;
        this->i = c.i;
        this->j = 0;
        this->k = 0;
        this->e_r = 0;
        this->e_i = 0;
        this->e_j = 0;
        this->e_k = 0;
        return *this;
    }
    dual_quaternion<T>& operator=(const quaternion<T> q){
        this->r = q.r;
        this->i = q.i;
        this->j = q.j;
        this->k = q.k;
        this->e_r = 0;
        this->e_i = 0;
        this->e_j = 0;
        this->e_k = 0;
        return *this;
    }
};
}
