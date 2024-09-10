void SmoothDisplacementMappingApp::renderNormalMap()
{
	if( mNormalMapShader && mNormalMapFbo ) 
	{
		mNormalMapFbo.bindFramebuffer();
		{
			// setup viewport and matrices 
			glPushAttrib( GL_VIEWPORT_BIT );
			gl::setViewport( mNormalMapFbo.getBounds() );

			gl::pushMatrices();
			gl::setMatricesWindow( mNormalMapFbo.getSize(), false );

			// clear the color buffer
			gl::clear();			

			// bind the displacement map
			mDispMapFbo.getTexture().bind(0);

			// render the normal map
			mNormalMapShader.bind();
			mNormalMapShader.uniform( "texture", 0 );
			mNormalMapShader.uniform( "amplitude", 4.0f );

			Area bounds = mNormalMapFbo.getBounds(); //bounds.expand(-1, -1);
			gl::drawSolidRect( bounds );

			mNormalMapShader.unbind();

			// clean up after ourselves
			mDispMapFbo.getTexture().unbind();

			gl::popMatrices();

			glPopAttrib();
		}
		mNormalMapFbo.unbindFramebuffer();
	}
}