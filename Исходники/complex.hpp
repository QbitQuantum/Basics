inline complex<typename boost::tr1_detail::promote_to_real<T, U>::type>
   pow (const T& x, const complex<U>& y)
{
   typedef typename boost::tr1_detail::promote_to_real<T, U>::type real_type;
   typedef complex<typename boost::tr1_detail::promote_to_real<T, U>::type> result_type;
   typedef typename boost::mpl::if_<boost::is_same<result_type, complex<U> >, result_type const&, result_type>::type cast_type;
   real_type r = x;
   std::complex<real_type> x1(r);
   cast_type y1(y);
   return std::pow(x1, y1);
}