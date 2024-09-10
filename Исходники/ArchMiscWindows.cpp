void
ArchMiscWindows::addBusyState(DWORD busyModes)
{
	s_busyState |= busyModes;
	setThreadExecutionState(s_busyState);
}