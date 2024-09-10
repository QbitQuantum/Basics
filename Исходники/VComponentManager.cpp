// ---------------------------------------------------------------------------
// VComponentManager::RegisterComponentLibrary						[static]
// ---------------------------------------------------------------------------
// Load all component creators from a given library. Make sure that the
// library exports the VComponentLibrary interface.
//
VError VComponentManager::RegisterComponentLibrary( const VFilePath& inLibraryFile)
{
	DebugMsg("VComponentManager load %V\n", &inLibraryFile.GetPath());
	if (!IsInitialized())
		return vThrowError(VE_COMP_UNITIALISED);
	
	VError	error = VE_OK;
	
	VLibrary*	library;
	VArrayIteratorOf<VLibrary*>	iterator(*sComponentLibraries);
	
	// Iterate through libraries
	while ((library = iterator.Next()) != NULL)
	{
		if (library->IsSameFile(inLibraryFile))
		{
			error = vThrowError(VE_COMP_ALLREADY_REGISTRED);
			break;
		}
	}
	
	if (library == NULL)
	{
		library = new VLibrary(inLibraryFile);
		
		if (library != NULL)
		{
			if (!library->Load())
			{
				error = vThrowError(VE_COMP_CANNOT_LOAD_LIBRARY);
				library->Release();
				library = NULL;
			}
		}
		
		if (library != NULL)
		{
			// Make sure the library export the needed interface
			MainProcPtr	mainPtr = (MainProcPtr) library->GetProcAddress(kDEFAULT_MAIN_SYMBOL);
			GetNthComponentTypeProcPtr	fetchPtr = (GetNthComponentTypeProcPtr) library->GetProcAddress(kDEFAULT_GET_TYPES_SYMBOL);
			CreateComponentProcPtr	creatorPtr = (CreateComponentProcPtr) library->GetProcAddress(kDEFAULT_CREATE_SYMBOL);
			
			// Fetch all implemented components
			if (creatorPtr != NULL && fetchPtr != NULL && mainPtr != NULL)
			{
				sAccessingTypes->Lock();
				sAccessingChecked->Lock();
				
				(mainPtr)(kDLL_EVENT_REGISTER, library);
					
				CType	newType;
				sLONG	index = 1;
				while ((fetchPtr)(index, newType))
				{
					VIndex	oldPos = sComponentTypes->FindPos(newType);
					if (oldPos > 0)
					{
						// Assumes its allready installed using ProcPtr
						assert(sComponentProcs->GetNth(oldPos) != NULL);
						assert(sComponentLibraries->GetNth(oldPos) == NULL);
						
						sComponentLibraries->SetNth(library, oldPos);
					}
					else
					{
						// Add entries
						sComponentLibraries->AddTail(library);
						sComponentProcs->AddTail(NULL);
						sComponentTypes->AddTail(newType);
					}
					
					// Increment library refcount for each type
					library->Retain();
					
					index++;
		
					// Reset checking for unavailable components
					ResetComponentRequirements(newType, false);
				}
				
				sAccessingChecked->Unlock();
				sAccessingTypes->Unlock();
			}
			else
			{
				error = VE_COMP_BAD_LIBRARY_TYPE;
			}
			
			// Release library ('new' balance)
			library->Release();
		}
		else
		{
			error = VE_MEMORY_FULL;
		}
	}
	
	return error;
}