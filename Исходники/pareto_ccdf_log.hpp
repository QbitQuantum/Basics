    typename return_type<T_y, T_scale, T_shape>::type
    pareto_ccdf_log(const T_y& y, const T_scale& y_min,
                    const T_shape& alpha) {
      typedef typename stan::partials_return_type<T_y, T_scale, T_shape>::type
        T_partials_return;

      // Size checks
      if ( !( stan::length(y) && stan::length(y_min) && stan::length(alpha) ) )
        return 0.0;

      // Check errors
      static const char* function("stan::math::pareto_ccdf_log");

      using stan::math::check_positive_finite;
      using stan::math::check_not_nan;
      using stan::math::check_greater_or_equal;
      using stan::math::check_consistent_sizes;
      using stan::math::check_nonnegative;
      using stan::math::value_of;
      using std::log;
      using std::exp;

      T_partials_return P(0.0);

      check_not_nan(function, "Random variable", y);
      check_nonnegative(function, "Random variable", y);
      check_positive_finite(function, "Scale parameter", y_min);
      check_positive_finite(function, "Shape parameter", alpha);
      check_consistent_sizes(function,
                             "Random variable", y,
                             "Scale parameter", y_min,
                             "Shape parameter", alpha);

      // Wrap arguments in vectors
      VectorView<const T_y> y_vec(y);
      VectorView<const T_scale> y_min_vec(y_min);
      VectorView<const T_shape> alpha_vec(alpha);
      size_t N = max_size(y, y_min, alpha);

      OperandsAndPartials<T_y, T_scale, T_shape>
        operands_and_partials(y, y_min, alpha);

      // Explicit return for extreme values
      // The gradients are technically ill-defined, but treated as zero

      for (size_t i = 0; i < stan::length(y); i++) {
        if (value_of(y_vec[i]) < value_of(y_min_vec[i]))
          return operands_and_partials.to_var(0.0, y, y_min, alpha);
      }

      // Compute vectorized cdf_log and its gradients

      for (size_t n = 0; n < N; n++) {
        // Explicit results for extreme values
        // The gradients are technically ill-defined, but treated as zero
        if (value_of(y_vec[n]) == std::numeric_limits<double>::infinity()) {
          return operands_and_partials.to_var(stan::math::negative_infinity(),
                                              y, y_min, alpha);
        }

        // Pull out values
        const T_partials_return log_dbl = log(value_of(y_min_vec[n])
                                              / value_of(y_vec[n]));
        const T_partials_return y_min_inv_dbl = 1.0 / value_of(y_min_vec[n]);
        const T_partials_return alpha_dbl = value_of(alpha_vec[n]);

        P += alpha_dbl * log_dbl;

        if (!is_constant_struct<T_y>::value)
          operands_and_partials.d_x1[n] -= alpha_dbl * y_min_inv_dbl
            * exp(log_dbl);
        if (!is_constant_struct<T_scale>::value)
          operands_and_partials.d_x2[n] += alpha_dbl * y_min_inv_dbl;
        if (!is_constant_struct<T_shape>::value)
          operands_and_partials.d_x3[n] += log_dbl;
      }

      return operands_and_partials.to_var(P, y, y_min, alpha);
    }