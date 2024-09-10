/*
 * Destroy stream.
 */
PJ_DEF(pj_status_t) pjmedia_snd_stream_close(pjmedia_snd_stream *stream)
{
    unsigned i;

    PJ_ASSERT_RETURN(stream != NULL, PJ_EINVAL);

    pjmedia_snd_stream_stop(stream);

    if (stream->thread)
    {
	SetEvent(stream->thread_quit_event);
	pj_thread_join(stream->thread);
	pj_thread_destroy(stream->thread);
	stream->thread = NULL;
    }

    /* Unprepare the headers and close the play device */
    if (stream->play_strm.hWave.Out)
    {
	waveOutReset(stream->play_strm.hWave.Out);
	for (i = 0; i < stream->play_strm.dwMaxBufIdx; ++i)
	    waveOutUnprepareHeader(stream->play_strm.hWave.Out, 
				   &(stream->play_strm.WaveHdr[i]),
				   sizeof(WAVEHDR));
	waveOutClose(stream->play_strm.hWave.Out);
	stream->play_strm.hWave.Out = NULL;
    }

    /* Close the play event */
    if (stream->play_strm.hEvent)
    {
	CloseHandle(stream->play_strm.hEvent);
	stream->play_strm.hEvent = NULL;
    }

    /* Unprepare the headers and close the record device */
    if (stream->rec_strm.hWave.In)
    {
	waveInReset(stream->rec_strm.hWave.In);
	for (i = 0; i < stream->play_strm.dwMaxBufIdx; ++i)
	    waveInUnprepareHeader(stream->rec_strm.hWave.In, 
				  &(stream->rec_strm.WaveHdr[i]),
				  sizeof(WAVEHDR));
	waveInClose(stream->rec_strm.hWave.In);
	stream->rec_strm.hWave.In = NULL;
    }

    /* Close the record event */
    if (stream->rec_strm.hEvent)
    {
	CloseHandle(stream->rec_strm.hEvent);
	stream->rec_strm.hEvent = NULL;
    }

    pj_pool_release(stream->pool);

    return PJ_SUCCESS;
}