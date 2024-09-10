	void wait()
	{
		DWORD result;
		
		while(!canceled)
		{
			Py_BEGIN_ALLOW_THREADS
			result = WaitForSingleObject( handle, 100 );
			Py_END_ALLOW_THREADS
			
			if(result!=WAIT_TIMEOUT)
			{
				break;
			}
		}

		if(canceled) return;
		
		if(result==WAIT_OBJECT_0)
		{
			FindNextChangeNotification(handle);
		}
		else if(result==WAIT_ABANDONED)
		{
			canceled = true;
		}
	}