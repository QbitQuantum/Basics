// ---------------------------------------------------------------------------
//	timeOfPeakEnergy (static helper function)
// ---------------------------------------------------------------------------
//	Return the time at which the given Partial attains its
//	maximum sinusoidal energy.
//
static double timeOfPeakEnergy( const Partial & p )
{
	Partial::const_iterator partialIter = p.begin();
	double maxAmp = 
		partialIter->amplitude() * std::sqrt( 1. - partialIter->bandwidth() );
	double time = partialIter.time();
	
	for ( ++partialIter; partialIter != p.end(); ++partialIter ) 
	{
		double a = partialIter->amplitude() * 
					std::sqrt( 1. - partialIter->bandwidth() );
		if ( a > maxAmp ) 
		{
			maxAmp = a;
			time = partialIter.time();
		}
	}			
	
	return time;
}