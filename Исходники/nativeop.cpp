BOOL OpMenuLoad::LoadFile(CCLexFile* pFileToLoad, UINT32 nPrefFilter)
{
	// Make sure we have a valid file to load.
/*	TRACEUSER( "JustinF", _T("In OpMenuLoad::LoadFile(%p, %u)\n"),
				(LPVOID) pFileToLoad, nPrefFilter);
*/	ERROR3IF(!pFileToLoad, "Null CCLexFile* in OpMenuLoad::LoadFile");
	
	// Find out the position of the filter selected by the user in the open dialog
	INT32 SelectedPos = 0;

#if !defined(EXCLUDE_FROM_RALPH) && !defined(EXCLUDE_FROM_XARALX)
	SelectedPos = BaseFileDialog::SelectedFilter;
#endif

	// Go get the first filter in the list
	Filter* pFilter = Filter::GetFirst();

	// Do we know which filter was used? (we know nothing about things in the recent file
	// list).  If we don't, then use the preferred one, by default the generic filter.
	if (nPrefFilter != FILTERID_USERCHOICE || SelectedPos == 0)
	{
		// We know nothing. We will have to go and have a look at all the possibles
		// We will find the Filter Family and ask it to try and load the file.
		UINT32 nID = (nPrefFilter != FILTERID_USERCHOICE) ? nPrefFilter : FILTERID_GENERIC;
		while (pFilter != NULL && pFilter->FilterID != nID)
		{
			// Try the next filter
			pFilter = Filter::GetNext(pFilter);
		}
	}
	else
	{
		// We know which type of filter the user had selected in the file dialog
		// Find the filter that the user chose.
		while (pFilter != NULL)
		{
			// This is the filter?
			if (pFilter->GetFlags().CanImport &&
				pFilter->pOILFilter->Position == SelectedPos)
					break;

			// Try the next filter
			pFilter = Filter::GetNext(pFilter);
		}
	}
	
	// Check that the Filter existed
	if (pFilter == NULL)
	{
		// It did not...
		InformError(_R(IDT_CANT_FIND_FILTER));
		return FALSE;
	}

	// Get pointer to current doc 'cos we'll need it several times...
	Document* pCurDoc = Document::GetCurrent();

	// If this is not a filter family, check for compatibility before asking
	// filter to load the file.
	// This means the user has chosen an explicit filter to handle the import
	PathName Path = pFileToLoad->GetPathName();
	String_256 FilePath = Path.GetPath();
	// FilePath will be null if a pathname is not valid
	if (!pFilter->IS_KIND_OF(FilterFamily) && !FilePath.IsEmpty())
	{
		UINT32		Size = 1024;
		size_t		FileSize;
		ADDR		FilterBuf = pFilter->LoadInitialSegment(Path, &Size, &FileSize);

		// If there has been a problem in the load initial segment then fail now.
		if (FilterBuf == NULL)
		{
			// Tell the user about the problem and get out now while the goings good 
			InformError();
			return FALSE;
		}

		// Inform any filters that we are about to do a HowCompatible call.
		// This would allow a set of filters which have common functionality hidden in a
		// filter that cannot import and cannot export handle this call and hence set
		// itself up. This would allow it to maybe cache a result which should only be
		// checked by the first filter in the group. 
		pFilter->PreHowCompatible();
		
		// Change this to be less than 8 as the filters like the Accusoft forms return
		// 8 and 9 to make sure that they are last in the chain.
		if (pFilter->HowCompatible(Path, FilterBuf, Size, UINT32(FileSize)) < 8)
		{
			// Not 100% happy with this file - ask for confirmation.
			ErrorInfo Question;
			Question.ErrorMsg = _R(IDW_OPENQUERY_NOTSURE);
			Question.Button[0] = _R(IDB_OPENQUERY_OPEN);
			Question.Button[1] = _R(IDB_OPENQUERY_DONTOPEN);

			if ((ResourceID)AskQuestion(&Question) != _R(IDB_OPENQUERY_OPEN))
			{
				// User asked for this to be cancelled.
				TRACEUSER( "Tim", _T("Filter compatibility was less than 10\n"));

				// Close the file, report the abort and finish.
				CCFree(FilterBuf);
				//InformMessage(_R(IDT_IMP_USERABORT));
				return FALSE;
			}
		}

		// Get rid of initial file header
		CCFree(FilterBuf);
	}

	// we have to try and open the file
	try
	{
		// Found the Filter, so ask it to import the file please
		if (!pFilter->DoImport(this, pFileToLoad, pCurDoc))
		{
			// Something went a bit wrong - tell the user what it was.
			// Only tell them if not special user cancelled error message
			if (Error::GetErrorNumber() != _R(IDN_USER_CANCELLED))
			{
				// Only supress the error if not the special user abort error
				// ***** For now use the native EPS filter
				if (pFilter->FilterID == FILTERID_NATIVE_EPS &&
					Error::GetErrorNumber() != _R(IDT_IMPORT_USERABORT))
				{
					Error::ClearError();
					InformError(_R(IDS_ERRORINARTFILE));
				}
				else
				{
					// Tell the user what the problem was
					InformError();
					wxMessageDialog dlg(
						NULL,
						_T( "Xara LX failed to load the design.\n\n")
						_T( "This is an early demonstration version of the program which does ")
						_T( "not yet support all of the data types that can appear in XAR designs."),
						_T("Load failed"),
						wxOK
					);
					dlg.ShowModal() ;
				}
			}
			else
			{
				// otherwise remove the error so it won't get reported
				Error::ClearError();
			}

			// and fail
			return FALSE;
		}

	}
	// See if there was a file io errir
	catch( CFileException )
	{
		// Report the error if no one else did, otherwise clear it.
		if (Error::GetErrorNumber() != _R(IDN_USER_CANCELLED))
			InformError();
		else
			Error::ClearError();

		// and fail
		return FALSE;
	}

	// Success.
	return TRUE;
}