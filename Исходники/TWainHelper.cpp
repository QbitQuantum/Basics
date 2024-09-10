void CTWainHelper::LogMessage(char msg[])
{
#ifdef _DEBUG
	
	HFILE file = NULL;
	OFSTRUCT of;
	
	memset(&of, 0, sizeof(OFSTRUCT));
	
	if (OpenFile("c:\\twainapp.log", &of, OF_EXIST) == HFILE_ERROR)
	{
		//create if no exist
		file = OpenFile("c:\\twainapp.log", &of, OF_CREATE|OF_WRITE|OF_SHARE_DENY_NONE);
	}
	else
	{
		file = OpenFile("c:\\twainapp.log", &of, OF_WRITE|OF_SHARE_DENY_NONE);
	}
	
	//附加模式
	if (_llseek(file,0,FILE_END)==-1)
	{
		OutputDebugString("LogMessage _llseek failed\n");
	}
	
	if (_lwrite(file,msg,lstrlen(msg))==-1)
	{
		OutputDebugString("LogMessage _lwrite failed\n");
	}
	
	if (_lclose(file)==-1) 
	{
		OutputDebugString("LogMessage _lclose failed\n");
	}
	
#endif
	return;
}