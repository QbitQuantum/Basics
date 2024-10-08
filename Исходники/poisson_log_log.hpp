    typename return_type<T_log_rate>::type
    poisson_log_log(const T_n& n, const T_log_rate& alpha) {
      typedef typename stan::partials_return_type<T_n,T_log_rate>::type
        T_partials_return;

      static const char* function("stan::prob::poisson_log_log");
      
      using boost::math::lgamma;
      using stan::math::check_not_nan;
      using stan::math::check_nonnegative;
      using stan::math::value_of;
      using stan::math::check_consistent_sizes;
      using stan::prob::include_summand;
      using std::exp;
      
      // check if any vectors are zero length
      if (!(stan::length(n)
            && stan::length(alpha)))
        return 0.0;

      // set up return value accumulator
      T_partials_return logp(0.0);

      // validate args
      check_nonnegative(function, "Random variable", n);
      check_not_nan(function, "Log rate parameter", alpha);
      check_consistent_sizes(function,
                             "Random variable", n, 
                             "Log rate parameter", alpha);
      
      // check if no variables are involved and prop-to
      if (!include_summand<propto,T_log_rate>::value)
        return 0.0;

      // set up expression templates wrapping scalars/vecs into vector views
      VectorView<const T_n> n_vec(n);
      VectorView<const T_log_rate> alpha_vec(alpha);
      size_t size = max_size(n, alpha);

      // FIXME: first loop size of alpha_vec, second loop if-ed for size==1
      for (size_t i = 0; i < size; i++)
        if (std::numeric_limits<double>::infinity() == alpha_vec[i])
          return LOG_ZERO;
      for (size_t i = 0; i < size; i++)
        if (-std::numeric_limits<double>::infinity() == alpha_vec[i] 
            && n_vec[i] != 0)
          return LOG_ZERO;
      
      // return accumulator with gradients
      agrad::OperandsAndPartials<T_log_rate> operands_and_partials(alpha);

      // FIXME: cache value_of for alpha_vec?  faster if only one?
      VectorBuilder<include_summand<propto,T_log_rate>::value,
                    T_partials_return, T_log_rate>
        exp_alpha(length(alpha));
      for (size_t i = 0; i < length(alpha); i++)
        if (include_summand<propto,T_log_rate>::value)
          exp_alpha[i] = exp(value_of(alpha_vec[i]));

      using stan::math::multiply_log;
      for (size_t i = 0; i < size; i++) {
        if (!(alpha_vec[i] == -std::numeric_limits<double>::infinity() 
              && n_vec[i] == 0)) {
          if (include_summand<propto>::value)
            logp -= lgamma(n_vec[i] + 1.0);
          if (include_summand<propto,T_log_rate>::value)
            logp += n_vec[i] * value_of(alpha_vec[i]) - exp_alpha[i];
        }

        // gradients
        if (!is_constant_struct<T_log_rate>::value)
          operands_and_partials.d_x1[i] += n_vec[i] - exp_alpha[i];
      }
      return operands_and_partials.to_var(logp,alpha);
    }