HRESULT ipcGetFiles(THeaderIPC *pipch, IDataObject* pDataObject, MCONTACT hContact)
{
	FORMATETC fet;
	fet.cfFormat = CF_HDROP;
	fet.ptd = NULL;
	fet.dwAspect = DVASPECT_CONTENT;
	fet.lindex = -1;
	fet.tymed = TYMED_HGLOBAL;

	STGMEDIUM stgm;
	HRESULT hr = pDataObject->GetData(&fet, &stgm);
	if (hr == S_OK) {
		// FIX, actually lock the global object and get a pointer
		HANDLE hDrop = GlobalLock(stgm.hGlobal);
		if (hDrop != 0) {
			// get the maximum number of files
			UINT iFile, iFileMax = DragQueryFileA((HDROP)stgm.hGlobal, -1, NULL, 0);
			for (iFile = 0; iFile < iFileMax; iFile++) {
				// get the size of the file path
				int cbSize = DragQueryFileA((HDROP)stgm.hGlobal, iFile, NULL, 0);
				// get the buffer
				TSlotIPC *pct = ipcAlloc(pipch, cbSize + 1); // including null term
				// allocated?
				if (pct == NULL)
					break;
				// store the hContact
				pct->hContact = hContact;
				// copy it to the buffer
				DragQueryFileA((HDROP)stgm.hGlobal, iFile, LPSTR(pct) + sizeof(TSlotIPC), pct->cbStrSection);
			}
			// store the number of files
			pipch->Slots = iFile;
			GlobalUnlock(stgm.hGlobal);
		} // if hDrop check
		// release the mediumn the lock may of failed
		ReleaseStgMedium(&stgm);
	}
	return hr;
}