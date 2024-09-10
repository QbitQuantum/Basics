double
doubleRem(double dividend, double divisor) {
    double res;

    if (!_finite(divisor)) {
	if (_isnan(divisor))
	    return divisor;
	if (_finite(dividend))
	    return dividend;
    }
    res = fmod(dividend, divisor);
    /* With MSVC, "res == 0" succeeds when res is NaN. */
    if (!_isnan(res) && res == 0) {  /*MSFT fmod doesn't do -0.0 right*/
      return _copysign(0.0,dividend);
    } else {
      return res;
    }
}