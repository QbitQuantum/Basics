 /**
  * @return \e J<sub>n</sub> the dynamical form factors of the ellipsoid.
  *
  * If \e n = 2 (the default), this is the value of <i>J</i><sub>2</sub>
  * used in the constructor.  Otherwise it is the zonal coefficient of the
  * Legendre harmonic sum of the normal gravitational potential.  Note that
  * \e J<sub>n</sub> = 0 if \e n is odd.  In most gravity applications,
  * fully normalized Legendre functions are used and the corresponding
  * coefficient is <i>C</i><sub><i>n</i>0</sub> = &minus;\e J<sub>n</sub> /
  * sqrt(2 \e n + 1).
  **********************************************************************/
 Math::real DynamicalFormFactor(int n = 2) const throw()
 { return Init() ? ( n == 2 ? _J2 : Jn(n)) : Math::NaN<real>(); }