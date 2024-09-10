T hypot_imp(T x, T y, const Policy& pol)
{
   //
   // Normalize x and y, so that both are positive and x >= y:
   //
   using std::fabs; using std::sqrt; // ADL of std names

   x = fabs(x);
   y = fabs(y);

#ifdef BOOST_MSVC
#pragma warning(push) 
#pragma warning(disable: 4127)
#endif
   // special case, see C99 Annex F:
   if(std::numeric_limits<T>::has_infinity
      && ((x == std::numeric_limits<T>::infinity())
      || (y == std::numeric_limits<T>::infinity())))
      return policies::raise_overflow_error<T>("boost::math::hypot<%1%>(%1%,%1%)", 0, pol);
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

   if(y > x)
      (std::swap)(x, y);

   if(x * tools::epsilon<T>() >= y)
      return x;

   T rat = y / x;
   return x * sqrt(1 + rat*rat);
} // template <class T> T hypot(T x, T y)