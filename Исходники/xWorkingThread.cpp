int xWorkingThread::stop()
{
	if(m_pRunner == NULL)
		return 1;
	exitThread(true);
	return 0;
}