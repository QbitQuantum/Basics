static void
win32_play_data (Win32_Audio_Data *audio_data)
{	int thisread, readcount ;
		
	readcount = (audio_data->remaining > audio_data->bufferlen) ? audio_data->bufferlen : (int) audio_data->remaining ;

	thisread = (int) sf_read_short (audio_data->sndfile, (short *) (audio_data->whdr [audio_data->current].lpData), readcount) ;

	audio_data->remaining -= thisread ;

	if (thisread > 0)
	{	/* Fix buffer length is only a partial block. */
		if (thisread * sizeof (short) < audio_data->bufferlen)
			audio_data->whdr [audio_data->current].dwBufferLength = thisread * sizeof (short) ;

		/* Queue the WAVEHDR */
		waveOutWrite (audio_data->hwave, (LPWAVEHDR) &(audio_data->whdr [audio_data->current]), sizeof (WAVEHDR)) ;
		}
	else
	{	/* Stop playback */
		waveOutPause (audio_data->hwave) ;

		SetEvent (audio_data->Event) ;
		} ;

	audio_data->current = (audio_data->current + 1) % 2 ;

} /* win32_play_data */