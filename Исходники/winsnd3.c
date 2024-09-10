static void winsnd_read_preprocess(MSFilter *f){
	WinSnd *d=(WinSnd*)f->data;
	MMRESULT mr;
	int i;
	int bsize;
	DWORD dwFlag;

	d->stat_input=0;
	d->stat_output=0;
	d->stat_notplayed=0;
	d->stat_minimumbuffer=WINSND_MINIMUMBUFFER;

	winsnd_apply_settings(d);
	/* Init Microphone device */
	dwFlag = CALLBACK_FUNCTION;
	if (d->dev_id != WAVE_MAPPER)
		dwFlag = WAVE_MAPPED | CALLBACK_FUNCTION;
	mr = waveInOpen (&d->indev, d->dev_id, &d->wfx,
	            (DWORD) read_callback, (DWORD)f, dwFlag);
	if (mr != MMSYSERR_NOERROR)
	{
	    ms_error("Failed to prepare windows sound device. (waveInOpen:0x%i)", mr);
		mr = waveInOpen (&d->indev, WAVE_MAPPER, &d->wfx,
					(DWORD) read_callback, (DWORD)d, CALLBACK_FUNCTION);
		if (mr != MMSYSERR_NOERROR)
		{
			d->indev=NULL;
			ms_error("Failed to prepare windows sound device. (waveInOpen:0x%i)", mr);
		    return ;
		}
	}
	bsize=WINSND_NSAMPLES*d->wfx.nAvgBytesPerSec/8000;
	ms_debug("Using input buffers of %i bytes",bsize);
	for(i=0;i<WINSND_NBUFS;++i){
		WAVEHDR *hdr=&d->hdrs_read[i];
		add_input_buffer(d,hdr,bsize);
	}
	d->running=TRUE;
	mr=waveInStart(d->indev);
	if (mr != MMSYSERR_NOERROR){
		ms_error("waveInStart() error");
		return ;
	}
#ifndef _TRUE_TIME
	ms_ticker_set_time_func(f->ticker,winsnd_get_cur_time,d);
#endif
}