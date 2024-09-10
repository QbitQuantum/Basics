HWND CConEmuInside::CheckInsideFocus()
{
	if (!isInsideWndSet())
	{
		//_ASSERTE(FALSE && "Inside was not initialized");
		return NULL;
	}

	wchar_t szInfo[512];
	GUITHREADINFO tif = { sizeof(tif) };
	HWND hParentWnd = GetParentRoot();
	DWORD nTID = GetWindowThreadProcessId(hParentWnd, NULL);

	if (!GetGUIThreadInfo(nTID, &tif))
	{
		_wsprintf(szInfo, SKIPCOUNT(szInfo) L"GetGUIThreadInfo(%u) failed, code=%u", nTID, GetLastError());
		LogString(szInfo);
		return NULL;
	}

	static GUITHREADINFO last_tif = {};
	if (memcmp(&last_tif, &tif, sizeof(tif)) != 0)
	{
		last_tif = tif;

		_wsprintf(szInfo, SKIPCOUNT(szInfo)
			L"ParentInputInfo: flags=x%X Active=x%X Focus=x%X Capture=x%X Menu=x%X MoveSize=x%X Caret=x%X (%i,%i)-(%i,%i)",
			tif.flags, LODWORD(tif.hwndActive), LODWORD(tif.hwndFocus), LODWORD(tif.hwndCapture), LODWORD(tif.hwndMenuOwner),
			LODWORD(tif.hwndMoveSize), LODWORD(tif.hwndCaret), LOGRECTCOORDS(tif.rcCaret));
		LogString(szInfo);
	}

	return tif.hwndFocus;
}