void BloomingNeonApp::draw()
{
	// clear our window
	gl::clear( Color::black() );

	// store our viewport, so we can restore it later
	Area viewport = gl::getViewport();

	// render scene into mFboScene using illumination texture
	mTextureIllumination.enableAndBind();
	mTextureSpecular.bind(1);
	gl::setViewport( mFboScene.getBounds() );
	mFboScene.bindFramebuffer();
		gl::pushMatrices();
			gl::setMatricesWindow(SCENE_SIZE, SCENE_SIZE, false);
			gl::clear( Color::black() );
			render();
		gl::popMatrices();
	mFboScene.unbindFramebuffer();

	// bind the blur shader
	mShaderBlur.bind();
	mShaderBlur.uniform("tex0", 0); // use texture unit 0
 
	// tell the shader to blur horizontally and the size of 1 pixel
	mShaderBlur.uniform("sample_offset", Vec2f(1.0f/mFboBlur1.getWidth(), 0.0f));
	mShaderBlur.uniform("attenuation", 2.5f);

	// copy a horizontally blurred version of our scene into the first blur Fbo
	gl::setViewport( mFboBlur1.getBounds() );
	mFboBlur1.bindFramebuffer();
		mFboScene.bindTexture(0);
		gl::pushMatrices();
			gl::setMatricesWindow(BLUR_SIZE, BLUR_SIZE, false);
			gl::clear( Color::black() );
			gl::drawSolidRect( mFboBlur1.getBounds() );
		gl::popMatrices();
		mFboScene.unbindTexture();
	mFboBlur1.unbindFramebuffer();	
 
	// tell the shader to blur vertically and the size of 1 pixel
	mShaderBlur.uniform("sample_offset", Vec2f(0.0f, 1.0f/mFboBlur2.getHeight()));
	mShaderBlur.uniform("attenuation", 2.5f);

	// copy a vertically blurred version of our blurred scene into the second blur Fbo
	gl::setViewport( mFboBlur2.getBounds() );
	mFboBlur2.bindFramebuffer();
		mFboBlur1.bindTexture(0);
		gl::pushMatrices();
			gl::setMatricesWindow(BLUR_SIZE, BLUR_SIZE, false);
			gl::clear( Color::black() );
			gl::drawSolidRect( mFboBlur2.getBounds() );
		gl::popMatrices();
		mFboBlur1.unbindTexture();
	mFboBlur2.unbindFramebuffer();

	// unbind the shader
	mShaderBlur.unbind();

	// render scene into mFboScene using color texture
	mTextureColor.enableAndBind();
	mTextureSpecular.bind(1);
	gl::setViewport( mFboScene.getBounds() );
	mFboScene.bindFramebuffer();
		gl::pushMatrices();
			gl::setMatricesWindow(SCENE_SIZE, SCENE_SIZE, false);
			gl::clear( Color::black() );
			render();
		gl::popMatrices();
	mFboScene.unbindFramebuffer();

	// restore the viewport
	gl::setViewport( viewport );

	// because the Fbo's have their origin in the LOWER-left corner,
	// flip the Y-axis before drawing
	gl::pushModelView();
	gl::translate( Vec2f(0, 256) );
	gl::scale( Vec3f(1, -1, 1) );

	// draw the 3 Fbo's 
	gl::color( Color::white() );
	gl::draw( mFboScene.getTexture(), Rectf(0, 0, 256, 256) );
	drawStrokedRect( Rectf(0, 0, 256, 256) );

	gl::draw( mFboBlur1.getTexture(), Rectf(260, 0, 260 + 256, 256) );
	drawStrokedRect( Rectf(260, 0, 260 + 256, 256) );

	gl::draw( mFboBlur2.getTexture(), Rectf(520, 0, 520 + 256, 256) );
	drawStrokedRect( Rectf(520, 0, 520 + 256, 256) );

	// draw our scene with the blurred version added as a blend
	gl::color( Color::white() );
	gl::draw( mFboScene.getTexture(), Rectf(780, 0, 780 + 256, 256) );

	gl::enableAdditiveBlending();
	gl::draw( mFboBlur2.getTexture(), Rectf(780, 0, 780 + 256, 256) );
	gl::disableAlphaBlending();
	drawStrokedRect( Rectf(780, 0, 780 + 256, 256) );
	
	// restore the modelview matrix
	gl::popModelView();

	// draw info
	gl::enableAlphaBlending();
	gl::drawStringCentered("Basic Scene", Vec2f(128, 236));
	gl::drawStringCentered("First Blur Pass (Horizontal)", Vec2f(260 + 128, 236));
	gl::drawStringCentered("Second Blur Pass (Vertical)", Vec2f(520 + 128, 236));
	gl::drawStringCentered("Final Scene", Vec2f(780 + 128, 236));
	gl::disableAlphaBlending();
}