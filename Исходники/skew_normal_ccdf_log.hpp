    typename return_type<T_y, T_loc, T_scale, T_shape>::type
    skew_normal_ccdf_log(const T_y& y, const T_loc& mu, const T_scale& sigma,
                         const T_shape& alpha) {
      static const char* function("stan::math::skew_normal_ccdf_log");
      typedef typename stan::partials_return_type<T_y, T_loc, T_scale,
                                                  T_shape>::type
        T_partials_return;

      using stan::math::check_positive;
      using stan::math::check_finite;
      using stan::math::check_not_nan;
      using stan::math::check_consistent_sizes;
      using stan::math::owens_t;
      using stan::math::value_of;

      T_partials_return ccdf_log(0.0);

      // check if any vectors are zero length
      if (!(stan::length(y)
            && stan::length(mu)
            && stan::length(sigma)
            && stan::length(alpha)))
        return ccdf_log;

      check_not_nan(function, "Random variable", y);
      check_finite(function, "Location parameter", mu);
      check_not_nan(function, "Scale parameter", sigma);
      check_positive(function, "Scale parameter", sigma);
      check_finite(function, "Shape parameter", alpha);
      check_not_nan(function, "Shape parameter", alpha);
      check_consistent_sizes(function,
                             "Random variable", y,
                             "Location parameter", mu,
                             "Scale parameter", sigma,
                             "Shape paramter", alpha);

      OperandsAndPartials<T_y, T_loc, T_scale, T_shape>
        operands_and_partials(y, mu, sigma, alpha);

      using stan::math::SQRT_2;
      using stan::math::pi;
      using std::log;
      using std::exp;

      VectorView<const T_y> y_vec(y);
      VectorView<const T_loc> mu_vec(mu);
      VectorView<const T_scale> sigma_vec(sigma);
      VectorView<const T_shape> alpha_vec(alpha);
      size_t N = max_size(y, mu, sigma, alpha);
      const double SQRT_TWO_OVER_PI = std::sqrt(2.0 / stan::math::pi());

      for (size_t n = 0; n < N; n++) {
        const T_partials_return y_dbl = value_of(y_vec[n]);
        const T_partials_return mu_dbl = value_of(mu_vec[n]);
        const T_partials_return sigma_dbl = value_of(sigma_vec[n]);
        const T_partials_return alpha_dbl = value_of(alpha_vec[n]);
        const T_partials_return alpha_dbl_sq = alpha_dbl * alpha_dbl;
        const T_partials_return diff = (y_dbl - mu_dbl) / sigma_dbl;
        const T_partials_return diff_sq = diff * diff;
        const T_partials_return scaled_diff =  diff / SQRT_2;
        const T_partials_return scaled_diff_sq =  diff_sq * 0.5;
        const T_partials_return ccdf_log_ = 1.0 - 0.5 * erfc(-scaled_diff)
          + 2 * owens_t(diff, alpha_dbl);

        // ccdf_log
        ccdf_log += log(ccdf_log_);

        // gradients
        const T_partials_return deriv_erfc = SQRT_TWO_OVER_PI * 0.5
          * exp(-scaled_diff_sq) / sigma_dbl;
        const T_partials_return deriv_owens = erf(alpha_dbl * scaled_diff)
          * exp(-scaled_diff_sq) / SQRT_TWO_OVER_PI / (-2.0 * pi()) / sigma_dbl;
        const T_partials_return rep_deriv = (-2.0 * deriv_owens + deriv_erfc)
          / ccdf_log_;

        if (!is_constant_struct<T_y>::value)
          operands_and_partials.d_x1[n] -= rep_deriv;
        if (!is_constant_struct<T_loc>::value)
          operands_and_partials.d_x2[n] += rep_deriv;
        if (!is_constant_struct<T_scale>::value)
          operands_and_partials.d_x3[n] += rep_deriv * diff;
        if (!is_constant_struct<T_shape>::value)
          operands_and_partials.d_x4[n] -= -2.0 * exp(-0.5 * diff_sq
                                                      * (1.0 + alpha_dbl_sq))
            / ((1 + alpha_dbl_sq) * 2.0 * pi()) / ccdf_log_;
      }

      return operands_and_partials.to_var(ccdf_log, y, mu, sigma, alpha);
    }