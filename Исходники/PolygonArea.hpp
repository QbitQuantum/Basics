    // an alternate version of transit to deal with longitudes in the direct
    // problem.
    static inline int transitdirect(real lon1, real lon2) {
      // We want to compute exactly
      //   int(floor(lon2 / 360)) - int(floor(lon1 / 360))
      // Since we only need the parity of the result we can use std::remquo;
      // but this is buggy with g++ 4.8.3 (glibc version < 2.22), see
      //   https://sourceware.org/bugzilla/show_bug.cgi?id=17569
      // and requires C++11.  So instead we do
#if GEOGRAPHICLIB_CXX11_MATH && GEOGRAPHICLIB_PRECISION != 4
      using std::remainder;
      lon1 = remainder(lon1, real(720)); lon2 = remainder(lon2, real(720));
      return ( (lon2 >= 0 && lon2 < 360 ? 0 : 1) -
               (lon1 >= 0 && lon1 < 360 ? 0 : 1) );
#else
      using std::fmod;
      lon1 = fmod(lon1, real(720)); lon2 = fmod(lon2, real(720));
      return ( ((lon2 >= 0 && lon2 < 360) || lon2 < -360 ? 0 : 1) -
               ((lon1 >= 0 && lon1 < 360) || lon1 < -360 ? 0 : 1) );
#endif
    }