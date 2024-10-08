    typename return_type<T_rate>::type
    poisson_cdf_log(const T_n& n, const T_rate& lambda) {
      static const char* function("stan::prob::poisson_cdf_log");
      typedef typename stan::partials_return_type<T_n,T_rate>::type 
        T_partials_return;
          
      using stan::math::check_not_nan;
      using stan::math::check_nonnegative;
      using stan::math::value_of;
      using stan::math::check_consistent_sizes;
          
      // Ensure non-zero argument slengths
      if (!(stan::length(n) && stan::length(lambda))) 
        return 0.0;
          
      T_partials_return P(0.0);
          
      // Validate arguments
      check_not_nan(function, "Rate parameter", lambda);
      check_nonnegative(function, "Rate parameter", lambda);
      check_consistent_sizes(function, 
                             "Random variable", n, 
                             "Rate parameter", lambda);
          
      // Wrap arguments into vector views
      VectorView<const T_n> n_vec(n);
      VectorView<const T_rate> lambda_vec(lambda);
      size_t size = max_size(n, lambda);
          
      // Compute vectorized cdf_log and gradient
      using stan::math::value_of;
      using stan::math::gamma_q;
      using boost::math::tgamma;
      using std::exp;
      using std::pow;
          
      agrad::OperandsAndPartials<T_rate> operands_and_partials(lambda);

      // Explicit return for extreme values
      // The gradients are technically ill-defined, but treated as neg infinity
      for (size_t i = 0; i < stan::length(n); i++) {
        if (value_of(n_vec[i]) < 0) 
          return operands_and_partials.to_var(stan::math::negative_infinity(),
                                              lambda);
      }
        
      for (size_t i = 0; i < size; i++) {
        // Explicit results for extreme values
        // The gradients are technically ill-defined, but treated as zero
        if (value_of(n_vec[i]) == std::numeric_limits<int>::max())
          continue;
          
        const T_partials_return n_dbl = value_of(n_vec[i]);
        const T_partials_return lambda_dbl = value_of(lambda_vec[i]);
        const T_partials_return Pi = gamma_q(n_dbl+1, lambda_dbl);

        P += log(Pi);
  
        if (!is_constant_struct<T_rate>::value)
          operands_and_partials.d_x1[i] -= exp(-lambda_dbl) 
            * pow(lambda_dbl,n_dbl) / tgamma(n_dbl+1) / Pi;

      }
      
      return operands_and_partials.to_var(P,lambda);
    }