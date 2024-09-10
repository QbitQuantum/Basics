bool importX264Cfg()
{
	wchar_t cmdToRun[MAX_PATH];
	ZeroMemory(cmdToRun, sizeof(wchar_t)*MAX_PATH);
	StringCchPrintf(cmdToRun, MAX_PATH*sizeof(wchar_t), L"REG IMPORT %s", _szX264Cfg);
	_wsystem(cmdToRun);
	return true;
}