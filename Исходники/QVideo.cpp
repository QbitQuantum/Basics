void QVideo::stop()
{
	if(m_video_decoder && m_video_loaded)
	{
		//m_video_decoder->restart();
		m_video_decoder->flushBuffers();
		seek(0, AVSEEK_FLAG_BACKWARD);
	}
	
	m_status = NotRunning;
	killTimer(m_play_timer);
	m_play_timer = 0;
	
	// Since there is no stop() or pause(), we dont need to touch m_run_time right now - it will be reset in play()
	m_total_runtime = 0;

	emit movieStateChanged(QMovie::NotRunning);
	
}