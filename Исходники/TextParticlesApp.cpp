void TextParticlesApp::mouseDrag( MouseEvent event )
{
	Rectf r	= Rectf( 0, 0, getWindowWidth(), getWindowHeight() );
	if ( r.contains( event.getPos() )) {
		mCamUi.mouseDrag( event );
	}
}