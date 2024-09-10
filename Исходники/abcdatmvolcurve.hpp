 inline Volatility AbcdAtmVolCurve::atmVolImpl(Time t) const {
     calculate();
     return k(t) * interpolation_->operator() (t, true);
 }