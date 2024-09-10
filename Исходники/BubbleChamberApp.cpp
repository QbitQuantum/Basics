void BubbleChamberApp::drawGuts(Area area)
{
	float power = mRoom.getPower();
	Color powerColor = Color( power, power, power );
	
	drawIntoRoomFbo();
	
	gl::setMatricesWindow( getWindowSize(), false );
	//gl::setViewport( getWindowBounds() );
	gl::setViewport( area );

	gl::disableDepthRead();
	gl::disableDepthWrite();
	gl::enableAlphaBlending();
	gl::enable( GL_TEXTURE_2D );
	gl::color( ColorA( 1.0f, 1.0f, 1.0f, 1.0f ) );
	
	// ROOM
	mRoomFbo.bindTexture();
	gl::drawSolidRect( getWindowBounds() );
	
	
	//mActiveCam.setFixedPipeline();
	// PANEL
	drawInfoPanel();

	gl::pushMatrices();
	gl::setMatrices( mActiveCam.getCam() );

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // zero it out
	glMultMatrixf(mActiveCam.mProjectionMatrix); // Apply the matrix to the loaded projection matrix
	glMatrixMode(GL_MODELVIEW); // Return to our modelview matrix
	
	gl::disable( GL_TEXTURE_2D );
	gl::enableDepthWrite();
	gl::enableDepthRead();
	gl::enableAlphaBlending();
	gl::color( ColorA( powerColor, 1.0f ) );
	
	// PARTICLES
	mController.drawParticles( power );
	
	// DRAW GIBS
	mController.drawGibs();
	
	// BUBBLES
	mController.drawBubbles( power );
	
	gl::enable( GL_TEXTURE_2D );
	gl::disableDepthWrite();
	
	// DECALS
	gl::color( powerColor );
	mDecalTex.bind( 0 );
	mController.drawDecals();
	
	// SMOKES
	Vec3f right, up;
	mActiveCam.getCam().getBillboardVectors( &right, &up );
	mSmokeTex.bind( 0 );
	mController.drawSmokes( right, up );

	gl::disable( GL_TEXTURE_2D );
	gl::enableDepthWrite();
	gl::color( powerColor );
	
	// MOTHS
	mController.drawMoths();
	
	// GLOWCUBES
	mGlowCubeShader.bind();
	mGlowCubeShader.uniform( "eyePos", mActiveCam.getEye() );
	mGlowCubeShader.uniform( "power", mRoom.getPower() );
	mGlowCubeShader.uniform( "mvpMatrix", mActiveCam.mMvpMatrix );
	mController.drawGlowCubes( &mGlowCubeShader );
	mGlowCubeShader.unbind();

	if( mSaveFrames ){
//		writeImage( getHomeDirectory() + "BubbleChamber/" + toString( mNumSaveFrames ) + ".png", copyWindowSurface() );
		mNumSaveFrames ++;
	}
	
	gl::popMatrices();
}