void AudioVisualizerApp::update()
{
	// update FMOD so it can notify us of events
	mFMODSystem->update();

	// handle signal: if audio has ended, play next file
	if(mIsAudioPlaying && signalChannelEnd)
		playAudio( nextAudio( mAudioPath ) );

	// reset FMOD signals
	signalChannelEnd= false;

	// get spectrum for left and right channels and copy it into our channels
	float* pDataLeft = mChannelLeft.getData() + kBands * mOffset;
	float* pDataRight = mChannelRight.getData() + kBands * mOffset;

	mFMODSystem->getSpectrum( pDataLeft, kBands, 0, FMOD_DSP_FFT_WINDOW_HANNING );	
	mFMODSystem->getSpectrum( pDataRight, kBands, 1, FMOD_DSP_FFT_WINDOW_HANNING );

	// increment texture offset
	mOffset = (mOffset+1) % kHistory;

	// clear the spectrum for this row to avoid old data from showing up
	pDataLeft = mChannelLeft.getData() + kBands * mOffset;
	pDataRight = mChannelRight.getData() + kBands * mOffset;
	memset( pDataLeft, 0, kBands * sizeof(float) );
	memset( pDataRight, 0, kBands * sizeof(float) );

	// animate camera if mouse has not been down for more than 30 seconds
	if(!mIsMouseDown && (getElapsedSeconds() - mMouseUpTime) > mMouseUpDelay)
	{
		float t = float( getElapsedSeconds() );
		float x = 0.5f + 0.5f * math<float>::cos( t * 0.07f );
		float y = 0.1f - 0.2f * math<float>::sin( t * 0.09f );
		float z = 0.25f * math<float>::sin( t * 0.05f ) - 0.25f;
		Vec3f eye = Vec3f(kWidth * x, kHeight * y, kHeight * z);

		x = 1.0f - x;
		y = -0.3f;
		z = 0.6f + 0.2f *  math<float>::sin( t * 0.12f );
		Vec3f interest = Vec3f(kWidth * x, kHeight * y, kHeight * z);

		// gradually move to eye position and center of interest
		mCamera.setEyePoint( eye.lerp(0.995f, mCamera.getEyePoint()) );
		mCamera.setCenterOfInterestPoint( interest.lerp(0.990f, mCamera.getCenterOfInterestPoint()) );
	}
}