void VideoComponent::closeAvi()
{
	// Stop it first as it might still be playing
	stopAvi();

	// Unload the video if there is already one
	if (m_pgf)
	{
		delete[] m_bgraData;
		m_bgraData = 0x0;
		if (m_hBitmap)
			DeleteObject(m_hBitmap);					// Delete The Device Dependant Bitmap Object
		if (m_pgf)
			AVIStreamGetFrameClose(m_pgf);				// Deallocates The GetFrame Resources
		m_pgf = 0x0;
		if (m_pavi)
			AVIStreamRelease(m_pavi);					// Release The Stream
		AVIFileExit();								// Release The File
		if (m_videoTexture)
		{
			// Remove video texture
			h3dRemoveResource(m_videoTexture);
			// And release it if unused now (should be, else we can't create the same again)
			h3dReleaseUnusedResources();		
			m_videoTexture = 0;
			m_originalSampler = 0;
			m_samplerIndex = 0;
		}
		if (m_hasAudio)
		{
			// Set an empty sound for releasing the old one
			GameEvent clearSound(GameEvent::E_SET_SOUND_FILE, &GameEventData(""), this);
			m_owner->executeEvent(&clearSound);
			m_hasAudio = false;
		}
	}
}