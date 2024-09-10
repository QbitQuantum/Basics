 static inline A0_n acos(const A0_n a0_n)
 {
   // 2130706432 values computed.
   // 1968272987 values (92.38%) within 0.0 ULPs
   //  162433445 values (7.62%)  within 0.5 ULPs
   // 8.5 cycles/element SSE4.2 g++-4.8
   const A0 a0 = a0_n;
   A0 x = nt2::abs(a0);
   bA0 x_larger_05 = gt(x, nt2::Half<A0>());
   x  = if_else(x_larger_05, nt2::sqrt(fma(nt2::Mhalf<A0>(), x, nt2::Half<A0>())), a0);
   x  = asin(x);
   x =  seladd(x_larger_05, x, x);
   x  = nt2::if_else(lt(a0, nt2::Mhalf<A0>()), nt2::Pi<A0>()-x, x);
   return nt2::if_else(x_larger_05, x, nt2::Pio_2<A0>()-x);
 }