void dgThreads::CreateThreaded(dgInt32 threads)
{
  if (m_numOfThreads)
  {
    DestroydgThreads();
  }

#ifdef _WIN32
  if ((threads > 1) && (m_numberOfCPUCores > 1))
  {
    m_numOfThreads = GetMin(threads, m_numberOfCPUCores);

    m_emptySlot = CreateSemaphoreA(NULL, DG_MAXQUEUE, DG_MAXQUEUE, NULL);
    m_workToDo = CreateSemaphoreA(NULL, 0, DG_MAXQUEUE, NULL);
    m_exit = CreateEventA(NULL, TRUE, FALSE, NULL);

    InitializeCriticalSection(&m_criticalSection);

    m_topIndex = 0;
    m_bottomIndex = 0;
    m_workInProgress = 0;
    for (dgInt32 i = 0; i < m_numOfThreads; i++)
    {
      m_threadhandles[i] = (HANDLE) _beginthreadex(NULL, 0, ThreadExecute,
          &m_localData[i], 0, NULL);
    }
  }
#else
  if ((threads > 1) && (m_numberOfCPUCores > 1))
  {
#ifdef TARGET_OS_IPHONE
    m_numOfThreads = 0;
#else
    m_numOfThreads = (threads<m_numberOfCPUCores ? threads : m_numberOfCPUCores);
#endif

    m_emptySlot = DG_MAXQUEUE;
    m_workToDo = 0;
    m_workToDoSpinLock = 0;
    m_exit = false;
    m_criticalSection = 0;

    m_topIndex = 0;
    m_bottomIndex = 0;
    m_workInProgress = 0;

#ifndef TARGET_OS_IPHONE
    for(dgInt32 i=0; i < m_numOfThreads; i++)
    {
      pthread_create( &m_threadhandles[i], NULL, ThreadExecute, &m_localData[i]);
    }
#endif
  }
#endif
}