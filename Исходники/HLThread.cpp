	void pause() const
	{
		_mutex.lock();
		SuspendThread(_handle);
		_mutex.unlock();
	}