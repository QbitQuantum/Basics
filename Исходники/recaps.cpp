///////////////////////////////////////////////////////////////////////////////
// Finds out which window has the focus
HWND RemoteGetFocus()
{
	GUITHREADINFO remoteThreadInfo;
	remoteThreadInfo.cbSize = sizeof(GUITHREADINFO);
	if(!GetGUIThreadInfo(0, &remoteThreadInfo))
	{
		return NULL;
	}

	return remoteThreadInfo.hwndFocus ? remoteThreadInfo.hwndFocus : remoteThreadInfo.hwndActive;
}