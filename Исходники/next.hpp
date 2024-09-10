inline T normalize_value(const T& val, const mpl::true_&)
{
   BOOST_STATIC_ASSERT(std::numeric_limits<T>::is_specialized);
   BOOST_STATIC_ASSERT(std::numeric_limits<T>::radix != 2);

   boost::intmax_t shift = std::numeric_limits<T>::digits - ilogb(val) - 1;
   T result = scalbn(val, shift);
   result = round(result);
   return scalbn(result, -shift);
}