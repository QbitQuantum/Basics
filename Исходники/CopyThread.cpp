void CCopyThread::DoCopyFile(string source, string dest)
{
	source = str_replaceallA(source,"\\\\","\\");
	dest = str_replaceallA(dest,"\\\\","\\");


	File_Size.QuadPart = File_Prog.QuadPart = 0;
	SetCurFile(source);

	if (Action == CDA_SDMODE)
	{
		//DebugMsg("Move %s to %s",source.c_str(),dest.c_str());
		if (MoveFile(source.c_str(),dest.c_str()))
			Total_FilesCopied++;
	} else {
		//DebugMsg("Copy %s to %s",source.c_str(),dest.c_str());
		if (CopyFileEx(source.c_str(),dest.c_str(),CopyProgressRoutine,(void*)this,NULL,0))
			Total_FilesCopied++;
	}

	if (Action == CDA_MOVEFILES)
	{
		//DebugMsg("_unlink %s",source.c_str());
		_unlink(source.c_str());
	}

	// add file progress to total progress and reset file stuff
	Total_Prog.QuadPart += File_Prog.QuadPart;
	File_Prog.QuadPart = 0;
	File_Size.QuadPart = 0;
}