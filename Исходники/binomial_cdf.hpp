    typename return_type<T_prob>::type
    binomial_cdf(const T_n& n, const T_N& N, const T_prob& theta) {
      static const char* function("stan::prob::binomial_cdf");
      typedef typename stan::partials_return_type<T_n,T_N,T_prob>::type
        T_partials_return;
          
      using stan::math::check_finite;
      using stan::math::check_bounded;
      using stan::math::check_nonnegative;
      using stan::math::value_of;
      using stan::math::check_consistent_sizes;
      using stan::prob::include_summand;
          
      // Ensure non-zero arguments lenghts
      if (!(stan::length(n) && stan::length(N) && stan::length(theta)))
        return 1.0;
          
      T_partials_return P(1.0);
          
      // Validate arguments
      check_nonnegative(function, "Population size parameter", N);
      check_finite(function, "Probability parameter", theta);
      check_bounded(function, "Probability parameter", theta, 0.0, 1.0);
      check_consistent_sizes(function, 
                             "Successes variable", n,
                             "Population size parameter", N, 
                             "Probability parameter", theta);
                             
          
      // Wrap arguments in vector views
      VectorView<const T_n> n_vec(n);
      VectorView<const T_N> N_vec(N);
      VectorView<const T_prob> theta_vec(theta);
      size_t size = max_size(n, N, theta);
          
      // Compute vectorized CDF and gradient
      using stan::math::value_of;
      using stan::math::inc_beta;
      using stan::math::lbeta;
      using std::exp;
      using std::pow;
          
      agrad::OperandsAndPartials<T_prob> operands_and_partials(theta);
          
      // Explicit return for extreme values
      // The gradients are technically ill-defined, but treated as zero
      for (size_t i = 0; i < stan::length(n); i++) {
        if (value_of(n_vec[i]) < 0) 
          return operands_and_partials.to_var(0.0,theta);
      }
        
      for (size_t i = 0; i < size; i++) {
              
        // Explicit results for extreme values
        // The gradients are technically ill-defined, but treated as zero
        if (value_of(n_vec[i]) >= value_of(N_vec[i])) {
          continue;
        }
          
        const T_partials_return n_dbl = value_of(n_vec[i]);
        const T_partials_return N_dbl = value_of(N_vec[i]);
        const T_partials_return theta_dbl = value_of(theta_vec[i]);
        const T_partials_return betafunc = exp(lbeta(N_dbl-n_dbl,n_dbl+1));
        const T_partials_return Pi = inc_beta(N_dbl - n_dbl, n_dbl + 1, 
                                              1 - theta_dbl);
          
        P *= Pi;

        if (!is_constant_struct<T_prob>::value)
          operands_and_partials.d_x1[i] -= pow(theta_dbl,n_dbl)
            * pow(1-theta_dbl,N_dbl-n_dbl-1) / betafunc / Pi;
      }
          
      if (!is_constant_struct<T_prob>::value) {
        for(size_t i = 0; i < stan::length(theta); ++i)
          operands_and_partials.d_x1[i] *= P;
      }
          
      return operands_and_partials.to_var(P,theta);
        
    }