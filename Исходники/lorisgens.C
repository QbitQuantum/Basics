// ---------------------------------------------------------------------------
//	apply_fadetime
// ---------------------------------------------------------------------------
//	Fade Partials in and out, if fadetime > 0.
//
static void apply_fadetime( PARTIALS & part, double fadetime )
{
	//	nothing to do if fadetime is zero:
	if (fadetime <= 0.)
		return;
		
	//	iterator over all Partials, adding Breakpoints at both ends:
	PARTIALS::iterator iter;
	for ( iter = part.begin(); iter != part.end(); ++iter )  
	{
		Partial & partial = *iter;
		
		double btime = partial.startTime();	// get start time of partial
	    double etime = partial.endTime();	// get end time of partial

		//	if a fadetime has been specified, introduce zero-amplitude
		//	Breakpoints to fade in and out over fadetime seconds:
		if( fadetime != 0 )
		{
			if ( partial.amplitudeAt(btime) > 0. )
			{
				//	only fade in if starting amplitude is non-zero:
				if( btime > 0. ) 
				{
					//	if the Partial begins after time 0, insert a Breakpoint
					//	of zero amplitude at a time fadetime before the beginning, 
					//	of the Partial, or at zero, whichever is later:
					double t = std::max(btime - fadetime, 0.);
					partial.insert( t, Breakpoint( partial.frequencyAt(t), partial.amplitudeAt(t), 
												   partial.bandwidthAt(t), partial.phaseAt(t)));
				}
				else 
				{
					//	if the Partial begins at time zero, insert the zero-amplitude
					//	Breakpoint at time zero, and make sure that the next Breakpoint
					//	in the Partial is no more than fadetime away from the beginning
					//	of the Partial:
					
					//	find the first Breakpoint later than time 0:
					Partial::iterator pit = partial.begin();
					while (pit.time() < 0.)
						++pit;
					if ( pit.time() > fadetime )
					{
						//	if first Breakpoint afer 0 is later than fadetime, 
						//	insert a Breakpoint at fadetime:
						double t = fadetime;
						partial.insert( t, Breakpoint( partial.frequencyAt(t), partial.amplitudeAt(t), 
													   partial.bandwidthAt(t), partial.phaseAt(t)));
					}
					
					//	insert the zero-amplitude Breakpoint at 0:
					partial.insert( 0, Breakpoint( partial.frequencyAt(0), 0, 
												   partial.bandwidthAt(0), partial.phaseAt(0)));

				}
			}
			
			//	add fadeout Breakpoint at end:
			double t = etime + fadetime;
			partial.insert( t, Breakpoint( partial.frequencyAt(t), 0, 
										   partial.bandwidthAt(t), partial.phaseAt(t)));
		}
	}
	
}