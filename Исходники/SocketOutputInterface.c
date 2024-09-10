void CALLBACK onThreadExit(ULONG_PTR dwParam)
{
	int err = onCleanSocket(threadStatus);
	ExitThread(err);
}