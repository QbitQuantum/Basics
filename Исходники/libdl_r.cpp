//-----------------------------------------------------------------------------
//Function Name : TInt SearchSymbolByLoadordering(TE32ExpSymInfoHdr* symInfoHeader
//							, char* aFileName, const char* aName, 
//							RPointerArray<TE32ExpSymInfoHdr>& aSearchedDlls,
//							void*& aSymAddress)
//Description   : To search for symbol named name in statically dependent dll 
//				  on aSymInfoHeader, it may be belonging to EXE or a DLL, also 
//				  dependencies of dependencies using Load-ordering. It also sets
//				  valid address in aSymAddress if name found, and all sll it searched in 
//				  aSearchedDlls param.	
//Return Value  : KErrNone if symbol found otherwise system wide error codes.
//-----------------------------------------------------------------------------
TInt SearchSymbolByLoadordering(const TE32ExpSymInfoHdr* symInfoHeader, const char* aFileName,
							    const char* aName,
							    RPointerArray<TE32ExpSymInfoHdr>& aSearchedDlls,
							    void*& aSymAddress)
	{
	//This is used as stack for Load-ordering or Depthfirst search.
	RArray<TImageData> dependentDllStack;
	//here on emulator we need two things one is Name to find symbol in that list,
	//second is TE32ExpSymInfoHdr to find dependencies
	TImageData imageData((char*)aFileName, (TE32ExpSymInfoHdr*)symInfoHeader);
	aSymAddress = NULL;
	//Add exe on the stack
	TInt err = dependentDllStack.Append(imageData);
	if ( KErrNone != err )
		{
		dependentDllStack.Close();
		return KErrNoMemory;
		}

	TE32ExpSymInfoHdr* tempSymInfoHeader = NULL;
	TInt lastIdx = 0;
	char* curDll = NULL;
	char* dependentDll = NULL;
	HMODULE handleToDll = NULL;
	TPtrC8 tempPtr;
	TBuf<KMaxFileName> dependentfileName;
	//Retunn address would be stored in this
	void* symAddr = NULL;
	//user to maintain load ordering
	RArray<TImageData> curDependentDll;
	TImageData tempImageData;
	//Depth First search for Load-ordering.
	while ( lastIdx >= 0 )
		{
		//Take first dll on the stack i.e. topmost
	    imageData = dependentDllStack[lastIdx];
	    symInfoHeader = imageData.iSymInfoHeader;
		//Remove from stack
	    dependentDllStack.Remove(lastIdx);

	    if(!symInfoHeader)
	    	{
	    	//skip non-std binaries...
		    lastIdx = dependentDllStack.Count() - 1;
	    	continue;
	    	}

		curDll = imageData.iFileName;
	 	tempPtr.Set((unsigned char*)curDll, strlen(curDll));
		dependentfileName.Copy(tempPtr);
		TParsePtr pParser(dependentfileName);
		dependentfileName = pParser.NameAndExt();
	  	//Search in this dll's symbol table	
		handleToDll = Emulator::GetModuleHandle(dependentfileName.PtrZ());
		symAddr = Emulator::GetProcAddress(handleToDll,aName);
		//Check if Symbol is found
		if( symAddr )
			{
			dependentDllStack.Close();
			aSymAddress = symAddr;
			return KErrNone;
			}
		//Add this dll to list of searched dlls
		err = aSearchedDlls.Append(symInfoHeader);
		if ( KErrNone != err )
			{
			dependentDllStack.Close();
			return KErrNoMemory;
			}
		dependentDll = (char*) symInfoHeader + sizeof(TE32ExpSymInfoHdr);
	
		//if this image is an exe - the these would be some symbols
		if ( symInfoHeader->iSymCount )
			{//skip all symbol addresse
			char* curSymbolStr = dependentDll + (KFourByteOffset * symInfoHeader->iSymCount);
			//skip all symbol names
			for (TInt i = 0; i < symInfoHeader->iSymCount; ++i )
				{
				curSymbolStr += strlen(curSymbolStr) + 1;
				}
			//initialise first dependent dll name	
			dependentDll = curSymbolStr;
			}
		//Store names of all dependent dlls of current dll/exe store there name in 
		//curDependentDll. This is done to maintain load ordering.
		for (TInt i = 0; i < symInfoHeader->iDllCount; ++i)
			{
			tempPtr.Set((unsigned char*)dependentDll, strlen(dependentDll));
			dependentfileName.Copy(tempPtr);
			handleToDll = Emulator::GetModuleHandle(dependentfileName.PtrZ());
			Emulator::TModule aModule((HINSTANCE)handleToDll);
			tempSymInfoHeader  = (TE32ExpSymInfoHdr*)aModule.Section(KWin32SectionName_NmdExpData);
			if ( tempSymInfoHeader && aSearchedDlls.Find(tempSymInfoHeader) == KErrNotFound )
				{
				tempImageData.iFileName = dependentDll;
				tempImageData.iSymInfoHeader = tempSymInfoHeader;
				err = curDependentDll.Append(tempImageData);
				if ( KErrNone != err )
					{
					dependentDllStack.Close();
					curDependentDll.Close();
					return KErrNoMemory;
					}
				}
			//advance to next dependent dll	
			dependentDll += tempPtr.Length() + 1;
			}
		//add in load order to dependentDllStack
		for (TInt i = curDependentDll.Count() - 1; i >= 0; --i)
			{
			err = dependentDllStack.Append(curDependentDll[i]);
			if ( KErrNone != err )
				{
				dependentDllStack.Close();
				curDependentDll.Close();
				return KErrNoMemory;
				}
			}
		curDependentDll.Close();	
		lastIdx = dependentDllStack.Count() - 1;	
		}
	dependentDllStack.Close();
	return KErrNotFound;
	}