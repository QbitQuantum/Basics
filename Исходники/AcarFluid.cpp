inline int FloatToInt( double x ) 
{
	return _mm_cvttsd_si32( _mm_load_sd( &x) );
}