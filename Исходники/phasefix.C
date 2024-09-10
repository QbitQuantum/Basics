// ---------------------------------------------------------------------------
//	phaseTravel
//
//	Compute the sinusoidal phase travel between two Breakpoints.
//	Return the total unwrapped phase travel.
//
static double phaseTravel( Partial::const_iterator bp0, Partial::const_iterator bp1 )
{
	return phaseTravel( bp0.breakpoint(), bp1.breakpoint(), 
	                    bp1.time() - bp0.time() );
	/*
	double f0 = bp0->frequency();
	double t0 = bp0.time();
	double f1 = bp1->frequency();
	double t1 = bp1.time();
	double favg = .5 * ( f0 + f1 );
	double dt = t1 - t0;
	return 2 * Pi * favg * dt;
	*/
}