bool ll_get_stack_trace(std::vector<std::string>& lines)
{
	const S32 MAX_STACK_DEPTH = 32;
	const S32 STRING_NAME_LENGTH = 200;
	const S32 FRAME_SKIP = 2;
	static BOOL symbolsLoaded = false;
	static BOOL firstCall = true;

	HANDLE hProc = GetCurrentProcess();

	// load the symbols if they're not loaded
	if(!symbolsLoaded && firstCall)
	{
		symbolsLoaded = SymInitialize(hProc, NULL, true);
		firstCall = false;
	}

	// if loaded, get the call stack
	if(symbolsLoaded)
	{
		// create the frames to hold the addresses
		void* frames[MAX_STACK_DEPTH];
		memset(frames, 0, sizeof(void*)*MAX_STACK_DEPTH);
		S32 depth = 0;

		// get the addresses
		depth = RtlCaptureStackBackTrace_fn(FRAME_SKIP, MAX_STACK_DEPTH, frames, NULL);

		IMAGEHLP_LINE64 line;
		memset(&line, 0, sizeof(IMAGEHLP_LINE64));
		line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

		// create something to hold address info
		PIMAGEHLP_SYMBOL64 pSym;
		pSym = (PIMAGEHLP_SYMBOL64)malloc(sizeof(IMAGEHLP_SYMBOL64) + STRING_NAME_LENGTH);
		memset(pSym, 0, sizeof(IMAGEHLP_SYMBOL64) + STRING_NAME_LENGTH);
		pSym->MaxNameLength = STRING_NAME_LENGTH;
		pSym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);

		// get address info for each address frame
		// and store
		for(S32 i=0; i < depth; i++)
		{
			std::stringstream stack_line;
			BOOL ret;

			DWORD64 addr = (DWORD64)frames[i];
			ret = SymGetSymFromAddr64(hProc, addr, 0, pSym);
			if(ret)
			{
				stack_line << pSym->Name << " ";
			}

			DWORD dummy;
			ret = SymGetLineFromAddr64(hProc, addr, &dummy, &line);
			if(ret)
			{
				std::string file_name = line.FileName;
				std::string::size_type index = file_name.rfind("\\");
				stack_line << file_name.substr(index + 1, file_name.size()) << ":" << line.LineNumber; 
			}

			lines.push_back(stack_line.str());
		}
		
		free(pSym);

		// TODO: figure out a way to cleanup symbol loading
		// Not hugely necessary, however.
		//SymCleanup(hProc);
		return true;
	}
	else
	{
		lines.push_back("Stack Trace Failed.  PDB symbol info not loaded");
	}

	return false;
}