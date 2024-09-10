	int WaitForSomethingToRead()
	{
		for (; ; )
		{
			int available = Size();
			if (available > 0)
				return available;
			//this is a greedy spinlock.
			SwitchToThread();
			//NOTE: it's annoying right now because libsnes processes die and eat a whole core.
			//we need to gracefully exit somehow
		}
	}