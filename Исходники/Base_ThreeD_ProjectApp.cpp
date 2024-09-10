/* 
 * @Description: render SSAO now - woohoo!
 * @param: KeyEvent
 * @return: none
 */
void Base_ThreeD_ProjectApp::renderSSAOToFBO()
{
	gl::setViewport( mSSAOMap.getBounds() );
	
	//render out main scene to FBO
	mSSAOMap.bindFramebuffer();
	
	glClearColor( 0.5f, 0.5f, 0.5f, 1 );
	glClearDepth(1.0f);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	gl::setMatricesWindow( mSSAOMap.getSize() );
	
	mRandomNoise.bind(1);
	mNormalDepthMap.getTexture().bind(2);
	
	mSSAOShader.bind();
	
	mSSAOShader.uniform("rnm", 1 );
	mSSAOShader.uniform("normalMap", 2 );
    
    //look at shader and see you can set these through the client if you so desire.
    //	mSSAOShader.uniform("rnm", 1 );
    //	mSSAOShader.uniform("normalMap", 2 );	
    //	mSSAOShader.uniform("totStrength", 1.38f);
    //	mSSAOShader.uniform("strength", 0.07f);
    //	mSSAOShader.uniform("offset", 10.0f);
    //	mSSAOShader.uniform("falloff", 0.2f);
    //	mSSAOShader.uniform("rad", 0.8f);
    
    //	mSSAOShader.uniform("rnm", 1 );
    //	mSSAOShader.uniform("normalMap", 2 );
    //	mSSAOShader.uniform("farClipDist", 20.0f);
    //	mSSAOShader.uniform("screenSizeWidth", (float)getWindowWidth());
    //	mSSAOShader.uniform("screenSizeHeight", (float)getWindowHeight());
	
    //	mSSAOShader.uniform("grandom", 1 );
    //	mSSAOShader.uniform("gnormals", 2 );
    //	mSSAOShader.uniform("gdepth", 1 );
    //	mSSAOShader.uniform("gdiffuse", 1 );
    
    gl::drawSolidRect( Rectf( 0, 0, getWindowWidth(), getWindowHeight()) );
	
	mSSAOShader.unbind();
	
	mNormalDepthMap.getTexture().unbind(2);
	mRandomNoise.unbind(1);
	
	mSSAOMap.unbindFramebuffer();
	
	gl::setViewport( getWindowBounds() );
}