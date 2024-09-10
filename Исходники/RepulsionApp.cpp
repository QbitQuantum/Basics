void RepulsionApp::setFboPositions( gl::Fbo &fbo )
{
	Surface32f pos( fbo.getTexture() );
	Surface32f::Iter it = pos.getIter();
	while( it.line() ){
		while( it.pixel() ){
			Vec3f r = mRoom.getRandRoomPos();
			float mass = Rand::randFloat( 20.0f, 30.0f );
			if( Rand::randFloat() < 0.05f ) 
				mass = Rand::randFloat( 50.0f, 60.0f );
			
			if( it.y() < 5  && it.x() < 50 )
				mass = Rand::randFloat( 300.0f, 5000.0f );
			else
				mass = Rand::randFloat( 50.0f, 300.0f );
			
			it.r() = r.x;
			it.g() = r.y;
			it.b() = r.z;
			it.a() = 100.0f;
		}
	}
	
	gl::Texture posTexture( pos );
	posTexture.bind();
	
	gl::setMatricesWindow( mFboSize, false );
	gl::setViewport( mFboBounds );
	
	fbo.bindFramebuffer();
	mPosInitShader.bind();
	mPosInitShader.uniform( "initTex", 0 );
	gl::drawSolidRect( mFboBounds );
	mPosInitShader.unbind();
	fbo.unbindFramebuffer();
}