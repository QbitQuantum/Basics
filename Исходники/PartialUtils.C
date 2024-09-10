// ---------------------------------------------------------------------------
//	NoiseRatioScaler function call operator
// ---------------------------------------------------------------------------
//	Scale the relative noise content of the specified Partial according 
//	to an envelope representing a (time-varying) noise energy 
//	scale value.
//
void 
NoiseRatioScaler::operator()( Partial & p ) const
{
	for ( Partial::iterator pos = p.begin(); pos != p.end(); ++pos ) 
	{		
		//	compute new bandwidth value:
		double bw = pos.breakpoint().bandwidth();
		if ( bw < 1. ) 
		{
			double ratio = bw  / (1. - bw);
			ratio *= env->valueAt( pos.time() );
			bw = ratio / ( 1. + ratio );
		}
		else 
		{
			bw = 1.;
		}		
		pos.breakpoint().setBandwidth( bw );
	}	
}