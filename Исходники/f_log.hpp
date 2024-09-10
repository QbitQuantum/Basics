 inline float log2(const float& a0)
 {
   typedef float A0;
   if (a0 == Inf<A0>()) return a0;
   if (iseqz(a0)) return Minf<A0>();
   if (nt2::is_nan(a0)||is_ltz(a0)) return Nan<A0>();
   A0 x, fe, x2, y;
   kernel_log(a0, fe, x, x2, y);
   y =  fma(Mhalf<A0>(),x2, y);
   // multiply log of fraction by log2(e)
   A0 z = fma( x
             , Const<float, 0x3ee2a8ed>()
             , mul(y,Const<float, 0x3ee2a8ed>())// 0.44269504088896340735992
             );
   return ((z+y)+x)+fe;
 }