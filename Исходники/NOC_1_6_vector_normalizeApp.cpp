void NOC_1_6_vector_normalizeApp::draw()
{
	gl::clear( Color( 1, 1, 1 ) );
	
	// A vector that points to the mouse location
	Vec2f mouse = Vec2f( getMousePos().x, getMousePos().y );
	// A vector that points to the center of the window
	Vec2f center = Vec2f( getWindowWidth() / 2, getWindowHeight() / 2 );
	// Subtract center from mouse which results in a vector that points from center to mouse
	mouse -= center;
	
	// Normalize the vector
	mouse.normalize();
	
	// Multiply its length by 50
	mouse *= 150;
	
	// Need push and pop matrix since the matrix doesn't reset on draw like in processing
	glPushMatrix();
	gl::translate( getWindowWidth() / 2, getWindowHeight() / 2 );
	glLineWidth( 2.0 );
	gl::color( 0, 0, 0 );
	gl::drawLine( Vec2f( 0,0 ), Vec2f( mouse.x, mouse.y ) );
	glPopMatrix();
}