	void draw()
	{
		if( ! mTexture )
			return;

		GLfloat LightPosition[]= { 0, 0, 1, 0.0f };
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		glLightfv( GL_LIGHT0, GL_POSITION, LightPosition );
		
		glMatrixMode( GL_PROJECTION );
		glLoadMatrixf( mCam->getProjectionMatrix().m );
		
		glMatrixMode( GL_MODELVIEW );
		glLoadMatrixf( mCam->getModelViewMatrix().m );

		
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glEnable( GL_MULTISAMPLE_ARB );
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_DEPTH_TEST );
		glDepthMask( GL_TRUE );
		glShadeModel( GL_SMOOTH );
		glEnable( GL_LIGHTING );
		
		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
		
		if( mDrawTextured )
			mTexture->bind();
		else
			glDisable( GL_TEXTURE_2D );
		for( size_t c = 0; c < mCubes.size(); ++c ) {
			mCubes[c]->draw();
		}
		mTexture->unbind();
		fli::gl::drawCube( Vec3f::zero(), Vec3f(1000, 0.01f, 1000) );
	}