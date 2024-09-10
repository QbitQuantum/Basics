//----------------------------------------------------------------------------------
// UpdatePatchList: Update the list of patches (and results).
//----------------------------------------------------------------------------------
void SelectHostCtrl::UpdatePatchList(void)
{
	CustomInfo* pCustInfo = GetCustomInfo();
	ResourceManager* pResMgr = pCustInfo->GetResourceManager();

	GUIString sError;
	int nManualPatches = 0;
	int nAutoPatches = 0;

	// Clear the list box of old refuse.
	m_pHostList->Clear();

	m_pHostList->BeginMultiChange();

	GUIString sDefault = pCustInfo->LoadDefaultSelection();
	sDefault.toLowerCase();
	CPatchDataList* pPatches = pCustInfo->GetPatchList();

	// Go through the list and decide if we have to mark manual downloads.
	CPatchDataList::iterator Itr = pPatches->begin();

	while (Itr != pPatches->end())
	{
		CPatchData* pData = *Itr;

		if (pData)
		{
			if (pData->GetMustVisitHost())
				nManualPatches++;
			else
				nAutoPatches++;
		}

		++Itr;
	}

	m_bMixedPatches = nManualPatches != 0 && nAutoPatches != 0;

	// Now go through the list and add all of the items to the list box.
	Itr = pPatches->begin();
	int nIndex = 0;
	int nSelectIndex = -1;

	while (Itr != pPatches->end())
	{
		CPatchData* pData = *Itr;
		//pData->MessageBox(GetWindow()); // Debugging Aide.

		if (pData)
		{
			// Start with the Patch Name (we will display this).
			std::string sLine = pData->GetPatchName();

			// Add the Manual flag (if needed).
			if (pData->GetMustVisitHost() && m_bMixedPatches)
				sLine += " *";

			// Now add the results of previous download atempts.
			int nFailures = pData->GetDownloadFailures();
			int nAborts = pData->GetDownloadAborts();

			if (nFailures)
			{
				sError = pResMgr->GetFinishedString(Global_DownloadFailures_String);
				ReplaceSubInt(sError, "%NUM_FAILURES%", nFailures);
			}
			else if (nAborts)
			{
				sError = pResMgr->GetFinishedString(Global_DownloadAborts_String);
				ReplaceSubInt(sError, "%NUM_ABORTS%", nAborts);
			}
			else
				sError = "";

			PatchDataItem* pItem = static_cast<PatchDataItem*>(m_pHostList->InsertItem(new PatchDataItem));
			m_pHostList->SetString(nIndex, 0, sLine);
			m_pHostList->SetString(nIndex, 1, sError);
			pItem->m_pPatchData = pData;

			// Check to see if this was the last 'successful download site', if so, select it.
			GUIString sHost = pData->GetHostName();
			sHost.toLowerCase();
			if (sDefault == sHost)
				nSelectIndex = nIndex;

			++nIndex;
		}

		++Itr;
	}

	// If no site was selected, choose one at random.
	if (nSelectIndex == -1 && nIndex > 0)
	{
		srand(GetTickCount());
		nSelectIndex = rand() % nIndex;
	}

	// Actually make the selection.
	if (nSelectIndex != -1)
		m_pHostList->SetSelItem(nSelectIndex);

	m_pHostList->EndMultiChange();

	// Changing the patch list can change the Info Text, so update it.
	UpdateInfoText();
	EnableControls();
}