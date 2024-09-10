// this is the factor which makes a unnormalized primitive spherical
// gauss orbital, i.e.   S_lm(r)*exp(-zeta r^2),'s self overlap one.
// note that the angular normalization factors are already absorbed in the S_lm
// (S_00 = 1). This function accounts for the radial part only. See purple
// book sec 6.6.4.
double GaussNormalizationSpher( double Zeta, int l )
{
   // purple book (6.6.14). (last 4*pi/(2*l+1) is for factor between
   // Ylm and Slm)
   using std::pow; using std::sqrt;
   return 2.0 * pow( 2.0 * Zeta, 0.75 ) / pow(M_PI,0.25) *
      sqrt( (1 << l) / static_cast<double>( DoubleFact(2*l+1) ) ) *
      intpow( sqrt( 2.0 * Zeta ), l ) / sqrt(4*M_PI/(2*l+1));
}