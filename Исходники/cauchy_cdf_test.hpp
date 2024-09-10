 typename stan::return_type<T_y, T_loc, T_scale>::type 
 cdf_function(const T_y& y, const T_loc& mu, const T_scale& sigma,
              const T3&, const T4&, const T5&) {
   using std::atan2;
   using stan::math::pi;
   return atan2(y-mu, sigma) / pi() + 0.5;
 }