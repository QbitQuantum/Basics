void String_Init()
{
	void* Buffer;

	StringAlloc();

	Buffer = malloc(MAXTEXT);
	if (Buffer)
	{
#ifdef NO_PLUGINS
		{
			int n;
			HANDLE Module = GetModuleHandle(NULL);
			HRSRC Rsrc = FindResource(Module,MAKEINTRESOURCE(2000),T("LANGTAR"));
			if (Rsrc)
			{
				int Size = SizeofResource(Module,Rsrc);
				HGLOBAL Global = LoadResource(Module,Rsrc);
				if (Global)
				{
					void* p = LockResource(Global);
					if (p)
					{
						stream* Stream = StreamOpenMem(p,Size);
						if (Stream)
						{
							LoadTGZ(Stream,Buffer);
							StreamCloseMem(Stream);
						}
					}
				}
			}
			for (n=2000;(Rsrc = FindResource(Module,MAKEINTRESOURCE(n),T("LANG")))!=NULL;++n)
			{
				int Size = SizeofResource(Module,Rsrc);
				HGLOBAL Global = LoadResource(Module,Rsrc);
				if (Global)
				{
					void* p = LockResource(Global);
					if (p)
						StringAddText(p,Size);
				}
			}
		}

#endif
#ifndef NO_LANG
		{
			tchar_t Path[MAXPATH];
			stream* p;

			GetModulePath(Path,T("common.dll"));
			tcscat_s(Path,TSIZEOF(Path),T("language.tgz"));
			p = StreamOpen(Path,0);
			if (p)
			{
				LoadTGZ(p,Buffer);
				StreamClose(p);
			}

			GetModulePath(Path,T("common.dll"));
			FindFiles(Path,T("*.txt"),LoadTXT,Buffer);
		}
#endif
		free(Buffer);
	}
}