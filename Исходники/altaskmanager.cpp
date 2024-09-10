//Main entry point.
int _tmain(int argc, _TCHAR* argv[])
{

	

	ZeroMemory(tskbuffer, sizeof(wchar_t) * 2048);
	m_logger = new AlCLogger(L"c://temp//taskmgr.log", true);

	//Read in the task file...
	//any tasks matching names within this file, will be auto killed!
	wchar_t* fileName = L"C:\\Alwyn\\dev\\c\\AlTaskManager\\Release\\taskmanager.ini";
	int taskCount = GetPrivateProfileInt(L"tasks", L"tasks.count", 0, fileName);

	if (taskCount < 1)
	{
		m_logger->debug("No tasks to manage...\r\n");
		goto exit;
	}

	m_Task_Thread = new AlTaskThread(m_logger);

	m_Task_Thread->tasksCount = taskCount;
	m_Task_Thread->tasks = new wchar_t*[m_Task_Thread->tasksCount];

	m_Task_Thread->timeOut = GetPrivateProfileInt(L"tasks", L"tasks.timeout", 1, fileName);

	for (int i=0; i<m_Task_Thread->tasksCount; i++)
	{
		//Buildup task name...
		swprintf_s(tskbuffer, L"tasks.%i\0", i+1);
		m_Task_Thread->tasks[i] = new wchar_t[1024];
		ZeroMemory(m_Task_Thread->tasks[i], sizeof(wchar_t) * 1024);

		GetPrivateProfileString(L"tasks", tskbuffer, L"", m_Task_Thread->tasks[i], sizeof(wchar_t) * 1024, fileName);
		_wcslwr_s(m_Task_Thread->tasks[i], sizeof(wchar_t) * 1024);

		swprintf_s(tskbuffer, L"Got a task name: #%i, '%s'\r\n\0", i, m_Task_Thread->tasks[i]);
		m_logger->debug(tskbuffer);
	}

	//Default stack size 64Kb
	m_Task_Thread->stackSize = 1024 * 64;
	m_logger->debug("Starting task manager..\r\n");
	m_Task_Thread->start();
	
	int v = 0;

	while (v != 9)
	{
		cout << "9 = quit task manager.\n";
		cin >> v;
	}


	m_Task_Thread->stop = true;
	while (!m_Task_Thread->completed)
	{
		Sleep(1);
		Yield();
	}


	m_logger->debug("Task manager has quit.\r\n");

exit:


	SAFE_DEL(m_Task_Thread);
	SAFE_DEL(m_logger);
	

	
	return 0;
}