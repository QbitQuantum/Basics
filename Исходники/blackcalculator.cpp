    void BlackCalculator::initialize(const shared_ptr<StrikedTypePayoff>& p) {
        QL_REQUIRE(strike_>=0.0,
                   "strike (" << strike_ << ") must be non-negative");
        QL_REQUIRE(forward_>0.0,
                   "forward (" << forward_ << ") must be positive");
        //QL_REQUIRE(displacement_>=0.0,
        //           "displacement (" << displacement_ << ") must be non-negative");
        QL_REQUIRE(stdDev_>=0.0,
                   "stdDev (" << stdDev_ << ") must be non-negative");
        QL_REQUIRE(discount_>0.0,
                   "discount (" << discount_ << ") must be positive");

        if (stdDev_>=QL_EPSILON) {
            if (close(strike_, 0.0)) {
                d1_ = QL_MAX_REAL;
                d2_ = QL_MAX_REAL;
                cum_d1_ = 1.0;
                cum_d2_ = 1.0;
                n_d1_ = 0.0;
                n_d2_ = 0.0;
            } else {
                d1_ = std::log(forward_/strike_)/stdDev_ + 0.5*stdDev_;
                d2_ = d1_-stdDev_;
                CumulativeNormalDistribution f;
                cum_d1_ = f(d1_);
                cum_d2_ = f(d2_);
                n_d1_ = f.derivative(d1_);
                n_d2_ = f.derivative(d2_);
            }
        } else {
            if (close(forward_, strike_)) {
                d1_ = 0;
                d2_ = 0;
                cum_d1_ = 0.5;
                cum_d2_ = 0.5;
                n_d1_ = M_SQRT_2 * M_1_SQRTPI;
                n_d2_ = M_SQRT_2 * M_1_SQRTPI;
            } else if (forward_>strike_) {
                d1_ = QL_MAX_REAL;
                d2_ = QL_MAX_REAL;
                cum_d1_ = 1.0;
                cum_d2_ = 1.0;
                n_d1_ = 0.0;
                n_d2_ = 0.0;
            } else {
                d1_ = QL_MIN_REAL;
                d2_ = QL_MIN_REAL;
                cum_d1_ = 0.0;
                cum_d2_ = 0.0;
                n_d1_ = 0.0;
                n_d2_ = 0.0;
            }
        }

        x_ = strike_;
        DxDstrike_ = 1.0;

        // the following one will probably disappear as soon as
        // super-share will be properly handled
        DxDs_ = 0.0;

        // this part is always executed.
        // in case of plain-vanilla payoffs, it is also the only part
        // which is executed.
        switch (p->optionType()) {
          case Option::Call:
            alpha_     =  cum_d1_;//  N(d1)
            DalphaDd1_ =    n_d1_;//  n(d1)
            beta_      = -cum_d2_;// -N(d2)
            DbetaDd2_  = -  n_d2_;// -n(d2)
            break;
          case Option::Put:
            alpha_     = -1.0+cum_d1_;// -N(-d1)
            DalphaDd1_ =        n_d1_;//  n( d1)
            beta_      =  1.0-cum_d2_;//  N(-d2)
            DbetaDd2_  =     -  n_d2_;// -n( d2)
            break;
          default:
            QL_FAIL("invalid option type");
        }

        // now dispatch on type.

        Calculator calc(*this);
        p->accept(calc);
    }