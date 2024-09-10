void NxVideo_Avi_Recorder::AddVideoFrame( unsigned char * bmBits )
{
	HRESULT hr;

	// compress bitmap
	hr = AVIStreamWrite( mVideo->m_pStreamCompressed,	// stream pointer
		mVideo->m_lFrame,						// time of this frame
		1,						// number to write
		bmBits,					// image buffer
		mVideo->m_bih.biSizeImage,		// size of this frame
		AVIIF_KEYFRAME,			// flags....
		NULL,
		NULL);

	// updating frame counter
	mVideo->m_lFrame++;
}