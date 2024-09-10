	~DWEntry()
	{
		if(thread)
		{
			FindCloseChangeNotification(h);
			thread->disconnect(this);
			thread->wait();
			delete thread;
		}
	}