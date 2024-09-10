void b3Win32ThreadSupport::startThreads(const Win32ThreadConstructionInfo& threadConstructionInfo)
{
	static int uniqueId = 0;
	uniqueId++;
	m_activeThreadStatus.resize(threadConstructionInfo.m_numThreads);
	m_completeHandles.resize(threadConstructionInfo.m_numThreads);

	m_maxNumTasks = threadConstructionInfo.m_numThreads;

	for (int i=0;i<threadConstructionInfo.m_numThreads;i++)
	{
		printf("starting thread %d\n",i);

		b3ThreadStatus&	threadStatus = m_activeThreadStatus[i];

		LPSECURITY_ATTRIBUTES lpThreadAttributes=NULL;
		SIZE_T dwStackSize=threadConstructionInfo.m_threadStackSize;
		LPTHREAD_START_ROUTINE lpStartAddress=&Thread_no_1;
		LPVOID lpParameter=&threadStatus;
		DWORD dwCreationFlags=0;
		LPDWORD lpThreadId=0;

		threadStatus.m_userPtr=0;

		sprintf(threadStatus.m_eventStartHandleName,"es%.8s%d%d",threadConstructionInfo.m_uniqueName,uniqueId,i);
		threadStatus.m_eventStartHandle = CreateEventA (0,false,false,threadStatus.m_eventStartHandleName);

		sprintf(threadStatus.m_eventCompletetHandleName,"ec%.8s%d%d",threadConstructionInfo.m_uniqueName,uniqueId,i);
		threadStatus.m_eventCompletetHandle = CreateEventA (0,false,false,threadStatus.m_eventCompletetHandleName);

		m_completeHandles[i] = threadStatus.m_eventCompletetHandle;

		HANDLE handle = CreateThread(lpThreadAttributes,dwStackSize,lpStartAddress,lpParameter,	dwCreationFlags,lpThreadId);
		switch(threadConstructionInfo.m_priority)
		{
		case 0:
		{
			SetThreadPriority(handle,THREAD_PRIORITY_HIGHEST);
			break;
		}
		case 1:
		{
			SetThreadPriority(handle,THREAD_PRIORITY_TIME_CRITICAL);
			break;
		}
		case 2:
		{
			SetThreadPriority(handle,THREAD_PRIORITY_BELOW_NORMAL);
			break;
		}
		
		default:
		{
			
		}

		}
		
		DWORD mask = 1;
		mask = 1<<mask;
		SetThreadAffinityMask(handle, mask);

		threadStatus.m_taskId = i;
		threadStatus.m_commandId = 0;
		threadStatus.m_status = 0;
		threadStatus.m_threadHandle = handle;
		threadStatus.m_lsMemory = threadConstructionInfo.m_lsMemoryFunc();
		threadStatus.m_userThreadFunc = threadConstructionInfo.m_userThreadFunc;

		printf("started %s thread %d with threadHandle %p\n",threadConstructionInfo.m_uniqueName,i,handle);
		
	}

}