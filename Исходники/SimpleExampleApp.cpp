void SimpleExampleApp::draw()
{
	gl::setMatrices( mCam );

	gl::clear( Color( 0, 0, 0 ) ); 

	gl::disableAlphaBlending();	
	if( mTriMesh.getNumTriangles() ) {
		gl::pushMatrices();

		mShader.bind();
		mShader.uniform( "eyeDir", mCam.getViewDirection().normalized() );
		gl::draw( mTriMesh );
		mShader.unbind();

		gl::popMatrices();
	}
	
	gl::enableAlphaBlending();

	// Simple FPS display
	gl::setMatricesWindow( getWindowSize() );
	gl::drawString( toString( getAverageFps() ) + " fps", Vec2i( 5, 5 ), ColorA( 1, 1, 1, 0.5f ), Font( "Arial", 18 ) );
}