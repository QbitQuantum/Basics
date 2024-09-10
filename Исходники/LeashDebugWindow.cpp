void CLeashDebugWindow::OnCopyToClipboard()
{
    if (!OpenClipboard())
	{
        MessageBox("Unable to open Clipboard!", "Error", MB_OK);
		return;
	}

	EmptyClipboard();

    int maxItems = m_debugListBox.GetCount();
	const int MAX_MEM = maxItems * 90; // 90 chars per line seems safe like a safe bet

	HGLOBAL hDebugText = GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, MAX_MEM);
    if (NULL != hDebugText)
    {
		CString listboxItem;
		LPSTR pDebugText = (LPSTR) GlobalLock(hDebugText);
		if (!pDebugText)
		{
		    MessageBox("Unable to write to Clipboard!", "Error", MB_OK);
			ASSERT(pDebugText);
			return;
		}

		*pDebugText = 0;
		for (int xItem = 0; xItem < maxItems; xItem++)
		{
			m_debugListBox.GetText(xItem, listboxItem);
			strcat(pDebugText, listboxItem);
			strcat(pDebugText, "\r\n");
		}

		GlobalUnlock(hDebugText);
    }

    if (NULL != hDebugText)
        SetClipboardData(CF_TEXT, hDebugText);

	CloseClipboard();
	MessageBox("Copy to Clipboard was Successful!\r\n Paste it in your favorite editor.",
                "Note", MB_OK);
}