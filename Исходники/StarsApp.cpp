void StarsApp::draw()
{		
	int w = getWindowWidth();
	int h = getWindowHeight();

	gl::clear( Color::black() ); 

	if(mIsStereoscopic) {
		glPushAttrib( GL_VIEWPORT_BIT );
		gl::pushMatrices();

		// render left eye
		mCamera.enableStereoLeft();

		gl::setViewport( Area(0, 0, w / 2, h) );
		gl::setMatrices( mCamera.getCamera() );
		render();
	
		// draw user interface
		mUserInterface.draw("Stereoscopic Projection");

		// render right eye
		mCamera.enableStereoRight();

		gl::setViewport( Area(w / 2, 0, w, h) );
		gl::setMatrices( mCamera.getCamera() );
		render();
	
		// draw user interface
		mUserInterface.draw("Stereoscopic Projection");

		gl::popMatrices();		
		glPopAttrib();
	}
	else if(mIsCylindrical) {
		// make sure we have a frame buffer to render to
		createFbo();

		// determine correct aspect ratio and vertical field of view for each of the 3 views
		w = mFbo.getWidth() / 3;
		h = mFbo.getHeight();

		const float aspect = float(w) / float(h);
		const float hFoV = 60.0f;
		const float vFoV = toDegrees( 2.0f * math<float>::atan( math<float>::tan( toRadians(hFoV) * 0.5f ) / aspect ) );

		// for values smaller than 1.0, this will cause each view to overlap the other ones
		const float overlap = 1.0f;	

		// bind the frame buffer object
		mFbo.bindFramebuffer();

		// store viewport, camera and matrices, so we can restore later
		glPushAttrib( GL_VIEWPORT_BIT );
		CameraStereo original = mCamera.getCamera();
		gl::pushMatrices();

		// setup camera	
		CameraStereo cam = mCamera.getCamera();
		cam.disableStereo();
		cam.setAspectRatio(aspect);
		cam.setFov( vFoV );

		Vec3f right, up;	
		cam.getBillboardVectors(&right, &up);
		Vec3f forward = up.cross(right);

		// render left side
		gl::setViewport( Area(0, 0, w, h) );

		cam.setViewDirection( Quatf(up, overlap * toRadians(hFoV)) * forward );
		cam.setWorldUp( up );
		gl::setMatrices( cam );
		render();
		
		// render front side
		gl::setViewport( Area(w, 0, w*2, h) );

		cam.setViewDirection( forward );
		cam.setWorldUp( up );
		gl::setMatrices( cam );
		render();	
	
		// draw user interface
		mUserInterface.draw( (boost::format("Cylindrical Projection (%d degrees)") % int( (1.0f + 2.0f * overlap) * hFoV ) ).str() );

		// render right side
		gl::setViewport( Area(w*2, 0, w*3, h) );

		cam.setViewDirection( Quatf(up, -overlap * toRadians(hFoV)) * forward );
		cam.setWorldUp( up );
		gl::setMatrices( cam );
		render();
		
		// unbind the frame buffer object
		mFbo.unbindFramebuffer();

		// restore states
		gl::popMatrices();		
		mCamera.setCurrentCam(original);
		glPopAttrib();

		// draw frame buffer and perform cylindrical projection using a fragment shader
		if(mShader) {
			float sides = 3;
			float radians = sides * toRadians( hFoV );
			float reciprocal = 0.5f / sides;

			mShader.bind();
			mShader.uniform("texture", 0);
			mShader.uniform("sides", sides);
			mShader.uniform("radians", radians );
			mShader.uniform("reciprocal", reciprocal );
		}

		Rectf centered = Rectf(mFbo.getBounds()).getCenteredFit( getWindowBounds(), false );
		gl::draw( mFbo.getTexture(), centered );

		if(mShader) mShader.unbind();
	}
	else {
		mCamera.disableStereo();

		gl::pushMatrices();
		gl::setMatrices( mCamera.getCamera() );
		render();
		gl::popMatrices();
	
		// draw user interface
		mUserInterface.draw("Perspective Projection");
	}

	// fade in at start of application
	gl::enableAlphaBlending();
	double t = math<double>::clamp( mTimer.getSeconds() / 3.0, 0.0, 1.0 );
	float a = ci::lerp<float>(1.0f, 0.0f, (float) t);

	if( a > 0.0f ) {
		gl::color( ColorA(0,0,0,a) );
		gl::drawSolidRect( getWindowBounds() );
	}
	gl::disableAlphaBlending();
}