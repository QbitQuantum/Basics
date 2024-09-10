void OvrGazeCursorLocal::UpdateCursorPositions( Vector4f * positions, Matrix4f const * transforms ) const
{
	OVR_ASSERT( positions != NULL );	

	const int numTrails = TRAIL_GHOSTS<CurrentTransform ? TRAIL_GHOSTS : CurrentTransform;

	// For missing trail transforms, draw degenerate triangles...
	for ( int slice = numTrails; slice < TRAIL_GHOSTS; slice++ )
	{
		for ( int i = 0; i < 4; i++ )
		{
			*( positions++ ) = Vector4f( 0.0f, 0.0f, 0.0f, 0.0f );
		}
	}

	// Transforming on the CPU shouldn't be too painful in this scenario since the vertex count is low
	// and we would be uploading the same amount of data in the form of transforms if we used instancing
	// anyways. So this costs us a few extra ops on the CPU, but allows us to bake the color fade into
	// a static VBO and avoids instancing which may or maynot be fast on all hardware.
	for ( int slice = numTrails - 1; slice >= 0; slice-- )
	{
		const int index = ( CurrentTransform - slice ) % TRAIL_GHOSTS;
		const Matrix4f transform = transforms[ index ];
		for ( int vertexIndex = 0; vertexIndex < 4; vertexIndex++ )
		{
			*( positions++ ) = transform.Transform( GazeCursorPositions[ vertexIndex ] );
		}
	}
}