// **************************************************************************
// DisplayComponentCatList ()
//
// Description:
//	Construct a list of installed 1.0 and 2.0 OPC servers and insert into 
//	tree control.
//
// Parameters:
//  HTREEITEM	hParent		Handle of parent tree control item.
//	CATID		catid		Catagory ID (CATID_OPCDAServer10 or
//							  CATID_OPCDAServer20).
//
// Returns:
//  void
// **************************************************************************
void CKServerGeneralPage::DisplayComponentCatList (HTREEITEM hParent, CATID catid)
{
	HRESULT hr;

	// Make sure COM is initialized:
	hr = CoInitializeEx (NULL, COINIT_MULTITHREADED);

	if (SUCCEEDED (hr))
	{
		ICatInformation *pCat = NULL;

		// Get component category manager:
		hr = CoCreateInstance (CLSID_StdComponentCategoriesMgr, 
			NULL,
			CLSCTX_SERVER, 
			IID_ICatInformation,
			(void **)&pCat);

		// If succeeded, enumerate registered components:
		if (SUCCEEDED (hr))
		{
			IEnumCLSID *pEnum = NULL;

			CATID arrcatid [1];
			arrcatid [0] = catid;

			// Enumerate registered components based on clsid:
			hr = pCat->EnumClassesOfCategories (
				sizeof (arrcatid) / sizeof (CATID),	// number of catids in the array that follows
				arrcatid,							// catid array
				0, 
				NULL,
				&pEnum);							// clsid enumerator for registered components under this category

			// If succeeded, process results:
			if (SUCCEEDED (hr))
			{
				GUID guid;
				ULONG fetched;

				// Loop over enumerated components.  Call enemerator's next
				// member function to reference next component and get its
				// guid:
				while ((hr = pEnum->Next (1, &guid, &fetched)) == S_OK)
				{
					// Get the ProgID from the guid:
					WCHAR *wszProgID;
					hr = ProgIDFromCLSID (guid, &wszProgID);

					// If succeeded, add component to list:
					if (SUCCEEDED (hr))
					{
						// ProgID string will be in UNICODE format.  Convert to 
						// ANSI format if this is and ANSI build.  Insert component
						// into list:
					#ifdef _UNICODE
						m_pServerList->InsertItem (wszProgID, ILI_COMPONENT, ILI_COMPONENT, hParent);
					#else
						TCHAR szProgID [DEFBUFFSIZE];

						_wcstombsz (szProgID, wszProgID, sizeof (szProgID) / sizeof (TCHAR));
						m_pServerList->InsertItem (szProgID, ILI_COMPONENT, ILI_COMPONENT, hParent);
					#endif
						// It is up to us to free the Prog ID string memory:
						CoTaskMemFree (wszProgID);
					}
				}

				// Release our enumerator:
				pEnum->Release ();
			}
			// release our category mamager
			pCat->Release ();
		}
		// Uninitialize COM:
		CoUninitialize ();
	}
}