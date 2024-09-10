void StereoscopicRenderingApp::render()
{	
	float seconds = (float) getElapsedSeconds();

	// enable 3D rendering
	gl::enableDepthRead();
	gl::enableDepthWrite();

	// set 3D camera matrices
	gl::pushMatrices();
	gl::setMatrices( mCamera );

	if( mShaderPhong && mMeshTrombone && mMeshNote ) {
		// enable phong shading
		mShaderPhong.bind();	
		
		// draw trombone
		gl::pushModelView();
		{
			gl::color( Color(0.7f, 0.6f, 0.0f) );
			gl::rotate( Vec3f::yAxis() * 10.0f * seconds );
			gl::draw( mMeshTrombone );

			// reflection
			gl::scale( 1.0f, -1.0f, 1.0f );
			gl::draw( mMeshTrombone );
		}
		gl::popModelView();	

		// draw animated notes
		Rand rnd;
		for(int i=-100; i<=100; ++i) {
			rnd.seed(i);

			float t = rnd.nextFloat() * 200.0f + 2.0f * seconds;
			float r = rnd.nextFloat() * 360.0f + 60.0f * seconds;
			float z = fmodf( 5.0f * t, 200.0f ) - 100.0f;		

			gl::pushModelView();
			{
				gl::color( Color( CM_HSV, rnd.nextFloat(), 1.0f, 1.0f ) );

				gl::pushModelView();
				gl::translate( i * 0.5f, 0.15f + 1.0f * math<float>::abs( sinf(3.0f * t) ), -z );
				gl::rotate( Vec3f::yAxis() * r );
				gl::draw( mMeshNote );
				gl::popModelView();
				
				// reflection
				gl::pushModelView();
				gl::scale( 1.0f, -1.0f, 1.0f );
				gl::translate( i * 0.5f, 0.15f + 1.0f * math<float>::abs( sinf(3.0f * t) ), -z );
				gl::rotate( Vec3f::yAxis() * r );
				gl::draw( mMeshNote );
				gl::popModelView();
			}
			gl::popModelView();
		}

		mShaderPhong.unbind();
	}

	// draw grid
	gl::color( Color(0.8f, 0.8f, 0.8f) );
	for(int i=-100; i<=100; ++i) {
		gl::drawLine( Vec3f((float) i, 0, -100), Vec3f((float) i, 0, 100) );
		gl::drawLine( Vec3f(-100, 0, (float) i), Vec3f(100, 0, (float) i) );
	}

	// draw floor
	gl::enableAlphaBlending();
	gl::color( ColorA(1,1,1,0.75f) );
	gl::drawCube( Vec3f(0.0f, -0.5f, 0.0f), Vec3f(200.0f, 1.0f, 200.0f) );
	gl::disableAlphaBlending();

	// restore 2D rendering
	gl::popMatrices();
	gl::disableDepthWrite();
	gl::disableDepthRead();

	// render UI
	if( mDrawUI ) renderUI();
}