void TextRenderingApp::draw()
{
	// note: when drawing text to an FBO, 
	//  make sure to enable maximum quality multisampling (16x is best)!

	// clear out the window
	gl::clear( mBackColor );

	// draw text box centered inside the window
	Area fit = Area::proportionalFit( Area(Vec2i::zero(), mTextBox.getSize()), getWindowBounds(), true, false ); 

	gl::color( mFrontColor );
	gl::enableAlphaBlending();

	gl::pushModelView();
	gl::translate( fit.getUL() );

	// bind shader
	if(mSdfShader) {
		mSdfShader.bind();
		mSdfShader.uniform("tex0", 0);
	}

	mTextBox.draw();

	// unbind shader
	if(mSdfShader) mSdfShader.unbind();

	if(mShowWireframe) mTextBox.drawWireframe();
	
	gl::popModelView();
	gl::disableAlphaBlending();

	if(mShowBounds)
		mTextBox.drawBounds( fit.getUL() );
}