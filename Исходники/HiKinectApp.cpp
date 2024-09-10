void HiKinectApp::draw3D() {
	
	gl::setMatrices( mCamUI.getCamera() );
	if (mWireframe) gl::enableWireframe();
	else gl::disableWireframe();
	
	if (mLighting) {
		glEnable( GL_LIGHTING );
		glEnable( GL_LIGHT0 );
	}
//	GLfloat light_position[] = { mMousePos.x, mMousePos.y, -275.0f, 0.0f };
	GLfloat light_position[] = { 0, 0, 1.0f, 0.0f };
	glLightfv( GL_LIGHT0, GL_POSITION, light_position );
	if( DIFFUSE ){
		ci::ColorA color( CM_RGB, 1.0f, 1.0f, 1.0f, 1.0f );
		glMaterialfv( GL_FRONT, GL_DIFFUSE,	color );
	} else {
		glMaterialfv( GL_FRONT, GL_DIFFUSE,	no_mat );
	}
	
	if( AMBIENT )
		glMaterialfv( GL_FRONT, GL_AMBIENT,	mat_ambient );
	else
		glMaterialfv( GL_FRONT, GL_AMBIENT,	no_mat );
	
	if( SPECULAR ){
		glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
		glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess );
	} else {
		glMaterialfv( GL_FRONT, GL_SPECULAR, no_mat );
		glMaterialfv( GL_FRONT, GL_SHININESS, no_shininess );
	}
	
	if( EMISSIVE )
		glMaterialfv( GL_FRONT, GL_EMISSION, mat_emission );
	else
		glMaterialfv( GL_FRONT, GL_EMISSION, no_mat );
	
	if (mDepthTexture)
		mDepthTexture.bind(0);
	mFbo.bindTexture(1);
	if (mColorTexture)
		mColorTexture.bind(2);
	
	mGridMesh.draw( lmap(mMousePos.x, 0.0f, (float)getWindowWidth(), 0.0f, 1.0f) );
	
	if (mLighting) {
		glDisable( GL_LIGHTING );
		glDisable( GL_LIGHT0 );
	}
	
	gl::disableWireframe();
}