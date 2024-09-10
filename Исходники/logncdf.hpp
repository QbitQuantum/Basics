 BOOST_FORCEINLINE static void conf_bounds(const A0& a0, A1& a1,
                                           const value_type& alpha )
 {
   typedef nt2::memory::container<tag::table_, value_type, nt2::_2D>  semantic;
   NT2_AS_TERMINAL_IN(semantic, pcov, boost::proto::child_c<3>(a0));
   const In0& x  = boost::proto::child_c<0>(a0);
   const In1& mu = boost::proto::child_c<1>(a0);
   const In2& sigma = boost::proto::child_c<2>(a0);
   auto z = (log(if_zero_else(is_lez(x), x))-mu)/sigma;
   // this is [1, x0]*pcov*[1; x0]
   auto zvar = fma(fma(pcov(2,2), z, Two<value_type>()*pcov(1,2)), z, pcov(1,1));
   BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gez(zvar)), "Covariance matrix must be positive");
   value_type normz = -nt2::norminv(alpha*nt2::Half<value_type>());
   auto halfwidth =  normz*nt2::sqrt(zvar)/sigma;
   boost::proto::child_c<0>(a1) = Half<value_type>()*nt2::erfc(-Sqrt_2o_2<value_type>()*z);
   boost::proto::child_c<1>(a1) = Half<value_type>()*nt2::erfc(-Sqrt_2o_2<value_type>()*(z-halfwidth));
   boost::proto::child_c<2>(a1) = Half<value_type>()*nt2::erfc(-Sqrt_2o_2<value_type>()*(z+halfwidth));
 }