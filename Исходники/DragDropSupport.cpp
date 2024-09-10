int DropHelper::DragDropThread() {
	int result = 0;

	HRESULT res = OleInitialize(NULL);
	if (res != S_OK && res != S_FALSE) {
		OutErr("[DnD] Error initializing OLE (Thread): %d\n", res);
		return -1;
	}

	CDropSource * src = new CDropSource();
	if (!src) {
		return -1;
	}
	CDataObject * dat = new CDataObject(m_dataWindow);
	if (!dat) {
		src->Release();
		return -1;
	}

	DWORD resEffect = 0;
	OutMsg("[DnD] Begin DoDragDrop");
	res = DoDragDrop(dat, src, DROPEFFECT_COPY, &resEffect);
	OutMsg("[DnD] End DoDragDrop");

	src->Release();
	dat->Release();
	if (res == S_OK || res == DRAGDROP_S_DROP)
		result = TRUE;
	else
		result = FALSE;

	m_dataWindow->OnEndDnD();

	::OleUninitialize();
	m_hThread = NULL;

	return result;
}