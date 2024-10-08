    typename return_type<T_size1,T_size2>::type
    beta_binomial_ccdf_log(const T_n& n, const T_N& N, const T_size1& alpha, 
                           const T_size2& beta) {
      static const char* function("stan::prob::beta_binomial_ccdf_log");
      typedef typename stan::partials_return_type<T_n,T_N,T_size1,
                                                  T_size2>::type 
        T_partials_return;

      using stan::math::check_positive_finite;
      using stan::math::check_nonnegative;
      using stan::math::value_of;
      using stan::math::check_consistent_sizes;
      using stan::prob::include_summand;
          
      // Ensure non-zero argument lengths
      if (!(stan::length(n) && stan::length(N) && stan::length(alpha) 
            && stan::length(beta)))
        return 0.0;
          
      T_partials_return P(0.0);
          
      // Validate arguments
      check_nonnegative(function, "Population size parameter", N);
      check_positive_finite(function, "First prior sample size parameter", alpha);
      check_positive_finite(function, "Second prior sample size parameter", beta);
      check_consistent_sizes(function,
                             "Successes variable", n, 
                             "Population size parameter", N, 
                             "First prior sample size parameter", alpha, 
                             "Second prior sample size parameter", beta);

      // Wrap arguments in vector views
      VectorView<const T_n> n_vec(n);
      VectorView<const T_N> N_vec(N);
      VectorView<const T_size1> alpha_vec(alpha);
      VectorView<const T_size2> beta_vec(beta);
      size_t size = max_size(n, N, alpha, beta);
          
      // Compute vectorized cdf_log and gradient
      using stan::math::lgamma;
      using stan::math::lbeta;
      using stan::math::digamma;
      using std::exp;

      agrad::OperandsAndPartials<T_size1, T_size2> 
        operands_and_partials(alpha, beta);
          
      // Explicit return for extreme values
      // The gradients are technically ill-defined, but treated as neg infinity
      for (size_t i = 0; i < stan::length(n); i++) {
        if (value_of(n_vec[i]) <= 0) 
          return operands_and_partials.to_var(0.0,alpha,beta);
      }
          
      for (size_t i = 0; i < size; i++) {
        // Explicit results for extreme values
        // The gradients are technically ill-defined, but treated as zero
        if (value_of(n_vec[i]) >= value_of(N_vec[i])) {
          return operands_and_partials.to_var(stan::math::negative_infinity(),
                                              alpha,beta);
        }
              
        const T_partials_return n_dbl = value_of(n_vec[i]);
        const T_partials_return N_dbl = value_of(N_vec[i]);
        const T_partials_return alpha_dbl = value_of(alpha_vec[i]);
        const T_partials_return beta_dbl = value_of(beta_vec[i]);
              
        const T_partials_return mu = alpha_dbl + n_dbl + 1;
        const T_partials_return nu = beta_dbl + N_dbl - n_dbl - 1;
              
        const T_partials_return F = stan::math::F32((T_partials_return)1, mu, 
                                                    -N_dbl + n_dbl + 1, 
                                                    n_dbl + 2, 1 - nu, 
                                                    (T_partials_return)1);
              
        T_partials_return C = lgamma(nu) - lgamma(N_dbl - n_dbl);
        C += lgamma(mu) - lgamma(n_dbl + 2);
        C += lgamma(N_dbl + 2) - lgamma(N_dbl + alpha_dbl + beta_dbl);
        C = exp(C);
                
        C *= F / exp(lbeta(alpha_dbl, beta_dbl));
        C /= N_dbl + 1;
              
        const T_partials_return Pi = C;
              
        P += log(Pi);
              
        T_partials_return dF[6];
        T_partials_return digammaOne = 0;
        T_partials_return digammaTwo = 0;
              
        if (contains_nonconstant_struct<T_size1,T_size2>::value) {
          digammaOne = digamma(mu + nu);
          digammaTwo = digamma(alpha_dbl + beta_dbl);
          stan::math::grad_F32(dF, (T_partials_return)1, mu, -N_dbl + n_dbl + 1,
                               n_dbl + 2, 1 - nu, (T_partials_return)1);
        }
        if (!is_constant_struct<T_size1>::value) {
          const T_partials_return g 
            = - C * (digamma(mu) - digammaOne + dF[1] / F
                     - digamma(alpha_dbl) + digammaTwo);
          operands_and_partials.d_x1[i] -= g / Pi;
        }
        if (!is_constant_struct<T_size2>::value) {
          const T_partials_return g 
            = - C * (digamma(nu) - digammaOne - dF[4] / F - digamma(beta_dbl) 
                     + digammaTwo);
          operands_and_partials.d_x2[i] -= g / Pi;
        }
      }
          
      return operands_and_partials.to_var(P,alpha,beta);
    }