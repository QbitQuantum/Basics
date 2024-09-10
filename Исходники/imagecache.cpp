void ImageBase::ProcessTimerTick(time_t ts)
{
	WaitForSingleObject(g_hMutexIm, 3000);
	if (m_lRefCount == 0 && m_timestamp < ts)
		if (!g_imagecache.remove(this))
			delete this;

	ReleaseMutex(g_hMutexIm);
}