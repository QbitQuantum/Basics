void GLTrianglesApp::mouseDown(MouseEvent event)
{
	// Compute normalized mouse position:
	mMouseAdjustedPos = static_cast<Vec2f>( event.getPos() ) / static_cast<Vec2f>( getWindowSize() );
	
	// Compute mouse distance from triangle strip vertices:
	size_t tCountA    = mTriangleStrip.size();
	float  tBestDistA = 1e6;
	int    tBestA     = -1;
	//
	for(size_t i = 0; i < tCountA; i++) {
		float tDistA = mMouseAdjustedPos.distance( mTriangleStrip[ i ] );
		if( tDistA < tBestDistA ) {
			tBestDistA = tDistA;
			tBestA = i;
		}
	}
	
	// Compute mouse distance from triangle vertices:
	size_t tCountB    = mTriangles.size();
	float  tBestDistB = 1e6;
	int    tBestB     = -1;
	//
	for(size_t i = 0; i < tCountB; i++) {
		float tDistB = mMouseAdjustedPos.distance( mTriangles[ i ] );
		if( tDistB < tBestDistB ) {
			tBestDistB = tDistB;
			tBestB = i;
		}
	}
	
	// Check whether mouse is closer to triangle strip or triangles
	// and set member flag/index accordingly:
	if( tBestDistA < tBestDistB ) {
		mBestIsA = true;
		mBestIdx = tBestA;
	}
	else {
		mBestIsA = false;
		mBestIdx = tBestB;
	}
}