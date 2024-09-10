/********************************************************************************************
  Function		: WaitTimeout    
  DateTime		: 2010/6/10 9:42	
  Description	: 等待条件变量，超时返回
  Input			: INT mseconds：等待的时间，毫秒
  Output		: NULL
  Return		: 返回0成功，其他表示失败
  Note			:				// 备注
********************************************************************************************/
INT CGSCond::WaitTimeout(INT mseconds)
{
#ifdef _WIN32

	INT iRet = -1;
	if (WaitForSingleObject(m_mutex,mseconds) == WAIT_OBJECT_0)
	{	
		iRet = SignalObjectAndWait(m_mutex, m_GSCond,mseconds,FALSE) == WAIT_OBJECT_0 ? 0 : -1;
		ResetEvent(m_GSCond);
	}
	return	iRet;

#elif _LINUX
	INT32	iRet = 0;
	struct timeval struTimeVal;
	struct timespec struTimeSpec;
	gettimeofday(&struTimeVal, NULL);
	struTimeSpec.tv_sec  = mseconds/1000;
	struTimeSpec.tv_nsec =1000L *(struTimeVal.tv_usec+(mseconds-struTimeSpec.tv_sec*1000)*1000L);
	struTimeSpec.tv_sec += struTimeVal.tv_sec;
	
	m_CondMutex->Lock();
	iRet = pthread_cond_timedwait( &m_GSCond, &m_CondMutex->m_GSMutex, &struTimeSpec);
	m_CondMutex->Unlock();

	return iRet;
#endif
}