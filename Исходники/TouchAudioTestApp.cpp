void TouchAudioTestApp::drawWaveForm()
{
	if( ! mPcmBuffer ) {
		return;
	}
	
	uint32_t bufferSamples = mPcmBuffer->getSampleCount();
	audio::Buffer32fRef leftBuffer = mPcmBuffer->getChannelData( audio::CHANNEL_FRONT_LEFT );
	//audio::Buffer32fRef rightBuffer = mPcmBuffer->getChannelData( audio::CHANNEL_FRONT_RIGHT );
	
	float center = getWindowWidth() / 2;
	float displaySize = getWindowHeight();
	uint32_t endIdx = bufferSamples;
	
	//only draw the last 1024 samples or less
	int32_t startIdx = ( endIdx - 1024 );
	startIdx = math<int32_t>::clamp( startIdx, 0, endIdx );
	
	float scale = displaySize / (float)( endIdx - startIdx );
	//float scale = displaySize / (float)( endIdx );
	
	PolyLine<vec2>	line;
	
	gl::color( Color( 1.0f, 0.5f, 0.25f ) );
	for( uint32_t i = startIdx, c = 0; i < endIdx; i++, c++ ) {
		float y = ( ( leftBuffer->mData[i] - 1 ) * - center );
		line.push_back( vec2( y, ( c * scale ) ) );
	}
	gl::draw( line );
	
	/*glColor3f( 1.0f, 0.96f, 0.0f );
	glBegin( GL_LINE_STRIP );
	for( int i = 0; i < endIdx; i++ ) {
		float y = ( ( rightBuffer->mData[i] - 1 ) * - 100 );
		glVertex2f( ( i * scale ) , y );
	}
	glEnd();*/
}