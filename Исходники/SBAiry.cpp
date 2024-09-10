 // This is a scale-free version of the Airy radial function.
 // Input radius is in units of lambda/D.  Output normalized
 // to integrate to unity over input units.
 double AiryInfoObs::RadialFunction::operator()(double radius) const
 {
     double nu = radius*M_PI;
     // Taylor expansion of j1(u)/u = 1/2 - 1/16 x^2 + ...
     // We can truncate this to 1/2 when neglected term is less than xvalue_accuracy
     // (relative error, so divide by 1/2)
     // xvalue_accuracy = 1/8 x^2
     const double thresh = sqrt(8.*_gsparams->xvalue_accuracy);
     double xval;
     if (nu < thresh) {
         // lim j1(u)/u = 1/2
         xval =  0.5 * (1.-_obssq);
     } else {
         // See Schroeder eq (10.1.10)
         xval = ( j1(nu) - _obscuration*j1(_obscuration*nu) ) / nu ;
     }
     xval *= xval;
     // Normalize to give unit flux integrated over area.
     xval *= _norm;
     return xval;
 }