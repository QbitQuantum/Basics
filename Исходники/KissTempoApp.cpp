// Draw
void KissTempoApp::draw()
{

	// Clear screen
	gl::clear( ColorAf::black() );

	// Check sizes
	if ( mDataSize > 0 && mWaveform.size() > 0 ) {

		// Get dimensions
		float windowWidth = (float)getWindowWidth();
		float center = windowWidth * 0.5f;

		// Draw waveform
		float y = 0.0f;
		PolyLine<Vec2f> mLine;
		uint32_t ampCount = mWaveform.size();
		for ( uint32_t i = 0; i < ampCount; i++, y += 6.5f ) {
			float x = mWaveform[ i ] * windowWidth;
			mLine.push_back( Vec2f( center + x, y ) );
			mLine.push_back( Vec2f( center - x, y + 3.25f ) );
		}
		gl::draw( mLine );

	}

	// Draw tempo (scale text to improve quality)
	gl::pushMatrices();
	gl::scale( 0.25f, 0.25f );
	mFont->drawString( toString( (int32_t)math<float>::ceil( mTempo ) ) + " BPM", Vec2f( 20.0f * 4.0f, 540.0f * 4.0f ) );
	gl::scale( 0.5f, 0.5f );
	mFont->drawString( "Press SPACE to reset track", Vec2f( 20.0f * 8.0f, 575.0f * 8.0f ) );
	gl::popMatrices();

}