// -1 to 1 range on panelMatrix, returns -2,-2 if looking away from the panel
Vector2f	GazeCoordinatesOnPanel( const Matrix4f & viewMatrix, const Matrix4f panelMatrix, const bool floatingPanel )
{
	// project along -Z in the viewMatrix onto the Z = 0 plane of activityMatrix

	const Vector3f viewForward = MatrixForward( viewMatrix ).Normalized();

	Vector3f panelForward;
	float approach;
	if ( floatingPanel )
	{
		Matrix4f mat = panelMatrix;
		mat.SetTranslation( Vector3f( 0.0f ) );
		panelForward = mat.Transform( Vector3f( 0.0f, 0.0f, 1.0f ) ).Normalized();
		approach = viewForward.Dot( panelForward );
		if ( approach >= -0.1 )
		{	// looking away
			return Vector2f( -2.0f, -2.0f );
		}
	}
	else
	{
		panelForward = -MatrixForward( panelMatrix ).Normalized();
		approach = viewForward.Dot( panelForward );
		if ( approach <= 0.1 )
		{	// looking away
			return Vector2f( -2.0f, -2.0f );
		}
	}

	const Matrix4f panelInvert = panelMatrix.Inverted();
	const Matrix4f viewInvert = viewMatrix.Inverted();

	const Vector3f viewOrigin = viewInvert.Transform( Vector3f( 0.0f ) );
	const Vector3f panelOrigin = MatrixOrigin( panelMatrix );

	// Should we disallow using panels from behind?
	const float d = panelOrigin.Dot( panelForward );
	const float t = -( viewOrigin.Dot( panelForward ) + d ) / approach;

	const Vector3f impact = viewOrigin + viewForward * t;
	const Vector3f localCoordinate = panelInvert.Transform( impact );

	return Vector2f( localCoordinate.x, localCoordinate.y );
}