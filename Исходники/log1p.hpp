T log1p_imp(T const & x, const Policy& pol, const mpl::int_<0>&)
{ // The function returns the natural logarithm of 1 + x.
   typedef typename tools::promote_args<T>::type result_type;
   BOOST_MATH_STD_USING
   using std::abs;

   static const char* function = "boost::math::log1p<%1%>(%1%)";

   if(x < -1)
      return policies::raise_domain_error<T>(
         function, "log1p(x) requires x > -1, but got x = %1%.", x, pol);
   if(x == -1)
      return -policies::raise_overflow_error<T>(
         function, 0, pol);

   result_type a = abs(result_type(x));
   if(a > result_type(0.5L))
      return log(1 + result_type(x));
   // Note that without numeric_limits specialisation support, 
   // epsilon just returns zero, and our "optimisation" will always fail:
   if(a < tools::epsilon<result_type>())
      return x;
   detail::log1p_series<result_type> s(x);
   boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582))
   result_type result = tools::sum_series(s, policies::digits<result_type, Policy>(), max_iter);
#else
   result_type zero = 0;
   result_type result = tools::sum_series(s, policies::digits<result_type, Policy>(), max_iter, zero);
#endif
   policies::check_series_iterations(function, max_iter, pol);
   return result;
}