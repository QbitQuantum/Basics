	Matrix44f Matrix44f::inverted( void )
	{
		Matrix44f m = *this;
		m.invert();
		return m;
	}