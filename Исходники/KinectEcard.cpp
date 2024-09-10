void KinectEcard::renderSubstractedVideo(){
	mSubstractedVideoFbo.bindFramebuffer();

	gl::pushMatrices();
	{
		// clear FBO
		gl::clear( Color::black() );
		gl::color( Color::white() );

		//
		gl::setMatricesWindowPersp( mSubstractedVideoFbo.getSize() );

		mSubstractShader.bind();
		mSubstractShader.uniform( "tex0", 0 );
		mSubstractShader.uniform( "tex1", 1 );
		mSubstractShader.uniform( "tex2", 2 );
		mSubstractShader.uniform( "tex3", 3 );

		mVideoFbo.bindTexture(0);
		mDepthFbo.bindTexture(1);
		mStoredVideoFbo.bindTexture(2);
		mStoredDepthFbo.bindTexture(3);
		
		gl::drawSolidRect( mSubstractedVideoFbo.getBounds() );

		mVideoFbo.unbindTexture();
		mDepthFbo.unbindTexture();
		mStoredVideoFbo.unbindTexture();
		mStoredDepthFbo.unbindTexture();

		mSubstractShader.unbind();
	}
	gl::popMatrices();

	mSubstractedVideoFbo.unbindFramebuffer();
}