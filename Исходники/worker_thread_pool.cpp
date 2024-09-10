    WorkerThread(WorkerThreadPool *owner, WorkerThreadPool::Priority p) 
	: m_owner(owner),
	  m_priority(p),
	  m_thread(Bind(this).To<&WorkerThread::Run>())
	{}