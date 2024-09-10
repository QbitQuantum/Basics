 typename stan::return_type<T_y, T_loc, T_scale>::type 
 ccdf_log_function(const T_y& y, const T_loc& mu, const T_scale& sigma,
                  const T3&, const T4&, const T5&) {
   using std::atan;
   using stan::math::pi;
   using std::log;
   return log(0.5 - atan((y - mu) / sigma) / pi());
 }