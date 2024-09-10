void FastTrailsApp::update()
{
	// find out how many trails we should add
	const double	trails_per_second = 2000.0;
	double			elapsed = getElapsedSeconds() - mTime;
	uint32_t		num_trails = uint32_t(elapsed * trails_per_second);
	
	// add this number of trails 
	// (note: it's an ugly function that draws a swirling trail around a sphere, just for demo purposes)
	for(size_t i=0; i<num_trails; ++i ) {
		float		phi = mAngle * 0.01f;
		float		prev_phi = phi - 0.01f;
		float		theta = phi * 0.03f;
		float		prev_theta = prev_phi * 0.03f;

		Vec3f		pos = 45.0f * Vec3f( sinf( phi ) * cosf( theta ), sinf( phi ) * sinf( theta ), cosf( phi ) );
		Vec3f		prev_pos = 45.0f * Vec3f( sinf( prev_phi ) * cosf( prev_theta ), sinf( prev_phi ) * sinf( prev_theta ), cosf( prev_phi ) );

		Vec3f		direction = pos - prev_pos;
		Vec3f		right = Vec3f( sinf( 20.0f * phi ), 0.0f, cosf( 20.0f * phi ) );
		Vec3f		normal = direction.cross( right ).normalized();

		// add two vertices, one at each side of the center line
		mTrail.push_front( pos - 1.0f * normal );
		mTrail.push_front( pos + 1.0f * normal );

		mAngle += 1.0;
	}

	// keep trail length within bounds
	while( mTrail.size() > TRAIL_LENGTH )
		mTrail.pop_back();

	// copy to trail to vbo (there's probably a faster way than this, need to check that out later)
	gl::VboMesh::VertexIter itr = mVboMesh.mapVertexBuffer();
	for( size_t i=0; i<mTrail.size(); ++i, ++itr )
		itr.setPosition( mTrail[i] );

	// advance time
	mTime += num_trails / trails_per_second;
}