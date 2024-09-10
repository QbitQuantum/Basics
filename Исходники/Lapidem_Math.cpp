float Lapidem_Math::AngleBetweenVectors( tVector2D _v1, tVector2D _v2 )
{
	float fDot( DotProduct( _v1, _v2 ) );
	float fLength( Vector2DLength( _v1 ) * Vector2DLength( _v2 ) );

	if( 0.0f == fLength )
		return 0.0f;

	float fAngle( acos( fDot / fLength ) );

	if( _isnan( fAngle ) )
		return 0.0f;

	return fAngle;
}