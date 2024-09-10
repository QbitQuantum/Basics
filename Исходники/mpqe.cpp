int main(int argc, char** argv)
{
	char version[] = "1.4";
	int hMPQ = 0;
	int hFile = 0;
	int FileSize = 0;
	int FileRead = 0;
	size_t slen = 0;
	mpqeOptions op;
	AddressTable at;
	op.option_verbose = false;
	op.option_outdir = NULL;
	op.option_lowercase = false;
	op.option_baseMPQ = NULL;
	op.option_searchglob = NULL;
	op.option_skipdirstructure = false;
	char* curdir;
	char* errbuf;
	
	printf("MPQ-Extractor v%s by WRS", version);
	if(!LoadAddresses(&at))
	{
		return -1;
	}
	printf(" powered by %s\n", at.pMpqGetVersionString());
	SFMPQVERSION v = at.pSFMpqGetVersion();
	printf("version: %d.%d.%d.%d\n", v.Major, v.Minor, v.Revision, v.Subrevision);
	if(argc<2)
	{
		ShowHelp();
		return -1;
	}
	errbuf = new char[ERRBUF_SIZE];
	curdir = new char[MAX_PATH];
	if(_getcwd(curdir, MAX_PATH) == NULL)
	{
		_strerror_s(errbuf, ERRBUF_SIZE, NULL);
		fprintf(stderr,"Unable to get current working directory : %s\n", errbuf);
		strcpy_s(curdir,MAX_PATH,".");
	}
	for(int i = 1; i < argc; ++i)
	{
		if(_stricmp(argv[i],"/p")==0) // use patch files if available
		{
// this can be a major slowdown in a batch file processing several MPQs
// for speed, extract all the other MPQs first then the patch-*.mpq last
// don't fatal-error out, just print warning message
			printf("Ignoring /p option (removed)\n");
		}
		else if(_stricmp(argv[i],"/l")==0)
		{
			printf("Lowercase output: Enabled\n");
			op.option_lowercase = true;
		}
		else if(_stricmp(argv[i],"/v")==0)
		{
			printf("Verbose output: Enabled\n");
			op.option_verbose = true;
		}
		else if(_stricmp(argv[i],"/d")==0)
		{
			if((i+1)>=argc)
			{
				fprintf(stderr,"Fatal: No output directory specified for /d\n");
				ShowHelp();
				return -1;
			}
			printf("Output directory: %s\n", argv[++i]);
			if(op.option_outdir != NULL)
			{
				delete [] op.option_outdir;
			}
			slen = strlen(argv[i])+1;
			op.option_outdir = new char[slen];
			strcpy_s(op.option_outdir, slen, argv[i]);
		}
		else if(_stricmp(argv[i],"/s")==0)
		{
			op.option_skipdirstructure = true;
			printf("Skipping directory structure creation\n");
		}
		else if(argv[i][0]=='/')
		{
			fprintf(stderr,"Fatal: Unknown option %s\n", argv[i]);
			ShowHelp();
			return -1;
		}
		else
		{
			if(op.option_baseMPQ == NULL)
			{
				slen = strlen(argv[i])+1;
				op.option_baseMPQ = new char[slen];
				strcpy_s(op.option_baseMPQ, slen, argv[i]);
			}
			else
			{
				if(op.option_searchglob != NULL)
				{
					delete [] op.option_searchglob;
				}
				slen = strlen(argv[i]) + 1;
				op.option_searchglob = new char[slen];
				strcpy_s(op.option_searchglob, slen, argv[i]);
			}
		}
	}
	if(op.option_baseMPQ == NULL)
	{
		fprintf(stderr,"Fatal: Did not provide MPQ file for extraction!\n");
		ShowHelp();
		return -1;
	}
	if(op.option_outdir == NULL)
	{
		op.option_outdir = new char[16];
		strcpy_s(op.option_outdir, 16, "MPQOUT");
	}
	if(strchr(op.option_baseMPQ,'\\')) // contains a backslash, change directory
	{
		char* d = op.option_baseMPQ;
		char* p = strrchr(op.option_baseMPQ,'\\');
		*p = '\0';
		p++;
		op.option_baseMPQ = p;
		if(_chdir(d)==-1)
		{
			_strerror_s(errbuf, ERRBUF_SIZE, NULL);
			fprintf(stderr,"Unable to change directory to %s : %s\n", d, errbuf);
			return -1;
		}
	}

	WIN32_FIND_DATA fd;
	HANDLE hf = FindFirstFile(op.option_baseMPQ, &fd);
	if(hf == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr,"Fatal: Could not open MPQ archive %s Error: %s\n", op.option_baseMPQ, GetErrorText(GetLastError()));
		_chdir(curdir);
		return -1;
	}
	// first, get number of matching mpq files ...
	DWORD nFiles = 1;
	while(GetLastError()!=ERROR_NO_MORE_FILES)
	{
		if(FindNextFile(hf, &fd))
		{
			++nFiles;
		}
	}
	FindClose(hf);
	// got number of files, now fill information
	FileList* fList = new FileList[nFiles];
	hf = FindFirstFile(op.option_baseMPQ, &fd);
	if(hf == INVALID_HANDLE_VALUE) // how did this happen? it was valid before!
	{
		fprintf(stderr,"Fatal: Could not open MPQ archive %s Error: %s\n", op.option_baseMPQ, GetErrorText(GetLastError()));
		_chdir(curdir);
		return -1;
	}
	// first, get number of matching mpq files ...
	DWORD index;
	for( index=0; index<nFiles; ++index )
	{
		fList[index].fwtime.HighPart = fd.ftLastWriteTime.dwHighDateTime;
		fList[index].fwtime.LowPart = fd.ftLastWriteTime.dwLowDateTime;
		fList[index].fname = new char[strlen(fd.cFileName)+1];
		strcpy(fList[index].fname, fd.cFileName);
		while(!FindNextFile(hf, &fd))
		{
			if(GetLastError()==ERROR_NO_MORE_FILES)
			{
				nFiles = index+1;
				break;
			}
		}
	}
	// got all mpq file names and last-write-times, now sort them (process oldest first)
	if(nFiles > 1) // no need to sort if there's only one
	{
		FileList tmp;
		// this is probably a slow sorter, but how many mpqs are there going to be anyway?
		for(index=1; index<nFiles; ++index)
		{
			if(fList[index-1].fwtime.QuadPart < fList[index].fwtime.QuadPart) // swap these
			{
				tmp.fname = fList[index].fname;
				tmp.fwtime = fList[index].fwtime;
				fList[index].fname = fList[index-1].fname;
				fList[index].fwtime = fList[index-1].fwtime;
				fList[index-1].fname = tmp.fname;
				fList[index-1].fwtime = tmp.fwtime;
				index = 0; // start over
			}
		}
	}
	// now process the mpqs
	for( index=0; index<nFiles; ++index )
	{
		mpqExtract(&at, &op, fList[index].fname);
	}
	_chdir(curdir);
	delete [] curdir;
	delete [] errbuf;
	return 0;
}