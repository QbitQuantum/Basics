void gpuPSApp::draw()
{
	gl::setMatrices( mCam );
	gl::setViewport( getWindowBounds() );
	gl::clear( ColorA( 0.0f, 0.0f, 0.0f, 1.0f ) );
	
	mFBO[mCurrentFBO].bindTexture(0,0);
	mDisplShader.bind();
	mDisplShader.uniform("displacementMap", 0 );
	gl::pushModelView();
	gl::translate( Vec3f( 0.0f, 0.0f, getWindowHeight() / 2.0f ) );
	gl::rotate( mArcball.getQuat() );
	gl::draw( mVboMesh );
    gl::popModelView();
	
	mDisplShader.unbind();
	mFBO[mCurrentFBO].unbindTexture();
	
	gl::setMatricesWindow(getWindowSize());
	gl::drawString( toString( SIDE*SIDE ) + " vertices", Vec2f(32.0f, 32.0f));
	gl::drawString( toString((int) getAverageFps()) + " fps", Vec2f(32.0f, 52.0f));
}