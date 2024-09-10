inline UINT __stdcall LuaNetworkThread::WorkerThread(void* context)
{
	LuaNetworkThread* thread = (LuaNetworkThread*)context;
	thread->ThreadRun();

	_endthreadex(0);

	return 0;
}