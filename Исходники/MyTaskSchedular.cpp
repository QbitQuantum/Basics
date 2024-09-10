	void Run(){
		m_threadid = GetCurrentThreadId(); 
		if (prevReply)
			prevReply->getReply<int>();
		pTask->operator()();
		evt.Set();

		printf("Task %s run at thread %Iu\n", m_desc.c_str(), m_threadid);
	}