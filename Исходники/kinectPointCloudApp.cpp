void kinectPointCloudApp::draw()
{
	gl::clear( Color( 0.0f, 0.0f, 0.0f ), true );
	
	gl::pushMatrices();
		gl::scale( Vec3f( -1.0f, -1.0f, 1.0f ) );
		gl::rotate( mSceneRotation );
		mDepthTexture.bind( 0 );
		mShader.bind();
		mShader.uniform( "depthTex", 0 );
		gl::draw( mVboMesh );
		mShader.unbind();
	gl::popMatrices();
	
	params::InterfaceGl::draw();
}