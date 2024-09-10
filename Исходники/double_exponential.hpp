    typename return_type<T_y,T_loc,T_scale>::type
    double_exponential_ccdf_log(const T_y& y, const T_loc& mu, 
                               const T_scale& sigma) {
      static const char* function
        = "stan::prob::double_exponential_ccdf_log(%1%)";
      
      using stan::math::check_finite;
      using stan::math::check_not_nan;
      using stan::math::check_positive;
      using stan::math::check_consistent_sizes;
      using stan::math::value_of;

      double ccdf_log(0.0);

      // check if any vectors are zero length
      if (!(stan::length(y) 
            && stan::length(mu) 
            && stan::length(sigma)))
        return ccdf_log;

      if(!check_not_nan(function, y, "Random variable", &ccdf_log))
        return ccdf_log;
      if(!check_finite(function, mu, "Location parameter", &ccdf_log))
        return ccdf_log;
      if(!check_finite(function, sigma, "Scale parameter", &ccdf_log))
        return ccdf_log;
      if(!check_positive(function, sigma, "Scale parameter", &ccdf_log))
        return ccdf_log;
      if (!(check_consistent_sizes(function, y, mu, sigma,
                                   "Random variable", "Location parameter", 
                                   "Scale Parameter", &ccdf_log)))
        return ccdf_log;
      
      using std::log;
      using std::exp;

      agrad::OperandsAndPartials<T_y, T_loc, T_scale> 
        operands_and_partials(y, mu, sigma);

      VectorView<const T_y> y_vec(y);
      VectorView<const T_loc> mu_vec(mu);
      VectorView<const T_scale> sigma_vec(sigma);
      const double log_half = std::log(0.5);
      size_t N = max_size(y, mu, sigma);

      for (size_t n = 0; n < N; n++) {
        const double y_dbl = value_of(y_vec[n]);
        const double mu_dbl = value_of(mu_vec[n]);
        const double sigma_dbl = value_of(sigma_vec[n]);
        const double scaled_diff = (y_dbl - mu_dbl) / sigma_dbl;
        const double inv_sigma = 1.0 / sigma_dbl;
        if(y_dbl < mu_dbl) {
          //log ccdf
          ccdf_log += log(1.0 - 0.5 * exp(scaled_diff));

          //gradients
          const double rep_deriv = 1.0 / (2.0 * exp(-scaled_diff) - 1.0);
        if (!is_constant_struct<T_y>::value)
          operands_and_partials.d_x1[n] -= rep_deriv * inv_sigma;
        if (!is_constant_struct<T_loc>::value)
          operands_and_partials.d_x2[n] += rep_deriv * inv_sigma;
        if (!is_constant_struct<T_scale>::value)
          operands_and_partials.d_x3[n] += rep_deriv * scaled_diff 
            * inv_sigma;
        }
        else {
          // log ccdf
          ccdf_log += log_half - scaled_diff;

          // gradients
          if (!is_constant_struct<T_y>::value)
            operands_and_partials.d_x1[n] -= inv_sigma;
          if (!is_constant_struct<T_loc>::value)
            operands_and_partials.d_x2[n] += inv_sigma;
          if (!is_constant_struct<T_scale>::value)
            operands_and_partials.d_x3[n] += scaled_diff * inv_sigma;
        }
      }
      return operands_and_partials.to_var(ccdf_log);
    }