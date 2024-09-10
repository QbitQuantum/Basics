extern "C" __declspec (dllexport) inline BOOL IsDebuggerAttached()
{
	BOOL remoteDebugger;
	CheckRemoteDebuggerPresent(GetCurrentProcess(), &remoteDebugger);
	return IsDebuggerPresent() || remoteDebugger;
}