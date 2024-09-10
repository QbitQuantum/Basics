void WaterSimApp::drawInfo()
{
	const int LOGO_OFFSET_X = 15, LOGO_OFFSET_Y = 20;
	
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	gl::setMatricesWindow( getWindowSize() );
	glEnable( GL_TEXTURE_2D );
	mInfo.bind();
	
	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	
	Vec2f center( getWindowWidth() - mInfo.getWidth() / 2.0f - LOGO_OFFSET_X, mInfo.getHeight() / 2.0f + LOGO_OFFSET_Y );
	float halfWidth = mInfo.getWidth() / 2.0f, halfHeight = mInfo.getHeight() / 2.0f;
	glTranslatef( center.x, center.y, 0 );
	glBegin( GL_QUADS );
		glTexCoord2f( 0, 0 ); glVertex2f( -halfWidth, -halfHeight );
		glTexCoord2f( 1.0, 0.0f ); glVertex2f( halfWidth, -halfHeight );
		glTexCoord2f( 1.0f, 1.0f ); glVertex2f( halfWidth, halfHeight );
		glTexCoord2f( 0.0f, 1.0f );	glVertex2f( -halfWidth, halfHeight );
	glEnd();
	glDisable( GL_TEXTURE_2D );
}