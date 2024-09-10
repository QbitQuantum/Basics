//
// Displays exemptions associated with a given type
//
VOID ExemptionsDialog::DisplayExemptions(
		IN EXEMPTION_TYPE Type)
{
	LRESULT ListIndex;
	LPTSTR  NtFilePath = NULL;
	DWORD   NtFilePathSize = 0;
	DWORD   Index = 0;
	HKEY    ScopeKey = NULL;
	HWND    ExemptionList;
	
	ExemptionList = GetControl(
			EXEMPTIONS_LIST_APPLIED);

	//
	// Flush out all of the currently applied exemptions
	//
	FlushExemptionList();

	//
	// Set the current exemption type to the one supplied
	//
	CurrentExemptionType = Type;

	do
	{
		//
		// Open the arbitrary exemption key
		//
		if (!(ScopeKey = Config::OpenExemptionScopeKey(
				GlobalScope)))
		{
			break;
		}

		//
		// Enumerate all of the exemptions in the key
		//
		while (1)
		{
			LPTSTR FileName;
			DWORD  Result;

			//
			// Allocate storage for the file path
			//
			NtFilePathSize = 1024 * sizeof(TCHAR);

			if (!(NtFilePath = (LPTSTR)malloc(
					NtFilePathSize)))
			{
				break;
			}

			//
			// If the enumeration fails, inspect the reason for the failure
			//
			if ((Result = Config::EnumerateExemptionScopeKey(
					ScopeKey,
					Type,
					&Index,
					NtFilePath,
					&NtFilePathSize,
					NULL)) != ERROR_SUCCESS)
			{
				// 
				// If the reason was because the buffer was too small...grow it
				//
				if (Result == ERROR_MORE_DATA)
				{
					free(
							NtFilePath);

					if (!(NtFilePath = (LPTSTR)malloc(
							NtFilePathSize)))
					{
						break;
					}

					// 
					// Loop around again with the same index in order to obtain the
					// NT path at this index now that the buffer is large enough
					//
					continue;
				}
				else
				{
					free(
							NtFilePath);
					break;
				}
			}

			//
			// Extract the file name from the path name
			//
			FileName = StrRChr(
					NtFilePath,
					NULL,
					'\\');

			if ((FileName) &&
			    (FileName[1] != 0))
				FileName++;
			else
				FileName = NtFilePath;

			//
			// Add this path name to the list control
			//
			ListIndex = SendMessage(
					ExemptionList,
					LB_ADDSTRING,
					0,
					(LPARAM)(LPTSTR)FileName);

			if (ListIndex >= 0)
			{
				SendMessage(
						ExemptionList,
						LB_SETITEMDATA,
						ListIndex,
						(LPARAM)(LPTSTR)NtFilePath);
			}

			//
			// Go to the next index
			//
			Index++;
		}

	} while (0);

	//
	// Close the exemption key
	//
	if (ScopeKey)
		Config::CloseExemptionScopeKey(
				ScopeKey);
}