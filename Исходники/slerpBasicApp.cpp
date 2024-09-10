void slerpBasicApp::drawPathBetweenVectors( Vec3f a, Vec3f b )
{
	// draws a path composed of 100 line segments
	glBegin( GL_LINE_STRIP );
	for( float t = 0; t <= 1.0f; t += 0.01f )
		gl::vertex( a.slerp( t, b ) );
	glEnd();
}