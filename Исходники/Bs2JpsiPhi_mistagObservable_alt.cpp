//..................................
double Bs2JpsiPhi_mistagObservable_alt::timeFactorOdd(  )   const
{
	//if( t < 0.0 ) return 0.0 ;
	double result = 
	( 1.0 - cos(phi_s) ) * expL( ) 
	+ ( 1.0 + cos(phi_s) ) * expH( ) 
	- q() * ( 2.0 * sin(phi_s)   ) * expSin( ) * (1.0 - 2.0*tagFraction) ;
	return result ;
};