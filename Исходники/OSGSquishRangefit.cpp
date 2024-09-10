RangeFit::RangeFit( ColourSet const* colours, int flags ) 
  : ColourFit( colours, flags )
{
	// initialise the metric
	bool perceptual = ( ( m_flags & kColourMetricPerceptual ) != 0 );
	if( perceptual )
		m_metric = Vec3( 0.2126f, 0.7152f, 0.0722f );
	else
		m_metric = Vec3( 1.0f );

	// initialise the best error
	m_besterror = FLT_MAX;

	// cache some values
	int const count = m_colours->GetCount();
	Vec3 const* values = m_colours->GetPoints();
	float const* weights = m_colours->GetWeights();
	
	// get the covariance matrix
	Sym3x3 covariance = ComputeWeightedCovariance( count, values, weights );
	
	// compute the principle component
	Vec3 principle = ComputePrincipleComponent( covariance );

	// get the min and max range as the codebook endpoints
	Vec3 start( 0.0f );
	Vec3 end( 0.0f );
	if( count > 0 )
	{
		float min, max;
		
		// compute the range
		start = end = values[0];
		min = max = Dot( values[0], principle );
		for( int i = 1; i < count; ++i )
		{
			float val = Dot( values[i], principle );
			if( val < min )
			{
				start = values[i];
				min = val;
			}
			else if( val > max )
			{
				end = values[i];
				max = val;
			}
		}
	}
			
	// clamp the output to [0, 1]
	Vec3 const one( 1.0f );
	Vec3 const zero( 0.0f );
	start = Min( one, Max( zero, start ) );
	end = Min( one, Max( zero, end ) );

	// clamp to the grid and save
	Vec3 const grid( 31.0f, 63.0f, 31.0f );
	Vec3 const gridrcp( 1.0f/31.0f, 1.0f/63.0f, 1.0f/31.0f );
	Vec3 const half( 0.5f );
	m_start = Truncate( grid*start + half )*gridrcp;
	m_end = Truncate( grid*end + half )*gridrcp;
}