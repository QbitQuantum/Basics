  result_type operator()(Engine& eng)
  {
#ifndef BOOST_NO_STDC_NAMESPACE
    // allow for Koenig lookup
    using std::tan; using std::sqrt; using std::exp; using std::log;
    using std::pow;
#endif
    if(_alpha == result_type(1)) {
      return _exp(eng);
    } else if(_alpha > result_type(1)) {
      // Can we have a boost::mathconst please?
      const result_type pi = result_type(3.14159265358979323846);
      for(;;) {
        result_type y = tan(pi * eng());
        result_type x = sqrt(result_type(2)*_alpha-result_type(1))*y
          + _alpha-result_type(1);
        if(x <= result_type(0))
          continue;
        if(eng() >
           (result_type(1)+y*y) * exp((_alpha-result_type(1))
                                        *log(x/(_alpha-result_type(1)))
                                        - sqrt(result_type(2)*_alpha
                                               -result_type(1))*y))
          continue;
        return x;
      }
    } else /* alpha < 1.0 */ {
      for(;;) {
        result_type u = eng();
        result_type y = _exp(eng);
        result_type x, q;
        if(u < _p) {
          x = exp(-y/_alpha);
          q = _p*exp(-x);
        } else {
          x = result_type(1)+y;
          q = _p + (result_type(1)-_p) * pow(x, _alpha-result_type(1));
        }
        if(u >= q)
          continue;
        return x;
      }
    }
  }