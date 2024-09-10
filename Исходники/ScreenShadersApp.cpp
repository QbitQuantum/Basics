void ScreenShadersApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
	
	// bind the Fbo
	mFbo.bindFramebuffer();
	// match the viewport to the Fbo dimensions
	gl::setViewport( mFbo.getBounds() );
	// setup an ortho projection
	gl::setMatricesWindow( mFbo.getWidth(), mFbo.getHeight() );
	// clear the Fbo
	gl::clear( Color( 0, 0, 0 ) );
	
	if ( mTexture ) {
		gl::draw( mTexture );
	}
	
	// unbind the Fbo
	mFbo.unbindFramebuffer();
	
	gl::setMatricesWindow( getWindowWidth(), getWindowHeight() );
	
	float kernelRes = 21.0f;
	
	mBlurShader.bind();
	mBlurShader.uniform( "kernelRes", kernelRes );
	mBlurShader.uniform( "invKernelRes", 1.0f / kernelRes );
	mBlurShader.uniform( "fboTex", 0 );
	mBlurShader.uniform( "kernelTex", 1 );
	mBlurShader.uniform( "orientationVector", Vec2f( 1.0f, 1.0f ) );
	mBlurShader.uniform( "blurAmt", 1.0f );
	mBlurShader.uniform( "colMulti", 1.0f );
	
	mBlurKernel.bind( 1 );
	
	gl::draw( mFbo.getTexture(0), Rectf( 0, getWindowHeight(), getWindowWidth(), 0 ) );
	mBlurShader.unbind();
}