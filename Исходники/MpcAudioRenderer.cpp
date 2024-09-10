CMpcAudioRenderer::~CMpcAudioRenderer()
{
	Stop();

	SAFE_DELETE  (m_pSoundTouch);
	SAFE_RELEASE (m_pDSBuffer);
	SAFE_RELEASE (m_pDS);
 SAFE_RELEASE (pRenderClient);
 SAFE_RELEASE (pAudioClient);
 
	
	if (m_pReferenceClock)
	{
		SetSyncSource(NULL);
		SAFE_RELEASE (m_pReferenceClock);
	}

	if (m_pWaveFileFormat)
	{
		BYTE *p = (BYTE *)m_pWaveFileFormat;
		SAFE_DELETE_ARRAY(p);
	}

 if (hTask != NULL)
 {
  AvRevertMmThreadCharacteristics(hTask);
 }
}