void DemuxThread::stopPlay()
{
	fprintf("stop demux thread\n");
	if(m_videoDecoder != NULL)
	{
		m_videoDecoder->exitThread();
		bool ret = m_videoDecoder->wait();
		if(!ret)
		{
			fprintf(stderr, "force to stop video thread\n");
		    m_videoDecoder->setThreadStatus(THREAD_STOP);
			m_videoDecoder->quit();		
		}
	}
	exitThread();	
	bool ret = wait();
	if(!ret)
	{
		fprintf("force to stop video thread\n");
		quit();
	}
	releaseVideoInfo();
}	