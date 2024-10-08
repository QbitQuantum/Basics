    typename return_type<T_y, T_dof, T_loc, T_scale>::type
    student_t_cdf_log(const T_y& y, const T_dof& nu, const T_loc& mu,
                      const T_scale& sigma) {
      typedef typename
        stan::partials_return_type<T_y, T_dof, T_loc, T_scale>::type
        T_partials_return;

      // Size checks
      if (!(stan::length(y) && stan::length(nu) && stan::length(mu)
            && stan::length(sigma)))
        return 0.0;

      static const char* function("stan::math::student_t_cdf_log");

      using stan::math::check_positive_finite;
      using stan::math::check_finite;
      using stan::math::check_not_nan;
      using stan::math::check_consistent_sizes;
      using stan::math::value_of;
      using std::exp;

      T_partials_return P(0.0);

      check_not_nan(function, "Random variable", y);
      check_positive_finite(function, "Degrees of freedom parameter", nu);
      check_finite(function, "Location parameter", mu);
      check_positive_finite(function, "Scale parameter", sigma);

      // Wrap arguments in vectors
      VectorView<const T_y> y_vec(y);
      VectorView<const T_dof> nu_vec(nu);
      VectorView<const T_loc> mu_vec(mu);
      VectorView<const T_scale> sigma_vec(sigma);
      size_t N = max_size(y, nu, mu, sigma);

      OperandsAndPartials<T_y, T_dof, T_loc, T_scale>
        operands_and_partials(y, nu, mu, sigma);

      // Explicit return for extreme values
      // The gradients are technically ill-defined, but treated as zero
      for (size_t i = 0; i < stan::length(y); i++) {
        if (value_of(y_vec[i]) == -std::numeric_limits<double>::infinity())
          return operands_and_partials.value(stan::math::negative_infinity());
      }

      using stan::math::digamma;
      using stan::math::lbeta;
      using stan::math::inc_beta;
      using std::pow;
      using std::exp;
      using std::log;

      // Cache a few expensive function calls if nu is a parameter
      T_partials_return digammaHalf = 0;

      VectorBuilder<!is_constant_struct<T_dof>::value,
                    T_partials_return, T_dof>
        digamma_vec(stan::length(nu));
      VectorBuilder<!is_constant_struct<T_dof>::value,
                    T_partials_return, T_dof>
        digammaNu_vec(stan::length(nu));
      VectorBuilder<!is_constant_struct<T_dof>::value,
                    T_partials_return, T_dof>
        digammaNuPlusHalf_vec(stan::length(nu));

      if (!is_constant_struct<T_dof>::value) {
        digammaHalf = digamma(0.5);

        for (size_t i = 0; i < stan::length(nu); i++) {
          const T_partials_return nu_dbl = value_of(nu_vec[i]);

          digammaNu_vec[i] = digamma(0.5 * nu_dbl);
          digammaNuPlusHalf_vec[i] = digamma(0.5 + 0.5 * nu_dbl);
        }
      }

      // Compute vectorized cdf_log and gradient
      for (size_t n = 0; n < N; n++) {
        // Explicit results for extreme values
        // The gradients are technically ill-defined, but treated as zero
        if (value_of(y_vec[n]) == std::numeric_limits<double>::infinity()) {
          continue;
        }

        const T_partials_return sigma_inv = 1.0 / value_of(sigma_vec[n]);
        const T_partials_return t = (value_of(y_vec[n]) - value_of(mu_vec[n]))
          * sigma_inv;
        const T_partials_return nu_dbl = value_of(nu_vec[n]);
        const T_partials_return q = nu_dbl / (t * t);
        const T_partials_return r = 1.0 / (1.0 + q);
        const T_partials_return J = 2 * r * r * q / t;
        const T_partials_return betaNuHalf = exp(lbeta(0.5, 0.5 * nu_dbl));
        T_partials_return zJacobian = t > 0 ? - 0.5 : 0.5;

        if (q < 2) {
          T_partials_return z
            = inc_beta(0.5 * nu_dbl, (T_partials_return)0.5, 1.0 - r);
          const T_partials_return Pn = t > 0 ? 1.0 - 0.5 * z : 0.5 * z;
          const T_partials_return d_ibeta = pow(r, -0.5)
            * pow(1.0 - r, 0.5*nu_dbl - 1) / betaNuHalf;

          P += log(Pn);

          if (!is_constant_struct<T_y>::value)
            operands_and_partials.d_x1[n]
              += - zJacobian * d_ibeta * J * sigma_inv / Pn;

          if (!is_constant_struct<T_dof>::value) {
            T_partials_return g1 = 0;
            T_partials_return g2 = 0;

            stan::math::grad_reg_inc_beta(g1, g2, 0.5 * nu_dbl,
                                          (T_partials_return)0.5, 1.0 - r,
                                          digammaNu_vec[n], digammaHalf,
                                          digammaNuPlusHalf_vec[n],
                                          betaNuHalf);

            operands_and_partials.d_x2[n]
              += zJacobian * (d_ibeta * (r / t) * (r / t) + 0.5 * g1) / Pn;
          }

          if (!is_constant_struct<T_loc>::value)
            operands_and_partials.d_x3[n]
              += zJacobian * d_ibeta * J * sigma_inv / Pn;
          if (!is_constant_struct<T_scale>::value)
            operands_and_partials.d_x4[n]
              += zJacobian * d_ibeta * J * sigma_inv * t / Pn;

        } else {
          T_partials_return z = 1.0 - inc_beta((T_partials_return)0.5,
                                               0.5*nu_dbl, r);
          zJacobian *= -1;

          const T_partials_return Pn = t > 0 ? 1.0 - 0.5 * z : 0.5 * z;

          T_partials_return d_ibeta = pow(1.0-r, 0.5*nu_dbl-1) * pow(r, -0.5)
            / betaNuHalf;

          P += log(Pn);

          if (!is_constant_struct<T_y>::value)
            operands_and_partials.d_x1[n]
              += zJacobian * d_ibeta * J * sigma_inv / Pn;

          if (!is_constant_struct<T_dof>::value) {
            T_partials_return g1 = 0;
            T_partials_return g2 = 0;

            stan::math::grad_reg_inc_beta(g1, g2, (T_partials_return)0.5,
                                          0.5 * nu_dbl, r,
                                          digammaHalf, digammaNu_vec[n],
                                          digammaNuPlusHalf_vec[n],
                                          betaNuHalf);

            operands_and_partials.d_x2[n]
              += zJacobian * (- d_ibeta * (r / t) * (r / t) + 0.5 * g2) / Pn;
          }

          if (!is_constant_struct<T_loc>::value)
            operands_and_partials.d_x3[n]
              += - zJacobian * d_ibeta * J * sigma_inv / Pn;
          if (!is_constant_struct<T_scale>::value)
            operands_and_partials.d_x4[n]
              += - zJacobian * d_ibeta * J * sigma_inv * t / Pn;
        }
      }

    return operands_and_partials.value(P);
    }