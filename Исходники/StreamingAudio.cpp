/* ------------------------------------------------------------------------------------ */
int StreamingAudio::Delete()
{
	if(ogg)
	{
		if(Ogg == NULL)
			return RGF_FAILURE;

		Ogg->Stop();
		delete Ogg;
		Ogg = NULL;
		return RGF_SUCCESS;
	}

	timeKillEvent(m_nTimerID);							// Kill timer

	if(mp3)
	{
		if(Mpeg3 == NULL)
			return RGF_FAILURE;

		Mpeg3->StopMp3();
		delete Mpeg3;
		Mpeg3 = NULL;
		return RGF_SUCCESS;
	}

	// Check for stream availability
	if(m_pStream == NULL)
		return RGF_FAILURE;								// No stream

	Stop();												// Stop playback

	return RGF_SUCCESS;
}