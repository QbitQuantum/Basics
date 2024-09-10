 inline Real operator() (Real t, Real x, Real y, Real z, UInt /*ic*/ = 0) const
 {
     return exp (-sin (Pi / 2 * t) ) * (x + y + z);
 }