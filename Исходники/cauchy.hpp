    typename return_type<T_y,T_loc,T_scale>::type
    cauchy_ccdf_log(const T_y& y, const T_loc& mu, const T_scale& sigma) {
        
      // Size checks
      if ( !( stan::length(y) && stan::length(mu) 
              && stan::length(sigma) ) ) 
        return 0.0;
        
      static const std::string function("stan::prob::cauchy_cdf");
      
      using stan::error_handling::check_positive_finite;
      using stan::error_handling::check_finite;
      using stan::error_handling::check_not_nan;
      using stan::error_handling::check_consistent_sizes;
      using boost::math::tools::promote_args;
      using stan::math::value_of;

      double ccdf_log(0.0);
        
      check_not_nan(function, "Random variable", y);
      check_finite(function, "Location parameter", mu);
      check_positive_finite(function, "Scale parameter", sigma);
      check_consistent_sizes(function, 
                             "Random variable", y, 
                             "Location parameter", mu, 
                             "Scale Parameter", sigma);
        
      // Wrap arguments in vectors
      VectorView<const T_y> y_vec(y);
      VectorView<const T_loc> mu_vec(mu);
      VectorView<const T_scale> sigma_vec(sigma);
      size_t N = max_size(y, mu, sigma);
        
      agrad::OperandsAndPartials<T_y, T_loc, T_scale> 
        operands_and_partials(y, mu, sigma);
        
      // Compute CDFLog and its gradients
      using std::atan;
      using stan::math::pi;

      // Compute vectorized CDF and gradient
      for (size_t n = 0; n < N; n++) {
            
        // Pull out values
        const double y_dbl = value_of(y_vec[n]);
        const double mu_dbl = value_of(mu_vec[n]);
        const double sigma_inv_dbl = 1.0 / value_of(sigma_vec[n]);
        const double sigma_dbl = value_of(sigma_vec[n]);
        const double z = (y_dbl - mu_dbl) * sigma_inv_dbl;
          
        // Compute
        const double Pn = 0.5 - atan(z) / pi();
        ccdf_log += log(Pn);
            
        const double rep_deriv = 1.0 / (Pn * pi() 
                                        * (z * z * sigma_dbl + sigma_dbl));
        if (!is_constant_struct<T_y>::value)
          operands_and_partials.d_x1[n] -= rep_deriv;
        if (!is_constant_struct<T_loc>::value)
          operands_and_partials.d_x2[n] += rep_deriv;
        if (!is_constant_struct<T_scale>::value)
          operands_and_partials.d_x3[n] += rep_deriv * z;
      }
      return operands_and_partials.to_var(ccdf_log);
    }