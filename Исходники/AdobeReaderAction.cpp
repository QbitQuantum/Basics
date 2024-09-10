vector <DWORD> AdobeReaderAction::_getProcessIDs()
{
	Runner runner;
	return runner.GetProcessID(wstring(L"AcroRd32.exe"));
}