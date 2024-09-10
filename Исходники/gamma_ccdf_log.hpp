    typename return_type<T_y, T_shape, T_inv_scale>::type
    gamma_ccdf_log(const T_y& y, const T_shape& alpha,
                   const T_inv_scale& beta) {
      if (!(stan::length(y) && stan::length(alpha) && stan::length(beta)))
        return 0.0;

      typedef typename stan::partials_return_type<T_y, T_shape,
                                                  T_inv_scale>::type
        T_partials_return;

      static const char* function("gamma_ccdf_log");

      using boost::math::tools::promote_args;
      using std::exp;

      T_partials_return P(0.0);

      check_positive_finite(function, "Shape parameter", alpha);
      check_positive_finite(function, "Scale parameter", beta);
      check_not_nan(function, "Random variable", y);
      check_nonnegative(function, "Random variable", y);
      check_consistent_sizes(function,
                             "Random variable", y,
                             "Shape parameter", alpha,
                             "Scale Parameter", beta);

      VectorView<const T_y> y_vec(y);
      VectorView<const T_shape> alpha_vec(alpha);
      VectorView<const T_inv_scale> beta_vec(beta);
      size_t N = max_size(y, alpha, beta);

      OperandsAndPartials<T_y, T_shape, T_inv_scale>
        operands_and_partials(y, alpha, beta);

      // Explicit return for extreme values
      // The gradients are technically ill-defined, but treated as zero
      for (size_t i = 0; i < stan::length(y); i++) {
        if (value_of(y_vec[i]) == 0)
          return operands_and_partials.value(0.0);
      }

      using boost::math::tgamma;
      using std::exp;
      using std::pow;
      using std::log;

      VectorBuilder<!is_constant_struct<T_shape>::value,
                    T_partials_return, T_shape> gamma_vec(stan::length(alpha));
      VectorBuilder<!is_constant_struct<T_shape>::value,
                    T_partials_return, T_shape>
        digamma_vec(stan::length(alpha));

      if (!is_constant_struct<T_shape>::value) {
        for (size_t i = 0; i < stan::length(alpha); i++) {
          const T_partials_return alpha_dbl = value_of(alpha_vec[i]);
          gamma_vec[i] = tgamma(alpha_dbl);
          digamma_vec[i] = digamma(alpha_dbl);
        }
      }

      for (size_t n = 0; n < N; n++) {
        // Explicit results for extreme values
        // The gradients are technically ill-defined, but treated as zero
        if (value_of(y_vec[n]) == std::numeric_limits<double>::infinity())
          return operands_and_partials.value(negative_infinity());

        const T_partials_return y_dbl = value_of(y_vec[n]);
        const T_partials_return alpha_dbl = value_of(alpha_vec[n]);
        const T_partials_return beta_dbl = value_of(beta_vec[n]);

        const T_partials_return Pn = gamma_q(alpha_dbl, beta_dbl * y_dbl);

        P += log(Pn);

        if (!is_constant_struct<T_y>::value)
          operands_and_partials.d_x1[n] -= beta_dbl * exp(-beta_dbl * y_dbl)
            * pow(beta_dbl * y_dbl, alpha_dbl-1) / tgamma(alpha_dbl) / Pn;
        if (!is_constant_struct<T_shape>::value)
          operands_and_partials.d_x2[n]
            += grad_reg_inc_gamma(alpha_dbl, beta_dbl
                                  * y_dbl, gamma_vec[n],
                                  digamma_vec[n]) / Pn;
        if (!is_constant_struct<T_inv_scale>::value)
          operands_and_partials.d_x3[n] -= y_dbl * exp(-beta_dbl * y_dbl)
            * pow(beta_dbl * y_dbl, alpha_dbl-1) / tgamma(alpha_dbl) / Pn;
      }
      return operands_and_partials.value(P);
    }