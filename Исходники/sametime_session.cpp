void WakeThread(HANDLE hThread)
{
	QueueUserAPC(NullAPC, hThread, 0);
}