HANDLE ExecuteProcess( const std::string & exe, const std::string &args, const std::string & WorkDir )
{
	std::string cmd="\""+exe+"\"";
	if( args!="" )
		cmd+=" "+args;
	HANDLE h=ExecuteProcessO(cmd, WorkDir);
	if( h!=NULL )
		return h;
		
	SHELLEXECUTEINFOA TempInfo = {0};
	TempInfo.cbSize = sizeof(SHELLEXECUTEINFOA);
	TempInfo.fMask = 0; //SEE_MASK_NOCLOSEPROCESS
	TempInfo.hwnd = NULL;
	TempInfo.lpVerb = "runas";
	TempInfo.lpFile = exe.c_str();
	TempInfo.lpParameters = args.c_str();
	TempInfo.lpDirectory = WorkDir.c_str();
	TempInfo.nShow = SW_NORMAL;

	BOOL b=ShellExecuteExA(&TempInfo);
	
	if( b==TRUE )
	{
		return (HANDLE)1;
	}
	else
		return NULL;
}