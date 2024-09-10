void *BarPlayerMacOSXThread(void *data){
	struct audioPlayer *player = data;
	
	char extraHeaders[25];
	void *ret = PLAYER_RET_OK;
    
	WaitressReturn_t wRet = WAITRESS_RET_ERR;
	
	/* init handles */
	player->waith.data = (void *) player;
	/* extraHeaders will be initialized later */
	player->waith.extraHeaders = extraHeaders;

    player->songPlayed = 0;
	switch (player->audioFormat) {
		case PIANO_AF_AACPLUS:
        {
            OSStatus err = AudioFileStreamOpen(player, StreamPropertyListenerProc, StreamPacketsProc, 
                                               kAudioFileAAC_ADTSType, &player->audioFileStream);
            if (err) 
                PRINTERROR ("Error opening stream!\n");
			player->waith.callback = BarPlayerAACCb;
        }
			break;

		case PIANO_AF_MP3:
		case PIANO_AF_MP3_HI:
        {
            OSStatus err = AudioFileStreamOpen(player, StreamPropertyListenerProc, StreamPacketsProc, 
                                               kAudioFileMP3Type, &player->audioFileStream);			
            if (err)
                PRINTERROR ("Error opening stream!\n");
			player->waith.callback = BarPlayerAACCb;
        }
			break;
			
		default:
			PRINTERROR ("Unsupported audio format!\n");
			return PLAYER_RET_OK;
			break;
	}
	
	player->mode = PLAYER_INITIALIZED;
	
	/* This loop should work around song abortions by requesting the
	 * missing part of the song */
	do {
		snprintf (extraHeaders, sizeof (extraHeaders), "Range: bytes=%zu-\r\n",
				  player->bytesReceived);
		wRet = WaitressFetchCall (&player->waith);
	} while (wRet == WAITRESS_RET_PARTIAL_FILE || wRet == WAITRESS_RET_TIMEOUT
			 || wRet == WAITRESS_RET_READ_ERR);
        
	switch (player->audioFormat) {
		case PIANO_AF_AACPLUS:
        case PIANO_AF_MP3:
		case PIANO_AF_MP3_HI:
            AudioQueueStop(player->audioQueue, false);
            AudioFileStreamClose(player->streamID);
            AudioQueueDispose(player->audioQueue, false);
			break;
		default:
			/* this should never happen: thread is aborted above */
			break;
	}
    
	WaitressFree (&player->waith);

	pthread_mutex_lock(&player->mutex);
	player->mode = PLAYER_FINISHED_PLAYBACK;
	pthread_cond_broadcast(&player->cond);
	pthread_mutex_unlock(&player->mutex);

	return ret;	
}