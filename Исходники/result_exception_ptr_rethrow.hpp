 template <class Impl> static constexpr void wide_value_check(Impl &&self)
 {
   if(!base::_has_value(std::forward<Impl>(self)))
   {
     if(base::_has_error(std::forward<Impl>(self)))
     {
       // ADL
       rethrow_exception(policy::exception_ptr(base::_error(std::forward<Impl>(self))));
     }
     BOOST_OUTCOME_THROW_EXCEPTION(bad_result_access("no value"));  // NOLINT
   }
 }