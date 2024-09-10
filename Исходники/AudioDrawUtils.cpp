void WaveformPlot::load( const audio::BufferRef &buffer, const ci::Rectf &bounds, size_t pixelsPerVertex )
{
	mBounds = bounds;
	mWaveforms.clear();

	size_t numChannels = buffer->getNumChannels();
	ivec2 waveSize = bounds.getSize();
	waveSize.y /= numChannels;
	for( size_t ch = 0; ch < numChannels; ch++ ) {
		mWaveforms.push_back( Waveform( buffer->getChannel( ch ), buffer->getNumFrames(), waveSize, pixelsPerVertex, Waveform::CalcMode::MIN_MAX ) );
		mWaveforms.push_back( Waveform( buffer->getChannel( ch ), buffer->getNumFrames(), waveSize, pixelsPerVertex, Waveform::CalcMode::AVERAGE ) );
	}
}