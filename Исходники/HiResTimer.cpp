	void Update()
	{
		Start = Stop;
		QueryPerformanceCounter(&Stop);
	}