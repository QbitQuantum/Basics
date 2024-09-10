const char* MemoryManager::GetCallerForAllocation(AllocHeader* pAllocation)
{
#ifdef USE_STACKTRACE
	const size_t cnBufferSize=512;
	char szFile[cnBufferSize];
	char szFunc[cnBufferSize];
	unsigned int nLine;
	static char szBuff[cnBufferSize*3];

	strcpy(szFile,"??");
	nLine=0;

	DWORD64 nPC;
	for(int i=0;i<AllocHeader::cnMaxStackFrames;++i) {
		nPC=pAllocation->nPC[i];
		if(nPC==0)
			break;

		unsigned char byBuffer[sizeof(IMAGEHLP_SYMBOL64)+cnBufferSize];
		IMAGEHLP_SYMBOL64* pSymbol=(IMAGEHLP_SYMBOL64*)byBuffer;
		DWORD64 dwDisplacement;
		memset(pSymbol,0,sizeof(IMAGEHLP_SYMBOL64)+cnBufferSize);
		pSymbol->SizeOfStruct=sizeof(IMAGEHLP_SYMBOL64);
		pSymbol->MaxNameLength=cnBufferSize;
		if(!SymGetSymFromAddr64(GetCurrentProcess(),nPC,&dwDisplacement,pSymbol))
			strcpy(szFunc,"??");
		else {
			pSymbol->Name[cnBufferSize-1]='\0';
			if(strncmp(pSymbol->Name,"MemMgr::",8)==0) {
				// In MemMgr,keep going...
			} else if(strncmp(pSymbol->Name,"operator new",12)==0) {
				// In operator new or new[],keep going...
			} else if(strncmp(pSymbol->Name,"std::",5)==0) {
				// In STL code,keep going...
			} else {
				// Found the allocator (Or near to it)
				strcpy(szFunc,pSymbol->Name);
				break;
			}
		}
	}

	if(nPC!=0) {
		IMAGEHLP_LINE64 theLine;
		DWORD dwDisplacement;
		memset(&theLine,0,sizeof(theLine));
		theLine.SizeOfStruct=sizeof(theLine);
		if(!SymGetLineFromAddr64(GetCurrentProcess(),nPC,&dwDisplacement,&theLine)) {
			strcpy(szFile,"??");
			nLine=0;
		} else {
			const char* pszFile=strrchr(theLine.FileName,'\\');
			if(!pszFile) pszFile=theLine.FileName;
			else ++pszFile;
			strncpy(szFile,pszFile,cnBufferSize);
			nLine=theLine.LineNumber;
		}
	}

	sprintf(szBuff,"%s:%d (%s)",szFile,nLine,szFunc);
	return szBuff;
#else
	UNREFERENCED_PARAMETER(pAllocation);
	return "Stack trace unavailable";
#endif
}