// Draw
void KissBasicApp::draw()
{

	// Clear screen
	gl::clear( ColorAf::black() );

	// Check init flag
	if ( mFft ) {

		// Get data in the frequency (transformed) and time domains
		float * freqData = mFft->getAmplitude();
		float * timeData = mFft->getData();
		int32_t dataSize = mFft->getBinSize();

		// Cast data size to float
		float dataSizef = (float)dataSize;

		// Get dimensions
		float scale = ( (float)getWindowWidth() - 20.0f ) / dataSizef;
		float windowHeight = (float)getWindowHeight();

		// Use polylines to depict time and frequency domains
		PolyLine<Vec2f> freqLine;
		PolyLine<Vec2f> timeLine;

		// Iterate through data
		for ( int32_t i = 0; i < dataSize; i++ ) {

			// Do logarithmic plotting for frequency domain
			float logSize = math<float>::log( dataSizef );
			float x = (float)( (math<float>::log( (float)i) / logSize ) * dataSizef );
			float y = math<float>::clamp( freqData[i] * ( x / dataSizef ) * ( math<float>::log( ( dataSizef - (float)i ) ) ), 0.0f, 2.0f );

			// Plot points on lines for tme domain
			freqLine.push_back( Vec2f(        x * scale + 10.0f,          -y   * ( windowHeight - 20.0f ) * 0.25f + ( windowHeight - 10.0f ) ) );
			timeLine.push_back( Vec2f( (float)i * scale + 10.0f, timeData[ i ] * ( windowHeight - 20.0f ) * 0.25f + ( windowHeight * 0.25f + 10.0f ) ) );

		}

		// Draw signals
		gl::draw( freqLine );
		gl::draw( timeLine );

	}

}