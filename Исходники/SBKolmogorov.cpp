 double operator()(double k) const
 { return k*std::exp(-std::pow(k, 5./3.))*j0(k*_r); }