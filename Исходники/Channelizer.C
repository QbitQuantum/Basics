// ---------------------------------------------------------------------------
//	channelize (one Partial)
// ---------------------------------------------------------------------------
//!	Label a Partial with the number of the frequency channel corresponding to
//!	the average frequency over all the Partial's Breakpoints.
//!	
//!	\param partial is the Partial to label.
//
void
Channelizer::channelize( Partial & partial ) const
{
    using std::pow;

	debugger << "channelizing Partial with " << partial.numBreakpoints() << " Breakpoints" << endl;
			
	//	compute an amplitude-weighted average channel
	//	label for each Partial:
	//double ampsum = 0.;
	double weightedlabel = 0.;
	Partial::const_iterator bp;
	for ( bp = partial.begin(); bp != partial.end(); ++bp )
	{
				
		double f = bp.breakpoint().frequency();
		double t = bp.time();
		
        double weight = 1;
        if ( 0 != _ampWeighting )
        {
            //  This used to be an amplitude-weighted avg, but for many sounds, 
            //  particularly those for which the weighted avg would be very
            //  different from the simple avg, the amplitude-weighted avg
            //  emphasized the part of the sound in which the frequency estimates
            //  are least reliable (e.g. a piano tone). The unweighted 
            //  average should give more intuitive results in most cases.

            //	use sinusoidal amplitude:
            double a = bp.breakpoint().amplitude() * std::sqrt( 1. - bp.breakpoint().bandwidth() );                
            weight = pow( a, _ampWeighting );
        }
        
        weightedlabel += weight * computeFractionalChannelNumber( t, f );
	}
	
	int label = 0;
	if ( 0 < partial.numBreakpoints() ) //  should always be the case
	{        
		label = (int)((weightedlabel / partial.numBreakpoints()) + 0.5);
	}
	Assert( label >= 0 );
			
	//	assign label, and remember it, but
	//	only if it is a valid (positive) 
	//	distillation label:
	partial.setLabel( label );

}