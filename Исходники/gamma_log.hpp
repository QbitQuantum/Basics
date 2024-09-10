    typename return_type<T_y, T_shape, T_inv_scale>::type
    gamma_log(const T_y& y, const T_shape& alpha, const T_inv_scale& beta) {
      static const char* function("gamma_log");
      typedef typename stan::partials_return_type<T_y, T_shape,
                                                  T_inv_scale>::type
        T_partials_return;

      using stan::is_constant_struct;

      if (!(stan::length(y)
            && stan::length(alpha)
            && stan::length(beta)))
        return 0.0;

      T_partials_return logp(0.0);

      check_not_nan(function, "Random variable", y);
      check_positive_finite(function, "Shape parameter", alpha);
      check_positive_finite(function, "Inverse scale parameter", beta);
      check_consistent_sizes(function,
                             "Random variable", y,
                             "Shape parameter", alpha,
                             "Inverse scale parameter", beta);

      if (!include_summand<propto, T_y, T_shape, T_inv_scale>::value)
        return 0.0;

      VectorView<const T_y> y_vec(y);
      VectorView<const T_shape> alpha_vec(alpha);
      VectorView<const T_inv_scale> beta_vec(beta);

      for (size_t n = 0; n < length(y); n++) {
        const T_partials_return y_dbl = value_of(y_vec[n]);
        if (y_dbl < 0)
          return LOG_ZERO;
      }

      size_t N = max_size(y, alpha, beta);
      OperandsAndPartials<T_y, T_shape, T_inv_scale>
        operands_and_partials(y, alpha, beta);

      using boost::math::lgamma;
      using boost::math::digamma;
      using std::log;

      VectorBuilder<include_summand<propto, T_y, T_shape>::value,
                    T_partials_return, T_y> log_y(length(y));
      if (include_summand<propto, T_y, T_shape>::value) {
        for (size_t n = 0; n < length(y); n++) {
          if (value_of(y_vec[n]) > 0)
            log_y[n] = log(value_of(y_vec[n]));
        }
      }

      VectorBuilder<include_summand<propto, T_shape>::value,
                    T_partials_return, T_shape> lgamma_alpha(length(alpha));
      VectorBuilder<!is_constant_struct<T_shape>::value,
                    T_partials_return, T_shape> digamma_alpha(length(alpha));
      for (size_t n = 0; n < length(alpha); n++) {
        if (include_summand<propto, T_shape>::value)
          lgamma_alpha[n] = lgamma(value_of(alpha_vec[n]));
        if (!is_constant_struct<T_shape>::value)
          digamma_alpha[n] = digamma(value_of(alpha_vec[n]));
      }

      VectorBuilder<include_summand<propto, T_shape, T_inv_scale>::value,
                    T_partials_return, T_inv_scale> log_beta(length(beta));
      if (include_summand<propto, T_shape, T_inv_scale>::value) {
        for (size_t n = 0; n < length(beta); n++)
          log_beta[n] = log(value_of(beta_vec[n]));
      }

      for (size_t n = 0; n < N; n++) {
        const T_partials_return y_dbl = value_of(y_vec[n]);
        const T_partials_return alpha_dbl = value_of(alpha_vec[n]);
        const T_partials_return beta_dbl = value_of(beta_vec[n]);

        if (include_summand<propto, T_shape>::value)
          logp -= lgamma_alpha[n];
        if (include_summand<propto, T_shape, T_inv_scale>::value)
          logp += alpha_dbl * log_beta[n];
        if (include_summand<propto, T_y, T_shape>::value)
          logp += (alpha_dbl-1.0) * log_y[n];
        if (include_summand<propto, T_y, T_inv_scale>::value)
          logp -= beta_dbl * y_dbl;

        if (!is_constant_struct<T_y>::value)
          operands_and_partials.d_x1[n] += (alpha_dbl-1)/y_dbl - beta_dbl;
        if (!is_constant_struct<T_shape>::value)
          operands_and_partials.d_x2[n] += -digamma_alpha[n] + log_beta[n]
            + log_y[n];
        if (!is_constant_struct<T_inv_scale>::value)
          operands_and_partials.d_x3[n] += alpha_dbl / beta_dbl - y_dbl;
      }
      return operands_and_partials.value(logp);
    }