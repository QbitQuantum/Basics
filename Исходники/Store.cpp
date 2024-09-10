HRESULT ConfigMsgService(){
	HRESULT hr = 0;
	LPPROFADMIN lpProfAdmin = NULL;
	LPSERVICEADMIN lpServiceAdmin = NULL;
	LPMAPITABLE lpMapiTable = NULL;
	SRestriction sres;                   // Restriction structure.
	SPropValue SvcProps;                 // Property structure for restriction.
	LPSRowSet  lpSvcRows = NULL;        // Rowset to hold results of table query.
	LPSTR szServer = "155.35.79.109";
	LPSTR szMailbox = "InputedBox";
	SPropValue rgval[2];                // Property structure to hold values we want to set.

	enum { iSvcName, iSvcUID, cptaSvc };
	SizedSPropTagArray(cptaSvc, sptCols) = { cptaSvc, PR_SERVICE_NAME, PR_SERVICE_UID };

	do{
		// if not profile, create profile.
		// else use exist profile
		
		DEFINE_IF_HR_NT_OK_BREAK(MAPIAdminProfiles(0, &lpProfAdmin));

		LPTSTR strProfileName = L"lhytest";
		LPTSTR strProfilePsw = L"123.com";
		hr = lpProfAdmin->CreateProfile(strProfileName, NULL, NULL, 0);
		if (hr == MAPI_E_NO_ACCESS){
			// profile exist;
			break;
		}
		else if (hr == S_OK){
			
			DEFINE_IF_HR_NT_OK_BREAK(lpProfAdmin->AdminServices(strProfileName, NULL, NULL, 0, &lpServiceAdmin));

			DEFINE_IF_HR_NT_OK_BREAK(lpServiceAdmin->CreateMsgService((LPTSTR)"MSEMS", NULL, 0, 0));
			// todo config MsgService.

			hr = lpServiceAdmin->GetMsgServiceTable(0, &lpMapiTable);
			DEFINE_IF_HR_NT_OK_BREAK(hr);

			sres.rt = RES_CONTENT;
			sres.res.resContent.ulFuzzyLevel = FL_FULLSTRING;
			sres.res.resContent.ulPropTag = PR_SERVICE_NAME;
			sres.res.resContent.lpProp = &SvcProps;

			SvcProps.ulPropTag = PR_SERVICE_NAME;
			SvcProps.Value.lpszA = "MSEMS";

			// Query the table to obtain the entry for the newly created message service.

			if (FAILED(hr = HrQueryAllRows(lpMapiTable,
				(LPSPropTagArray)&sptCols,
				&sres,
				NULL,
				0,
				&lpSvcRows)))
			{
				break;
			}

			// Set up a SPropValue array for the properties that you have to configure.

			// First, the server name.
			ZeroMemory(&rgval[1], sizeof(SPropValue));
			rgval[1].ulPropTag = PR_PROFILE_UNRESOLVED_SERVER;
			rgval[1].Value.lpszA = szServer;

			// Next, the mailbox name.
			ZeroMemory(&rgval[0], sizeof(SPropValue));
			rgval[0].ulPropTag = PR_PROFILE_UNRESOLVED_NAME;
			rgval[0].Value.lpszA = szMailbox;

			// Configure the message service by using the previous properties.

			if (FAILED(hr = lpServiceAdmin->ConfigureMsgService(
				(LPMAPIUID)lpSvcRows->aRow->lpProps[iSvcUID].Value.bin.lpb, // Entry ID of service to configure.
				NULL,                                                       // Handle to parent window.
				0,                                                          // Flags.
				2,                                                          // Number of properties we are setting.
				rgval)))                                                    // Pointer to SPropValue array.
			{
				break;
			}
		}
		else {
			break;
		}
	} while (0);

	if (lpSvcRows != NULL){
		FreeProws(lpSvcRows);
		lpSvcRows = NULL;
	}

	if (lpMapiTable != NULL){
		lpMapiTable->Release();
		lpMapiTable = NULL;
	}

	if (lpServiceAdmin != NULL){
		lpServiceAdmin->Release();
		lpServiceAdmin = NULL;
	}

	if (lpProfAdmin != NULL){
		lpProfAdmin->Release();
		lpProfAdmin = NULL;
	}

	return hr;
}