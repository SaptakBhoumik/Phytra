#pragma once
#include "../number.hpp"
#include "../ops/ops.hpp"
#include "primitive_math.hpp"
#include "rational_math.hpp"
#include "complex_math.hpp"
#include "quaternion_math.hpp"

namespace Phytra{
//TODO:I genuenly dont know anything about dual quaternions. These are implemented with help of claude. More study is needed on my part to verify
namespace detail{
// Core Fréchet-derivative machine.
// Given q, e, and the complex value/derivative of f at lambda = q.r + i*|v|,
// returns (f(q), D_f(q)[e]) packed as a dual_quaternion.
template<typename T>
dual_quaternion<T> apply_quat_fn(const quaternion<T>& q, const quaternion<T>& e,
                                  const complex<T>& F, const complex<T>& Fp){
    const auto vi = q.i, vj = q.j, vk = q.k;
    const auto r  = sqrt(vi*vi + vj*vj + vk*vk);

    if(double(r) < 1e-10){
        // q is (numerically) real: everything degenerates to the scalar case
        return dual_quaternion<T>(
            quaternion<T>(F.r, T(0), T(0), T(0)),
            quaternion<T>(Fp.r*e.r, Fp.r*e.i, Fp.r*e.j, Fp.r*e.k));
    }

    const auto ni = vi/r, nj = vj/r, nk = vk/r;

    const auto fq = quaternion<T>(F.r, F.i*ni, F.i*nj, F.i*nk);

    const auto e0  = e.r;
    const auto e1  = e.i*ni + e.j*nj + e.k*nk;      // component of e along n
    const auto epi = e.i - e1*ni;                    // perpendicular remainder
    const auto epj = e.j - e1*nj;
    const auto epk = e.k - e1*nk;

    // parallel part: complex multiplication (Fp.r + i*Fp.i) * (e0 + i*e1)
    const auto par_r = Fp.r*e0 - Fp.i*e1;
    const auto par_n = Fp.r*e1 + Fp.i*e0;

    // perpendicular part: scalar coefficient I(lambda)/r
    const auto c_perp = F.i / r;

    const auto de = quaternion<T>(par_r,
                                   par_n*ni + c_perp*epi,
                                   par_n*nj + c_perp*epj,
                                   par_n*nk + c_perp*epk);

    return dual_quaternion<T>(fq, de);
}
} // namespace detail

//Power/root functions
template<typename T>
dual_quaternion<T> pow(const dual_quaternion<T>& lhs, const dual_quaternion<T>& rhs){
    const auto ln_lhs = ln(lhs);
    const auto ln_lhs_times_rhs = ln_lhs * rhs;
    return exp(ln_lhs_times_rhs);
}
template<typename T>
dual_quaternion<T> sqrt(const dual_quaternion<T>& lhs){
    const auto ln_lhs = ln(lhs);
    return exp(dual_quaternion<T>(
        quaternion<T>(ln_lhs.q.r/T(2), ln_lhs.q.i/T(2), ln_lhs.q.j/T(2), ln_lhs.q.k/T(2)),
        quaternion<T>(ln_lhs.e.r/T(2), ln_lhs.e.i/T(2), ln_lhs.e.j/T(2), ln_lhs.e.k/T(2))));
}
template<typename T>
dual_quaternion<T> cbrt(const dual_quaternion<T>& lhs){
    const auto ln_lhs = ln(lhs);
    return exp(dual_quaternion<T>(
        quaternion<T>(ln_lhs.q.r/T(3), ln_lhs.q.i/T(3), ln_lhs.q.j/T(3), ln_lhs.q.k/T(3)),
        quaternion<T>(ln_lhs.e.r/T(3), ln_lhs.e.i/T(3), ln_lhs.e.j/T(3), ln_lhs.e.k/T(3))));
}

template<typename T>
dual_quaternion<T> exp(const dual_quaternion<T>& Q){
    const auto a = Q.q.r;
    const auto r = sqrt(Q.q.i*Q.q.i + Q.q.j*Q.q.j + Q.q.k*Q.q.k);
    const auto ea = exp(a);
    complex<T> F(ea*cos(r), ea*sin(r));
    complex<T> Fp = F; // d/dλ exp(λ) = exp(λ)
    return detail::apply_quat_fn(Q.q, Q.e, F, Fp);
}
template<typename T>
dual_quaternion<T> exp2(const dual_quaternion<T>& lhs){
    return pow(dual_quaternion<T>(T(2)), lhs);
}
template<typename T>
dual_quaternion<T> expm1(const dual_quaternion<T>& lhs){
    return exp(lhs) - dual_quaternion<T>(T(1));
}
template<typename T>
dual_quaternion<T> expp1(const dual_quaternion<T>& lhs){
    return exp(lhs) + dual_quaternion<T>(T(1));
}

template<typename T>
dual_quaternion<T> ln(const dual_quaternion<T>& Q){
    const auto a = Q.q.r;
    const auto r = sqrt(Q.q.i*Q.q.i + Q.q.j*Q.q.j + Q.q.k*Q.q.k);
    const auto mod2 = a*a + r*r;
    complex<T> F(ln(sqrt(mod2)), atan2(r, a));
    complex<T> Fp(a/mod2, -r/mod2); // 1/lambda
    return detail::apply_quat_fn(Q.q, Q.e, F, Fp);
}
template<typename T>
dual_quaternion<T> log2(const dual_quaternion<T>& lhs){
    using U = std::conditional_t<std::is_floating_point_v<T> || is_rational<T>::value, T, double>;
    const auto ln_2 = U(0.6931471805599453);
    const auto ln_lhs = ln(lhs);
    return dual_quaternion<T>(
        quaternion<T>(T(U(ln_lhs.q.r)/ln_2), T(U(ln_lhs.q.i)/ln_2), T(U(ln_lhs.q.j)/ln_2), T(U(ln_lhs.q.k)/ln_2)),
        quaternion<T>(T(U(ln_lhs.e.r)/ln_2), T(U(ln_lhs.e.i)/ln_2), T(U(ln_lhs.e.j)/ln_2), T(U(ln_lhs.e.k)/ln_2)));
}
template<typename T>
dual_quaternion<T> log10(const dual_quaternion<T>& lhs){
    using U = std::conditional_t<std::is_floating_point_v<T> || is_rational<T>::value, T, double>;
    const auto ln_10 = U(2.302585092994046);
    const auto ln_lhs = ln(lhs);
    return dual_quaternion<T>(
        quaternion<T>(T(U(ln_lhs.q.r)/ln_10), T(U(ln_lhs.q.i)/ln_10), T(U(ln_lhs.q.j)/ln_10), T(U(ln_lhs.q.k)/ln_10)),
        quaternion<T>(T(U(ln_lhs.e.r)/ln_10), T(U(ln_lhs.e.i)/ln_10), T(U(ln_lhs.e.j)/ln_10), T(U(ln_lhs.e.k)/ln_10)));
}
template<typename T>
dual_quaternion<T> log(const dual_quaternion<T>& lhs, const dual_quaternion<T>& rhs){
    return ln(lhs) / ln(rhs);
}
template<typename T>
dual_quaternion<T> ln_1p(const dual_quaternion<T>& lhs){
    return ln(dual_quaternion<T>(T(1)) + lhs);
}
template<typename T>
dual_quaternion<T> log2_1p(const dual_quaternion<T>& lhs){
    return log2(dual_quaternion<T>(T(1)) + lhs);
}
template<typename T>
dual_quaternion<T> log10_1p(const dual_quaternion<T>& lhs){
    return log10(dual_quaternion<T>(T(1)) + lhs);
}
template<typename T>
dual_quaternion<T> log_1p(const dual_quaternion<T>& lhs, const dual_quaternion<T>& rhs){
    return log(dual_quaternion<T>(T(1)) + lhs, rhs);
}

//Trigonometric functions
template<typename T>
dual_quaternion<T> sin(const dual_quaternion<T>& Q){
    const auto a = Q.q.r;
    const auto r = sqrt(Q.q.i*Q.q.i + Q.q.j*Q.q.j + Q.q.k*Q.q.k);
    complex<T> F(sin(a)*cosh(r), cos(a)*sinh(r));
    complex<T> Fp(cos(a)*cosh(r), -sin(a)*sinh(r)); // cos(lambda)
    return detail::apply_quat_fn(Q.q, Q.e, F, Fp);
}
template<typename T>
dual_quaternion<T> cos(const dual_quaternion<T>& Q){
    const auto a = Q.q.r;
    const auto r = sqrt(Q.q.i*Q.q.i + Q.q.j*Q.q.j + Q.q.k*Q.q.k);
    complex<T> F(cos(a)*cosh(r), -sin(a)*sinh(r));
    complex<T> Fp(-sin(a)*cosh(r), -cos(a)*sinh(r)); // -sin(lambda)
    return detail::apply_quat_fn(Q.q, Q.e, F, Fp);
}
template<typename T>
dual_quaternion<T> tan(const dual_quaternion<T>& lhs){ return sin(lhs) / cos(lhs); }
template<typename T>
dual_quaternion<T> sec(const dual_quaternion<T>& lhs){ return dual_quaternion<T>(T(1)) / cos(lhs); }
template<typename T>
dual_quaternion<T> cosec(const dual_quaternion<T>& lhs){ return dual_quaternion<T>(T(1)) / sin(lhs); }
template<typename T>
dual_quaternion<T> cot(const dual_quaternion<T>& lhs){ return cos(lhs) / sin(lhs); }

template<typename T>
dual_quaternion<T> asin(const dual_quaternion<T>& Q){
    const auto a = Q.q.r;
    const auto r = sqrt(Q.q.i*Q.q.i + Q.q.j*Q.q.j + Q.q.k*Q.q.k);
    complex<T> lambda(a, r);
    complex<T> one(T(1), T(0));
    complex<T> F  = asin(lambda);
    complex<T> Fp = one / sqrt(one - lambda*lambda);
    return detail::apply_quat_fn(Q.q, Q.e, F, Fp);
}
template<typename T>
dual_quaternion<T> acos(const dual_quaternion<T>& Q){
    const auto a = Q.q.r;
    const auto r = sqrt(Q.q.i*Q.q.i + Q.q.j*Q.q.j + Q.q.k*Q.q.k);
    complex<T> lambda(a, r);
    complex<T> one(T(1), T(0));
    complex<T> F  = acos(lambda);
    complex<T> Fp = complex<T>(T(-1), T(0)) / sqrt(one - lambda*lambda);
    return detail::apply_quat_fn(Q.q, Q.e, F, Fp);
}
template<typename T>
dual_quaternion<T> atan(const dual_quaternion<T>& Q){
    const auto a = Q.q.r;
    const auto r = sqrt(Q.q.i*Q.q.i + Q.q.j*Q.q.j + Q.q.k*Q.q.k);
    complex<T> lambda(a, r);
    complex<T> one(T(1), T(0));
    complex<T> F  = atan(lambda);
    complex<T> Fp = one / (one + lambda*lambda);
    return detail::apply_quat_fn(Q.q, Q.e, F, Fp);
}
template<typename T>
dual_quaternion<T> atan2(const dual_quaternion<T>& lhs, const dual_quaternion<T>& rhs){
    return atan(lhs / rhs);
}
template<typename T>
dual_quaternion<T> asec(const dual_quaternion<T>& lhs){ return acos(dual_quaternion<T>(T(1)) / lhs); }
template<typename T>
dual_quaternion<T> acosec(const dual_quaternion<T>& lhs){ return asin(dual_quaternion<T>(T(1)) / lhs); }
template<typename T>
dual_quaternion<T> acot(const dual_quaternion<T>& lhs){ return atan(dual_quaternion<T>(T(1)) / lhs); }
template<typename T>
dual_quaternion<T> acot2(const dual_quaternion<T>& lhs, const dual_quaternion<T>& rhs){ return atan2(rhs, lhs); }

//Hyperbolic functions — built from exp, exactly as in quaternion_math.hpp,
//so they inherit correct noncommutative derivatives for free.
template<typename T>
dual_quaternion<T> sinh(const dual_quaternion<T>& lhs){
    const auto ex = exp(lhs);
    const auto exinv = dual_quaternion<T>(T(1)) / ex;
    const auto num = ex - exinv;
    return dual_quaternion<T>(
        quaternion<T>(num.q.r/T(2), num.q.i/T(2), num.q.j/T(2), num.q.k/T(2)),
        quaternion<T>(num.e.r/T(2), num.e.i/T(2), num.e.j/T(2), num.e.k/T(2)));
}
template<typename T>
dual_quaternion<T> cosh(const dual_quaternion<T>& lhs){
    const auto ex = exp(lhs);
    const auto exinv = dual_quaternion<T>(T(1)) / ex;
    const auto num = ex + exinv;
    return dual_quaternion<T>(
        quaternion<T>(num.q.r/T(2), num.q.i/T(2), num.q.j/T(2), num.q.k/T(2)),
        quaternion<T>(num.e.r/T(2), num.e.i/T(2), num.e.j/T(2), num.e.k/T(2)));
}
template<typename T>
dual_quaternion<T> tanh(const dual_quaternion<T>& lhs){
    const auto ex = exp(lhs);
    const auto exinv = dual_quaternion<T>(T(1)) / ex;
    const auto num = (ex - exinv);
    const auto den = (ex + exinv);
    return num / den;
}
template<typename T>
dual_quaternion<T> sech(const dual_quaternion<T>& lhs){
    const auto ex = exp(lhs);
    const auto exinv = dual_quaternion<T>(T(1)) / ex;
    const auto den = (ex + exinv);
    return dual_quaternion<T>(T(2)) / den;
}
template<typename T>
dual_quaternion<T> cosech(const dual_quaternion<T>& lhs){
    const auto ex = exp(lhs);
    const auto exinv = dual_quaternion<T>(T(1)) / ex;
    const auto den = (ex - exinv);
    return dual_quaternion<T>(T(2)) / den;
}
template<typename T>
dual_quaternion<T> coth(const dual_quaternion<T>& lhs){
    const auto ex = exp(lhs);
    const auto exinv = dual_quaternion<T>(T(1)) / ex;
    const auto num = (ex + exinv);
    const auto den = (ex - exinv);
    return num / den;
}

template<typename T>
dual_quaternion<T> asinh(const dual_quaternion<T>& lhs){
    const auto one = dual_quaternion<T>(T(1));
    return ln(lhs + sqrt(lhs*lhs + one));
}
template<typename T>
dual_quaternion<T> acosh(const dual_quaternion<T>& lhs){
    const auto one = dual_quaternion<T>(T(1));
    return ln(lhs + sqrt(lhs - one) * sqrt(lhs + one));
}
template<typename T>
dual_quaternion<T> atanh(const dual_quaternion<T>& lhs){
    const auto one = dual_quaternion<T>(T(1));
    const auto ln_result = ln((one + lhs) / (one - lhs));
    return dual_quaternion<T>(
        quaternion<T>(ln_result.q.r/T(2), ln_result.q.i/T(2), ln_result.q.j/T(2), ln_result.q.k/T(2)),
        quaternion<T>(ln_result.e.r/T(2), ln_result.e.i/T(2), ln_result.e.j/T(2), ln_result.e.k/T(2)));
}
template<typename T>
dual_quaternion<T> asech(const dual_quaternion<T>& lhs){ return acosh(dual_quaternion<T>(T(1)) / lhs); }
template<typename T>
dual_quaternion<T> acosech(const dual_quaternion<T>& lhs){ return asinh(dual_quaternion<T>(T(1)) / lhs); }
template<typename T>
dual_quaternion<T> acoth(const dual_quaternion<T>& lhs){ return atanh(dual_quaternion<T>(T(1)) / lhs); }

//Rounding/classification
// |Q| is a *dual number*: |q+εe| = |q| + ε*(q·e)/|q|.
// Embedded here as a dual_quaternion whose q/e parts carry only a real component.
template<typename T>
dual_quaternion<T> abs(const dual_quaternion<T>& Q){
    const auto qn  = sqrt(Q.q.r*Q.q.r + Q.q.i*Q.q.i + Q.q.j*Q.q.j + Q.q.k*Q.q.k);
    const auto dot = Q.q.r*Q.e.r + Q.q.i*Q.e.i + Q.q.j*Q.e.j + Q.q.k*Q.e.k;
    return dual_quaternion<T>(quaternion<T>(qn, T(0), T(0), T(0)),
                               quaternion<T>(dot/qn, T(0), T(0), T(0)));
}

//Other binary functions
template<typename T>
dual_quaternion<T> mod(const dual_quaternion<T>& lhs, const dual_quaternion<T>& rhs){ 
    return lhs % rhs; 
}
template<typename T>
dual_quaternion<T> hypot(const dual_quaternion<T>& lhs, const dual_quaternion<T>& rhs){
    return sqrt(lhs*lhs + rhs*rhs);
}
}