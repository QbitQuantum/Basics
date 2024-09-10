	//--------------------------------------------------------------------------------
	unsigned long CSemaphore::Wait( unsigned long dwMilliseconds )
	{
		_WINQ_FCONTEXT( "CSemaphore::Wait" );
		unsigned long dwResult = 0;
		__QOR_PROTECT
		{
			CWaitHelper WaitHelper;
			dwResult = WaitHelper.WaitForSingleObject( m_Handle, dwMilliseconds );
		}__QOR_ENDPROTECT
		return dwResult;
	}