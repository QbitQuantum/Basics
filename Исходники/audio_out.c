static void
win32_play (get_audio_callback_t callback, AUDIO_OUT *audio_out, void *callback_data)
{	WIN32_AUDIO_OUT	*win32_out ;
	int		error ;

	if ((win32_out = (WIN32_AUDIO_OUT*) audio_out) == NULL)
	{	printf ("win32_play : AUDIO_OUT is NULL.\n") ;
		return ;
		} ;

	if (win32_out->magic != WIN32_MAGIC)
	{	printf ("win32_play : Bad magic number (%d %d).\n", win32_out->magic, WIN32_MAGIC) ;
		return ;
		} ;

	/* Set the callback function and callback data. */
	win32_out->callback = callback ;
	win32_out->callback_data = callback_data ;

	win32_out->whdr [0].lpData = (char*) win32_out->short_buffer ;
	win32_out->whdr [1].lpData = ((char*) win32_out->short_buffer) + sizeof (win32_out->short_buffer) / 2 ;

	win32_out->whdr [0].dwBufferLength = sizeof (win32_out->short_buffer) / 2 ;
	win32_out->whdr [1].dwBufferLength = sizeof (win32_out->short_buffer) / 2 ;

	win32_out->bufferlen = sizeof (win32_out->short_buffer) / 2 / sizeof (short) ;

	/* Prepare the WAVEHDRs */
	if ((error = waveOutPrepareHeader (win32_out->hwave, &(win32_out->whdr [0]), sizeof (WAVEHDR))))
	{	printf ("waveOutPrepareHeader [0] failed : %08X\n", error) ;
		waveOutClose (win32_out->hwave) ;
		return ;
		} ;

	if ((error = waveOutPrepareHeader (win32_out->hwave, &(win32_out->whdr [1]), sizeof (WAVEHDR))))
	{	printf ("waveOutPrepareHeader [1] failed : %08X\n", error) ;
		waveOutUnprepareHeader (win32_out->hwave, &(win32_out->whdr [0]), sizeof (WAVEHDR)) ;
		waveOutClose (win32_out->hwave) ;
		return ;
		} ;

	waveOutRestart (win32_out->hwave) ;

	/* Fake 2 calls to the callback function to queue up enough audio. */
	win32_audio_out_callback (0, MM_WOM_DONE, (DWORD) win32_out, 0, 0) ;
	win32_audio_out_callback (0, MM_WOM_DONE, (DWORD) win32_out, 0, 0) ;

	/* Wait for playback to finish. The callback notifies us when all
	** wave data has been played.
	*/
	WaitForSingleObject (win32_out->Event, INFINITE) ;

	waveOutPause (win32_out->hwave) ;
	waveOutReset (win32_out->hwave) ;

	waveOutUnprepareHeader (win32_out->hwave, &(win32_out->whdr [0]), sizeof (WAVEHDR)) ;
	waveOutUnprepareHeader (win32_out->hwave, &(win32_out->whdr [1]), sizeof (WAVEHDR)) ;

	waveOutClose (win32_out->hwave) ;
	win32_out->hwave = 0 ;

	return ;
} /* win32_play */