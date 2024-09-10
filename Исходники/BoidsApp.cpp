void BoidsApp::drawCapture(){
	if( texture){
		glPushAttrib(GL_CURRENT_BIT);
		

		
		gl::enableDepthRead( false );
		gl::enableDepthWrite( true );
		
		glDepthMask( GL_FALSE ); //IMPORTANT
		glDisable( GL_DEPTH_TEST ); //IMPORTANT
		glEnable( GL_BLEND ); //IMPORTANT
		glBlendFunc( GL_SRC_ALPHA, GL_ONE ); //IMPORTANT
		
		texture.bind();
		gl::color( ColorA( 1.0f, 1.0f, 1.0f, 0.0f ) );
		gl::color(imageColor);
		gl::pushModelView();
		gl::multModelView(imageToScreenMap);
		gl::draw(texture);
		gl::popModelView();
		texture.unbind();
		
		glPopAttrib();
		
	}
}