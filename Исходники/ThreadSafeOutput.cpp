ThreadSafeOutput::ThreadSafeOutput()
{
	//set up critical section for below
	InitializeCriticalSection(&ourCritSection);
}