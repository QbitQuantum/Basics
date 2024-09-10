returnValue VariablesGrid::getIntegral(	InterpolationMode mode,
										DVector& value
										) const
{
	value.setZero();
	
	switch( mode )
	{
		case IM_CONSTANT:
			for( uint i=0; i<getNumIntervals( ); ++i )
			{
				for( uint j=0; j<getNumValues( ); ++j )
				{
					//value(j) += ( getIntervalLength( i ) / getIntervalLength( ) ) * operator()( i,j );
					value(j) +=  getIntervalLength( i ) * operator()( i,j );
				}
			}
			break;

		case IM_LINEAR:
			for( uint i=0; i<getNumIntervals( ); ++i )
			{
				for( uint j=0; j<getNumValues( ); ++j )
				{
					//value(j) += ( getIntervalLength( i ) / getIntervalLength( ) ) * ( operator()( i,j ) + operator()( i+1,j ) ) / 2.0;
					value(j) += getIntervalLength( i ) * ( operator()( i,j ) + operator()( i+1,j ) ) / 2.0;
				}
			}
			break;
		
		default: 
			return ACADOERROR( RET_NOT_YET_IMPLEMENTED );
	}

	return SUCCESSFUL_RETURN;
}