    typename return_type<T_y, T_loc, T_scale>::type
    double_exponential_cdf(const T_y& y,
                           const T_loc& mu, const T_scale& sigma) {
      static const char* function("stan::math::double_exponential_cdf");
      typedef typename stan::partials_return_type<T_y, T_loc, T_scale>::type
        T_partials_return;

      // Size checks
      if ( !( stan::length(y) && stan::length(mu)
              && stan::length(sigma) ) )
        return 1.0;

      using stan::math::value_of;
      using stan::math::check_finite;
      using stan::math::check_positive_finite;
      using stan::math::check_not_nan;
      using boost::math::tools::promote_args;
      using std::exp;

      T_partials_return cdf(1.0);

      check_not_nan(function, "Random variable", y);
      check_finite(function, "Location parameter", mu);
      check_positive_finite(function, "Scale parameter", sigma);

      OperandsAndPartials<T_y, T_loc, T_scale>
        operands_and_partials(y, mu, sigma);

      VectorView<const T_y> y_vec(y);
      VectorView<const T_loc> mu_vec(mu);
      VectorView<const T_scale> sigma_vec(sigma);
      size_t N = max_size(y, mu, sigma);

      // cdf
      for (size_t n = 0; n < N; n++) {
        const T_partials_return y_dbl = value_of(y_vec[n]);
        const T_partials_return mu_dbl = value_of(mu_vec[n]);
        const T_partials_return sigma_dbl = value_of(sigma_vec[n]);
        const T_partials_return scaled_diff = (y_dbl - mu_dbl) / (sigma_dbl);
        const T_partials_return exp_scaled_diff = exp(scaled_diff);

        if (y_dbl < mu_dbl)
          cdf *= exp_scaled_diff * 0.5;
        else
          cdf *= 1.0 - 0.5 / exp_scaled_diff;
      }

      // gradients
      for (size_t n = 0; n < N; n++) {
        const T_partials_return y_dbl = value_of(y_vec[n]);
        const T_partials_return mu_dbl = value_of(mu_vec[n]);
        const T_partials_return sigma_dbl = value_of(sigma_vec[n]);
        const T_partials_return scaled_diff = (y_dbl - mu_dbl) / sigma_dbl;
        const T_partials_return exp_scaled_diff = exp(scaled_diff);
        const T_partials_return inv_sigma = 1.0 / sigma_dbl;

        if (y_dbl < mu_dbl) {
          if (!is_constant_struct<T_y>::value)
            operands_and_partials.d_x1[n] += inv_sigma * cdf;
          if (!is_constant_struct<T_loc>::value)
            operands_and_partials.d_x2[n] -= inv_sigma * cdf;
          if (!is_constant_struct<T_scale>::value)
            operands_and_partials.d_x3[n] -= scaled_diff * inv_sigma  * cdf;
        } else {
          const T_partials_return rep_deriv = cdf * inv_sigma
            / (2.0 * exp_scaled_diff - 1.0);
          if (!is_constant_struct<T_y>::value)
            operands_and_partials.d_x1[n] += rep_deriv;
          if (!is_constant_struct<T_loc>::value)
            operands_and_partials.d_x2[n] -= rep_deriv;
          if (!is_constant_struct<T_scale>::value)
            operands_and_partials.d_x3[n] -= rep_deriv * scaled_diff;
        }
      }
      return operands_and_partials.value(cdf);
    }