	static void connectService() {
		Thread<worker_thread> *pThread = new Thread<worker_thread>(_T("tray-worker-thread"));
		pThread->createThread(worker_thread::init(_T("connect-service"), NULL));
	}