 typename stan::return_type<T_y, T_shape, T_scale>::type 
 cdf_log_function(const T_y& y, const T_shape& alpha, const T_scale& sigma,
                  const T3&, const T4&, const T5&) {
   using std::log;
   using std::pow;
   return log(1.0 - exp(-pow(y / sigma, alpha)));
 }