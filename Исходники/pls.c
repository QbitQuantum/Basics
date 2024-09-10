static int ReadList(pls* p,tchar_t* Path,int PathLen,tchar_t* DispName,int DispNameLen,tick_t* Length)
{
	tchar_t s[MAXLINE];
	int No,Len;
	int Result = ERR_END_OF_FILE;

	while (Result==ERR_END_OF_FILE && ParserLine(&p->Playlist.Parser,s,MAXLINE))
	{
		tcsuprto(s,'=');
		if (stscanf(s,T("FILE%d ="),&No)==1)
		{
			if (No != p->Playlist.No && Fill(p,Path,PathLen,DispName,DispNameLen,Length))
				Result = ERR_NONE;
			p->Playlist.No = No;
			tcscpy_s(p->File,TSIZEOF(p->File),tcschr(s,'=')+1);
		}
		else
		if (stscanf(s,T("TITLE%d ="),&No)==1)
		{
			if (No != p->Playlist.No && Fill(p,Path,PathLen,DispName,DispNameLen,Length))
				Result = ERR_NONE;
			p->Playlist.No = No;
			tcscpy_s(p->Title,TSIZEOF(p->Title),tcschr(s,'=')+1);
		}
		else
		if (stscanf(s,T("LENGTH%d = %d"),&No,&Len)==2)
		{
			if (No != p->Playlist.No && Fill(p,Path,PathLen,DispName,DispNameLen,Length))
				Result = ERR_NONE;
			p->Playlist.No = No;
			p->Length = Len;
		}
	}

	if (Result==ERR_END_OF_FILE && Fill(p,Path,PathLen,DispName,DispNameLen,Length))
		Result = ERR_NONE;

	return Result;
}