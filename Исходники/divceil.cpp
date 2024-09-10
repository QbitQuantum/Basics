#include <boost/simd/constant/inf.hpp>
#include <boost/simd/constant/minf.hpp>
#include <boost/simd/constant/mone.hpp>
#include <boost/simd/constant/nan.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/constant/valmax.hpp>
#include <boost/simd/constant/valmin.hpp>
#include <boost/simd/constant/two.hpp>


STF_CASE_TPL (" div real",  STF_IEEE_TYPES)
{
  namespace bs = boost::simd;
  using bs::div;
  using r_t = decltype(div(T(), T()));

#ifndef BOOST_SIMD_NO_INVALIDS
  STF_IEEE_EQUAL(div(bs::Inf<T>(), bs::Inf<T>(), bs::ceil), bs::Nan<r_t>());
  STF_IEEE_EQUAL(div(bs::Minf<T>(), bs::Minf<T>(), bs::ceil), bs::Nan<r_t>());
  STF_IEEE_EQUAL(div(bs::Nan<T>(), bs::Nan<T>(), bs::ceil), bs::Nan<r_t>());
#endif
  STF_EQUAL(div(T(4),T(0), bs::ceil), bs::Inf<r_t>());
  STF_EQUAL(div(T(4),T(3), bs::ceil), 2);
  STF_EQUAL(div(bs::Mone<T>(), bs::Mone<T>(), bs::ceil), bs::One<r_t>());
  STF_EQUAL(div(bs::Mone<T>(),bs::Zero<T>(), bs::ceil), bs::Minf<r_t>());
  STF_EQUAL(div(bs::One<T>(), bs::One<T>(), bs::ceil), bs::One<r_t>());
  STF_EQUAL(div(bs::One<T>(),bs::Zero<T>(), bs::ceil), bs::Inf<r_t>());
  STF_IEEE_EQUAL(div(bs::Zero<T>(),bs::Zero<T>(), bs::ceil), bs::Nan<r_t>());
} // end of test for floating_
