#pragma once
#include "number.hpp" 
#include <type_traits>
#include <cstdint>
namespace Phytra {
// ---------- AXIS 1: scalar rank ----------
// Every leaf integer type gets its own rank so rational can sit strictly above ALL of them.
// Leave gaps (steps of 10) so you can insert new integer widths later without renumbering everything.

template<typename T> struct scalar_rank; // no default -> must register every leaf type explicitly

template<> struct scalar_rank<int8_t>   { static constexpr int64_t value = 0;  };
template<> struct scalar_rank<uint8_t>  { static constexpr int64_t value = 5;  };
template<> struct scalar_rank<int16_t>  { static constexpr int64_t value = 10; };
template<> struct scalar_rank<uint16_t> { static constexpr int64_t value = 15; };
template<> struct scalar_rank<int32_t>  { static constexpr int64_t value = 20; };
template<> struct scalar_rank<uint32_t> { static constexpr int64_t value = 25; };
template<> struct scalar_rank<int64_t>  { static constexpr int64_t value = 30; };
template<> struct scalar_rank<uint64_t> { static constexpr int64_t value = 35; };

// rational<U> ranks ABOVE every integer (rank 40 base), but its own relative
// order among different rational<U> is broken by U's rank, not a shared flat rank.
template<typename U>
struct scalar_rank<rational<U>> {
    static constexpr int64_t value = 40 + scalar_rank<U>::value; // strictly > any bare integer (max int64_t rank 35)
};

template<> struct scalar_rank<float>  { static constexpr int64_t value = 1000; };
template<> struct scalar_rank<double> { static constexpr int64_t value = 1010; };

template<typename T>
inline constexpr int64_t scalar_rank_v = scalar_rank<T>::value;

// picks the higher-ranked TYPE (not just int64_t) -- when equal rank (shouldn't happen given the +scalar_rank<U> trick,
// but kept as an explicit tiebreak in case two custom types ever collide), prefer A.
template<typename A, typename B>
using promote_scalar_t = std::conditional_t<(scalar_rank_v<B> > scalar_rank_v<A>), B, A>;


// ---------- AXIS 2: container/algebra rank ----------

template<typename T> struct container_rank{static constexpr int64_t value = 0;}; // plain scalar
template<typename T> struct container_rank<complex<T>>{static constexpr int64_t value = 1;};
template<typename T> struct container_rank<quaternion<T>>{static constexpr int64_t value = 2;};
template<typename T> struct container_rank<dual_quaternion<T>>{static constexpr int64_t value = 3;};

template<typename T>
inline constexpr int64_t container_rank_v = container_rank<T>::value;

template<typename T> struct inner_type{using type = T;};
template<typename T> struct inner_type<complex<T>>{using type = T;};
template<typename T> struct inner_type<quaternion<T>>{ using type = T; };
template<typename T> struct inner_type<dual_quaternion<T>>{ using type = T; };
template<typename T> using inner_type_t = typename inner_type<T>::type;

template<int64_t Rank, typename Inner> struct container_of; // no default -> unregistered rank = hard compile error
template<typename Inner> struct container_of<0, Inner> { using type = Inner; };
template<typename Inner> struct container_of<1, Inner> { using type = complex<Inner>; };
template<typename Inner> struct container_of<2, Inner> { using type = quaternion<Inner>; };
template<typename Inner> struct container_of<3, Inner> { using type = dual_quaternion<Inner>; };


// ---------- COMBINED PROMOTION ----------

template<typename A, typename B>
struct promote {
    using inner_promoted = promote_scalar_t<inner_type_t<A>, inner_type_t<B>>;
    static constexpr int64_t rank_a = container_rank_v<A>;
    static constexpr int64_t rank_b = container_rank_v<B>;
    static constexpr int64_t max_rank = (rank_a > rank_b) ? rank_a : rank_b;

    using type = typename container_of<max_rank, inner_promoted>::type;
};

template<typename A, typename B>
using promote_t = typename promote<A, B>::type;
} 