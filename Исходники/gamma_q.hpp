    inline
    fvar<T>
    gamma_q(const fvar<T>& x1, const double x2){
      using stan::math::gamma_q;
      using std::log;
      using std::exp;
      using std::pow;
      using std::fabs;
      using boost::math::tgamma;
      using boost::math::digamma;

      T u = gamma_q(x1.val_, x2);
      
      T S = 0;
      double s = 1;
      double l = log(x2);
      T g = tgamma(x1.val_);
      T dig = digamma(x1.val_);
      
      int k = 0;
      T delta = s / (x1.val_ * x1.val_);
      
      while (fabs(delta) > 1e-6) {
        S += delta;
        ++k;
        s *= -x2 / k;
        delta = s / ((k + x1.val_) * (k + x1.val_));
      }
      
      T der1 = (1.0 - u) * ( dig - l ) + exp( x1.val_ * l ) * S / g;
      
      return fvar<T>(u, x1.d_ * der1);
    }