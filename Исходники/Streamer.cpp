void Streamer::draw()
{
	glBegin( GL_TRIANGLE_STRIP );
	for( int i=0; i<mLen-1; i++ ){
		Vec3f p1 = mPositions[i];
		Vec3f p2 = mPositions[i+1];
		Vec3f dir = p2 - p1;
		dir.normalize();
		Vec3f perp1 = dir.cross( Vec3f::yAxis() );
		perp1.normalize();
		gl::vertex( p1 - perp1 * 2.0f * mAgePer );
		gl::vertex( p1 + perp1 * 2.0f * mAgePer );
	}
	glEnd();
}