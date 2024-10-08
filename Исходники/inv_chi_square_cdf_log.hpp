    typename return_type<T_y, T_dof>::type
    inv_chi_square_cdf_log(const T_y& y, const T_dof& nu) {
      typedef typename stan::partials_return_type<T_y, T_dof>::type
        T_partials_return;

      // Size checks
      if ( !( stan::length(y) && stan::length(nu) ) ) return 0.0;

      // Error checks
      static const char* function("stan::math::inv_chi_square_cdf_log");

      using stan::math::check_positive_finite;
      using stan::math::check_not_nan;
      using stan::math::check_consistent_sizes;
      using stan::math::check_nonnegative;
      using boost::math::tools::promote_args;
      using stan::math::value_of;
      using std::exp;

      T_partials_return P(0.0);

      check_positive_finite(function, "Degrees of freedom parameter", nu);
      check_not_nan(function, "Random variable", y);
      check_nonnegative(function, "Random variable", y);
      check_consistent_sizes(function,
                             "Random variable", y,
                             "Degrees of freedom parameter", nu);

      // Wrap arguments in vectors
      VectorView<const T_y> y_vec(y);
      VectorView<const T_dof> nu_vec(nu);
      size_t N = max_size(y, nu);

      OperandsAndPartials<T_y, T_dof> operands_and_partials(y, nu);

      // Explicit return for extreme values
      // The gradients are technically ill-defined, but treated as zero

      for (size_t i = 0; i < stan::length(y); i++)
        if (value_of(y_vec[i]) == 0)
          return operands_and_partials.to_var(stan::math::negative_infinity(),
                                              y, nu);

      // Compute cdf_log and its gradients
      using stan::math::gamma_q;
      using stan::math::digamma;
      using boost::math::tgamma;
      using std::exp;
      using std::pow;
      using std::log;

      // Cache a few expensive function calls if nu is a parameter
      VectorBuilder<!is_constant_struct<T_dof>::value,
                    T_partials_return, T_dof> gamma_vec(stan::length(nu));
      VectorBuilder<!is_constant_struct<T_dof>::value,
                    T_partials_return, T_dof> digamma_vec(stan::length(nu));

      if (!is_constant_struct<T_dof>::value)  {
        for (size_t i = 0; i < stan::length(nu); i++) {
          const T_partials_return nu_dbl = value_of(nu_vec[i]);
          gamma_vec[i] = tgamma(0.5 * nu_dbl);
          digamma_vec[i] = digamma(0.5 * nu_dbl);
        }
      }

      // Compute vectorized cdf_log and gradient
      for (size_t n = 0; n < N; n++) {
        // Explicit results for extreme values
        // The gradients are technically ill-defined, but treated as zero
        if (value_of(y_vec[n]) == std::numeric_limits<double>::infinity()) {
          continue;
        }

        // Pull out values
        const T_partials_return y_dbl = value_of(y_vec[n]);
        const T_partials_return y_inv_dbl = 1.0 / y_dbl;
        const T_partials_return nu_dbl = value_of(nu_vec[n]);

        // Compute
        const T_partials_return Pn = gamma_q(0.5 * nu_dbl, 0.5 * y_inv_dbl);

        P += log(Pn);

        if (!is_constant_struct<T_y>::value)
          operands_and_partials.d_x1[n] += 0.5 * y_inv_dbl * y_inv_dbl
            * exp(-0.5*y_inv_dbl) * pow(0.5*y_inv_dbl, 0.5*nu_dbl-1)
            / tgamma(0.5*nu_dbl) / Pn;
        if (!is_constant_struct<T_dof>::value)
          operands_and_partials.d_x2[n]
            += 0.5 * stan::math::grad_reg_inc_gamma(0.5 * nu_dbl,
                                                    0.5 * y_inv_dbl,
                                                    gamma_vec[n],
                                                    digamma_vec[n]) / Pn;
      }

      return operands_and_partials.to_var(P, y, nu);
    }