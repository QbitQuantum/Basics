void AbsPath(tchar_t* Abs, int AbsLen, const tchar_t* Path, const tchar_t* Base)
{
	if (Base && GetProtocol(Base,NULL,0,NULL)!=Base && (Path[0] == '/' || Path[0] == '\\') &&
        (Path[1] != '/' && Path[1] != '\\'))
	{
		tchar_t* s;
		bool_t HasHost;

		tcscpy_s(Abs,AbsLen,Base);
		s = (tchar_t*)GetProtocol(Abs,NULL,0,&HasHost);
		if (!HasHost)
		{
			// keep "mime://" from Base
			++Path;
			*s = 0;
		}
		else
		{
			// keep "mime://host" from Base
			tchar_t *a,*b;
			a = tcschr(s,'\\');
			b = tcschr(s,'/');
			if (!a || (b && b<a))
				a=b;
			if (a)
				*a=0;
		}
	}
	else
	if (Base && GetProtocol(Path,NULL,0,NULL)==Path && Path[0] != '/' && Path[0] != '\\' &&
		!(Path[0] && Path[1]==':' && (Path[2]=='\\' || Path[2]=='\0')))
	{	
		// doesn't have mime or drive letter or pathdelimiter at the start
		const tchar_t* MimeEnd = GetProtocol(Base,NULL,0,NULL);
		tcscpy_s(Abs,AbsLen,Base);

#if defined(TARGET_WIN) || defined(TARGET_SYMBIAN)
		if (MimeEnd==Base)
			AddPathDelimiter(Abs,AbsLen);
		else
#endif
		if (MimeEnd[0])
			AddPathDelimiter(Abs,AbsLen);
	}
	else
		Abs[0] = 0;

	tcscat_s(Abs,AbsLen,Path);
    AbsPathNormalize(Abs,AbsLen);
}