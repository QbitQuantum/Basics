// get value for the leading order exponential SF 
double EvtPFermi::getSFBLNP(const double &what)
{
  double SF;
  double massB = 5.2792; 
  

  if ( what      > massB )   return 0;
  if ( what < 0 ) return 0; 

#if defined(__SUNPRO_CC)
  report(Severity::Error,"EvtGen") << "The tgamma function is not available on this platform\n";
  report(Severity::Error,"EvtGen") <<"Presumably, you are getting the wrong answer, so I abort..";
  ::abort();
#else
  SF = pow(_b,_b)/(tgamma(_b)*_Lambda)*pow(what/_Lambda,_b-1)*exp(-_b*what/_Lambda); 
#endif
  
  return SF;
}