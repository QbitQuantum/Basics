void shaderExternalFileExampleApp::draw(){
    
	gl::clear( Color::black() );
	
    if( mTexture ) {
        mTexture.bind( 0 );
        mShader.bind();
        mShader.uniform( "texture", 0 );
        mShader.uniform( "width", (float)CAM_W );
        mShader.uniform( "height", (float)CAM_H );
        gl::drawSolidRect( getWindowBounds() );
        mShader.unbind();
        mTexture.unbind();
    }
}