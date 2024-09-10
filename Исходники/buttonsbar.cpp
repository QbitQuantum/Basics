static INT_PTR CB_RemoveButton(WPARAM, LPARAM lParam)
{
	BBButton *bbdi = (BBButton *)lParam;
	if (!bbdi)
		return 1;

	DWORD tempCID = 0;
	DWORD dwFlags = 0;
	{
		mir_cslock lck(ToolBarCS);

		for (int i = LButtonsList.getCount()-1; i >= 0; i--) {
			CustomButtonData *cbd = LButtonsList[i];
			if (!strcmp(cbd->pszModuleName, bbdi->pszModuleName) && cbd->dwButtonOrigID == bbdi->dwButtonID) {
				tempCID = cbd->dwButtonCID;
				dwFlags = cbd->bLSided ? BBBF_ISLSIDEBUTTON : BBBF_ISRSIDEBUTTON;
				LButtonsList.remove(i);
			}
		}

		if (!tempCID) {
			for (int i = RButtonsList.getCount()-1; i >= 0; i--) {
				CustomButtonData *cbd = RButtonsList[i];
				if (!strcmp(cbd->pszModuleName, bbdi->pszModuleName) && cbd->dwButtonOrigID == bbdi->dwButtonID) {
					tempCID = cbd->dwButtonCID;
					dwFlags = cbd->bLSided ? BBBF_ISLSIDEBUTTON : BBBF_ISRSIDEBUTTON;
					RButtonsList.remove(i);
				}
			}
		}
	}

	if (tempCID)
		M.BroadcastMessage(DM_CBDESTROY, (WPARAM)tempCID, (LPARAM)dwFlags);
	return 0;
}