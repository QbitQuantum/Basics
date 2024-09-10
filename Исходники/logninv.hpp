 BOOST_FORCEINLINE static void conf_bounds(const A0& a0, A1& a1,
                                           const value_type& alpha )
 {
   typedef nt2::memory::container<tag::table_, value_type, nt2::_2D>  semantic;
   NT2_AS_TERMINAL_IN(semantic, pcov, boost::proto::child_c<3>(a0));
   const In0& p  = boost::proto::child_c<0>(a0);
   const In1& mu = boost::proto::child_c<1>(a0);
   const In2& sigma = boost::proto::child_c<2>(a0);
   auto logx0 = -Sqrt_2<A0>()*erfcinv( nt2::Two<A0>()*p);
   auto xvar =   fma(fma(pcov(2,2), logx0, Two<value_type>()*pcov(1,2)), logx0, pcov(1,1));
   BOOST_ASSERT_MSG(nt2::globalall(nt2::is_nltz(xvar)), "Covariance matrix must be positive");
   value_type normz = -nt2::norminv(alpha*nt2::Half<value_type>());
   auto halfwidth = normz*nt2::sqrt(xvar);
   boost::proto::child_c<0>(a1) = exp(fma(sigma, logx0, mu));
   auto coef = exp(-halfwidth);
   boost::proto::child_c<1>(a1) = boost::proto::child_c<0>(a1)*coef;
   boost::proto::child_c<2>(a1) = boost::proto::child_c<0>(a1)/coef;
 }