void GestureApp::drawUi()
{
	// Dial
	gl::color( ColorAf( Colorf::white(), 0.2f + mDialBrightness ) );
	gl::drawSolidCircle( mDialPosition, mDialRadius, mCircleResolution * 2 );
	gl::color( mBackgroundColor );
	float angle = mDialValue * (float)M_PI * 2.0f;
	vec2 pos( math<float>::cos( angle ), math<float>::sin( angle ) );
	pos *= mDialRadius - mDotSpacing;
	gl::drawSolidCircle( mDialPosition + pos, mDotRadius, mCircleResolution );
	
	// Swipe
	float x = mSwipeRect.x1 + mSwipePos * mSwipeRect.getWidth();
	Rectf a( mSwipeRect.x1, mSwipeRect.y1, x, mSwipeRect.y2 );
	Rectf b( x, mSwipeRect.y1, mSwipeRect.x2, mSwipeRect.y2 );
	gl::color( ColorAf( Colorf::gray( 0.5f ), 0.2f + mSwipeBrightness ) );
	gl::drawSolidRect( a );
	gl::color( ColorAf( Colorf::white(), 0.2f + mSwipeBrightness ) );
	gl::drawSolidRect( b );
	
	// Keys
	for ( vector<Key>::iterator iter = mKeys.begin(); iter != mKeys.end(); ++iter ) {
		gl::color( ColorAf( Colorf::white(), 0.2f + iter->mBrightness ) );
		gl::drawSolidRect( iter->mBounds );
	}
}