bool isProcessAlive(U32 pid)
{
	return (bool) GetProcessVersion((DWORD)pid);
}