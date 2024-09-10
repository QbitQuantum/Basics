// ---------------------------------------------------------------------------
//	parametersAt
// ---------------------------------------------------------------------------
//!	Return the interpolated parameters of this Partial at
//!	the specified time, same as building a Breakpoint from
//!	the results of frequencyAt, ampitudeAt, bandwidthAt, and
//!	phaseAt, but performs only one Breakpoint envelope search.
//!	Throw an InvalidPartial exception if this Partial has no
//!	Breakpoints. If non-zero fadeTime is specified, then the
//!	amplitude at the ends of the Partial is coomputed using a 
//!	linear fade. The default fadeTime is ShortestSafeFadeTime.
//
Breakpoint
Partial::parametersAt( double time, double fadeTime ) const 
{
	if ( numBreakpoints() == 0 )
	{
		Throw( InvalidPartial, "Tried to interpolate a Partial with no Breakpoints." );
	}
	
	//	findAfter returns the position of the earliest
	//	Breakpoint later than time, or the end
	//	position if no such Breakpoint exists:
	Partial::const_iterator it = findAfter( time );
		
	if ( it == begin() ) 
	{
		//	time is before the onset of the Partial:
		//	frequency is starting frequency, 
		//	amplitude is 0 (or fading), bandwidth is starting 
		//	bandwidth, and phase is rolled back.
		double alpha =  (time < it.time()) ? 0. : 1.;
		if ( fadeTime > 0 )
		{
			//	fade in ampltude if time is before the onset of the Partial:
			alpha = std::max(0., 1. - ((it.time() - time) / fadeTime) );
		}
		double amp = alpha * it.breakpoint().amplitude();

		double dp = 2. * Pi * (it.time() - time) * it.breakpoint().frequency();
		double ph = std::fmod( it.breakpoint().phase() - dp, 2. * Pi);
		
		return Breakpoint( it.breakpoint().frequency(), amp, 
						   it.breakpoint().bandwidth(), ph );
	}
	else if (it == end() ) 
	{
		//	time is past the end of the Partial:
		//	frequency is ending frequency, 
		//	amplitude is 0 (or fading), bandwidth is ending 
		//	bandwidth, and phase is rolled forward.
		--it; 
		
		double alpha =  (time > it.time()) ? 0. : 1.;
		if ( fadeTime > 0 )
		{
			//	fade out ampltude if time is past the end of the Partial:
			alpha = std::max(0., 1. - ((time - it.time()) / fadeTime) );
		}
		double amp = alpha * it.breakpoint().amplitude();

		double dp = 2. * Pi * (time - it.time()) * it.breakpoint().frequency();
		double ph = std::fmod( it.breakpoint().phase() + dp, 2. * Pi );

		return Breakpoint( it.breakpoint().frequency(), amp, 
						   it.breakpoint().bandwidth(), ph );
	}
	else 
	{
	//	interpolate between it and its predeccessor
	//	(we checked already that it is not begin):
		const Breakpoint & hi = it.breakpoint();
		double hitime = it.time();
		const Breakpoint & lo = (--it).breakpoint();
		double lotime = it.time();
		double alpha = (time - lotime) / (hitime - lotime);

		double finterp = ( alpha * hi.frequency() ) + 
						 ( ( 1. - alpha ) * lo.frequency() );

		//	need to keep fmod in here because other stuff 
		//	(Spc export and sdif export, for example) rely 
		//	on it:
		double ph = 0;
		if ( alpha < 0.5 )
		{
			double favg = 0.5 * ( lo.frequency() + finterp );
			double dp = 2. * Pi * (time - lotime) * favg;
			ph = std::fmod( lo.phase() + dp, 2. * Pi );
		}
		else
		{
			double favg = 0.5 * ( hi.frequency() + finterp );
			double dp = 2. * Pi * (hitime - time) * favg;
			ph = std::fmod( hi.phase() - dp, 2. * Pi );
		}

		return Breakpoint( (alpha * hi.frequency()) + ((1. - alpha) * lo.frequency()),
						   (alpha * hi.amplitude()) + ((1. - alpha) * lo.amplitude()),
						   (alpha * hi.bandwidth()) + ((1. - alpha) * lo.bandwidth()),
						   ph );
				
	}
}