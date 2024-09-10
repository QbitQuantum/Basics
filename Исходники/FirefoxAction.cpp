vector <DWORD> FirefoxAction::_getProcessIDs()
{
	Runner runner;
	return runner.GetProcessID(wstring(L"firefox.exe"));
}