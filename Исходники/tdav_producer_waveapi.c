int tdav_producer_waveapi_stop(tmedia_producer_t* self)
{
	tdav_producer_waveapi_t* producer = (tdav_producer_waveapi_t*)self;
	MMRESULT result;

	if(!self){
		TSK_DEBUG_ERROR("Invalid parameter");
		return -1;
	}

	if(!producer->started){
		TSK_DEBUG_WARN("Producer not started");
		return 0;
	}

	/* stop thread */
	if(producer->tid[0]){
		SetEvent(producer->events[1]);
		tsk_thread_join(&(producer->tid[0]));
	}

	/* should be done here */
	producer->started = tsk_false;

	if(producer->hWaveIn && (((result = waveInReset(producer->hWaveIn)) != MMSYSERR_NOERROR) || ((result = waveInClose(producer->hWaveIn)) != MMSYSERR_NOERROR))){
		print_last_error(result, "waveInReset/waveInClose");
	}

	return 0;
}