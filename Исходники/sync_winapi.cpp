	void notify()
	{
		WakeAllConditionVariable(&cv);
	}