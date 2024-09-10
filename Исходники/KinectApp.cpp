// Render
void KinectApp::draw()
{

	// Clear window
	gl::setViewport( getWindowBounds() );
	gl::clear( Colorf( 0.1f, 0.1f, 0.1f ) );

	// We're capturing
	if ( mKinect->isCapturing() ) {

		// Set up camera for 3D
		gl::setMatrices( mCamera );

		// Move skeletons down below the rest of the interface
		gl::pushMatrices();
		gl::translate( 0.0f, -0.62f, 0.0f );

		// Iterate through skeletons
		uint32_t i = 0;
		for ( vector<Skeleton>::const_iterator skeletonIt = mSkeletons.cbegin(); skeletonIt != mSkeletons.cend(); ++skeletonIt, i++ ) {

			// Skeleton is valid when all joints are present
			if ( skeletonIt->size() == JointName::NUI_SKELETON_POSITION_COUNT ) {

				// Set color
				gl::color( mKinect->getUserColor( i ) );

				// Draw joints
				for ( Skeleton::const_iterator jointIt = skeletonIt->cbegin(); jointIt != skeletonIt->cend(); ++jointIt ) {
					gl::drawSphere( jointIt->second * Vec3f( -1.0f, 1.0f, 1.0f ), 0.025f, 16 );
				}

				// Draw body
				for ( vector<vector<JointName> >::const_iterator segmentIt = mSegments.cbegin(); segmentIt != mSegments.cend(); ++segmentIt ) {
					drawSegment( * skeletonIt, * segmentIt );
				}

			}

		}

		// Switch to 2D
		gl::popMatrices();
		gl::setMatricesWindow( getWindowSize(), true );

		// Draw depth and video textures
		gl::color( Colorf::white() );
		if ( mDepthSurface ) {
			Area srcArea( 0, 0, mDepthSurface.getWidth(), mDepthSurface.getHeight() );
			Rectf destRect( 265.0f, 15.0f, 505.0f, 195.0f );
			gl::draw( gl::Texture( mDepthSurface ), srcArea, destRect );
		}
		if ( mVideoSurface ) {
			Area srcArea( 0, 0, mVideoSurface.getWidth(), mVideoSurface.getHeight() );
			Rectf destRect( 508.0f, 15.0f, 748.0f, 195.0f );
			gl::draw( gl::Texture( mVideoSurface ), srcArea, destRect);
		}

	}

	// Check audio data
	if ( mData != 0 ) {

		// Get dimensions
		int32_t dataSize = mInput->getDataSize();
		float scale = 240.0f / (float)dataSize;
		float height = 180.0f;
		Vec2f position( 751.0f, 15.0f );

		// Draw background
		gl::color( ColorAf::black() );
		Rectf background( position.x, position.y, position.x + 240.0f, position.y + 180.0f );
		gl::drawSolidRect( background );

		// Draw audio input
		gl::color( ColorAf::white() );
		PolyLine<Vec2f> mLine;
		for ( int32_t i = 0; i < dataSize; i++ ) {
			mLine.push_back( position + Vec2f( i * scale, math<float>::clamp( mData[ i ], -1.0f, 1.0f ) * height * 0.5f + height * 0.5f ) );
		}
		if ( mLine.size() > 0 ) {
			gl::draw( mLine );
		}

	}

	// Draw the interface
	params::InterfaceGl::draw();

}