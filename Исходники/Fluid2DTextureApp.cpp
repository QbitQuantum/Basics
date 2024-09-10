void Fluid2DTextureApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
	gl::setMatricesWindow( getWindowWidth(), getWindowHeight() );

	// Update the positions and tex coords
	Rectf drawRect = getWindowBounds();
	int limX = mFluid2D.resX() - 1;
	int limY = mFluid2D.resY() - 1;
	float dx = drawRect.getWidth()/(float)limX;
	float dy = drawRect.getHeight()/(float)limY;
	
	for( int j = 0; j < mFluid2D.resY(); ++j ) {
		for( int i = 0; i < mFluid2D.resX(); ++i ) {
			Vec2f P = Vec2f( i*dx, j*dy );
			Vec2f uv = mFluid2D.texCoordAt( i, j );

			int idx = j*mFluid2D.resX() + i;
			mTriMesh.getVertices()[idx] = P;
			mTriMesh.getTexCoords()[idx] = uv;
			
		}
	}

	mTex.bind();
	gl::draw( mTriMesh ); 
	mTex.unbind();
	
	mParams.draw();	
}