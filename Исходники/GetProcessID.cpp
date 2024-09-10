bool getSetOfProcessID(string processName, std::vector<DWORD>*SetOfPID)
{
    wstring wscons = stringToWidestring(processName);
    LPCTSTR p_Name = wscons.c_str();
    GetProcessID(p_Name, *SetOfPID);
    if (SetOfPID->empty())		// Process is not running
    {
        return false;
    }
    return true;
}