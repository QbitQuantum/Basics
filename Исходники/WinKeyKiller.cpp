BOOL WINAPI DisableWinKey() 
{
	//http://ru.stackoverflow.com/q/510916/207326
	//Глобальный отваливается!
	threadId = GetWindowThreadProcessId(GetShellWindow(), nullptr);
	hHook = SetWindowsHookEx(WH_CBT, CBTProc, GetModuleHandleA("WinKeyKiller.dll"), threadId);
	return BOOL(hHook);
}