void TextTestApp::draw()
{
	// this pair of lines is the standard way to clear the screen in OpenGL
	glClearColor( 0,0,0,1 );
	glClear( GL_COLOR_BUFFER_BIT );
	
	if (flipScreen==true){
		gl::pushMatrices();
		
		gl::scale( Vec3f(-1, 1, 1) );
		gl::translate( Vec2f(-ci::app::getWindowWidth(), 0 ) );
		gl::translate( Vec3f(-1, 1, 1) );
	}

	gl::enableAlphaBlending();
	gl::enableAdditiveBlending();

	mbackground.draw();

	drawSkeleton();

	// FONT NOW GETS RENDERED AFTER SCENE SO WE CAN OVERRIDE DRAW OPERATION IF REQUIRED
	currentScene->draw();

	myFont.draw();	
	
	// kill this all and refresh
	gl::disableAlphaBlending();
	gl::enableAdditiveBlending();

	// store our viewport, so we can restore it later
	Area viewport = gl::getViewport();

	// render a simple scene into mFboScene
	gl::setViewport( mFboScene.getBounds() );
	mFboScene.bindFramebuffer();
		gl::pushMatrices();
		gl::setMatricesWindow( viewport.getWidth(), viewport.getHeight(), false );
			gl::clear( ColorA( 0,0,0,1 ));
			fgParticles.draw();
			//gl::drawSolidCircle( Vec2f(50,50), 20 );
			//gl::draw( mFboScene.getTexture() );//TODO - screenshot?
		gl::popMatrices();
	mFboScene.unbindFramebuffer();

	// bind the blur shader
	mShaderBlur.bind();
	mShaderBlur.uniform("tex0", 0); // use texture unit 0
 
	// tell the shader to blur horizontally and the size of 1 pixel
	mShaderBlur.uniform("sampleOffset", Vec2f(1.0f/mFboBlur1.getWidth(), 0.0f));

	// copy a horizontally blurred version of our scene into the first blur Fbo
	
	gl::setViewport( mFboBlur1.getBounds() );
	mFboBlur1.bindFramebuffer();
		mFboScene.bindTexture(0);
		gl::pushMatrices();
			gl::setMatricesWindow( viewport.getWidth(), viewport.getHeight(), false );
			gl::clear( Color::black() );
			gl::drawSolidRect( mFboBlur1.getBounds() );
		gl::popMatrices();
		mFboScene.unbindTexture();
	mFboBlur1.unbindFramebuffer();

 
	// tell the shader to blur vertically and the size of 1 pixel
	mShaderBlur.uniform("sampleOffset", Vec2f(0.0f, 1.0f/mFboBlur2.getHeight()));

	// copy a vertically blurred version of our blurred scene into the second blur Fbo
	gl::setViewport( mFboBlur2.getBounds() );
	mFboBlur2.bindFramebuffer();
		mFboBlur1.bindTexture(0);
		gl::pushMatrices();
			gl::setMatricesWindow( viewport.getWidth(), viewport.getHeight(), false );
			gl::clear( Color::black() );
			gl::drawSolidRect( mFboBlur2.getBounds() );
		gl::popMatrices();
		mFboBlur1.unbindTexture();
	mFboBlur2.unbindFramebuffer();

	// unbind the shader
	mShaderBlur.unbind();

	// restore the viewport
	gl::setViewport( viewport );
	// because the Fbo's have their origin in the LOWER-left corner,
	// flip the Y-axis before drawing
	gl::pushModelView();
	gl::translate( Vec2f(0, 0 ) );// viewport.getHeight() ) );
	gl::scale( Vec3f(1, 1, 1) );

	// draw the 3 Fbo's 
	//gl::color( Color::white() );
	//gl::draw( mFboScene.getTexture(), Rectf(0, 0, 256, 256) );
	//gl::draw( mFboBlur1.getTexture(), Rectf(260, 0, 260 + 256, 256) );
	//gl::draw( mFboBlur2.getTexture(), Rectf(520, 0, 520 + 256, 256) );

	// draw our scene with the blurred version added as a blend
	gl::color( Color::white() );
	
	gl::enableAdditiveBlending();
	gl::draw( mFboScene.getTexture(), Rectf(0, 0, viewport.getWidth(), viewport.getHeight() ));

	gl::draw( mFboBlur2.getTexture(), Rectf(0, 0, viewport.getWidth(), viewport.getHeight() ));
	gl::disableAlphaBlending();

	// restore the modelview matrix
	gl::popModelView();

	if (flipScreen == true){
		gl::popMatrices();
	}
	
	gl::color( Color(1.0,1.0,1.0) );
	
	
	//These are for debug only
	//drawTitleSafeArea();
	//OutlineParams::getInstance()->draw();
}