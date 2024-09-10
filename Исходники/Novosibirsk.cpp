double Novosibirsk::Normalisation(PhaseSpaceBoundary * boundary)
{
	(void) boundary;
	
	// Get the physics parameters
	width = allParameters.GetPhysicsParameter( widthName )->GetValue();
	peak  = allParameters.GetPhysicsParameter( peakName )->GetValue();
	tail  = allParameters.GetPhysicsParameter( tailName )->GetValue();

	double tailLog4 = tail * sqrt(log(4.));
	double widthLog4 = width * sqrt(log(4.));
	double _sinh = sinh(tailLog4);
	double _csch = 1./sinh(tailLog4);
	
	double val(0.);

	double xhigh = 0.12;
	double xlow = 0.;
	
	//cout << - width*tail*sqrt(TMath::Pi()*log(2.))*_csch*erf( ( tail*tail - log( (xhigh - peak)*_sinh/widthLog4 + 1. ) ) / (sqrt(2.)*tail) ) << endl;
	//cout << + width*tail*sqrt(TMath::Pi()*log(2.))*_csch*erf( ( tail*tail - log( (xlow  - peak)*_sinh/widthLog4 + 1. ) ) / (sqrt(2.)*tail) ) << endl;

	val = - width*tail*sqrt(TMath::Pi()*log(2.))*_csch*erf( ( tail*tail - log( (xhigh - peak)*_sinh/widthLog4 + 1. ) ) / (sqrt(2.)*tail) );
	      //+ width*tail*sqrt(TMath::Pi()*log(2.))*_csch*erf( ( tail*tail - log( (xlow  - peak)*_sinh/widthLog4 + 1. ) ) / (sqrt(2.)*tail) );

	return 2.*val;
}