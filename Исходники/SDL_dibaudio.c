void DIB_CloseAudio(_THIS)
{
	int i;

	/* Close up audio */
	if ( audio_event != INVALID_HANDLE_VALUE ) {
#if defined(_WIN32_WCE) && (_WIN32_WCE < 300)
		CloseSynchHandle(audio_event);
#else
		CloseHandle(audio_event);
#endif
	}
	if ( sound ) {
	    waveOutReset(sound);
	}

	/* Clean up mixing buffers */
	for ( i=0; i<NUM_BUFFERS; ++i ) {
		if ( wavebuf[i].dwUser != 0xFFFF ) {
			waveOutUnprepareHeader(sound, &wavebuf[i],
						sizeof(wavebuf[i]));
			wavebuf[i].dwUser = 0xFFFF;
		}
	}
	/* Free raw mixing buffer */
	if ( mixbuf != NULL ) {
		SDL_free(mixbuf);
		mixbuf = NULL;
	}

	if ( sound )
		waveOutClose(sound);
}