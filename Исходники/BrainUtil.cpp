bool BrainUtil::RunSystemCommand(const CString& cmd)
{
    CString tempCmd = cmd;
    //int ret = _wsystem(tempCmd.GetBuffer());
    //DATA_ASSERT(0 == ret); // Don't aseert the failure is accepted.

	// Get the output from the pipe
	FILE* pipe = _wpopen(tempCmd.GetBuffer(), _T("r"));
	if (!pipe) 
	{
		return false;
		LogOut(_T("Error: failed to create the piple."));
	}

	TCHAR buffer[256];
	while(!feof(pipe)) {
		if(fgetws(buffer, 256, pipe) != NULL)
		{
			LogOut(buffer);
		}
	}
	int ret = _pclose(pipe);

    return 0 == ret;
}